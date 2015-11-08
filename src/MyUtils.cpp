///////////////////////////////////////////////////////////////////////////////////////
// MyUtils.cpp
// Developed by Dongjin Kwon
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011-2014 Dongjin Kwon
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
#if !defined(__APPLE__)
#include <malloc.h>
#endif
#include "MyUtils.h"
#ifdef USE_GPROGRESSBAR
#include "gprogressbar.h"
#else
#define _TIME_CHECK
#endif
//#define _MALLOC_CHECK


void* MyAlloc(size_t size) {
	void* ptr = malloc(size);
	if (ptr == NULL) {
#ifdef USE_MESSAGEBOX
		char str_tmp[2048];
		sprintf(str_tmp, "MyMalloc: memory allocation failed, size: %d", (int)size);
		AfxMessageBox(str_tmp);
#endif
		return NULL;
	} else {
#ifdef _MALLOC_CHECK
		size_t size_alloc = _msize(ptr);
		if (size_alloc != size) {
#ifdef USE_MESSAGEBOX
			char str_tmp[2048];
			sprintf(str_tmp, "MyMalloc: allocated memory size is different, size: %d, size_alloc: %d", (int)size, (int)size_alloc);
			AfxMessageBox(str_tmp);
#endif
			free(ptr);
			return NULL;
		}
#endif
	}
	return ptr;
}

void* MyAllocEx(size_t size, LPCTSTR str_info) {
	void* ptr = malloc(size);
	if (ptr == NULL) {
#ifdef USE_MESSAGEBOX
		char str_tmp[2048];
		sprintf(str_tmp, "MyMalloc: memory allocation failed, size: %d, info: %s", (int)size, str_info);
		AfxMessageBox(str_tmp);
#endif
		return NULL;
	} else {
#ifdef _MALLOC_CHECK
		size_t size_alloc = _msize(ptr);
		if (size_alloc != size) {
#ifdef USE_MESSAGEBOX
			char str_tmp[2048];
			sprintf(str_tmp, "MyMalloc: allocated memory size is different, size: %d, size_alloc: %d, info: %s", (int)size, (int)size_alloc, str_info);
			AfxMessageBox(str_tmp);
#endif
			free(ptr);
			return NULL;
		}
#endif
	}
	return ptr;
}

void* MyCAllocEx(size_t num, size_t size, LPCTSTR str_info) {
	void* ptr = calloc(num, size);
	if (ptr == NULL) {
#ifdef USE_MESSAGEBOX
		char str_tmp[2048];
		sprintf(str_tmp, "MyCAlloc: memory allocation failed, size: %d, info: %s", (int)size, str_info);
		AfxMessageBox(str_tmp);
#endif
		return NULL;
	} else {
#ifdef _MALLOC_CHECK
		size_t size_alloc = _msize(ptr);
		if (size_alloc != num*size) {
#ifdef USE_MESSAGEBOX
			char str_tmp[2048];
			sprintf(str_tmp, "MyCAlloc: allocated memory size is different, size: %d, size_alloc: %d, info: %s", (int)size, (int)size_alloc, str_info);
			AfxMessageBox(str_tmp);
#endif
			free(ptr);
			return NULL;
		}
#endif
	}
	return ptr;
}

void MyFree(void* ptr) {
	if (ptr != NULL) {
		free(ptr);
		ptr = NULL;
	}
}

//#ifdef USE_MESSAGEBOX
#if 0
BOOL GetFileNameDialog(char *type_name, char *type, CString *path_name, CString *file_name) {
	char filter[1024];
	sprintf(filter, "%s (%s) |%s; |", type_name, type, type);

	DWORD flag = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_LONGNAMES;
	CFileDialog dlg(TRUE, NULL, NULL, flag, filter);

	if(dlg.DoModal() == IDOK) {
		if (path_name != NULL) {
			*path_name = dlg.GetPathName();
		}
		if (file_name != NULL) {
			*file_name = dlg.GetFileName();
		}
		return TRUE;
	} else {
		AfxMessageBox("Failed to load files.");
		return FALSE;
	}
}
BOOL GetFileNameDialog(char *type_name, char *type, CString *init_name, CString *path_name, CString *file_name, BOOL bOpenFileDialog) {
	char filter[1024];
	sprintf(filter, "%s (%s) |%s; |", type_name, type, type);

	DWORD flag = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_LONGNAMES;
	CFileDialog dlg(bOpenFileDialog, NULL, *init_name, flag, filter);

	if(dlg.DoModal() == IDOK) {
		if (path_name != NULL) {
			*path_name = dlg.GetPathName();
		}
		if (file_name != NULL) {
			*file_name = dlg.GetFileName();
		}
		return TRUE;
	} else {
		AfxMessageBox("Failed to select files.");
		return FALSE;
	}
}
#endif

void str_strip_path(char* str_path_file, char* str_file)
{
	if (strrchr(str_path_file, '\\') == NULL) {
		if (strrchr(str_path_file, '/') == NULL) {
			strcpy(str_file, str_path_file);
		} else {
			strcpy(str_file, strrchr(str_path_file, '/')+1);
		}
	} else {
		strcpy(str_file, strrchr(str_path_file, '\\')+1);
	}
}
void str_strip_file(char* str_path_file, char* str_path)
{
	int result;
	char* pos;
	pos = strrchr(str_path_file, '\\');
	if (pos == NULL) {
		pos = strrchr(str_path_file, '/');
	}
	result = (int)(pos - str_path_file + 1);
	strncpy(str_path, str_path_file, result);
	str_path[result] = 0;
}
void str_strip_file2(char* str_file_ext, char* str_ext)
{
	if (strrchr(str_file_ext, '.') == NULL) {
		strcpy(str_ext, str_file_ext);
	} else {
		strcpy(str_ext, strrchr(str_file_ext, '.') + 1);
	}
}
void str_strip_ext(char* str_file_ext, char* str_file)
{
	int result;
	if (strrchr(str_file_ext, '.') == NULL) {
		str_file[0] = 0;
		return;
	}
	result = (int)(strrchr(str_file_ext, '.') - str_file_ext);
	strncpy(str_file, str_file_ext, result);
	str_file[result] = 0;
}
void str_strip_ext_all(char* str_file_ext, char* str_file)
{
	int result;
	if (strrchr(str_file_ext, '.') == NULL) {
		str_file[0] = 0;
		return;
	}
	result = (int)(strchr(str_file_ext, '.') - str_file_ext);
	strncpy(str_file, str_file_ext, result);
	str_file[result] = 0;
}
void str_strip_footer(char* str_file_footer, char* str_file)
{
	int result;
	result = (int)(strrchr(str_file_footer, '_') - str_file_footer);
	strncpy(str_file, str_file_footer, result);
	str_file[result] = 0;
}
void str_divide_header(char* str_header_file, char* str_file, char* str_header, char delim)
{
	char str_tmp[1024];
	int result;
	strcpy(str_tmp, str_header_file);
	result = (int)(strchr(str_tmp, delim) - str_tmp);
	if (str_file != NULL) {
		strncpy(str_file, str_tmp+result+1, strlen(str_tmp)-(result+1));
		str_file[strlen(str_tmp)-(result+1)] = 0;
	}
	if (str_header != NULL) {
		strncpy(str_header, str_tmp, result);
		str_header[result] = 0;
	}
}
void str_divide_footer(char* str_file_footer, char* str_file, char* str_footer, char delim)
{
	char str_tmp[1024];
	int result;
	strcpy(str_tmp, str_file_footer);
	result = (int)(strrchr(str_tmp, delim) - str_tmp);
	if (str_file != NULL) {
		strncpy(str_file, str_tmp, result);
		str_file[result] = 0;
	}
	if (str_footer != NULL) {
		strncpy(str_footer, str_tmp+result+1, strlen(str_tmp)-(result+1));
		str_footer[strlen(str_tmp)-(result+1)] = 0;
	}
}

#ifdef USE_DOEVENTS
void DoEvents()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}
#endif

BOOL IsFileExist(char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "r");
	if (fp == NULL) {
		return FALSE;
	} else {
		fclose(fp);
		return TRUE;
	}
}

BOOL ExecuteProcess(char* szCmdLine) {
#if defined(WIN32) || defined(WIN64)
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szCmdLine,
		NULL,						// Process handle not inheritable
		NULL,						// Thread handle not inheritable
		FALSE,						// Set handle inheritance to FALSE
		0,							// No creation flags
		NULL,						// Use parent's environment block
		NULL,						// Use parent's starting directory 
		&si, &pi)) 
	{
		//TRACE("CreateProcess failed (%d).\n", GetLastError());
		return FALSE;
	}

	// Wait until child process exits
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return TRUE;
#else
    pid_t nPid = -1;
	const char* lpszArgList[256] = {0,};
	int nArgNum;
	BOOL nArgNew;
	char* argarr[256];
	int i, j, k;

	i = 0;
	nArgNum = 0;
	nArgNew = FALSE;
	while (szCmdLine[i] != 0) {
		if ((szCmdLine[i] == ' ') || (szCmdLine[i] == '\t')) {
			nArgNew = FALSE;
		} else {
			if (!nArgNew) {
				nArgNum++;
				nArgNew = TRUE;
			}
		}
		i++;
	}
	//
	for (k = 0; k < nArgNum; k++) {
		argarr[k] = (char*)malloc(1024 * sizeof(char));
	}
	//
	i = 0;
	j = 0;
	k = 0;
	nArgNew = FALSE;
	while (szCmdLine[i] != 0) {
		if ((szCmdLine[i] == ' ') || (szCmdLine[i] == '\t')) {
			nArgNew = FALSE;
		} else {
			if (!nArgNew) {
				k++;
				j = 0;
				nArgNew = TRUE;
			}
			argarr[k-1][j  ] = szCmdLine[i];
			argarr[k-1][j+1] = 0;
			j++;
		}
		i++;
	}
	//
	for (k = 0; k < nArgNum; k++) {
		//TRACE("arg[%d] = %s\n", k, argarr[k]);
		lpszArgList[k] = argarr[k];
	}

    nPid = fork();
    if (nPid == -1) {
		//TRACE("Fail to fork, errno=%d\n", errno);
		return FALSE;
    } else if (nPid == 0) {
        // child
        //TRACE("in fork child, before exec %s\n", szCmdLine);

        if (execvp(argarr[0], (char* const*)lpszArgList) == -1) {
            //TRACE("Fail to execl, errno=%d\n", errno);
            if (errno != 0) {
				 _exit(errno);
            }
        }

		_exit(255);
    } else {
        // parent
	    int nStatVal = 0;
		/*
        if (wait(&nStatVal) == -1) {
            TRACE("Fail to wait, errno=%d\n", errno);
			return FALSE;
        }
		/*/
		while (waitpid(nPid, &nStatVal, 0) == -1) {
            if (errno != EINTR) {
                //TRACE("waitpid error\n");
                return FALSE;
            }
		}
        if (WIFEXITED(nStatVal)) {
            //TRACE("child exited with %d\n", WEXITSTATUS(nStatVal));
		} else if (WIFSIGNALED(nStatVal)) {
            //TRACE("child killed by %d\n", WTERMSIG(nStatVal));
		}
		//*/
    }

	for (k = 0; k < nArgNum; k++) {
		free(argarr[k]);
	}

	return TRUE;
