///////////////////////////////////////////////////////////////////////////////////////
// MyUtils.h
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

#ifndef MYUTILS_H
#define MYUTILS_H


#include "stdafx.h"

#ifdef VIPL
#include "vipimgtempl.h"
#include "VipWndTools.h"
#endif
//
#include "nifti1_io.h"
#ifdef USE_METAIO
#include "metaImage.h"
#endif


#define MEM_CHUNK
#define _TIME_CHECK
#define USE_MESSAGEBOX
#define AfxMessageBox TRACE


#define ROUND(t)			((t) < 0 ? (int) ((t)-0.5f) : (int) ((t)+0.5f))
#define CLAMP(a, l, h)		((a) < (l) ? (l) : (a) > (h) ? (h) : (a))


void* MyAlloc(size_t size);
void* MyAllocEx(size_t size, LPCTSTR str_info);
void* MyCAllocEx(size_t num, size_t size, LPCTSTR str_info);
void MyFree(void* ptr);

//#ifdef USE_MESSAGEBOX
#if 0
BOOL GetFileNameDialog(char *type_name, char *type, CString *path_name, CString *file_name);
BOOL GetFileNameDialog(char *type_name, char *type, CString *init_name, CString *path_name, CString *file_name, BOOL bOpenFileDialog);
#endif

void str_strip_path(char* str_path_file, char* str_file);
void str_strip_file(char* str_path_file, char* str_path);
void str_strip_file2(char* str_file_ext, char* str_ext);
void str_strip_ext(char* str_file_ext, char* str_file);
void str_strip_ext_all(char* str_file_ext, char* str_file);
void str_strip_footer(char* str_file_footer, char* str_file);
void str_divide_header(char* str_header_file, char* str_file, char* str_header, char delim);
void str_divide_footer(char* str_file_footer, char* str_file, char* str_footer, char delim);


#ifdef USE_DOEVENTS
void DoEvents();
#endif

BOOL IsFileExist(char* file_name);
BOOL ExecuteProcess(char* szCmdLine);
BOOL IsExecutableExistInPath(const char* executable_name, char* path_name = NULL);
BOOL FindExecutableInPath(const char* executable_name, char* module_path, char* path_name = NULL);


#ifdef VIPL
void GetImage(BYTE** ImageData, int id_x, int id_y, ByteImage& image);
void GetImageData(ByteImage& image, BYTE** ImageData, int id_x, int id_y);
#endif
void SetImageData(BYTE** ImageData, int id_x, int id_y, BYTE value);

BOOL AllocateImageData(BYTE*** pImageData, int id_x, int id_y, BOOL fill_zero = TRUE);
BOOL AllocateImageData(float*** pImageData, int id_x, int id_y, BOOL fill_zero = TRUE);
BOOL AllocateImageData(double*** pImageData, int id_x, int id_y, BOOL fill_zero = TRUE);
BOOL AllocateImageData(int*** pImageData, int id_x, int id_y, BOOL fill_zero = TRUE);
void FreeImageData(BYTE*** pImageData, int id_x, int id_y);
void FreeImageData(float*** pImageData, int id_x, int id_y);
void FreeImageData(double*** pImageData, int id_x, int id_y);
void FreeImageData(int*** pImageData, int id_x, int id_y);
void CopyImageData(BYTE** ImageData1, int id1_x, int id1_y, BYTE** ImageData2, int id2_x, int id2_y);
void CopyImageDataHalf(BYTE** ImageData1, int id1_x, int id1_y, BYTE** ImageData2, int id2_x, int id2_y);
BOOL LoadImageData(LPCTSTR lpszPathName, float*** pImageData, int& id_x, int& id_y);
BOOL SaveImageData(LPCTSTR lpszPathName, float** pImageData, int id_x, int id_y);
BOOL SaveImageData(LPCTSTR lpszPathName, double** pImageData, int id_x, int id_y);
BOOL LoadImageData(LPCTSTR lpszPathName, int*** pImageData, int& id_x, int& id_y);
BOOL SaveImageData(LPCTSTR lpszPathName, int** pImageData, int id_x, int id_y);
#ifdef VIPL
#ifndef WIN64
BOOL LoadImageData(LPCTSTR lpszPathName, ByteImage& image, BYTE*** pImageMaskData, int& id_x, int& id_y, BOOL bShowDialog = FALSE);
#endif
#endif
BOOL SaveImageData(LPCTSTR lpszPathName, BYTE** pImageData, int id_x, int id_y);
BOOL LoadImageData(LPCTSTR lpszPathName, double** pImageData, int& id_x, int& id_y);
BOOL SaveImageData(LPCTSTR lpszPathName, double* pImageData, int id_x, int id_y);


BOOL AllocateVoxelData(BYTE**** pVoxelData, int vd_x, int vd_y, int vd_z, BOOL fill_zero = FALSE);
BOOL AllocateVoxelData(short**** pVoxelData, int vd_x, int vd_y, int vd_z, BOOL init = FALSE, short init_value = 0);
BOOL AllocateVoxelData(float**** pVoxelData, int vd_x, int vd_y, int vd_z, BOOL fill_zero = FALSE);
void FreeVoxelData(BYTE**** pVoxelData, int vd_x, int vd_y, int vd_z);
void FreeVoxelData(short**** pVoxelData, int vd_x, int vd_y, int vd_z);
void FreeVoxelData(float**** pVoxelData, int vd_x, int vd_y, int vd_z);
BOOL LoadVoxelData(LPCTSTR lpszPathName, short**** pVoxelData, BYTE**** pVoxelMaskData, int& vd_x, int& vd_y, int& vd_z, int& vd_sz, int& vd_z1, int& vd_z2, BOOL bShowDialog);
BOOL LoadVoxelData(LPCTSTR lpszPathName, float**** pVoxelData, int& vd_x, int& vd_y, int& vd_z);
BOOL SaveVoxelMaskData(LPCTSTR lpszPathName, BYTE*** pVoxelMaskData, int vd_x, int vd_y, int vd_z, int vd_sz, int vd_z1, int vd_z2);
BOOL SaveVoxelData(LPCTSTR lpszPathName, short*** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_sz, int vd_z1, int vd_z2);
BOOL LoadVoxelData(LPCTSTR lpszPathName, float**** pVoxelData, int& vd_x, int& vd_y, int& vd_z);
BOOL SaveVoxelData(LPCTSTR lpszPathName, float*** pVoxelData, int vd_x, int vd_y, int vd_z);

