#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cassert>
#include <ctime>
#include <iomanip>

#ifdef NDEBUG
#define LOG(x) ;
#else
#define LOG(x) Logger::Log((x))
#endif

class Logger {
public:
	static void Log(const char * message);
	static void Init(std::ostream * LogDestination, bool bOwnsStream);
	static void Init(std::ostream & LogDestination);

	Logger();
	Logger(const Logger & Right) = delete;
	Logger(Logger && Right) = delete;
	Logger & operator=(const Logger & Right) = delete;
	Logger & operator=(Logger && Right) = delete;
	~Logger();
private:
	bool bOwnsStream;
	std::ostream * LogDestination;
};

#endif