#endif
}

BOOL IsExecutableExistInPath(const char* executable_name, char* path_name)
{
	char *path_env, path[4096];
    char *dir;
	char file_name[1024];
	BOOL bExist = FALSE;

	path_env = getenv("PATH");
	if (path_env == NULL) {
		return FALSE;
	}
	sprintf(path, "%s", path_env);
#if defined(WIN32) || defined(WIN64)
	for (dir = strtok(path, ";"); dir; dir = strtok(NULL, ";")) {
		//TRACE("%s\n", dir);
		sprintf(file_name, "%s\\%s", dir, executable_name);
		if (IsFileExist(file_name)) {
			bExist = TRUE;
			if (path_name != NULL) {
				sprintf(path_name, "%s", file_name);
			}
			break;
		}
    }
#else
	for (dir = strtok(path, ":"); dir; dir = strtok(NULL, ":")) {
		//TRACE("%s\n", dir);
		sprintf(file_name, "%s/%s", dir, executable_name);
		if (IsFileExist(file_name)) {
			bExist = TRUE;
			if (path_name != NULL) {
				sprintf(path_name, "%s", file_name);
			}
			break;
		}
    }
#endif

	return bExist;
}

BOOL FindExecutableInPath(const char* executable_name, char* module_path, char* path_name)
{
	char file_name[1024];

	// find the executable in the module path first
	sprintf(file_name, "%s%s", module_path, executable_name);
	if (IsFileExist(file_name)) {
		//TRACE("%s is located in %s.\n", executable_name, file_name);
		if (path_name != NULL) {
			sprintf(path_name, "%s", file_name);
		}
		return TRUE;
	}

	// find the executable in the path
	if (IsExecutableExistInPath(executable_name, path_name)) {
		//TRACE("%s is located in %s.\n", executable_name, path_name);
		return TRUE;
	}

	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#ifdef VIPL
void GetImage(BYTE** ImageData, int id_x, int id_y, ByteImage& image)
{
	int i, j;
	for (j = 0; j < id_y; j++) {
		BYTE* p = ImageData[j];
		for (i = 0; i < id_x; i++) {
			image(i, j) = *p++;
		}
	}
}
void GetImageData(ByteImage& image, BYTE** ImageData, int id_x, int id_y)
{
	int i, j;
	for (j = 0; j < id_y; j++) {
		BYTE* q = ImageData[j];
		for (i = 0; i < id_x; i++) {
			*q++ = image(i, j);
		}
	}
}
#endif
void SetImageData(BYTE** ImageData, int id_x, int id_y, BYTE value)
{
	int i, j;
	for (j = 0; j < id_y; j++) {
		BYTE* p = ImageData[j];
		for (i = 0; i < id_x; i++) {
			*p++ = value;
		}
	}
}

void FreeImageData(BYTE*** pImageData, int id_x, int id_y)
{
	int j;
	if (*pImageData) {
		for (j = 0; j < id_y; j++) {
			MyFree((*pImageData)[j]);
			(*pImageData)[j] = NULL;
		}
		MyFree(*pImageData);
		*pImageData = NULL;
	}
}
void FreeImageData(float*** pImageData, int id_x, int id_y)
{
	int j;
	if (*pImageData) {
		for (j = 0; j < id_y; j++) {
			MyFree((*pImageData)[j]);
			(*pImageData)[j] = NULL;
		}
		MyFree(*pImageData);
		*pImageData = NULL;
	}
}
void FreeImageData(double*** pImageData, int id_x, int id_y)
{
	int j;
	if (*pImageData) {
		for (j = 0; j < id_y; j++) {
			MyFree((*pImageData)[j]);
			(*pImageData)[j] = NULL;
		}
		MyFree(*pImageData);
		*pImageData = NULL;
	}
}
void FreeImageData(int*** pImageData, int id_x, int id_y)
{
	int j;
	if (*pImageData) {
		for (j = 0; j < id_y; j++) {
			MyFree((*pImageData)[j]);
			(*pImageData)[j] = NULL;
		}
		MyFree(*pImageData);
		*pImageData = NULL;
	}
}
BOOL AllocateImageData(BYTE*** pImageData, int id_x, int id_y, BOOL fill_zero)
{
	if (*pImageData != NULL) {
		FreeImageData(pImageData, id_x, id_y);
	}
	int j;
	if (!fill_zero) {
		*pImageData = (BYTE**)MyAllocEx(id_y*sizeof(BYTE*), "AllocateImageData BYTE");
		for (j = 0; j < id_y; j++) {
			(*pImageData)[j] = (BYTE*)MyCAllocEx(id_x, sizeof(BYTE), "AllocateImageData BYTE");
		}
	} else {
		*pImageData = (BYTE**)MyAllocEx(id_y*sizeof(BYTE*), "AllocateImageData BYTE");
		for (j = 0; j < id_y; j++) {
			(*pImageData)[j] = (BYTE*)MyCAllocEx(id_x, sizeof(BYTE), "AllocateImageData BYTE");
			memset((*pImageData)[j], 0, id_x * sizeof(BYTE));
		}
	}
	return TRUE;
}
BOOL AllocateImageData(float*** pImageData, int id_x, int id_y, BOOL fill_zero)
{
	if (*pImageData != NULL) {
		FreeImageData(pImageData, id_x, id_y);
	}
	int j;
	if (!fill_zero) {
		*pImageData = (float**)MyAllocEx(id_y*sizeof(float*), "AllocateImageData float");
		for (j = 0; j < id_y; j++) {
			(*pImageData)[j] = (float*)MyCAllocEx(id_x, sizeof(float), "AllocateImageData float");
		}
	} else {
		*pImageData = (float**)MyAllocEx(id_y*sizeof(float*), "AllocateImageData float");
		for (j = 0; j < id_y; j++) {
			(*pImageData)[j] = (float*)MyCAllocEx(id_x, sizeof(float), "AllocateImageData float");
			memset((*pImageData)[j], 0, id_x * sizeof(float));
		}
	}
	return TRUE;
}
BOOL AllocateImageData(double*** pImageData, int id_x, int id_y, BOOL fill_zero)
{
	if (*pImageData != NULL) {
		FreeImageData(pImageData, id_x, id_y);
	}
	int j;
	if (!fill_zero) {
		*pImageData = (double**)MyAllocEx(id_y*sizeof(double*), "AllocateImageData double");
		for (j = 0; j < id_y; j++) {
			(*pImageData)[j] = (double*)MyCAllocEx(id_x, sizeof(double), "AllocateImageData double");
		}
	} else {
		*pImageData = (double**)MyAllocEx(id_y*sizeof(double*), "AllocateImageData double");
		for (j = 0; j < id_y; j++) {
			(*pImageData)[j] = (double*)MyCAllocEx(id_x, sizeof(double), "AllocateImageData double");
			memset((*pImageData)[j], 0, id_x * sizeof(double));
		}
	}
	return TRUE;
}
BOOL AllocateImageData(int*** pImageData, int id_x, int id_y, BOOL fill_zero)
{
	if (*pImageData != NULL) {
		FreeImageData(pImageData, id_x, id_y);
	}
	int j;
	if (!fill_zero) {
		*pImageData = (int**)MyAllocEx(id_y*sizeof(int*), "AllocateImageData int");
		for (j = 0; j < id_y; j++) {
			(*pImageData)[j] = (int*)MyCAllocEx(id_x, sizeof(int), "AllocateImageData int");
		}
	} else {
		*pImageData = (int**)MyAllocEx(id_y*sizeof(int*), "AllocateImageData int");
		for (j = 0; j < id_y; j++) {
			(*pImageData)[j] = (int*)MyCAllocEx(id_x, sizeof(int), "AllocateImageData int");
			memset((*pImageData)[j], 0, id_x * sizeof(int));
		}
	}
	return TRUE;
}

void CopyImageData(BYTE** ImageData1, int id1_x, int id1_y, BYTE** ImageData2, int id2_x, int id2_y)
{
	int i, j;
	for (j = 0; j < MIN(id1_y, id2_y); j++) {
		BYTE* p = ImageData1[j];
		BYTE* q = ImageData2[j];
		for (i = 0; i < MIN(id1_x, id2_x); i++) {
			*q++ = *p++;
		}
	}
}
void CopyImageDataHalf(BYTE** ImageData1, int id1_x, int id1_y, BYTE** ImageData2, int id2_x, int id2_y)
{
	int i, j;
	for (j = 0; j < id2_y; j++) {
		BYTE* p = ImageData1[j<<1];
		BYTE* q = ImageData2[j   ];
		for (i = 0; i < id2_x; i++) {
			*q++ = *p;
			p += 2;
		}
	}
}

BOOL LoadImageData(LPCTSTR lpszPathName, float*** pImageData, int& id_x, int& id_y)
{
	FILE* fp_data = NULL;
	float buf_data[2048];
	int id_z;
	int i, j;

	fp_data = fopen(lpszPathName, "rb");
	if (fp_data == NULL) return FALSE;

	fread(&id_x, sizeof(int), 1, fp_data);
	fread(&id_y, sizeof(int), 1, fp_data);
	fread(&id_z, sizeof(int), 1, fp_data);

	if (!AllocateImageData(pImageData, id_x, id_y)) {
		return FALSE;
	}

	for (j = 0; j < id_y; j++) {
		fread(buf_data, sizeof(float), id_x, fp_data);
		for (i = 0; i < id_x; i++) {
			(*pImageData)[j][i] = buf_data[i];
		}
	}

	if (fp_data) fclose(fp_data);

	return TRUE;
}
BOOL LoadImageData(LPCTSTR lpszPathName, int*** pImageData, int& id_x, int& id_y)
{
	FILE* fp_data = NULL;
	int buf_data[2048];
	int id_z;
	int i, j;

	fp_data = fopen(lpszPathName, "rb");
	if (fp_data == NULL) return FALSE;

	fread(&id_x, sizeof(int), 1, fp_data);
	fread(&id_y, sizeof(int), 1, fp_data);
	fread(&id_z, sizeof(int), 1, fp_data);

	if (!AllocateImageData(pImageData, id_x, id_y)) {
		return FALSE;
	}

	for (j = 0; j < id_y; j++) {
		fread(buf_data, sizeof(int), id_x, fp_data);
		for (i = 0; i < id_x; i++) {
			(*pImageData)[j][i] = buf_data[i];
		}
	}

	if (fp_data) fclose(fp_data);

	return TRUE;
}
BOOL SaveImageData(LPCTSTR lpszPathName, float** pImageData, int id_x, int id_y)
{
	FILE* fp_data;
	float buf_data[2048];
	int id_z = 1;
	int i, j;

	fp_data = fopen(lpszPathName, "wb");
	fwrite(&id_x, sizeof(int), 1, fp_data);
	fwrite(&id_y, sizeof(int), 1, fp_data);
	fwrite(&id_z, sizeof(int), 1, fp_data);

	for (j = 0; j < id_y; j++) {
		for (i = 0; i < id_x; i++) {
			buf_data[i] = pImageData[j][i];
		}
		fwrite(buf_data, sizeof(float), id_x, fp_data);
	}

	fclose(fp_data);

	return TRUE;
}
BOOL SaveImageData(LPCTSTR lpszPathName, double** pImageData, int id_x, int id_y)
{
	FILE* fp_data;
	double buf_data[2048];
	int id_z = 1;
	int i, j;

	fp_data = fopen(lpszPathName, "wb");
	fwrite(&id_x, sizeof(int), 1, fp_data);
	fwrite(&id_y, sizeof(int), 1, fp_data);
	fwrite(&id_z, sizeof(int), 1, fp_data);

	for (j = 0; j < id_y; j++) {
		for (i = 0; i < id_x; i++) {
			buf_data[i] = pImageData[j][i];
		}
		fwrite(buf_data, sizeof(double), id_x, fp_data);
	}

	fclose(fp_data);

	return TRUE;
}
BOOL SaveImageData(LPCTSTR lpszPathName, int** pImageData, int id_x, int id_y)
{
	FILE* fp_data;
	int buf_data[2048];
	int id_z = 1;
	int i, j;

	fp_data = fopen(lpszPathName, "wb");
	fwrite(&id_x, sizeof(int), 1, fp_data);
	fwrite(&id_y, sizeof(int), 1, fp_data);
	fwrite(&id_z, sizeof(int), 1, fp_data);

	for (j = 0; j < id_y; j++) {
		for (i = 0; i < id_x; i++) {
			buf_data[i] = pImageData[j][i];
		}
		fwrite(buf_data, sizeof(int), id_x, fp_data);
	}

	fclose(fp_data);

	return TRUE;
}

#ifdef VIPL
BOOL LoadImageData(LPCTSTR lpszPathName, ByteImage& image, BYTE*** pImageMaskData, int& id_x, int& id_y, BOOL bShowDialog)
{
	FILE* fp_data = NULL;
	FILE* fp_data_mask = NULL;
	BYTE buf_data_mask[2048];
	int i, j;

	image.LoadImage(lpszPathName);
	if (image.GetCSize() == 3) image = ColorToGray(image);
	id_x = image.GetXSize();
	id_y = image.GetYSize();

	if (pImageMaskData != NULL) {
		CString str_tmp(lpszPathName);
		str_tmp = str_tmp.Left(str_tmp.ReverseFind('.'));
		str_tmp += ".msk";

		//*
		fp_data_mask = NULL;
		fp_data_mask = fopen((LPCSTR)str_tmp, "rb");
		if (fp_data_mask != NULL) {
			int idm_x, idm_y, idm_z;
			if (bShowDialog) {
				if (AfxMessageBox("Load Mask Data?", MB_YESNO) == IDYES) {
					fread(&idm_x, sizeof(int), 1, fp_data_mask);
					fread(&idm_y, sizeof(int), 1, fp_data_mask);
					fread(&idm_z, sizeof(int), 1, fp_data_mask);
				} else {
					fclose(fp_data_mask);
					fp_data_mask = NULL;
					goto errret;
				}
			} else {
				fread(&idm_x, sizeof(int), 1, fp_data_mask);
				fread(&idm_y, sizeof(int), 1, fp_data_mask);
				fread(&idm_z, sizeof(int), 1, fp_data_mask);
			}

			AllocateImageData(pImageMaskData, id_x, id_y);
			for (j = 0; j < id_y; j++) {
				fread(buf_data_mask, sizeof(BYTE), id_x, fp_data_mask);
				for (i = 0; i < id_x; i++) {
					(*pImageMaskData)[j][i] = buf_data_mask[i];
				}
			}
		} else {
			int idm_x, idm_y, idm_z;
			if (bShowDialog) {
				if (AfxMessageBox("Create Mask Data?", MB_YESNO) == IDYES) {
				} else {
					fp_data_mask = NULL;
					goto errret;
				}
			} else {
			}

			AllocateImageData(pImageMaskData, id_x, id_y);
			for (j = 0; j < id_y; j++) {
				for (i = 0; i < id_x; i++) {
					(*pImageMaskData)[j][i] = 1; // IMG_FOREGROUND
				}
			}
		}
		/*/
		int idm_x, idm_y, idm_z;
		fp_data_mask = NULL;
		fp_data_mask = fopen((LPCTSTR)str_tmp, "rb");
		if (fp_data_mask != NULL) {
			fread(&idm_x, sizeof(int), 1, fp_data_mask);
			fread(&idm_y, sizeof(int), 1, fp_data_mask);
			fread(&idm_z, sizeof(int), 1, fp_data_mask);
		}
		//*/
	}

errret:
	if (fp_data_mask) fclose(fp_data_mask);

	return TRUE;
}
#endif
BOOL SaveImageData(LPCTSTR lpszPathName, BYTE** pImageData, int id_x, int id_y)
{
	FILE* fp_data;
	BYTE buf_data[2048];
	int id_z = 1;
	int i, j;

	fp_data = fopen(lpszPathName, "wb");
	fwrite(&id_x, sizeof(int), 1, fp_data);
	fwrite(&id_y, sizeof(int), 1, fp_data);
	fwrite(&id_z, sizeof(int), 1, fp_data);

	for (j = 0; j < id_y; j++) {
		for (i = 0; i < id_x; i++) {
			buf_data[i] = pImageData[j][i];
		}
		fwrite(buf_data, sizeof(BYTE), id_x, fp_data);
	}

	fclose(fp_data);

	return TRUE;
}

BOOL LoadImageData(LPCTSTR lpszPathName, double** pImageData, int& id_x, int& id_y)
{
	FILE* fp_data = NULL;
	double buf_data[2048];
	int id_z;
	int i, j;

	fp_data = fopen(lpszPathName, "rb");
	if (fp_data == NULL) return FALSE;

	fread(&id_x, sizeof(int), 1, fp_data);
	fread(&id_y, sizeof(int), 1, fp_data);
	fread(&id_z, sizeof(int), 1, fp_data);

	(*pImageData) = (double*)malloc(id_x * id_y * sizeof(double));

	for (j = 0; j < id_y; j++) {
		fread(buf_data, sizeof(double), id_x, fp_data);
		for (i = 0; i < id_x; i++) {
			(*pImageData)[j*id_x+i] = buf_data[i];
		}
	}

	if (fp_data) fclose(fp_data);

	return TRUE;
}
BOOL SaveImageData(LPCTSTR lpszPathName, double* pImageData, int id_x, int id_y)
{
	FILE* fp_data;
	double buf_data[2048];
	int id_z = 1;
	int i, j;

	fp_data = fopen(lpszPathName, "wb");
	fwrite(&id_x, sizeof(int), 1, fp_data);
	fwrite(&id_y, sizeof(int), 1, fp_data);
	fwrite(&id_z, sizeof(int), 1, fp_data);

	for (j = 0; j < id_y; j++) {
		for (i = 0; i < id_x; i++) {
			buf_data[i] = pImageData[j*id_x+i];
		}
		fwrite(buf_data, sizeof(double), id_x, fp_data);
	}

	fclose(fp_data);

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BOOL AllocateVoxelData(BYTE**** pVoxelData, int vd_x, int vd_y, int vd_z, BOOL fill_zero)
{
	if (*pVoxelData != NULL) {
		FreeVoxelData(pVoxelData, vd_x, vd_y, vd_z);
	}
	// 512*512*512   = 128MB
	// 512*512*512*2 = 256MB
	// 512*512*512*4 = 512MB : allocation limit
	int j, k;
#ifndef MEM_CHUNK
	if (!fill_zero) {
		*pVoxelData = (BYTE***)MyAllocEx(vd_z*sizeof(BYTE**), "AllocateVoxelData BYTE");
		for (k = 0; k < vd_z; k++) {
			(*pVoxelData)[k] = (BYTE**)MyAllocEx(vd_y*sizeof(BYTE*), "AllocateVoxelData BYTE");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (BYTE*)MyCAllocEx(vd_x, sizeof(BYTE), "AllocateVoxelData BYTE");
			}
		}
	} else {
		*pVoxelData = (BYTE***)MyAllocEx(vd_z*sizeof(BYTE**), "AllocateVoxelData BYTE");
		for (k = 0; k < vd_z; k++) {
			(*pVoxelData)[k] = (BYTE**)MyAllocEx(vd_y*sizeof(BYTE*), "AllocateVoxelData BYTE");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (BYTE*)MyCAllocEx(vd_x, sizeof(BYTE), "AllocateVoxelData BYTE");
				memset((*pVoxelData)[k][j], 0, vd_x * sizeof(BYTE));
			}
		}
	}
#else
	if (!fill_zero) {
		*pVoxelData = (BYTE***)MyAllocEx(vd_z*sizeof(BYTE**), "AllocateVoxelData BYTE");
		for (k = 0; k < vd_z; k++) {
			BYTE* mem_chunk = (BYTE*)MyAllocEx(vd_x*vd_y*sizeof(BYTE), "AllocateVoxelData BYTE mem_chunk");
			(*pVoxelData)[k] = (BYTE**)MyAllocEx(vd_y*sizeof(BYTE*), "AllocateVoxelData BYTE");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = &mem_chunk[j*vd_x];
			}
		}
	} else {
		*pVoxelData = (BYTE***)MyAllocEx(vd_z*sizeof(BYTE**), "AllocateVoxelData BYTE");
		for (k = 0; k < vd_z; k++) {
			BYTE* mem_chunk = (BYTE*)MyAllocEx(vd_x*vd_y*sizeof(BYTE), "AllocateVoxelData BYTE mem_chunk");
			memset(mem_chunk, 0, vd_x*vd_y*sizeof(BYTE));
			(*pVoxelData)[k] = (BYTE**)MyAllocEx(vd_y*sizeof(BYTE*), "AllocateVoxelData BYTE");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = &mem_chunk[j*vd_x];
			}
		}
	}