template <class T>
BOOL AllocateVoxelData(T***** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s, BOOL fill_zero = FALSE);
template <class T>
void FreeVoxelData(T***** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s);
//
template <class T>
BOOL LoadVoxelData(LPCTSTR lpszPathName, T***** pVoxelData, int& vd_x, int& vd_y, int& vd_z, int& vd_s);
template <class T>
BOOL SaveVoxelData(LPCTSTR lpszPathName, T**** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s);
//
BOOL LoadNIIDataSize(LPCTSTR lpszPathName, int& vd_x, int& vd_y, int& vd_z, int& vd_s, float& vd_dx, float& vd_dy, float& vd_dz, float& vd_ox, float& vd_oy, float& vd_oz);
template <class T>
BOOL LoadNIIData(LPCTSTR lpszPathName, T***** pVoxelData, int& vd_x, int& vd_y, int& vd_z, int& vd_s, float& vd_dx, float& vd_dy, float& vd_dz, float& vd_ox, float& vd_oy, float& vd_oz, analyze_75_orient_code& vd_oc);
template <class T>
BOOL SaveNIIData(LPCTSTR lpszPathName, T**** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s, float vd_dx, float vd_dy, float vd_dz, float vd_ox, float vd_oy, float vd_oz, analyze_75_orient_code vd_oc);
//
template <class T>
BOOL LoadIMGData(LPCTSTR img_name, LPCTSTR hdr_name, T***** pVoxelData, int& vd_x, int& vd_y, int& vd_z, int& vd_s, float& vd_dx, float& vd_dy, float& vd_dz, analyze_75_orient_code& vd_oc);
template <class T>
BOOL SaveIMGData(LPCTSTR img_name, LPCTSTR hdr_name, T**** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s, float vd_dx, float vd_dy, float vd_dz, analyze_75_orient_code vd_oc);
//
BOOL ChangeNIIHeader(char* target_file, char* header_file);
//
BOOL ReadXFMData(LPCTSTR xfm_name, float a[4][4]);
//
#ifdef USE_METAIO
template <class T>
BOOL LoadMHDData(LPCTSTR img_name, LPCTSTR hdr_name, T***** pVoxelData, int& vd_x, int& vd_y, int& vd_z, int& vd_s, float& vd_dx, float& vd_dy, float& vd_dz,
	float& vd_ox, float& vd_oy, float& vd_oz);
template <class T>
BOOL SaveMHDData(LPCTSTR img_name, LPCTSTR hdr_name, T**** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s, float vd_dx, float vd_dy, float vd_dz,
	float vd_ox, float vd_oy, float vd_oz);
template <class T>
BOOL LoadMHDData(LPCTSTR img_name, LPCTSTR hdr_name, T**** vx_data, T**** vy_data, T**** vz_data, int& vd_x, int& vd_y, int& vd_z, float& vd_dx, float& vd_dy, float& vd_dz,
	float& vd_ox, float& vd_oy, float& vd_oz);
template <class T>
BOOL SaveMHDData(LPCTSTR img_name, LPCTSTR hdr_name, T**** vx_data, T**** vy_data, T**** vz_data, int vd_x, int vd_y, int vd_z, float vd_dx, float vd_dy, float vd_dz,
	float vd_ox, float vd_oy, float vd_oz);
BOOL CopyMHDData(LPCTSTR in_img_name, LPCTSTR in_hdr_name, LPCTSTR out_img_name, LPCTSTR out_hdr_name, bool bEraseOffset = false);
#endif


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
template <class T>
BOOL AllocateVoxelData(T***** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s, BOOL fill_zero)
{
	if (*pVoxelData != NULL) {
		FreeVoxelData(pVoxelData, vd_x, vd_y, vd_z, vd_s);
	}
	int i, j, k;
#ifndef MEM_CHUNK
	if (!fill_zero) {
		*pVoxelData = (T****)MyAllocEx(vd_z*sizeof(T***), "AllocateVoxelData");
		for (k = 0; k < vd_z; k++) {
			(*pVoxelData)[k] = (T***)MyAllocEx(vd_y*sizeof(T**), "AllocateVoxelData");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (T**)MyCAllocEx(vd_x, sizeof(T*), "AllocateVoxelData");
				for (i = 0; i < vd_x; i++) {
					(*pVoxelData)[k][j][i] = (T*)MyCAllocEx(vd_s, sizeof(T), "AllocateVoxelData");
				}
			}
		}
	} else {
		*pVoxelData = (T****)MyAllocEx(vd_z*sizeof(T***), "AllocateVoxelData");
		for (k = 0; k < vd_z; k++) {
			(*pVoxelData)[k] = (T***)MyAllocEx(vd_y*sizeof(T**), "AllocateVoxelData");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (T**)MyCAllocEx(vd_x, sizeof(T*), "AllocateVoxelData");
				for (i = 0; i < vd_x; i++) {
					(*pVoxelData)[k][j][i] = (T*)MyCAllocEx(vd_s, sizeof(T), "AllocateVoxelData");
					memset((*pVoxelData)[k][j][i], 0, vd_s * sizeof(T));
				}
			}
		}
	}
