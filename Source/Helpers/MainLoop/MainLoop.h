#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include <Helpers\WindowHelper\WindowHelper.h>
#include <Helpers\OrthoCamera\OrthoCamera.h>
#include <Helpers\OpenGLHelper\OpenGLHelper.h>
#include <Helpers\OpenGLRenderer\OpenGLRenderer.h>
#include <Helpers\OpenGLTextureManager\OpenGLTextureManager.h>

class MainLoop
{
public:
	inline void SetRenderFunction(bool (*RenderFunction)(DWORD dt)) { this->RenderFunction = RenderFunction; }
	inline void SetLogicFunction(bool (*LogicFunction)(DWORD dt)) { this->LogicFunction = LogicFunction; }
	void Run();
	void SetFPS(UINT FPS);
	inline float GetRealFPS() const { return this->RealFPS; }

	MainLoop();
	MainLoop(UINT FPS, bool (*RenderFunction)(DWORD dt), bool (*LogicFunction)(DWORD dt));
	MainLoop(const MainLoop & Right) = delete;
	MainLoop(MainLoop && Right) = delete;
	MainLoop & operator=(const MainLoop & Right) = delete;
	MainLoop & operator=(MainLoop && Right) = delete;
	~MainLoop();
private:
	bool (*RenderFunction)(DWORD dt);
	bool (*LogicFunction)(DWORD dt);
	DWORD StartTime;
	DWORD DeltaTime;
	DWORD CumulativeTime;
	DWORD FPSCounterTimer;
	DWORD TimePerFrame;
	DWORD FPS;
	DWORD Frames;
	DWORD Dt;
	float RealFPS;
	bool bBreak;
	MSG Msg;
};

#endif