#endif
	return TRUE;
}
BOOL AllocateVoxelData(short**** pVoxelData, int vd_x, int vd_y, int vd_z, BOOL init, short init_value)
{
	if (*pVoxelData != NULL) {
		FreeVoxelData(pVoxelData, vd_x, vd_y, vd_z);
	}
	int i, j, k;
#ifndef MEM_CHUNK
	if (!init) {
		*pVoxelData = (short***)MyAllocEx(vd_z*sizeof(short**), "AllocateVoxelData short");
		for (k = 0; k < vd_z; k++) {
			(*pVoxelData)[k] = (short**)MyAllocEx(vd_y*sizeof(short*), "AllocateVoxelData short");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (short*)MyCAllocEx(vd_x, sizeof(short), "AllocateVoxelData short");
			}
		}
	} else {
		*pVoxelData = (short***)MyAllocEx(vd_z*sizeof(short**), "AllocateVoxelData short");
		for (k = 0; k < vd_z; k++) {
			(*pVoxelData)[k] = (short**)MyAllocEx(vd_y*sizeof(short*), "AllocateVoxelData short");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (short*)MyCAllocEx(vd_x, sizeof(short), "AllocateVoxelData short");
				{
					short* p = (*pVoxelData)[k][j];
					for (i = 0; i < vd_x; i++) {
						*p++ = init_value;
					}
				}
			}
		}
	}