#else
	if (!fill_zero) {
		*pVoxelData = (T****)MyAllocEx(vd_z*sizeof(T***), "AllocateVoxelData");
		for (k = 0; k < vd_z; k++) {
			T* mem_chunk = (T*)MyAllocEx(vd_x*vd_y*vd_s*sizeof(T), "AllocateVoxelData mem_chunk");
			(*pVoxelData)[k] = (T***)MyAllocEx(vd_y*sizeof(T**), "AllocateVoxelData");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (T**)MyCAllocEx(vd_x, sizeof(T*), "AllocateVoxelData");
				for (i = 0; i < vd_x; i++) {
					(*pVoxelData)[k][j][i] = &mem_chunk[(j*vd_x+i)*vd_s];
				}
			}
		}
	} else {
		*pVoxelData = (T****)MyAllocEx(vd_z*sizeof(T***), "AllocateVoxelData");
		for (k = 0; k < vd_z; k++) {
			T* mem_chunk = (T*)MyAllocEx(vd_x*vd_y*vd_s*sizeof(T), "AllocateVoxelData mem_chunk");
			memset(mem_chunk, 0, vd_x*vd_y*vd_s*sizeof(T));
			(*pVoxelData)[k] = (T***)MyAllocEx(vd_y*sizeof(T**), "AllocateVoxelData");
			for (j = 0; j < vd_y; j++) {
				(*pVoxelData)[k][j] = (T**)MyCAllocEx(vd_x, sizeof(T*), "AllocateVoxelData");
				for (i = 0; i < vd_x; i++) {
					(*pVoxelData)[k][j][i] = &mem_chunk[(j*vd_x+i)*vd_s];
				}
			}
		}
	}
#endif
	return TRUE;
}

template <class T>
void FreeVoxelData(T***** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s)
{
	int i, j, k;
#ifndef MEM_CHUNK
	if (*pVoxelData) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				for (i = 0; i < vd_x; i++) {
					MyFree((*pVoxelData)[k][j][i]);
					(*pVoxelData)[k][j][i] = NULL;
				}
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
			MyFree((*pVoxelData)[k][0][0]);
			for (j = 0; j < vd_y; j++) {
				for (i = 0; i < vd_x; i++) {
					(*pVoxelData)[k][j][i] = NULL;
				}
				MyFree((*pVoxelData)[k][j]);
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

template <class T>
BOOL LoadVoxelData(LPCTSTR lpszPathName, T***** pVoxelData, int& vd_x, int& vd_y, int& vd_z, int& vd_s)
{
	int i, j, k, s;
	FILE* fp_data = NULL;
	T buf_data[2048];

	fp_data = fopen(lpszPathName, "rb");
	fread(&vd_x, sizeof(int), 1, fp_data);
	fread(&vd_y, sizeof(int), 1, fp_data);
	fread(&vd_z, sizeof(int), 1, fp_data);
	fread(&vd_s, sizeof(int), 1, fp_data);

#ifndef _TIME_CHECK
	CGProgressBar Bar("Loding Voxel Data...", 100);
#endif

	if (!AllocateVoxelData(pVoxelData, vd_x, vd_y, vd_z, vd_s)) {
		return FALSE;
	}

	for (k = vd_z-1; k >= 0; k--) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				fread(buf_data, sizeof(T), vd_s, fp_data);
				for (s = 0; s < vd_s; s++) {
					(*pVoxelData)[k][j][i][s] = buf_data[s];
				}
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos((100*(vd_z-1-k))/vd_z);
#endif
	}

	if (fp_data) fclose(fp_data);

	return TRUE;
}

template <class T>
BOOL SaveVoxelData(LPCTSTR lpszPathName, T**** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s)
{
	FILE* fp_data;
	T buf_data[2048];
	int i, j, k, s;

	fp_data = fopen(lpszPathName, "wb");
	fwrite(&vd_x, sizeof(int), 1, fp_data);
	fwrite(&vd_y, sizeof(int), 1, fp_data);
	fwrite(&vd_z, sizeof(int), 1, fp_data);
	fwrite(&vd_s, sizeof(int), 1, fp_data);

#ifndef _TIME_CHECK
	CGProgressBar Bar("Saving Voxel Data...", 100);
#endif

	for (k = vd_z-1; k >= 0; k--) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				for (s = 0; s < vd_s; s++) {
					buf_data[s] = pVoxelData[k][j][i][s];
				}
				fwrite(buf_data, sizeof(T), vd_s, fp_data);
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*(vd_z-1-k)/vd_z);
#endif
	}

	fclose(fp_data);

	return TRUE;
}

