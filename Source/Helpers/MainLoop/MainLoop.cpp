#include "MainLoop.h"
#include <mmsystem.h> //timeBeginPeriod & timeEndPeriod

//default 60 fps, 17 ms for frame
MainLoop::MainLoop() : RenderFunction{ nullptr }, LogicFunction{ nullptr }, StartTime{ 0 },
DeltaTime{ 0 }, CumulativeTime{ 0 }, FPSCounterTimer{ 0 }, TimePerFrame{ 17 }, FPS{ 60 }, Frames{ 0 }, Dt{ 0 }, RealFPS{ 0.f }, bBreak{ false }, Msg{}
{
}

MainLoop::MainLoop(UINT FPS, bool(*_RenderFunction)(DWORD dt), bool(*_LogicFunction)(DWORD dt)) : RenderFunction{ _RenderFunction }, LogicFunction{ _LogicFunction }, StartTime{ 0 },
DeltaTime{ 0 }, CumulativeTime{ 0 }, FPSCounterTimer{ 0 }, Frames{ 0 }, Dt{ 0 }, RealFPS{ 0.f }, bBreak{ false }, Msg{}
{
	this->SetFPS(FPS);
}

MainLoop::~MainLoop()
{
}

void MainLoop::SetFPS(UINT FPS)
{
	if (FPS == 0) 
	{
		this->FPS = 1;
		this->TimePerFrame = 1000;
	}
	else if (FPS > 1000) 
	{
		this->FPS = 1000;
		this->TimePerFrame = 1;
	}
	else
	{
		this->FPS = FPS;
		this->TimePerFrame = static_cast<UINT>(1000.f / static_cast<float>(FPS));
	}
}

void MainLoop::Run()
{
	assert(this->RenderFunction);
	assert(this->LogicFunction);

	timeBeginPeriod(1);
	this->CumulativeTime = timeGetTime();
	this->FPSCounterTimer = 0;
	this->Frames = 0;
	this->bBreak = false;
	srand((UINT)time(NULL));
	LOG("Starting main loop");

	while (true) 
	{
		this->StartTime = timeGetTime();

		while (PeekMessage(&this->Msg, NULL, 0, 0, PM_REMOVE)) 
		{
			if (this->Msg.message == WM_QUIT) 
			{
				this->bBreak = true;
			}
			TranslateMessage(&this->Msg);
			DispatchMessage(&this->Msg);
		}
		if (this->bBreak) 
		{
			break;
		}

		this->Dt = this->StartTime - this->CumulativeTime;
		if (this->Dt < this->TimePerFrame) 
		{
			Sleep(this->TimePerFrame - this->Dt);
			this->DeltaTime = this->TimePerFrame;
			this->FPSCounterTimer += (this->TimePerFrame);
		}
		else 
		{
			if (this->Dt > 1000) 
			{
				this->Dt = 1000;
			}
			this->DeltaTime = Dt;
			this->FPSCounterTimer += this->Dt;
		}
		this->CumulativeTime = timeGetTime();
		this->Frames += 1;
		if (this->FPSCounterTimer >= 1000) 
		{
			this->RealFPS = static_cast<float>(this->Frames * 1000) / static_cast<float>(this->FPSCounterTimer);
			this->FPSCounterTimer = 0;
			this->Frames = 0;
		}
		if (!LogicFunction(this->DeltaTime)) 
		{
			break;
		}
		if (!RenderFunction(this->DeltaTime)) 
		{
			break;
		}
	}
	timeEndPeriod(1);
	LOG("Finishing main loop");
}