#else
	if (!init) {
		*pVoxelData = (short***)MyAllocEx(vd_z*sizeof(short**), "AllocateVoxelData short");
		for (k = 0; k < vd_z; k++) {
			short* mem_chunk = (short*)MyAllocEx(vd_x*vd_y*sizeof(short), "AllocateVoxelData float mem_chunk");
			(*pVoxelData)[k] = (short**)MyAllocEx(vd_y*sizeof(short*), "AllocateVoxelData short");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = &mem_chunk[j*vd_x];
			}
		}
	} else {
		*pVoxelData = (short***)MyAllocEx(vd_z*sizeof(short**), "AllocateVoxelData short");
		for (k = 0; k < vd_z; k++) {
			short* mem_chunk = (short*)MyAllocEx(vd_x*vd_y*sizeof(short), "AllocateVoxelData float mem_chunk");
			(*pVoxelData)[k] = (short**)MyAllocEx(vd_y*sizeof(short*), "AllocateVoxelData short");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = &mem_chunk[j*vd_x];
				{
					short* p = (*pVoxelData)[k][j];
					for (i = 0; i < vd_x; i++) {
						*p++ = init_value;
					}
				}
			}
		}
	}
#endif
	return TRUE;
}
BOOL AllocateVoxelData(float**** pVoxelData, int vd_x, int vd_y, int vd_z, BOOL fill_zero)
{
	if (*pVoxelData != NULL) {
		FreeVoxelData(pVoxelData, vd_x, vd_y, vd_z);
	}
	int j, k;
#ifndef MEM_CHUNK
	if (!fill_zero) {
		*pVoxelData = (float***)MyAllocEx(vd_z*sizeof(float**), "AllocateVoxelData float");
		for (k = 0; k < vd_z; k++) {
			(*pVoxelData)[k] = (float**)MyAllocEx(vd_y*sizeof(float*), "AllocateVoxelData float");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (float*)MyCAllocEx(vd_x, sizeof(float), "AllocateVoxelData float");
			}
		}
	} else {
		*pVoxelData = (float***)MyAllocEx(vd_z*sizeof(float**), "AllocateVoxelData float");
		for (k = 0; k < vd_z; k++) {
			(*pVoxelData)[k] = (float**)MyAllocEx(vd_y*sizeof(float*), "AllocateVoxelData float");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (float*)MyCAllocEx(vd_x, sizeof(float), "AllocateVoxelData float");
				memset((*pVoxelData)[k][j], 0, vd_x * sizeof(float));
			}
		}
	}
#else
	if (!fill_zero) {
		*pVoxelData = (float***)MyAllocEx(vd_z*sizeof(float**), "AllocateVoxelData float");
		for (k = 0; k < vd_z; k++) {
			float* mem_chunk = (float*)MyAllocEx(vd_x*vd_y*sizeof(float), "AllocateVoxelData float mem_chunk");
			(*pVoxelData)[k] = (float**)MyAllocEx(vd_y*sizeof(float*), "AllocateVoxelData float");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = &mem_chunk[j*vd_x];
			}
		}
	} else {
		*pVoxelData = (float***)MyAllocEx(vd_z*sizeof(float**), "AllocateVoxelData float");
		for (k = 0; k < vd_z; k++) {
			float* mem_chunk = (float*)MyAllocEx(vd_x*vd_y*sizeof(float), "AllocateVoxelData float mem_chunk");
			memset(mem_chunk, 0, vd_x*vd_y*sizeof(float));
			(*pVoxelData)[k] = (float**)MyAllocEx(vd_y*sizeof(float*), "AllocateVoxelData float");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = &mem_chunk[j*vd_x];
			}
		}
	}
#endif
	return TRUE;
}
void FreeVoxelData(BYTE**** pVoxelData, int vd_x, int vd_y, int vd_z)
{
	int j, k;
#ifndef MEM_CHUNK
	if (*pVoxelData) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				MyFree((*pVoxelData)[k][j]);
				(*pVoxelData)[k][j] = NULL;
			}
			MyFree((*pVoxelData)[k]);
			(*pVoxelData)[k] = NULL;
		}
		MyFree(*pVoxelData);
		*pVoxelData = NULL;
	}
#else
	if (*pVoxelData) {
		for (k = 0; k < vd_z; k++) {
			MyFree((*pVoxelData)[k][0]);
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = NULL;
			}
			MyFree((*pVoxelData)[k]);
			(*pVoxelData)[k] = NULL;
		}
		MyFree(*pVoxelData);
		*pVoxelData = NULL;
	}
#endif
}
void FreeVoxelData(short**** pVoxelData, int vd_x, int vd_y, int vd_z)
{
	int j, k;
#ifndef MEM_CHUNK
	if (*pVoxelData) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				MyFree((*pVoxelData)[k][j]);
				(*pVoxelData)[k][j] = NULL;
			}
			MyFree((*pVoxelData)[k]);
			(*pVoxelData)[k] = NULL;
		}
		MyFree(*pVoxelData);
		*pVoxelData = NULL;
	}
#else
	if (*pVoxelData) {
		for (k = 0; k < vd_z; k++) {
			MyFree((*pVoxelData)[k][0]);
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = NULL;
			}
			MyFree((*pVoxelData)[k]);
			(*pVoxelData)[k] = NULL;
		}
		MyFree(*pVoxelData);
		*pVoxelData = NULL;
	}
#endif
}
void FreeVoxelData(float**** pVoxelData, int vd_x, int vd_y, int vd_z)
{
	int j, k;
#ifndef MEM_CHUNK
	if (*pVoxelData) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				MyFree((*pVoxelData)[k][j]);
				(*pVoxelData)[k][j] = NULL;
			}
			MyFree((*pVoxelData)[k]);
			(*pVoxelData)[k] = NULL;
		}
		MyFree(*pVoxelData);
		*pVoxelData = NULL;
	}
#else
	if (*pVoxelData) {
		for (k = 0; k < vd_z; k++) {
			MyFree((*pVoxelData)[k][0]);
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = NULL;
			}
			MyFree((*pVoxelData)[k]);
			(*pVoxelData)[k] = NULL;
		}
		MyFree(*pVoxelData);
		*pVoxelData = NULL;
	}
#endif
}

