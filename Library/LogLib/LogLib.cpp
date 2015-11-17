// LogLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <ctime>
#include <stdarg.h>

#include "LogLib.h"
//#define BUFSIZ 250
////////////////////////////////////////////////////////////////////////////////
struct MyDay
{
	tm _tm;

	MyDay()
	{
		time_t now = time(0);
		localtime_s(&_tm, &now);
	}

	bool operator!=(const MyDay &_MyDay)
	{
		if ( (this->_tm.tm_yday != _MyDay._tm.tm_year )
			|| ( this->_tm.tm_mon != _MyDay._tm.tm_mon )
			|| (this->_tm.tm_mday != _MyDay._tm.tm_mday) )
		{
			return true;
		}
		return false;
	}

	void toString(char* strDay)
	{
		sprintf_s(strDay, 9, "%2d%2d%4d", this->_tm.tm_mon + 1, this->_tm.tm_mday, this->_tm.tm_year + 1900);
	}

	void toLongString(char* strDay)
	{
		sprintf_s(strDay, 16, "%2d%2d%4d:%2d%2d%2d", this->_tm.tm_mon + 1, this->_tm.tm_mday, this->_tm.tm_year + 1900, this->_tm.tm_hour, this->_tm.tm_min, this->_tm.tm_sec);
	}

	static void CurrDateToString(char* strDay)
	{
		MyDay md;
		md.toLongString(strDay);
	}
};

////////////////////////////////////////////////////////////////////////////////
// Implementation of the ILOG interface.
class CLogFile : public ILog
{
	// implement interface
public:
	int Foo(int n);
	void Release();
	void getLogFile(char* logFile);
	void Log(char* format, ...);
private:
	MyDay *date;
	FILE *pFile;
	char m_szFileLog[250];
	void getLogFile();
private:
	static CLogFile* instance;
	CLogFile();
public:
	static CLogFile* getInstance();
}; 
CLogFile* CLogFile::instance = NULL;


////////////////////////////////////////////////////////////////////////////////////
// Impement interface
void CLogFile::getLogFile(char* logFile)
{
	strcpy_s(logFile, strlen("logfile"), "logfile");
	//wvsprintf()
}

int CLogFile::Foo(int n)
{
	return n * n;
}

void CLogFile::Release()
{
	delete this;
}

void CLogFile::Log(char* format, ...)
{
	va_list ap;
	char buffer[BUFSIZ];
	char szLogString[BUFSIZ] = { 0 } ;
	va_start(ap, format);
	vsnprintf(buffer, sizeof buffer, format, ap);
	va_end(ap);
	
	char szDay[9] = { 0 } ;
	date->toString(szDay);
	char szFileName[BUFSIZ] = {0};
	strcpy_s(szFileName, BUFSIZ, "LogFile_");
	strcat_s(szFileName, BUFSIZ, szDay);
	strcat_s(szFileName, BUFSIZ, ".txt");
	fopen_s(&pFile, szFileName, "a+");
	if ( pFile )
	{
		MyDay::CurrDateToString(szLogString);
		strcat_s(szLogString, BUFSIZ, " : ");
		strcat_s(szLogString, BUFSIZ, buffer);
		strcat_s(szLogString, BUFSIZ, "\n");
		fprintf_s(pFile, szLogString);
		fclose(pFile);
		pFile = NULL ;
	}
	return;
}

// Get log file
void CLogFile::getLogFile()
{

}

// constructer
CLogFile::CLogFile()
{
	date = new MyDay();
	pFile = NULL;
}

CLogFile* CLogFile::getInstance(void)
{
	if (!instance)
	{
		instance = new CLogFile();
	}

	return instance;
}

////////////////////////////////////////////////////////////////////////////////
// Factory function that creates instances if the LOG object.

// Export both decorated and undecorated names.
//   GetLOG     - Undecorated name, which can be easily used with GetProcAddress
//                Win32 API function.
//   _GetLOG@0  - Common name decoration for __stdcall functions in C language.
//
// For more information on name decoration see here:
// "Format of a C Decorated Name"
// http://msdn.microsoft.com/en-us/library/x7kb4e2f.aspx

#if !defined(_WIN64)
// This pragma is required only for 32-bit builds. In a 64-bit environment,
// C functions are not decorated.
#pragma comment(linker, "/export:GetLOG=_GetLOG@0")
#endif  // _WIN64

LOGAPI LOGHANDLE APIENTRY GetLOG()
{
	return CLogFile::getInstance();
}

////////////////////////////////////////////////////////////////////////////////
// Regular C++ class implementatin.
// The class is exported.

//int CLOG::Foo(int n)
//{
//	return n * n;
//}

////////////////////////////////////////////////////////////////////////////////
// C interface implementation.
// Internally these functions are written in the C++ language and
// use CLogFile instances.

LOGAPI INT APIENTRY LogFoo(LOGHANDLE handle, INT n)
{
	INT nResult = -1;

	if (handle)
	{
		nResult = handle->Foo(n);
	}

	return nResult;
}

LOGAPI VOID APIENTRY LogRelease(LOGHANDLE handle)
{
	if (handle)
	{
		handle->Release();
	}
}

////////////////////////////////////////////////////////////////////////////////