template <class T>
BOOL LoadNIIData(LPCTSTR lpszPathName, T***** pVoxelData, int& vd_x, int& vd_y, int& vd_z, int& vd_s, float& vd_dx, float& vd_dy, float& vd_dz, float& vd_ox, float& vd_oy, float& vd_oz, analyze_75_orient_code& vd_oc)
{
	nifti_image* pNII;
	int i, j, k, l;
	BOOL bRes = FALSE;
	char fname[1024];
	char ext[1024];
	int icod, jcod, kcod;
	int si, sj, sk;

	if (strlen(lpszPathName) < 6) {
		strcpy(fname, lpszPathName);
	} else {
		strncpy(ext, (char*)&lpszPathName[strlen(lpszPathName)-3], 3);
		ext[3] = 0;
		if (strcmp(ext, "img") != 0 && strcmp(ext, "hdr") != 0) {
			strncpy(ext, (char*)&lpszPathName[strlen(lpszPathName)-6], 6);
			ext[6] = 0;
			if (strcmp(ext, "nii.gz") != 0) {
				sprintf(fname, "%s.nii.gz", lpszPathName);
			} else {
				strcpy(fname, lpszPathName);
			}
		} else {
			strcpy(fname, lpszPathName);
		}
	}

	pNII = nifti_image_read(fname, 1);
	if (pNII == NULL) {
		return FALSE;
	}

	vd_x = pNII->nx;
	vd_y = pNII->ny;
	vd_z = pNII->nz;
	if (pNII->nt > 1 || pNII->nu <= 1) {
		vd_s = pNII->nt;
	} else if (pNII->nt <= 1 || pNII->nu > 1) {
		vd_s = pNII->nu;
	} else {
		vd_s = 1;
	}
	vd_dx = pNII->dx;
	vd_dy = pNII->dy;
	vd_dz = pNII->dz;
	vd_ox = pNII->qoffset_x;
	vd_oy = pNII->qoffset_y;
	vd_oz = pNII->qoffset_z;
	vd_oc = pNII->analyze75_orient;
	//
#ifndef USE_ASSUME_LPS
	nifti_mat44_to_orientation(pNII->qto_ijk, &icod, &jcod, &kcod);
	if (icod == NIFTI_R2L) {
		si = 0;
	} else {
		si = 1;
	}
	if (jcod == NIFTI_A2P) {
		sj = 0;
	} else {
		sj = 1;
	}
	if (kcod == NIFTI_I2S) {
		sk = 0;
	} else {
		sk = 1;
	}
#else
	si = sj = sk = 0;
#endif
	//
	if (!AllocateVoxelData(pVoxelData, vd_x, vd_y, vd_z, vd_s)) {
		return FALSE;
	}
	//
	if (pNII->nbyper == 1) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				for (i = 0; i < vd_x; i++) {
					BYTE* p = (BYTE*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
					for (l = 0; l < vd_s; l++) {
						(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = (T)*p++;
					}
				}
			}
		}
	} else if (pNII->nbyper == 2) {
		if (pNII->datatype == DT_INT16) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						short* p = (short*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = (T)*p++;
						}
					}
				}
			}
		} else if (pNII->datatype == DT_UINT16) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						unsigned short* p = (unsigned short*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = (T)*p++;
						}
					}
				}
			}
		} else {
#ifdef USE_MESSAGEBOX
			AfxMessageBox("Error: m_pNII->datatype is unsupported.");
#endif
			goto errret;
		}
	} else if (pNII->nbyper == 4) {
		if (pNII->datatype == DT_FLOAT32) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						float* p = (float*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = (T)*p++;
						}
					}
				}
			}
		} else if (pNII->datatype == DT_INT32) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						int* p = (int*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = (T)*p++;
						}
					}
				}
			}
		} else {
#ifdef USE_MESSAGEBOX
			AfxMessageBox("Error: m_pNII->datatype is unsupported.");
#endif
			goto errret;
		}
	} else if (pNII->nbyper == 8) {
		if (pNII->datatype == DT_FLOAT64) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						double* p = (double*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = (T)*p++;
						}
					}
				}
			}
		} else {
#ifdef USE_MESSAGEBOX
			AfxMessageBox("Error: m_pNII->datatype is unsupported.");
#endif
			goto errret;
		}
	} else {
#ifdef USE_MESSAGEBOX
		AfxMessageBox("Error: m_pNII->nbyper is unsupported.");
#endif
		goto errret;
	}

	bRes = TRUE;

errret:
	nifti_image_free(pNII);

	return bRes;
}

template <class T>
BOOL LoadNIIDataV3D(char* vx_name, char* vy_name, char* vz_name, T***** pVoxelData, int& vd_x, int& vd_y, int& vd_z, int& vd_s, float& vd_dx, float& vd_dy, float& vd_dz, float& vd_ox, float& vd_oy, float& vd_oz, analyze_75_orient_code& vd_oc)
{
	T**** vx = NULL;
	T**** vy = NULL;
	T**** vz = NULL;
	int i, j, k;
	BOOL ret_val = FALSE;

	if (!LoadNIIData(vx_name, &vx, vd_x, vd_y, vd_z, vd_s, vd_dx, vd_dy, vd_dz, vd_ox, vd_oy, vd_oz, vd_oc)) {
		goto errret;
	}
	if (!LoadNIIData(vy_name, &vy, vd_x, vd_y, vd_z, vd_s, vd_dx, vd_dy, vd_dz, vd_ox, vd_oy, vd_oz, vd_oc)) {
		goto errret;
	}
	if (!LoadNIIData(vz_name, &vz, vd_x, vd_y, vd_z, vd_s, vd_dx, vd_dy, vd_dz, vd_ox, vd_oy, vd_oz, vd_oc)) {
		goto errret;
	}

	vd_s = 3;

	if (!AllocateVoxelData(pVoxelData, vd_x, vd_y, vd_z, vd_s)) {
		return FALSE;
	}

	for (k = 0; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				(*pVoxelData)[k][j][i][0] = vx[k][j][i][0];
				(*pVoxelData)[k][j][i][1] = vy[k][j][i][0];
				(*pVoxelData)[k][j][i][2] = vz[k][j][i][0];
			}
		}
	}
	
	ret_val = TRUE;

errret:
	if (vx != NULL) {
		FreeVoxelData(&vx, vd_x, vd_y, vd_z, 1);
	}
	if (vy != NULL) {
		FreeVoxelData(&vy, vd_x, vd_y, vd_z, 1);
	}
	if (vz != NULL) {
		FreeVoxelData(&vz, vd_x, vd_y, vd_z, 1);
	}

	return ret_val;
}