BOOL LoadVoxelData(LPCTSTR lpszPathName, short**** pVoxelData, BYTE**** pVoxelMaskData, 
				   int& vd_x, int& vd_y, int& vd_z, int& vd_sz, int& vd_z1, int& vd_z2, BOOL bShowDialog)
{
	int i, j, k;
	FILE* fp_data = NULL;
	FILE* fp_data_mask = NULL;
	short buf_data[2048];
	char buf_data_mask[2048];

	fp_data = fopen(lpszPathName, "rb");
	fread(&vd_x, sizeof(int), 1, fp_data);
	if (vd_x < 0) {
		float fXSp, fYSp, fZSp, fXOrg, fYOrg, fZOrg;
		fread(&fXSp, sizeof(float), 1, fp_data);
		fread(&fYSp, sizeof(float), 1, fp_data);
		fread(&fZSp, sizeof(float), 1, fp_data);
		fread(&fXOrg, sizeof(float), 1, fp_data);
		fread(&fYOrg, sizeof(float), 1, fp_data);
		fread(&fZOrg, sizeof(float), 1, fp_data);
		fread(&vd_x, sizeof(int), 1, fp_data);
	}
	fread(&vd_y, sizeof(int), 1, fp_data);
	fread(&vd_z, sizeof(int), 1, fp_data);
#ifdef USE_CSTRING
	{
		CString str_tmp(lpszPathName);
		str_tmp = str_tmp.Left(str_tmp.ReverseFind('.'));
		str_tmp += ".txt";
		FILE* fp_tmp = NULL;
		fp_tmp = fopen((LPCTSTR)str_tmp, "r");
		if (fp_tmp != NULL) {
			int z1_r, z2_r;
			fscanf(fp_tmp, "%d %d", &z1_r, &z2_r);
			fclose(fp_tmp);
			vd_z1 = vd_z-1 - z2_r;
			vd_z2 = vd_z-1 - z1_r;
			if (vd_z1 < 0 || vd_z1 > vd_z-2 || vd_z2 <= vd_z1 || vd_z2 > vd_z-1) {
				vd_z1 = 0;
				vd_z2 = vd_z-1;
			}
		} else {
			vd_z1 = 0;
			vd_z2 = vd_z-1;
		}
	}
#endif
	vd_sz = vd_z2 - vd_z1 + 1;
#ifdef USE_CSTRING
	if (pVoxelMaskData != NULL) {
		CString str_tmp(lpszPathName);
		str_tmp = str_tmp.Left(str_tmp.ReverseFind('.'));
		str_tmp += ".msk";

		//*
		fp_data_mask = NULL;
		fp_data_mask = fopen((LPCTSTR)str_tmp, "rb");
		if (fp_data_mask != NULL) {
			int vdm_x, vdm_y, vdm_z;
			if (bShowDialog) {
				if (AfxMessageBox("Load Mask Data?", MB_YESNO) == IDYES) {
					fread(&vdm_x, sizeof(int), 1, fp_data_mask);
					if (vdm_x < 0) {
						float fXSp, fYSp, fZSp, fXOrg, fYOrg, fZOrg;
						fread(&fXSp, sizeof(float), 1, fp_data_mask);
						fread(&fYSp, sizeof(float), 1, fp_data_mask);
						fread(&fZSp, sizeof(float), 1, fp_data_mask);
						fread(&fXOrg, sizeof(float), 1, fp_data_mask);
						fread(&fYOrg, sizeof(float), 1, fp_data_mask);
						fread(&fZOrg, sizeof(float), 1, fp_data_mask);
						fread(&vdm_x, sizeof(int), 1, fp_data_mask);
					}
					fread(&vdm_y, sizeof(int), 1, fp_data_mask);
					fread(&vdm_z, sizeof(int), 1, fp_data_mask);
				} else {
					fclose(fp_data_mask);
					fp_data_mask = NULL;
				}
			} else {
				fread(&vdm_x, sizeof(int), 1, fp_data_mask);
				if (vdm_x < 0) {
					float fXSp, fYSp, fZSp, fXOrg, fYOrg, fZOrg;
					fread(&fXSp, sizeof(float), 1, fp_data_mask);
					fread(&fYSp, sizeof(float), 1, fp_data_mask);
					fread(&fZSp, sizeof(float), 1, fp_data_mask);
					fread(&fXOrg, sizeof(float), 1, fp_data_mask);
					fread(&fYOrg, sizeof(float), 1, fp_data_mask);
					fread(&fZOrg, sizeof(float), 1, fp_data_mask);
					fread(&vdm_x, sizeof(int), 1, fp_data_mask);
				}
				fread(&vdm_y, sizeof(int), 1, fp_data_mask);
				fread(&vdm_z, sizeof(int), 1, fp_data_mask);
			}
		}
		/*/
		int vdm_x, vdm_y, vdm_z;
		fp_data_mask = NULL;
		fp_data_mask = fopen((LPCTSTR)str_tmp, "rb");
		if (fp_data_mask != NULL) {
			fread(&vdm_x, sizeof(int), 1, fp_data_mask);
			fread(&vdm_y, sizeof(int), 1, fp_data_mask);
			fread(&vdm_z, sizeof(int), 1, fp_data_mask);
		}
		//*/
	}
#endif

#ifndef _TIME_CHECK
	CGProgressBar Bar("Loding Voxel Data...", 100);
#endif

	if (pVoxelMaskData == NULL) {
		AllocateVoxelData(pVoxelData, vd_x, vd_y, vd_sz);

		for (k = 0; k < vd_z1; k++) {
			for (j = 0; j < vd_y; j++) {
				fread(buf_data, sizeof(short), vd_x, fp_data);
			}
		}
		for (k = vd_sz-1; k >= 0; k--) {
			for (j = 0; j < vd_y; j++) {
				fread(buf_data, sizeof(short), vd_x, fp_data);
				for (i = 0; i < vd_x; i++) {
					(*pVoxelData)[k][j][i] = buf_data[i];
				}
			}

#ifndef _TIME_CHECK
			Bar.SetPos((100*(vd_sz-1-k))/vd_sz);
#endif
		}
	} else if (fp_data_mask == NULL) {
		AllocateVoxelData(pVoxelData, vd_x, vd_y, vd_sz);
		AllocateVoxelData(pVoxelMaskData, vd_x, vd_y, vd_sz);

		for (k = 0; k < vd_z1; k++) {
			for (j = 0; j < vd_y; j++) {
				fread(buf_data, sizeof(short), vd_x, fp_data);
			}
		}
		for (k = vd_sz-1; k >= 0; k--) {
			for (j = 0; j < vd_y; j++) {
				fread(buf_data, sizeof(short), vd_x, fp_data);
				for (i = 0; i < vd_x; i++) {
					(*pVoxelData)[k][j][i] = buf_data[i];
					(*pVoxelMaskData)[k][j][i] = 0;
				}
			}

#ifndef _TIME_CHECK
			Bar.SetPos((100*(vd_sz-1-k))/vd_sz);
#endif
		}
	} else {
		AllocateVoxelData(pVoxelData, vd_x, vd_y, vd_sz);
		AllocateVoxelData(pVoxelMaskData, vd_x, vd_y, vd_sz);

		for (k = 0; k < vd_z1; k++) {
			for (j = 0; j < vd_y; j++) {
				fread(buf_data, sizeof(short), vd_x, fp_data);
				fread(buf_data_mask, sizeof(char), vd_x, fp_data_mask);
			}
		}
		for (k = vd_sz-1; k >= 0; k--) {
			for (j = 0; j < vd_y; j++) {
				fread(buf_data, sizeof(short), vd_x, fp_data);
				fread(buf_data_mask, sizeof(char), vd_x, fp_data_mask);
				for (i = 0; i < vd_x; i++) {
					(*pVoxelData)[k][j][i] = buf_data[i];
					(*pVoxelMaskData)[k][j][i] = (BYTE)(buf_data_mask[i]);
				}
			}

#ifndef _TIME_CHECK
			Bar.SetPos((100*(vd_sz-1-k))/vd_sz);
#endif
		}
	}

	if (fp_data) fclose(fp_data);
	if (fp_data_mask) fclose(fp_data_mask);

	return TRUE;
}
BOOL SaveVoxelMaskData(LPCTSTR lpszPathName, BYTE*** pVoxelMaskData, int vd_x, int vd_y, int vd_z, int vd_sz, int vd_z1, int vd_z2)
{
	FILE* fp_data_mask;
	BYTE buf_data_mask[2048];
	int z1_r, z2_r;
	int j, k;

	fp_data_mask = fopen(lpszPathName, "wb");
	fwrite(&vd_x, sizeof(int), 1, fp_data_mask);
	fwrite(&vd_y, sizeof(int), 1, fp_data_mask);
	fwrite(&vd_z, sizeof(int), 1, fp_data_mask);

	// fill background seeds
	memset(buf_data_mask, 2, vd_x * sizeof(BYTE));

	z1_r = vd_z-1 - vd_z2;
	z2_r = vd_z-1 - vd_z1;

#ifndef _TIME_CHECK
	CGProgressBar Bar("Saving Voxel Data...", 100);
#endif

	for (k = 0; k < vd_z1; k++) {
		for (j = 0; j < vd_y; j++) {
			fwrite(buf_data_mask, sizeof(BYTE), vd_x, fp_data_mask);
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*k/vd_z);
#endif
	}
	for (k = vd_sz-1; k >= 0; k--) {
		for (j = 0; j < vd_y; j++) {
			fwrite(pVoxelMaskData[k][j], sizeof(BYTE), vd_x, fp_data_mask);
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*(vd_z1+vd_sz-1-k)/vd_z);
#endif
	}
	for (k = vd_z2+1; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			fwrite(buf_data_mask, sizeof(BYTE), vd_x, fp_data_mask);
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*k/vd_z);
#endif
	}

	fclose(fp_data_mask);

	return TRUE;
}
BOOL SaveVoxelData(LPCTSTR lpszPathName, short*** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_sz, int vd_z1, int vd_z2)
{
	FILE* fp_data;
	short buf_data_back[2048];
	short buf_data[2048];
	int z1_r, z2_r;
	int i, j, k;

	fp_data = fopen(lpszPathName, "wb");
	fwrite(&vd_x, sizeof(int), 1, fp_data);
	fwrite(&vd_y, sizeof(int), 1, fp_data);
	fwrite(&vd_z, sizeof(int), 1, fp_data);

	// fill background
	for (i = 0; i < vd_x; i++) {
		buf_data_back[i] = -1000;
	}

	z1_r = vd_z-1 - vd_z2;
	z2_r = vd_z-1 - vd_z1;

#ifndef _TIME_CHECK
	CGProgressBar Bar("Saving Voxel Data...", 100);
#endif

	for (k = 0; k < vd_z1; k++) {
		for (j = 0; j < vd_y; j++) {
			fwrite(buf_data_back, sizeof(short), vd_x, fp_data);
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*k/vd_z);
#endif
	}
	for (k = vd_sz-1; k >= 0; k--) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				buf_data[i] = pVoxelData[k][j][i];
			}
			fwrite(buf_data, sizeof(short), vd_x, fp_data);
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*(vd_z1+vd_sz-1-k)/vd_z);
#endif
	}
	for (k = vd_z2+1; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			fwrite(buf_data_back, sizeof(short), vd_x, fp_data);
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*k/vd_z);
#endif
	}

	fclose(fp_data);

	return TRUE;
}
BOOL LoadVoxelData(LPCTSTR lpszPathName, float**** pVoxelData, int& vd_x, int& vd_y, int& vd_z)
{
	int i, j, k;
	FILE* fp_data = NULL;
	float buf_data[2048];

	fp_data = fopen(lpszPathName, "rb");
	fread(&vd_x, sizeof(int), 1, fp_data);
	fread(&vd_y, sizeof(int), 1, fp_data);
	fread(&vd_z, sizeof(int), 1, fp_data);

#ifndef _TIME_CHECK
	CGProgressBar Bar("Loding Voxel Data...", 100);
#endif

	if (!AllocateVoxelData(pVoxelData, vd_x, vd_y, vd_z)) {
		return FALSE;
	}

	for (k = vd_z-1; k >= 0; k--) {
		for (j = 0; j < vd_y; j++) {
			fread(buf_data, sizeof(float), vd_x, fp_data);
			for (i = 0; i < vd_x; i++) {
				(*pVoxelData)[k][j][i] = buf_data[i];
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos((100*(vd_z-1-k))/vd_z);
#endif
	}

	if (fp_data) fclose(fp_data);

	return TRUE;
}
BOOL SaveVoxelData(LPCTSTR lpszPathName, float*** pVoxelData, int vd_x, int vd_y, int vd_z)
{
	FILE* fp_data;
	float buf_data[2048];
	int i, j, k;

	fp_data = fopen(lpszPathName, "wb");
	fwrite(&vd_x, sizeof(int), 1, fp_data);
	fwrite(&vd_y, sizeof(int), 1, fp_data);
	fwrite(&vd_z, sizeof(int), 1, fp_data);

#ifndef _TIME_CHECK
	CGProgressBar Bar("Saving Voxel Data...", 100);
#endif

	for (k = vd_z-1; k >= 0; k--) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				buf_data[i] = pVoxelData[k][j][i];
			}
			fwrite(buf_data, sizeof(float), vd_x, fp_data);
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*(vd_z-1-k)/vd_z);
#endif
	}

	fclose(fp_data);

	return TRUE;
}

