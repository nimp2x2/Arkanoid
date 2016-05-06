#include "Logger.h"

Logger gLogger;

Logger::Logger() : bOwnsStream{ false }, LogDestination{ nullptr }
{
}

void Logger::Init(std::ostream * _LogDestination, bool _bOwnsStream)
{
	assert(_LogDestination);
	if (!gLogger.LogDestination) {
		gLogger.LogDestination = _LogDestination;
		gLogger.bOwnsStream = _bOwnsStream;
		(*gLogger.LogDestination) << std::setfill('0');
	}
}

void Logger::Init(std::ostream & _LogDestination)
{
	assert(_LogDestination.good());
	if (!gLogger.LogDestination) {
		gLogger.LogDestination = &_LogDestination;
		gLogger.bOwnsStream = false;
		(*gLogger.LogDestination) << std::setfill('0');
	}
}

Logger::~Logger()
{
	if (this->bOwnsStream) 
	{
		delete this->LogDestination;
	}
}

void Logger::Log(const char * message) 
{
	assert(message);
	if (gLogger.LogDestination && gLogger.LogDestination->good()) 
	{
		tm timeInfo;
		time_t	rawTime = time(NULL);
		localtime_s(&timeInfo, &rawTime);
		(*gLogger.LogDestination) << "[" << std::setw(2) << timeInfo.tm_hour << ":" << std::setw(2) << timeInfo.tm_min << ":" << std::setw(2) << timeInfo.tm_sec << "] " << message << std::endl;
		gLogger.LogDestination->flush();
	}
}