template <class T>
BOOL SaveNIIData(LPCTSTR lpszPathName, T**** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s, float vd_dx, float vd_dy, float vd_dz, float vd_ox, float vd_oy, float vd_oz, analyze_75_orient_code vd_oc)
{
	nifti_image* pNII = NULL;
	int i, j, k, l;
	BOOL bRes = FALSE;
	char ext[1024];

    int dims[] = { 4, vd_x, vd_y, vd_z, vd_s, 1, 1, 1 };
	if (sizeof(T) == 1) {
	    pNII = nifti_make_new_nim(dims, DT_UINT8, 1);
		if (pNII == NULL) {
			return FALSE;
		}
	    pNII->datatype = DT_UINT8;
	} else if (sizeof(T) == 2) {
	    pNII = nifti_make_new_nim(dims, DT_INT16, 1);
		if (pNII == NULL) {
			return FALSE;
		}
	    pNII->datatype = DT_INT16;
	} else if (sizeof(T) == 4) {
	    pNII = nifti_make_new_nim(dims, DT_FLOAT32, 1);
		if (pNII == NULL) {
			return FALSE;
		}
	    pNII->datatype = DT_FLOAT32;
	} else if (sizeof(T) == 8) {
	    pNII = nifti_make_new_nim(dims, DT_FLOAT64, 1);
		if (pNII == NULL) {
			return FALSE;
		}
	    pNII->datatype = DT_FLOAT64;
	} else {
		return FALSE;
	}
	if (pNII == NULL) {
		return FALSE;
	}

	pNII->fname = (char*)malloc(1024);
	pNII->iname = (char*)malloc(1024);

	if (strlen(lpszPathName) < 6) {
		strcpy(pNII->fname, lpszPathName);
	} else {
		strncpy(ext, (char*)&lpszPathName[strlen(lpszPathName)-6], 6);
		ext[6] = 0;
		if (strcmp(ext, "nii.gz") != 0) {
			sprintf(pNII->fname, "%s.nii.gz", lpszPathName);
		} else {
			strcpy(pNII->fname, lpszPathName);
		}
	}
	strcpy(pNII->iname, pNII->fname);

    pNII->dx = vd_dx;
    pNII->dy = vd_dy;
    pNII->dz = vd_dz;
	pNII->qoffset_x = vd_ox;
	pNII->qoffset_y = vd_oy;
	pNII->qoffset_z = vd_oz;
	pNII->analyze75_orient = vd_oc;
	//
	// LPS
	pNII->qform_code = 1;
	pNII->quatern_d = 1;
    pNII->qfac = 1;

	for (k = 0; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				T* p = (T*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
				for (l = 0; l < vd_s; l++) {
					*p++ = pVoxelData[k][j][i][l];
				}
			}
		}
	}

	nifti_image_write(pNII);

	bRes = TRUE;

	if (pNII != NULL) {
		nifti_image_free(pNII);
		pNII = NULL;
	}

	return bRes;
}