BOOL LoadNIIDataSize(LPCTSTR lpszPathName, int& vd_x, int& vd_y, int& vd_z, int& vd_s, float& vd_dx, float& vd_dy, float& vd_dz, float& vd_ox, float& vd_oy, float& vd_oz)
{
	char fname[1024];
	char ext[1024];

	if (strlen(lpszPathName) < 6) {
		strcpy(fname, lpszPathName);
	} else {
		strncpy(ext, (char*)&lpszPathName[strlen(lpszPathName)-6], 6);
		ext[6] = 0;
		if (strcmp(ext, "nii.gz") != 0) {
			sprintf(fname, "%s.nii.gz", lpszPathName);
		} else {
			strcpy(fname, lpszPathName);
		}
	}

	/*
	{
		nifti_image* pNII;
		pNII = nifti_image_read(fname, 1);
		if (pNII == NULL) {
			return FALSE;
		}

		vd_x = pNII->nx;
		vd_y = pNII->ny;
		vd_z = pNII->nz;
		vd_s = pNII->nt;
		vd_dx = pNII->dx;
		vd_dy = pNII->dy;
		vd_dz = pNII->dz;
		vd_ox = pNII->qoffset_x;
		vd_oy = pNII->qoffset_y;
		vd_oz = pNII->qoffset_z;

		nifti_image_free(pNII);
	}
	/*/
	{
		nifti_1_header* pNIH;
		int swapped;
		pNIH = nifti_read_header(fname, &swapped, 1);
		if (pNIH == NULL) {
			return FALSE;
		}

		vd_x = pNIH->dim[1];
		vd_y = pNIH->dim[2];
		vd_z = pNIH->dim[3];
		vd_s = pNIH->dim[4];
		vd_dx = pNIH->pixdim[1];
		vd_dy = pNIH->pixdim[2];
		vd_dz = pNIH->pixdim[3];
		vd_ox = pNIH->qoffset_x;
		vd_oy = pNIH->qoffset_y;
		vd_oz = pNIH->qoffset_z;

		free(pNIH);
	}
	//*/

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BOOL ChangeNIIHeader(char* target_file, char* header_file)
{
	nifti_image* h_pNII;
	nifti_image* t_pNII;

	h_pNII = nifti_image_read(header_file, 1);
	if (h_pNII == NULL) {
		return FALSE;
	}

	t_pNII = nifti_image_read(target_file, 1);
	if (t_pNII == NULL) {
		return FALSE;
	}

#if 0
	int i, j, k, l;
	int vd_x, vd_y, vd_z, vd_s;

	vd_x = t_pNII->nx;
	vd_y = t_pNII->ny;
	vd_z = t_pNII->nz;
	vd_s = t_pNII->nt;

	if (vd_x != h_pNII->nx || vd_y != h_pNII->ny || vd_z != h_pNII->nz || vd_s != h_pNII->nt) {
		return FALSE;
	}
	if (t_pNII->nbyper != h_pNII->nbyper) {
		return FALSE;
	}
	if (t_pNII->datatype != h_pNII->datatype) {
		return FALSE;
	}
	
	if (t_pNII->nbyper == 1) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				for (i = 0; i < vd_x; i++) {
					BYTE* p = (BYTE*)t_pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
					BYTE* q = (BYTE*)h_pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
					for (l = 0; l < vd_s; l++) {
						*q++ = *p++;
					}
				}
			}
		}
	} else if (t_pNII->nbyper == 2) {
		if (t_pNII->datatype == DT_INT16) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						short* p = (short*)t_pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						short* q = (short*)h_pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							*q++ = *p++;
						}
					}
				}
			}
		} else {
		}
	} else if (t_pNII->nbyper == 4) {
		if (t_pNII->datatype == DT_FLOAT32) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						float* p = (float*)t_pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						float* q = (float*)h_pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							*q++ = *p++;
						}
					}
				}
			}
		} else {
		}
	} else {
	}

	h_pNII->nbyper = t_pNII->nbyper;
	h_pNII->datatype = t_pNII->datatype;

	free(h_pNII->fname);
	h_pNII->fname = (char*)malloc(1024 * sizeof(char));
	strcpy(h_pNII->fname, t_pNII->fname);

	free(h_pNII->iname);
	h_pNII->iname = (char*)malloc(1024 * sizeof(char));
	strcpy(h_pNII->iname, t_pNII->iname);

	nifti_image_write(h_pNII);
