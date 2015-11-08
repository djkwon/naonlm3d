///////////////////////////////////////////////////////////////////////////////////////
// stdafx.cpp
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

#include "stdafx.h"

#ifdef USE_TRACE
#if defined(WIN32) || defined(WIN64)
//#define USE_FILE
BOOL g_bTrace = FALSE;
FILE *g_fp_trace = NULL;
char g_trace_file[1024] = "";
BOOL g_bTraceStdOut = FALSE;
int g_verbose = 0;
//
void Trace(const char* szFormat, ...)
{
#ifdef USE_FILE
	if (!g_bTrace) {
		if (!g_fp_trace) {
			if (g_trace_file[0] == 0) {
				g_fp_trace = fopen("trace.txt", "a");
			} else {
				g_fp_trace = fopen(g_trace_file, "a");
			}
			if (g_fp_trace != NULL) {
				g_bTrace = TRUE;
			}
		}
	}
#endif

    char szTempBuf[2048];
    va_list vlMarker;

    va_start(vlMarker, szFormat);
    vsprintf(szTempBuf, szFormat, vlMarker);
    va_end(vlMarker);

#ifndef USE_FILE
	/*
    OutputDebugString(szTempBuf);
	/*/
	{
	    char szTempBuf2[2048];
		sprintf(szTempBuf2, "%s", szTempBuf);
		OutputDebugString(szTempBuf2);
	}
	//*/
#else
	if (g_fp_trace != NULL) {
		fprintf(g_fp_trace, szTempBuf);
		fflush(g_fp_trace);
	}
#endif

	if (g_bTraceStdOut) {
		printf("%s", szTempBuf);
		fflush(stdout);
	}
}
//
#endif
#endif