template <class T>
BOOL LoadIMGData(LPCTSTR img_name, LPCTSTR hdr_name, T***** pVoxelData, int& vd_x, int& vd_y, int& vd_z, int& vd_s, float& vd_dx, float& vd_dy, float& vd_dz, analyze_75_orient_code& vd_oc)
{
	nifti_image* pNII;
	int i, j, k, l;
	BOOL bRes = FALSE;
	char fname[1024];
	char ext[1024];
	int icod, jcod, kcod;
	int si, sj, sk;

	strcpy(fname, hdr_name);

	pNII = nifti_image_read(fname, 1);
	if (pNII == NULL) {
		return FALSE;
	}

	vd_x = pNII->nx;
	vd_y = pNII->ny;
	vd_z = pNII->nz;
	if (pNII->nt > 1 || pNII->nu <= 1) {
		vd_s = pNII->nt;
	} else if (pNII->nt <= 1 || pNII->nu > 1) {
		vd_s = pNII->nu;
	} else {
		vd_s = 1;
	}
	vd_dx = pNII->dx;
	vd_dy = pNII->dy;
	vd_dz = pNII->dz;
	vd_oc = pNII->analyze75_orient;
	//
#ifndef USE_ASSUME_LPS
	nifti_mat44_to_orientation(pNII->qto_ijk, &icod, &jcod, &kcod);
	if (icod == NIFTI_R2L) {
		si = 0;
	} else {
		si = 1;
	}
	if (jcod == NIFTI_A2P) {
		sj = 0;
	} else {
		sj = 1;
	}
	if (kcod == NIFTI_I2S) {
		sk = 0;
	} else {
		sk = 1;
	}
#else
	si = sj = sk = 0;
#endif
	//
	if (!AllocateVoxelData(pVoxelData, vd_x, vd_y, vd_z, vd_s)) {
		return FALSE;
	}
	//
	if (pNII->nbyper == 1) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				for (i = 0; i < vd_x; i++) {
					BYTE* p = (BYTE*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
					for (l = 0; l < vd_s; l++) {
						(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = *p++;
					}
				}
			}
		}
	} else if (pNII->nbyper == 2) {
		if (pNII->datatype == DT_INT16) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						short* p = (short*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = *p++;
						}
					}
				}
			}
		} else {
#ifdef USE_MESSAGEBOX
			AfxMessageBox("Error: m_pNII->datatype is unsupported.");
#endif
			goto errret;
		}
	} else if (pNII->nbyper == 4) {
		if (pNII->datatype == DT_FLOAT32) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						float* p = (float*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = *p++;
						}
					}
				}
			}
		} else {
#ifdef USE_MESSAGEBOX
			AfxMessageBox("Error: m_pNII->datatype is unsupported.");
#endif
			goto errret;
		}
	} else if (pNII->nbyper == 8) {
		if (pNII->datatype == DT_FLOAT64) {
			for (k = 0; k < vd_z; k++) {
				for (j = 0; j < vd_y; j++) {
					for (i = 0; i < vd_x; i++) {
						double* p = (double*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
						for (l = 0; l < vd_s; l++) {
							(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = *p++;
						}
					}
				}
			}
		} else {
#ifdef USE_MESSAGEBOX
			AfxMessageBox("Error: m_pNII->datatype is unsupported.");
#endif
			goto errret;
		}
	} else {
#ifdef USE_MESSAGEBOX
		AfxMessageBox("Error: m_pNII->nbyper is unsupported.");
#endif
		goto errret;
	}

	bRes = TRUE;

errret:
	nifti_image_free(pNII);

	return bRes;
}

template <class T>
BOOL SaveIMGData(LPCTSTR img_name, LPCTSTR hdr_name, T**** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s, float vd_dx, float vd_dy, float vd_dz, analyze_75_orient_code vd_oc)
{
	nifti_image* pNII = NULL;
	int i, j, k, l;
	BOOL bRes = FALSE;
	char ext[1024];

    int dims[] = { 4, vd_x, vd_y, vd_z, vd_s, 1, 1, 1 };
	if (sizeof(T) == 1) {
	    pNII = nifti_make_new_nim(dims, DT_UINT8, 1);
		if (pNII == NULL) {
			return FALSE;
		}
	    pNII->datatype = DT_UINT8;
	} else if (sizeof(T) == 2) {
	    pNII = nifti_make_new_nim(dims, DT_INT16, 1);
		if (pNII == NULL) {
			return FALSE;
		}
	    pNII->datatype = DT_INT16;
	} else if (sizeof(T) == 4) {
	    pNII = nifti_make_new_nim(dims, DT_FLOAT32, 1);
		if (pNII == NULL) {
			return FALSE;
		}
	    pNII->datatype = DT_FLOAT32;
	} else if (sizeof(T) == 8) {
	    pNII = nifti_make_new_nim(dims, DT_FLOAT64, 1);
		if (pNII == NULL) {
			return FALSE;
		}
	    pNII->datatype = DT_FLOAT32;
	} else {
		return FALSE;
	}

	pNII->nifti_type = NIFTI_FTYPE_ANALYZE;

	pNII->fname = (char*)malloc(1024);
	pNII->iname = (char*)malloc(1024);

	strcpy(pNII->fname, hdr_name);
	strcpy(pNII->iname, img_name);

    pNII->qform_code = 1;    
    pNII->dx = vd_dx;
    pNII->dy = vd_dy;
    pNII->dz = vd_dz;
	pNII->analyze75_orient = vd_oc;

	for (k = 0; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				T* p = (T*)pNII->data + ((k*vd_y+j)*vd_x+i)*vd_s;
				for (l = 0; l < vd_s; l++) {
					*p++ = pVoxelData[k][j][i][l];
				}
			}
		}
	}

	nifti_image_write(pNII);

	bRes = TRUE;

errret:
	if (pNII != NULL) {
		nifti_image_free(pNII);
		pNII = NULL;
	}

	return bRes;
}

#ifdef USE_METAIO
template <class T>
BOOL LoadMHDData(LPCTSTR img_name, LPCTSTR hdr_name, T***** pVoxelData, int& vd_x, int& vd_y, int& vd_z, int& vd_s, float& vd_dx, float& vd_dy, float& vd_dz,
	float& vd_ox, float& vd_oy, float& vd_oz)
{
	MetaImage* pMI = NULL;
	int i, j, k, l;
	BOOL bRes = FALSE;
	//int icod, jcod, kcod;
	int si, sj, sk;
	int v;

	pMI = new MetaImage(hdr_name);
	if (pMI->ElementData() == NULL) {
		goto errret;
	}

	vd_x = pMI->DimSize(0);
	vd_y = pMI->DimSize(1);
	vd_z = pMI->DimSize(2);
	vd_s = pMI->ElementNumberOfChannels();
	v = 0; vd_dx = pMI->ElementSize(v);
	v = 1; vd_dy = pMI->ElementSize(v);
	v = 2; vd_dz = pMI->ElementSize(v);
	v = 0; vd_ox = (float)pMI->Offset(v);
	v = 1; vd_oy = (float)pMI->Offset(v);
	v = 2; vd_oz = (float)pMI->Offset(v);
	//
	/*
#ifndef USE_ASSUME_LPS
	v = 0; if (pMI->AnatomicalOrientation(v) == MET_ORIENTATION_LR) {
		si = 0;
	} else {
		si = 1;
	}
	v = 1; if (pMI->AnatomicalOrientation(v) == MET_ORIENTATION_PA) {
		sj = 0;
	} else {
		sj = 1;
	}
	v = 2; if (pMI->AnatomicalOrientation(v) == MET_ORIENTATION_SI) {
		sk = 0;
	} else {
		sk = 1;
	}
#else
	si = sj = sk = 0;
#endif
	/*/
	si = sj = sk = 0;
	//*/
	//
	if (*pVoxelData == NULL) {
		if (!AllocateVoxelData(pVoxelData, vd_x, vd_y, vd_z, vd_s)) {
			return FALSE;
		}
	}
	//
	if (pMI->ElementType() == MET_FLOAT) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				for (i = 0; i < vd_x; i++) {
					float* p = (float*)pMI->ElementData() + ((k*vd_y+j)*vd_x+i)*vd_s;
					for (l = 0; l < vd_s; l++) {
						(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = (T)*p++;
					}
				}
			}
		}
	} else if (pMI->ElementType() == MET_DOUBLE) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				for (i = 0; i < vd_x; i++) {
					double* p = (double*)pMI->ElementData() + ((k*vd_y+j)*vd_x+i)*vd_s;
					for (l = 0; l < vd_s; l++) {
						(*pVoxelData)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][l] = (T)*p++;
					}
				}
			}
		}
	} else {
#ifdef USE_MESSAGEBOX
		AfxMessageBox("Error: pMI->ElementType() is unsupported.");
#endif
		goto errret;
	}

	bRes = TRUE;