#endif
#if 1
	t_pNII->dx = h_pNII->dx;
	t_pNII->dy = h_pNII->dy;
	t_pNII->dz = h_pNII->dz;
	t_pNII->dt = h_pNII->dt;
	t_pNII->du = h_pNII->du;
	t_pNII->dv = h_pNII->dv;
	t_pNII->dw = h_pNII->dw;
	memcpy(t_pNII->pixdim, h_pNII->pixdim, 8*sizeof(float));

	t_pNII->scl_slope = h_pNII->scl_slope;
	t_pNII->scl_inter = h_pNII->scl_inter;
	t_pNII->cal_min = h_pNII->cal_min;
	t_pNII->cal_max = h_pNII->cal_max;
	t_pNII->qform_code = h_pNII->qform_code;
	t_pNII->sform_code = h_pNII->sform_code;
	t_pNII->freq_dim = h_pNII->freq_dim;
	t_pNII->phase_dim = h_pNII->phase_dim;
	t_pNII->slice_dim = h_pNII->slice_dim;
	t_pNII->slice_code = h_pNII->slice_code;
	t_pNII->slice_start = h_pNII->slice_start;
	t_pNII->slice_end = h_pNII->slice_end;
	t_pNII->slice_duration = h_pNII->slice_duration;

	t_pNII->quatern_b = h_pNII->quatern_b;
	t_pNII->quatern_c = h_pNII->quatern_c;
	t_pNII->quatern_d = h_pNII->quatern_d;
	t_pNII->qoffset_x = h_pNII->qoffset_x;
	t_pNII->qoffset_y = h_pNII->qoffset_y;
	t_pNII->qoffset_z = h_pNII->qoffset_z;
	t_pNII->qfac = h_pNII->qfac;

	t_pNII->slice_duration = h_pNII->slice_duration;

	t_pNII->qto_xyz.m[0][0] = h_pNII->qto_xyz.m[0][0];
	t_pNII->qto_xyz.m[0][1] = h_pNII->qto_xyz.m[0][1];
	t_pNII->qto_xyz.m[0][2] = h_pNII->qto_xyz.m[0][2];
	t_pNII->qto_xyz.m[0][3] = h_pNII->qto_xyz.m[0][3];
	t_pNII->qto_xyz.m[1][0] = h_pNII->qto_xyz.m[1][0];
	t_pNII->qto_xyz.m[1][1] = h_pNII->qto_xyz.m[1][1];
	t_pNII->qto_xyz.m[1][2] = h_pNII->qto_xyz.m[1][2];
	t_pNII->qto_xyz.m[1][3] = h_pNII->qto_xyz.m[1][3];
	t_pNII->qto_xyz.m[2][0] = h_pNII->qto_xyz.m[2][0];
	t_pNII->qto_xyz.m[2][1] = h_pNII->qto_xyz.m[2][1];
	t_pNII->qto_xyz.m[2][2] = h_pNII->qto_xyz.m[2][2];
	t_pNII->qto_xyz.m[2][3] = h_pNII->qto_xyz.m[2][3];
	t_pNII->qto_xyz.m[3][0] = h_pNII->qto_xyz.m[3][0];
	t_pNII->qto_xyz.m[3][1] = h_pNII->qto_xyz.m[3][1];
	t_pNII->qto_xyz.m[3][2] = h_pNII->qto_xyz.m[3][2];
	t_pNII->qto_xyz.m[3][3] = h_pNII->qto_xyz.m[3][3];

	t_pNII->qto_ijk.m[0][0] = h_pNII->qto_ijk.m[0][0];
	t_pNII->qto_ijk.m[0][1] = h_pNII->qto_ijk.m[0][1];
	t_pNII->qto_ijk.m[0][2] = h_pNII->qto_ijk.m[0][2];
	t_pNII->qto_ijk.m[0][3] = h_pNII->qto_ijk.m[0][3];
	t_pNII->qto_ijk.m[1][0] = h_pNII->qto_ijk.m[1][0];
	t_pNII->qto_ijk.m[1][1] = h_pNII->qto_ijk.m[1][1];
	t_pNII->qto_ijk.m[1][2] = h_pNII->qto_ijk.m[1][2];
	t_pNII->qto_ijk.m[1][3] = h_pNII->qto_ijk.m[1][3];
	t_pNII->qto_ijk.m[2][0] = h_pNII->qto_ijk.m[2][0];
	t_pNII->qto_ijk.m[2][1] = h_pNII->qto_ijk.m[2][1];
	t_pNII->qto_ijk.m[2][2] = h_pNII->qto_ijk.m[2][2];
	t_pNII->qto_ijk.m[2][3] = h_pNII->qto_ijk.m[2][3];
	t_pNII->qto_ijk.m[3][0] = h_pNII->qto_ijk.m[3][0];
	t_pNII->qto_ijk.m[3][1] = h_pNII->qto_ijk.m[3][1];
	t_pNII->qto_ijk.m[3][2] = h_pNII->qto_ijk.m[3][2];
	t_pNII->qto_ijk.m[3][3] = h_pNII->qto_ijk.m[3][3];

	t_pNII->sto_xyz.m[0][0] = h_pNII->sto_xyz.m[0][0];
	t_pNII->sto_xyz.m[0][1] = h_pNII->sto_xyz.m[0][1];
	t_pNII->sto_xyz.m[0][2] = h_pNII->sto_xyz.m[0][2];
	t_pNII->sto_xyz.m[0][3] = h_pNII->sto_xyz.m[0][3];
	t_pNII->sto_xyz.m[1][0] = h_pNII->sto_xyz.m[1][0];
	t_pNII->sto_xyz.m[1][1] = h_pNII->sto_xyz.m[1][1];
	t_pNII->sto_xyz.m[1][2] = h_pNII->sto_xyz.m[1][2];
	t_pNII->sto_xyz.m[1][3] = h_pNII->sto_xyz.m[1][3];
	t_pNII->sto_xyz.m[2][0] = h_pNII->sto_xyz.m[2][0];
	t_pNII->sto_xyz.m[2][1] = h_pNII->sto_xyz.m[2][1];
	t_pNII->sto_xyz.m[2][2] = h_pNII->sto_xyz.m[2][2];
	t_pNII->sto_xyz.m[2][3] = h_pNII->sto_xyz.m[2][3];
	t_pNII->sto_xyz.m[3][0] = h_pNII->sto_xyz.m[3][0];
	t_pNII->sto_xyz.m[3][1] = h_pNII->sto_xyz.m[3][1];
	t_pNII->sto_xyz.m[3][2] = h_pNII->sto_xyz.m[3][2];
	t_pNII->sto_xyz.m[3][3] = h_pNII->sto_xyz.m[3][3];

	t_pNII->sto_ijk.m[0][0] = h_pNII->sto_ijk.m[0][0];
	t_pNII->sto_ijk.m[0][1] = h_pNII->sto_ijk.m[0][1];
	t_pNII->sto_ijk.m[0][2] = h_pNII->sto_ijk.m[0][2];
	t_pNII->sto_ijk.m[0][3] = h_pNII->sto_ijk.m[0][3];
	t_pNII->sto_ijk.m[1][0] = h_pNII->sto_ijk.m[1][0];
	t_pNII->sto_ijk.m[1][1] = h_pNII->sto_ijk.m[1][1];
	t_pNII->sto_ijk.m[1][2] = h_pNII->sto_ijk.m[1][2];
	t_pNII->sto_ijk.m[1][3] = h_pNII->sto_ijk.m[1][3];
	t_pNII->sto_ijk.m[2][0] = h_pNII->sto_ijk.m[2][0];
	t_pNII->sto_ijk.m[2][1] = h_pNII->sto_ijk.m[2][1];
	t_pNII->sto_ijk.m[2][2] = h_pNII->sto_ijk.m[2][2];
	t_pNII->sto_ijk.m[2][3] = h_pNII->sto_ijk.m[2][3];
	t_pNII->sto_ijk.m[3][0] = h_pNII->sto_ijk.m[3][0];
	t_pNII->sto_ijk.m[3][1] = h_pNII->sto_ijk.m[3][1];
	t_pNII->sto_ijk.m[3][2] = h_pNII->sto_ijk.m[3][2];
	t_pNII->sto_ijk.m[3][3] = h_pNII->sto_ijk.m[3][3];

	t_pNII->toffset = h_pNII->toffset;

	t_pNII->xyz_units = h_pNII->xyz_units;
	t_pNII->time_units = h_pNII->time_units;

	t_pNII->nifti_type = h_pNII->nifti_type;

	t_pNII->intent_code = h_pNII->intent_code;
	t_pNII->intent_p1 = h_pNII->intent_p1;
	t_pNII->intent_p2 = h_pNII->intent_p2;
	t_pNII->intent_p3 = h_pNII->intent_p3;
	memcpy(t_pNII->intent_name, h_pNII->intent_name, 16*sizeof(char));
	memcpy(t_pNII->descrip, h_pNII->descrip, 80*sizeof(char));
	memcpy(t_pNII->aux_file, h_pNII->aux_file, 24*sizeof(char));

	t_pNII->analyze75_orient = h_pNII->analyze75_orient;

	nifti_image_write(t_pNII);
#endif

	nifti_image_free(h_pNII);
	nifti_image_free(t_pNII);

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BOOL ReadXFMData(LPCTSTR xfm_name, float a[4][4])
{
	FILE* fp;
	
	fp = fopen(xfm_name, "r");
	if (fp == NULL) {
		return FALSE;
	}

	fscanf(fp, "%f %f %f %f", &a[0][0], &a[0][1], &a[0][2], &a[0][3]);
	fscanf(fp, "%f %f %f %f", &a[1][0], &a[1][1], &a[1][2], &a[1][3]);
	fscanf(fp, "%f %f %f %f", &a[2][0], &a[2][1], &a[2][2], &a[2][3]);
	fscanf(fp, "%f %f %f %f", &a[3][0], &a[3][1], &a[3][2], &a[3][3]);

	fclose(fp);
	
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#ifdef USE_METAIO
BOOL CopyMHDData(LPCTSTR in_img_name, LPCTSTR in_hdr_name, LPCTSTR out_img_name, LPCTSTR out_hdr_name, bool bEraseOffset)
{
	char tmp_name[1024], img_name[1024];
	MetaImage* pMI = NULL;

	pMI = new MetaImage(in_hdr_name);
	if (pMI->ElementData() == NULL) {
		return FALSE;
	}

	pMI->CompressedData(true);
	
	if (bEraseOffset) {
		pMI->Offset(0, 0);
		pMI->Offset(1, 0);
		pMI->Offset(2, 0);
	}

	if (out_img_name == NULL) {
		str_strip_ext((char*)out_hdr_name, tmp_name);
		sprintf(img_name, "%s.zraw", tmp_name);
	} else {
		sprintf(img_name, "%s", out_img_name);
	}

	if (!pMI->Write(out_hdr_name, img_name)) {
		delete pMI;
		return FALSE;
	}

	delete pMI;
	return TRUE;
}
#endif
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#if !defined(WIN32) && !defined(WIN64)
BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists)
{
#if 0
	int src;               // file descriptor for source file
	int dest;              // file descriptor for destination file
	struct stat stat_buf;  // hold information about input file
	off_t offset = 0;      // byte offset used by sendfile
	int result;

	// check that source file exists and can be opened
	if ((src = open(lpExistingFileName, O_RDONLY)) == -1) {
		TRACE("src open error: %s\n", lpExistingFileName);
		return FALSE;
	}

	// get size and permissions of the source file
	fstat(src, &stat_buf);

	// open destination file
	if (bFailIfExists) {
		if ((dest = open(lpNewFileName, O_RDONLY)) != -1) {
			TRACE("dest exists: %s\n", lpNewFileName);
			close(src);
			close(dest);
			return FALSE;
		}
	}
	if ((dest = open(lpNewFileName, O_WRONLY | O_CREAT, stat_buf.st_mode)) == -1) {
		TRACE("dest open error: %s\n", lpNewFileName);
		close(src);
		return FALSE;
	}
	
	// copy file using sendfile
	result = sendfile(dest, src, &offset, stat_buf.st_size);

	// clean up and exit
	close(src);
	close(dest);

	if (result == -1) {
		TRACE("sendfile error\n");
		return FALSE;
	} else {
		return TRUE;
	}
#else
	int src;
	int dest;
	struct stat stat_buf;
	char buf[8192];

	src = open(lpExistingFileName, O_RDONLY);
	if (src < 0) {
		TRACE("src open error: %s\n", lpExistingFileName);
		return FALSE;
	}

	// get size and permissions of the source file
	fstat(src, &stat_buf);

	if (bFailIfExists) {
		dest = open(lpNewFileName, O_RDONLY);
		if (dest >= 0) {
			TRACE("dest exists: %s\n", lpNewFileName);
			close(src);
			close(dest);
			return FALSE;
		}
	}
	dest = open(lpNewFileName, O_WRONLY | O_CREAT, stat_buf.st_mode);
	if (dest < 0) {
		TRACE("dest open error: %s\n", lpNewFileName);
		close(src);
		return FALSE;
	}

	while (1) {
		ssize_t result = read(src, &buf[0], sizeof(buf));
		if (!result) break;
		if (result < 0) {
			TRACE("src read error = %d\n", result);
			close(src);
			close(dest);
			return FALSE;
		}
		if (write(dest, &buf[0], result) != result) {
			TRACE("dest write error\n");
			close(src);
			close(dest);
			return FALSE;
		}
	}

	close(src);
	close(dest);
	return TRUE;
#endif
}

