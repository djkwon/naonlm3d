///////////////////////////////////////////////////////////////////////////////////////
// stdafx.h
// Developed by Dongjin Kwon
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2015 Dongjin Kwon
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////////

#pragma once

#if defined(WIN32) || defined(WIN64)
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////
#else
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
//
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <float.h>
#include <fcntl.h>
#if !defined(__APPLE__)
#include <sys/sendfile.h>
#endif
#include <dirent.h>
#include <fnmatch.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

#define USE_TRACE

#ifndef BOOL
#define BOOL int
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef BYTE
#define BYTE unsigned char
#endif
#ifndef DWORD
#define DWORD unsigned long
#endif
#ifndef LPCTSTR
#define LPCTSTR const char*
#endif

#define MIN(a,b)  (((a) < (b)) ? (a) : (b))
#define MAX(a,b)  (((a) > (b)) ? (a) : (b))

#ifdef USE_TRACE
//
//#ifdef _DEBUG
#if defined(WIN32) || defined(WIN64)
#undef TRACE
#define TRACE Trace
#define TRACE1(...) {(g_verbose>=1)?Trace(__VA_ARGS__):((void)0);}
#define TRACE2(...) {(g_verbose>=2)?Trace(__VA_ARGS__):((void)0);}
#define TRACE3(...) {(g_verbose>=3)?Trace(__VA_ARGS__):((void)0);}
#ifdef __cplusplus
extern "C" {
#endif
extern BOOL g_bTrace;
extern FILE *g_fp_trace;
extern char g_trace_file[1024];
extern BOOL g_bTraceStdOut;
extern int g_verbose;
void Trace(const char* szFormat, ...);
#ifdef __cplusplus
}
#endif
#else
#ifndef TRACE
#define TRACE printf
#define TRACE1(...) {(g_verbose>=1)?printf(__VA_ARGS__):((void)0);}
#define TRACE2(...) {(g_verbose>=2)?printf(__VA_ARGS__):((void)0);}
#define TRACE3(...) {(g_verbose>=3)?printf(__VA_ARGS__):((void)0);}
#endif
#endif
//
#endif