errret:
	if (pMI != NULL) {
		delete pMI;
		pMI = NULL;
	}
	
	return bRes;
}

template <class T>
BOOL SaveMHDData(LPCTSTR img_name, LPCTSTR hdr_name, T**** pVoxelData, int vd_x, int vd_y, int vd_z, int vd_s, float vd_dx, float vd_dy, float vd_dz,
	float vd_ox, float vd_oy, float vd_oz)
{
	MetaImage* pMI = NULL;
	int i, j, k, l;
	BOOL bRes = FALSE;

	if (sizeof(T) == 1) {
		pMI = new MetaImage(vd_x, vd_y, vd_z, vd_dx, vd_dy, vd_dz, MET_UCHAR, vd_s);
		if (pMI->ElementData() == NULL) {
			delete pMI;
			pMI = NULL;
			return FALSE;
		}
	} else if (sizeof(T) == 2) {
		pMI = new MetaImage(vd_x, vd_y, vd_z, vd_dx, vd_dy, vd_dz, MET_SHORT, vd_s);
		if (pMI->ElementData() == NULL) {
			delete pMI;
			pMI = NULL;
			return FALSE;
		}
	} else if (sizeof(T) == 4) {
		pMI = new MetaImage(vd_x, vd_y, vd_z, vd_dx, vd_dy, vd_dz, MET_FLOAT, vd_s);
		if (pMI->ElementData() == NULL) {
			delete pMI;
			pMI = NULL;
			return FALSE;
		}
	} else if (sizeof(T) == 8) {
		pMI = new MetaImage(vd_x, vd_y, vd_z, vd_dx, vd_dy, vd_dz, MET_DOUBLE, vd_s);
		if (pMI->ElementData() == NULL) {
			delete pMI;
			pMI = NULL;
			return FALSE;
		}
	} else {
		return FALSE;
	}

	//*
	// LPS
	pMI->AnatomicalOrientation(0, MET_ORIENTATION_RL);
	pMI->AnatomicalOrientation(1, MET_ORIENTATION_AP);
	pMI->AnatomicalOrientation(2, MET_ORIENTATION_IS);
	/*/
	// RAI
	pMI->AnatomicalOrientation(0, MET_ORIENTATION_LR);
	pMI->AnatomicalOrientation(1, MET_ORIENTATION_PA);
	pMI->AnatomicalOrientation(2, MET_ORIENTATION_SI);
	//*/

	// Offset
	pMI->Offset(0, fabs(vd_ox));
	pMI->Offset(1, fabs(vd_oy));
	pMI->Offset(2, fabs(vd_oz));

	for (k = 0; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				T* p = (T*)pMI->ElementData() + ((k*vd_y+j)*vd_x+i)*vd_s;
				for (l = 0; l < vd_s; l++) {
					*p++ = pVoxelData[k][j][i][l];
				}
			}
		}
	}

	pMI->CompressedData(true);

	pMI->Write(hdr_name, img_name);

	bRes = TRUE;

	if (pMI != NULL) {
		delete pMI;
		pMI = NULL;
	}
	
	return bRes;
}

template <class T>
BOOL LoadMHDData(LPCTSTR img_name, LPCTSTR hdr_name, T***** vx_data, T***** vy_data, T***** vz_data, int& vd_x, int& vd_y, int& vd_z, float& vd_dx, float& vd_dy, float& vd_dz,
	float& vd_ox, float& vd_oy, float& vd_oz)
{
	MetaImage* pMI = NULL;
	int i, j, k;
	BOOL bRes = FALSE;
	//int icod, jcod, kcod;
	int si, sj, sk;
	int v;
	int vd_s;

	pMI = new MetaImage(hdr_name);
	if (pMI->ElementData() == NULL) {
		goto errret;
	}

	vd_x = pMI->DimSize(0);
	vd_y = pMI->DimSize(1);
	vd_z = pMI->DimSize(2);
	vd_s = pMI->ElementNumberOfChannels();
	if (vd_s != 3) {
		return FALSE;
	}
	v = 0; vd_dx = pMI->ElementSize(v);
	v = 1; vd_dy = pMI->ElementSize(v);
	v = 2; vd_dz = pMI->ElementSize(v);
	v = 0; vd_ox = (float)pMI->Offset(v);
	v = 1; vd_oy = (float)pMI->Offset(v);
	v = 2; vd_oz = (float)pMI->Offset(v);
	//
	/*
#ifndef USE_ASSUME_LPS
	v = 0; if (pMI->AnatomicalOrientation(v) == MET_ORIENTATION_LR) {
		si = 0;
	} else {
		si = 1;
	}
	v = 1; if (pMI->AnatomicalOrientation(v) == MET_ORIENTATION_PA) {
		sj = 0;
	} else {
		sj = 1;
	}
	v = 2; if (pMI->AnatomicalOrientation(v) == MET_ORIENTATION_SI) {
		sk = 0;
	} else {
		sk = 1;
	}
#else
	si = sj = sk = 0;
#endif
	/*/
	si = sj = sk = 0;
	//*/
	//
	if (*vx_data == NULL) {
		if (!AllocateVoxelData(vx_data, vd_x, vd_y, vd_z, 1)) {
			return FALSE;
		}
	}
	if (*vy_data == NULL) {
		if (!AllocateVoxelData(vy_data, vd_x, vd_y, vd_z, 1)) {
			return FALSE;
		}
	}
	if (*vz_data == NULL) {
		if (!AllocateVoxelData(vz_data, vd_x, vd_y, vd_z, 1)) {
			return FALSE;
		}
	}
	//
	if (pMI->ElementType() == MET_FLOAT) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				for (i = 0; i < vd_x; i++) {
					float* p = (float*)pMI->ElementData() + ((k*vd_y+j)*vd_x+i)*vd_s;
					(*vx_data)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][0] = ((T)*p++) / vd_dx;
					(*vy_data)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][0] = ((T)*p++) / vd_dy;
					(*vz_data)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][0] = ((T)*p++) / vd_dz;
				}
			}
		}
	} else if (pMI->ElementType() == MET_DOUBLE) {
		for (k = 0; k < vd_z; k++) {
			for (j = 0; j < vd_y; j++) {
				for (i = 0; i < vd_x; i++) {
					double* p = (double*)pMI->ElementData() + ((k*vd_y+j)*vd_x+i)*vd_s;
					(*vx_data)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][0] = ((T)*p++) / vd_dx;
					(*vy_data)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][0] = ((T)*p++) / vd_dy;
					(*vz_data)[(1-sk)*k+(sk)*(vd_z-1-k)][(1-sj)*j+(sj)*(vd_y-1-j)][(1-si)*i+(si)*(vd_x-1-i)][0] = ((T)*p++) / vd_dz;
				}
			}
		}
	} else {
#ifdef USE_MESSAGEBOX
		AfxMessageBox("Error: pMI->ElementType() is unsupported.");
#endif
		goto errret;
	}

	bRes = TRUE;

	vd_dx = 1; vd_dy = 1; vd_dz = 1;
	vd_ox = 0; vd_oy = 0; vd_oz = 0;