BOOL CreateDirectory(LPCTSTR lpPathName, void* lpSecurityAttributes)
{
	int result;

	result = mkdir(lpPathName, 0777);

	if (result == -1) {
		//TRACE("mkdir error\n");
		return FALSE;
	} else {
		return TRUE;
	}
}

BOOL SetCurrentDirectory(LPCTSTR lpPathName)
{
	int result;
	//char buf[1024];

	//getcwd(buf, 1024);
	//TRACE("cwd = %s\n", buf);

	result = chdir(lpPathName);
	//TRACE("chdir returned %d\n", result);

	//getcwd(buf, 1024);
	//TRACE("cwd = %s\n", buf);

	if (result == -1) {
		TRACE("chdir error\n");
		return FALSE;
	} else {
		return TRUE;
	}
}

BOOL DeleteFile(LPCTSTR lpFileName)
{
	int result;

	result = remove(lpFileName);

	if (result == -1) {
		TRACE("remove error\n");
		return FALSE;
	} else {
		return TRUE;
	}
}
#endif

void DeleteAll(char* sFolder, BOOL bDeleteFolderToo)
{
#if defined(WIN32) || defined(WIN64)
	// Declare variables
	WIN32_FIND_DATA wfd;
	HANDLE hFile;
	DWORD dwFileAttr;
	char sFile[1024];
	char sSpec[1024];
	char sPathFile[1024];

	sprintf(sSpec, "%s\\*.*", sFolder);

	// Find the first file
	hFile = FindFirstFile(sSpec, &wfd);
	if (hFile != INVALID_HANDLE_VALUE) {
		do {
			sprintf(sFile, "%s",  wfd.cFileName);
			sprintf(sPathFile, "%s\\%s", sFolder, wfd.cFileName);

			// Get the file attributes
			dwFileAttr = GetFileAttributes(sPathFile);

			// See if file is read-only : if so unset read-only
			if (dwFileAttr & FILE_ATTRIBUTE_READONLY) {
				dwFileAttr &= ~FILE_ATTRIBUTE_READONLY;
				SetFileAttributes(sPathFile, dwFileAttr);
			}

			// See if the file is a directory
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// Make sure it isn't current or parent directory
				if (strcmp(sFile, ".") != 0 && strcmp(sFile, "..") != 0) {
					// Recursively delete all files in this folder
					DeleteAll(sPathFile, TRUE);

					// Remove the directory
					//RemoveDirectory(sPathFile);
				}
			} else {
				// Delete the file
				DeleteFile(sPathFile);
			}
		}
		while (FindNextFile(hFile, &wfd));
	}

	// Close handle to file
	FindClose(hFile);

	// Delete directory too if needed
	if (bDeleteFolderToo) {
		RemoveDirectory(sFolder);
	}
#else
	DIR *dir;
	struct dirent *entry;
	char sFile[1024];
	char sPathFile[1024];

	if (!(dir = opendir(sFolder))) {
		//TRACE("opendir error\n");
		return;
	}
	if (!(entry = readdir(dir))) {
		//TRACE("readdir error\n");
		return;
	}

	do {
		sprintf(sFile, "%s",  entry->d_name);
		sprintf(sPathFile, "%s/%s", sFolder, entry->d_name);

		if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				DeleteAll(sPathFile, TRUE);
			}
		} else {
			DeleteFile(sPathFile);
		}
	} while ((entry = readdir(dir)));

	closedir(dir);

	if (bDeleteFolderToo) {
		rmdir(sFolder);
	}
#endif
}
void DeleteFiles(char* sFolder, const char* sPattern, BOOL bSubDir)
{
#if defined(WIN32) || defined(WIN64)
	// Declare variables
	WIN32_FIND_DATA wfd;
	HANDLE hFile;
	DWORD dwFileAttr;
	char sFile[1024];
	char sSpec[1024];
	char sPathFile[1024];

	sprintf(sSpec, "%s\\%s", sFolder, sPattern);

	// Find the first file
	hFile = FindFirstFile(sSpec, &wfd);
	if (hFile != INVALID_HANDLE_VALUE) {
		do {
			sprintf(sFile, "%s",  wfd.cFileName);
			sprintf(sPathFile, "%s\\%s", sFolder, wfd.cFileName);

			// Get the file attributes
			dwFileAttr = GetFileAttributes(sPathFile);

			// See if file is read-only : if so unset read-only
			if (dwFileAttr & FILE_ATTRIBUTE_READONLY) {
				dwFileAttr &= ~FILE_ATTRIBUTE_READONLY;
				SetFileAttributes(sPathFile, dwFileAttr);
			}

			// See if the file is a directory
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// Make sure it isn't current or parent directory
				if (strcmp(sFile, ".") != 0 && strcmp(sFile, "..") != 0) {
					// Recursively delete all files in this folder
					if (bSubDir) {
						DeleteFiles(sPathFile, sPattern, TRUE);
					}
				}
			} else {
				// Delete the file
				DeleteFile(sPathFile);
			}
		}
		while (FindNextFile(hFile, &wfd));
	}

	// Close handle to file
	FindClose(hFile);
#else
	DIR *dir;
	struct dirent *entry;
	char sFile[1024];
	char sPathFile[1024];

	if (!(dir = opendir(sFolder))) {
		return;
	}
	if (!(entry = readdir(dir))) {
		return;
	}

	do {
		sprintf(sFile, "%s",  entry->d_name);
		sprintf(sPathFile, "%s/%s", sFolder, entry->d_name);

		if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				if (bSubDir) {
					DeleteFiles(sPathFile, sPattern, TRUE);
				}
			}
		} else {
			if (fnmatch(sPattern, entry->d_name, FNM_CASEFOLD) == 0) {
				DeleteFile(sPathFile);
			}
		}
	} while ((entry = readdir(dir)));

	closedir(dir);
#endif
}
void DeleteSubDirs(char* sFolder, const char* sPattern)
{
#if defined(WIN32) || defined(WIN64)
	// Declare variables
	WIN32_FIND_DATA wfd;
	HANDLE hFile;
	char sFile[1024];
	char sSpec[1024];
	char sPathFile[1024];

	sprintf(sSpec, "%s\\%s", sFolder, sPattern);

	// Find the first file
	hFile = FindFirstFile(sSpec, &wfd);
	if (hFile != INVALID_HANDLE_VALUE) {
		do {
			sprintf(sFile, "%s",  wfd.cFileName);
			sprintf(sPathFile, "%s\\%s", sFolder, wfd.cFileName);

			// See if the file is a directory
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// Make sure it isn't current or parent directory
				if (strcmp(sFile, ".") != 0 && strcmp(sFile, "..") != 0) {
					DeleteAll(sPathFile, TRUE);
				}
			}
		}
		while (FindNextFile(hFile, &wfd));
	}

	// Close handle to file
	FindClose(hFile);
#else
	DIR *dir;
	struct dirent *entry;
	char sFile[1024];
	char sPathFile[1024];

	if (!(dir = opendir(sFolder))) {
		return;
	}
	if (!(entry = readdir(dir))) {
		return;
	}

	do {
		sprintf(sFile, "%s",  entry->d_name);
		sprintf(sPathFile, "%s/%s", sFolder, entry->d_name);

		if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				if (fnmatch(sPattern, entry->d_name, FNM_CASEFOLD) == 0) {
					DeleteAll(sPathFile, TRUE);
				}
			}
		}
	} while ((entry = readdir(dir)));

	closedir(dir);
#endif
}
#if defined(WIN32) || defined(WIN64)
BOOL GetModulePath(char* sPath)
{
	char sBuf[1024];
	int res;
	res = GetModuleFileName(NULL, sBuf, 1024);
	if (res > 0) {
		//printf("%s\n", sBuf);
		str_strip_file(sBuf, sPath);
		return TRUE;
	} else  {
		sPath[0] = 0;
		return FALSE;
	}
}
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
BOOL GetModulePath(char* sPath)
{
	char sBuf[1024];
	uint32_t size = 1024;
	if (_NSGetExecutablePath(sBuf, &size) == 0) {
		sBuf[size] = 0;
		//printf("%s\n", sBuf);
		str_strip_file(sBuf, sPath);
		return TRUE;
	} else {
		sPath[0] = 0;
		return FALSE;
	}
}
#else
BOOL GetModulePath(char* sPath)
{
	char sBuf[1024];
	int res;
	// caution: readlink() does not append a null byte
	res = readlink("/proc/self/exe", sBuf, 1024);
	if (res > 0) {
		sBuf[res] = 0;
		//printf("%s\n", sBuf);
		str_strip_file(sBuf, sPath);
		return TRUE;
	} else  {
		sPath[0] = 0;
		return FALSE;
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void MySleep(int tick)
{
#if defined(WIN32) || defined(WIN64)
	Sleep(tick);
#else
	long t1 = clock(), t2;
	do
	{
		t2 = clock();
	} while(((float)(t2 - t1) / CLOCKS_PER_SEC) < (float)tick/1000.0f);
#endif
}  
