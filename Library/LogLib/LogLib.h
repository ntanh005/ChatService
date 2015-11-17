#pragma once
#include "stdafx.h"
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LOGLIB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LOGAPI functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LOGLIB_EXPORTS
#define LOGAPI __declspec(dllexport)
#else
#define LOGAPI __declspec(dllimport)
#endif

////////////////////////////////////////////////////////////////////////////////
// 

#ifdef __cplusplus

// COM-Like abstract interface.
// This interface doesn't require __declspec(dllexport/dllimport) specifier.
// Method calls are dispatched via virtual table.
// Any C++ compiler can use it.
// Instances are obtained via factory function.
struct ILog
{
	virtual void getLogFile(char* logFile) = 0;
	virtual void Log(char* format, ...) = 0;
	virtual int Foo(int n) = 0;
	virtual void Release() = 0;
};

// Regular C++ class.
// The __declspec specifier is required, otherwise clients won't be able to
// call methods of the class.
// Both DLL and EXE must use the same version of a C++ compiler.
// No need to use factory to make an instance of this class.
class LOGAPI CXyz
{
public:
	int Foo(int n);
};

// Handle type. In C++ language the iterface type is used.
typedef ILog* LOGHANDLE;

#else   // C

// Handle type. In C language there are no classes, so empty struct is used
// in order to ensure type safety.
typedef struct tagLOGHANDLE {} *LOGHANDLE;

#endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////
// 
#ifdef __cplusplus
	#define EXTERN_C     extern "C"
#else
	#define EXTERN_C
#endif // __cplusplus

// Factory function that creates instances of the Xyz object.
EXTERN_C
LOGAPI
LOGHANDLE
WINAPI
GetLOG(
	VOID);

////////////////////////////////////////////////////////////////////////////////
// Classic C interface.
// These functions can be used with any compiler that knows how to call
// an exported C routine.

EXTERN_C
LOGAPI
INT
APIENTRY
LogFoo(
	LOGHANDLE handle,
	INT n);

EXTERN_C
LOGAPI
VOID
APIENTRY
LogRelease(
	LOGHANDLE handle);

////////////////////////////////////////////////////////////////////////////////