errret:
	if (pMI != NULL) {
		delete pMI;
		pMI = NULL;
	}
	
	return bRes;
}

template <class T>
BOOL SaveMHDData(LPCTSTR img_name, LPCTSTR hdr_name, T**** vx_data, T**** vy_data, T**** vz_data, int vd_x, int vd_y, int vd_z, float vd_dx, float vd_dy, float vd_dz,
	float vd_ox, float vd_oy, float vd_oz)
{
	MetaImage* pMI = NULL;
	int i, j, k;
	int vd_s = 3;
	BOOL bRes = FALSE;

	if (sizeof(T) == 1) {
		pMI = new MetaImage(vd_x, vd_y, vd_z, vd_dx, vd_dy, vd_dz, MET_UCHAR, vd_s);
		if (pMI->ElementData() == NULL) {
			return FALSE;
		}
	} else if (sizeof(T) == 2) {
		pMI = new MetaImage(vd_x, vd_y, vd_z, vd_dx, vd_dy, vd_dz, MET_SHORT, vd_s);
		if (pMI->ElementData() == NULL) {
			return FALSE;
		}
	} else if (sizeof(T) == 4) {
		pMI = new MetaImage(vd_x, vd_y, vd_z, vd_dx, vd_dy, vd_dz, MET_FLOAT, vd_s);
		if (pMI->ElementData() == NULL) {
			return FALSE;
		}
	} else if (sizeof(T) == 8) {
		pMI = new MetaImage(vd_x, vd_y, vd_z, vd_dx, vd_dy, vd_dz, MET_DOUBLE, vd_s);
		if (pMI->ElementData() == NULL) {
			return FALSE;
		}
	} else {
		return FALSE;
	}

	//*
	// LPS
	pMI->AnatomicalOrientation(0, MET_ORIENTATION_RL);
	pMI->AnatomicalOrientation(1, MET_ORIENTATION_AP);
	pMI->AnatomicalOrientation(2, MET_ORIENTATION_IS);
	/*/
	// RAI
	pMI->AnatomicalOrientation(0, MET_ORIENTATION_LR);
	pMI->AnatomicalOrientation(1, MET_ORIENTATION_PA);
	pMI->AnatomicalOrientation(2, MET_ORIENTATION_SI);
	//*/

	// Offset
	pMI->Offset(0, fabs(vd_ox));
	pMI->Offset(1, fabs(vd_oy));
	pMI->Offset(2, fabs(vd_oz));

	for (k = 0; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				T* p = (T*)pMI->ElementData() + ((k*vd_y+j)*vd_x+i)*vd_s;
				*p++ = vx_data[k][j][i][0] * vd_dx;
				*p++ = vy_data[k][j][i][0] * vd_dy;
				*p++ = vz_data[k][j][i][0] * vd_dz;
			}
		}
	}

	pMI->CompressedData(true);

	pMI->Write(hdr_name, img_name);

	bRes = TRUE;

	if (pMI != NULL) {
		delete pMI;
		pMI = NULL;
	}
	
	return bRes;
}
#endif
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#if !defined(WIN32) && !defined(WIN64)
BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists);
BOOL CreateDirectory(LPCTSTR lpPathName, void* lpSecurityAttributes);
BOOL SetCurrentDirectory(LPCTSTR lpPathName);
BOOL DeleteFile(LPCTSTR lpFileName);
#endif
void DeleteAll(char* sFolder, BOOL bDeleteFolderToo);
void DeleteFiles(char* sFolder, const char* sPattern, BOOL bSubDir);
void DeleteSubDirs(char* sFolder, const char* sPattern);
BOOL GetModulePath(char* sPath);

void MySleep(int tick);

#endif
