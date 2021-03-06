/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#include "Core/API.h"
#include "Core/Event.h"
#include "Core/String.h"

NAMESPACE_EXTERN_BEGIN

//-----------------------------------//

enum class LogLevel
{
	Info,
	Warn,
	Error,
	Debug,
	Assert
};

struct API_CORE LogEntry
{
	float time;
	String message;
	LogLevel level;
};

typedef void (*LogFunction)(LogEntry*);

struct Timer;
struct Mutex;
struct Allocator;

struct API_CORE Log
{
	Log();
	~Log();

	Timer* timer;
	Mutex* mutex;
	Event1<LogEntry*> handlers;
};

API_CORE Log* LogCreate(Allocator*);
API_CORE void LogDestroy(Log*);
API_CORE void LogAddHandler(Log*, LogFunction);
API_CORE void LogRemoveHandler(Log*, LogFunction);
API_CORE void LogWrite(Log*, LogEntry* entry);

API_CORE Log* LogGetDefault();
API_CORE void LogSetDefault(Log*);

API_CORE void LogInfo(const char* msg, ...);
API_CORE void LogWarn(const char* msg, ...);
API_CORE void LogError(const char* msg, ...);
API_CORE void LogDebug(const char* msg, ...);
API_CORE void LogAssert(const char* msg, ...);

//-----------------------------------//

NAMESPACE_EXTERN_END