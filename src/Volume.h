///////////////////////////////////////////////////////////////////////////////////////
// Volume.h
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

#pragma once


#include <iostream>
#include <fstream>
#include <typeinfo>
#define USE_MYUTILS
#ifdef USE_MYUTILS
#include "MyUtils.h"
#else
#define MyAlloc(size) malloc(size)
#define MyAllocEx(size, str_info) malloc(size)
#define MyCAlloc(num, size) calloc(num, size)
#define MyCAllocEx(num, size, str_info) calloc(num, size)
#define MyFree(ptr) free(ptr)
#ifndef MIN
#define MIN(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef BOOL
#define BOOL int
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#endif
#ifdef USE_GPROGRESSBAR
#include "gprogressbar.h"
#else
#define _TIME_CHECK
#endif


using namespace std;


template <class T>
class VolumeBase
{
public:
	T**** m_pData;
	int m_vd_x, m_vd_y, m_vd_z, m_vd_s;
	float m_vd_dx, m_vd_dy, m_vd_dz;
	float m_vd_ox, m_vd_oy, m_vd_oz;
#ifdef USE_MYUTILS
	analyze_75_orient_code m_vd_oc;
#endif
	long long m_nPixels, m_nElements;

public:
	VolumeBase(void);
	VolumeBase(int x, int y, int z, int s = 1, float dx = 1.0f, float dy = 1.0f, float dz = 1.0f);
	virtual ~VolumeBase(void);

	virtual inline void computeDimension() { m_nPixels = m_vd_x * m_vd_y * m_vd_z; m_nElements = m_nPixels * m_vd_s; };

	virtual void allocate(int x, int y, int z, int s = 1, float dx = 1.0f, float dy = 1.0f, float dz = 1.0f);

	virtual void clear();
	virtual void reset();

	inline T****& data() { return m_pData; };
	inline const T****& data() const { return (const T****&)m_pData; };
	inline int x() const { return m_vd_x; };
	inline int y() const { return m_vd_y; };
	inline int z() const { return m_vd_z; };
	inline int s() const { return m_vd_s; };
	inline int npixels() const { return m_nPixels; };
	inline int nelements() const { return m_nElements; };

	BOOL save(char* filename, int mode = 0);
	BOOL load(char* filename, int mode = 0);
	BOOL loadSize(char* filename, int mode = 0);

#ifdef USE_MYUTILS
	BOOL saveNII(char* filename);
	BOOL loadNII(char* filename);
	BOOL loadNIISize(char* filename);
#endif
};

template <class T>
class Volume : public VolumeBase<T>
{
public:
	bool m_IsDerivativeImage;
	enum color_type { RGB, BGR, DATA, GRAY };
	color_type m_ColorType;

public:
	Volume(void);
	Volume(int x, int y, int z, int s = 1, float dx = 1.0f, float dy = 1.0f, float dz = 1.0f);
	Volume(const T& value, int x, int y, int z, int s = 1, float dx = 1.0f, float dy = 1.0f, float dz = 1.0f);
	Volume(const Volume<T>& other);
	virtual ~Volume(void);
	virtual Volume<T>& operator=(const Volume<T>& other);
	virtual Volume<T>& operator+=(const Volume<T>& other);
	virtual Volume<T>& operator-=(const Volume<T>& other);

	virtual void copyData(const Volume<T>& other);
	virtual void addData(const Volume<T>& other);
	virtual void subData(const Volume<T>& other);
	void setValue(const T& value);
	void setValue(const T& value, int x, int y, int z, int s = 1, float dx = 1.0f, float dy = 1.0f, float dz = 1.0f);
	void setData(T**** data);
	void setData(T*** data);
	void setData3(T**** data0, T**** data1, T**** data2);
	T immax() const
	{
		int i, j, k, l;
		T Max = VolumeBase<T>::m_pData[0][0][0][0];
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						Max = MAX(Max, VolumeBase<T>::m_pData[k][j][i][l]);
					}
				}
			}
		}
		return Max;
	};
	T immin() const
	{
		int i, j, k, l;
		T Min = VolumeBase<T>::m_pData[0][0][0][0];
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						Min = MIN(Min, VolumeBase<T>::m_pData[k][j][i][l]);
					}
				}
			}
		}
		return Min;
	}
	template <class T1>
	void copy(const Volume<T1>& other);

	inline bool isDerivativeImage() const { return m_IsDerivativeImage; };
	inline color_type colortype() const { return m_ColorType; };

	virtual bool imresize(float ratio, bool bNN = false);
	template <class T1>
	bool imresize(Volume<T1>& dst, int dst_x, int dst_y, int dst_z, int dst_s, bool bNN = false) const;
	void ReduceVolume(Volume<T>& dst, bool bAvg);

	template <class T1>
	void GaussianSmoothing(Volume<T1>& vol, double sigma, int fsize) const;
	template <class T1>
	void GetGradient(Volume<T1>& gx, Volume<T1>& gy, Volume<T1>& gz) const;
	template <class T1, class T2>
	void GetGradient(Volume<T1>& gx, Volume<T1>& gy, Volume<T1>& gz, Volume<T2>& mask, T2 mask_th) const;
	template <class T1>
	void GetGradientSobel(Volume<T1>& gx, Volume<T1>& gy, Volume<T1>& gz) const;
	template <class T1>
	void GetGradientWeightSobel(Volume<T1>& gw) const;

	void NormalizeImage();

	bool NormalizeSize(bool bNN = false, bool bCrop = false, int wx = 256, int wy = 256, int wz = 256);

	void GetAt(float fx, float fy, float fz, T* dv, bool bNN = false);
	void MultiplyValue(float mv);
};


typedef Volume<unsigned char> BVolume;
typedef Volume<short int> SVolume;
typedef Volume<int> IVolume;
typedef Volume<float> FVolume;
typedef Volume<double> DVolume;
//
typedef Volume<float> RVolume;
typedef float REALV;


#define _round(t) ((t) < 0 ? (int) ((t)-0.5f) : (int) ((t)+0.5f))


////////////////////////////////////////////////////////////////////////////////////////////
// VolumeBase
////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------
// constructor
//------------------------------------------------------------------------------------------
template <class T>
VolumeBase<T>::VolumeBase()
{
	m_pData = NULL;
	m_vd_x = m_vd_y = m_vd_z = m_vd_s = 0;
	m_vd_dx = m_vd_dy = m_vd_dz = 1.0f;
	m_vd_ox = m_vd_oy = m_vd_oz = 0;
#ifdef USE_MYUTILS
	m_vd_oc = a75_transverse_flipped; // LPS
#endif
	m_nPixels = m_nElements = 0;
}

//------------------------------------------------------------------------------------------
// constructor with specified dimensions
//------------------------------------------------------------------------------------------
template <class T>
VolumeBase<T>::VolumeBase(int x, int y, int z, int s, float dx, float dy, float dz)
{
	m_pData = NULL;
	allocate(x, y, z, s, dx, dy, dz);
}

template <class T>
void VolumeBase<T>::allocate(int x, int y, int z, int s, float dx, float dy, float dz)
{
	int i, j, k;
	//
	clear();
	//
	m_vd_x = x;
	m_vd_y = y;
	m_vd_z = z;
	m_vd_s = s;
	m_vd_dx = dx;
	m_vd_dy = dy;
	m_vd_dz = dz;
	computeDimension();
	m_pData = NULL;
	if (m_nElements > 0) {
#ifndef _TIME_CHECK
		CGProgressBar Bar("Allocating...", 100);
#endif
		/*
		m_pData = (T****)malloc(m_vd_z * sizeof(T***));
		for (k = 0; k < m_vd_z; k++) {
			m_pData[k] = (T***)malloc(m_vd_y * sizeof(T**));
			for (j = 0; j < m_vd_y; j++) {
				m_pData[k][j] = (T**)malloc(m_vd_x * sizeof(T*));
				for (i = 0; i < m_vd_x; i++) {
					m_pData[k][j][i] = (T*)malloc(m_vd_s * sizeof(T));
					memset(m_pData[k][j][i], 0, m_vd_s * sizeof(T));
				}
			}
#ifndef _TIME_CHECK
			Bar.SetPos(100*k/m_vd_z);
#endif
		}
		/*/
		m_pData = (T****)MyAllocEx(m_vd_z*sizeof(T***), "allocate");
		for (k = 0; k < m_vd_z; k++) {
			T* mem_chunk = (T*)MyAllocEx(m_vd_x*m_vd_y*m_vd_s*sizeof(T), "allocate mem_chunk");
			memset(mem_chunk, 0, m_vd_x*m_vd_y*m_vd_s*sizeof(T));
			m_pData[k] = (T***)MyAllocEx(m_vd_y*sizeof(T**), "allocate");
			for (j = 0; j < m_vd_y; j++) {
				m_pData[k][j] = (T**)MyCAllocEx(m_vd_x, sizeof(T*), "allocate");
				for (i = 0; i < m_vd_x; i++) {
					m_pData[k][j][i] = &mem_chunk[(j*m_vd_x+i)*m_vd_s];
				}
			}
#ifndef _TIME_CHECK
			Bar.SetPos(100*k/m_vd_z);
#endif
		}
		//*/
	}
}

//------------------------------------------------------------------------------------------
// destructor
//------------------------------------------------------------------------------------------
template <class T>
VolumeBase<T>::~VolumeBase()
{
	clear();
}

//------------------------------------------------------------------------------------------
// clear the image
//------------------------------------------------------------------------------------------
template <class T>
void VolumeBase<T>::clear()
{
	int i, j, k;
	//
	if (m_pData != NULL) {
#ifndef _TIME_CHECK
		CGProgressBar Bar("Freeing...", 100);
#endif
		for (k = 0; k < m_vd_z; k++) {
			MyFree(m_pData[k][0][0]);
			for (j = 0; j < m_vd_y; j++) {
				for (i = 0; i < m_vd_x; i++) {
					m_pData[k][j][i] = NULL;
				}
				MyFree(m_pData[k][j]);
				m_pData[k][j] = NULL;
			}
			MyFree(m_pData[k]);
			m_pData[k] = NULL;
#ifndef _TIME_CHECK
			Bar.SetPos(100*k/m_vd_z);
#endif
		}
		MyFree(m_pData);
		m_pData = NULL;
	}
	m_vd_x = m_vd_y = m_vd_z = m_vd_s = 0;
	m_nPixels = m_nElements = 0;
}

//------------------------------------------------------------------------------------------
// reset the image (reset the buffer to zero)
//------------------------------------------------------------------------------------------
template <class T>
void VolumeBase<T>::reset()
{
	int i, j, k;
	//
	if (m_pData != NULL) {
		for (k = 0; k < m_vd_z; k++) {
			for (j = 0; j < m_vd_y; j++) {
				for (i = 0; i < m_vd_x; i++) {
					memset(m_pData[k][j][i], 0, m_vd_s * sizeof(T));
				}
			}
		}
	}
}

template <class T>
BOOL VolumeBase<T>::save(char* filename, int mode)
{
	FILE* fp = NULL;
	int i, j, k;
	//
#ifdef USE_MYUTILS 
	if (mode == 1) {
		return saveNII(filename);
	}
#endif
	//
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		return FALSE;
	}
	fwrite(&m_vd_x, sizeof(int), 1, fp);
	fwrite(&m_vd_y, sizeof(int), 1, fp);
	fwrite(&m_vd_z, sizeof(int), 1, fp);
	fwrite(&m_vd_s, sizeof(int), 1, fp);
	//
	if (m_pData != NULL) {
#ifndef _TIME_CHECK
		CGProgressBar Bar("Saving...", 100);
#endif
		for (k = 0; k < m_vd_z; k++) {
			for (j = 0; j < m_vd_y; j++) {
				for (i = 0; i < m_vd_x; i++) {
					fwrite(m_pData[k][j][i], sizeof(T), m_vd_s, fp);
				}
			}
#ifndef _TIME_CHECK
			Bar.SetPos(100*k/m_vd_z);
#endif
		}
	}
	//
	fclose(fp);
	//
	return TRUE;
}

template <class T>
BOOL VolumeBase<T>::load(char* filename, int mode)
{
	FILE* fp = NULL;
	int i, j, k;
	//
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		if (mode == 1) {
			char filename2[1024];
			sprintf(filename2, "%s.nii.gz", filename);
			fp = fopen(filename2, "rb");
			if (fp == NULL) {
				return FALSE;
			}
		} else {
			return FALSE;
		}
	}
	//
#ifdef USE_MYUTILS    
	if (mode == 1) {
		fclose(fp);
		return loadNII(filename);
	}
#endif
	//
	fread(&m_vd_x, sizeof(int), 1, fp);
	fread(&m_vd_y, sizeof(int), 1, fp);
	fread(&m_vd_z, sizeof(int), 1, fp);
	fread(&m_vd_s, sizeof(int), 1, fp);
	//
	allocate(m_vd_x, m_vd_y, m_vd_z, m_vd_s);
	//
	if (m_pData != NULL) {
#ifndef _TIME_CHECK
		CGProgressBar Bar("Loading...", 100);
#endif
		for (k = 0; k < m_vd_z; k++) {
			for (j = 0; j < m_vd_y; j++) {
				for (i = 0; i < m_vd_x; i++) {
					fread(m_pData[k][j][i], sizeof(T), m_vd_s, fp);
				}
			}
#ifndef _TIME_CHECK
			Bar.SetPos(100*k/m_vd_z);
#endif
		}
	}
	//
	fclose(fp);
	//
	return TRUE;
}

template <class T>
BOOL VolumeBase<T>::loadSize(char* filename, int mode)
{
	FILE* fp = NULL;
	int i, j, k;
	//
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		if (mode == 1) {
			char filename2[1024];
			sprintf(filename2, "%s.nii.gz", filename);
			fp = fopen(filename2, "rb");
			if (fp == NULL) {
				return FALSE;
			}
		} else {
			return FALSE;
		}
	}
	//
#ifdef USE_MYUTILS    
	if (mode == 1) {
		fclose(fp);
		return loadNIISize(filename);
	}
#endif
	//
	fread(&m_vd_x, sizeof(int), 1, fp);
	fread(&m_vd_y, sizeof(int), 1, fp);
	fread(&m_vd_z, sizeof(int), 1, fp);
	fread(&m_vd_s, sizeof(int), 1, fp);
	//
	fclose(fp);
	//
	return TRUE;
}

#ifdef USE_MYUTILS
template <class T>
BOOL VolumeBase<T>::saveNII(char* filename)
{
	return SaveNIIData(filename, m_pData, m_vd_x, m_vd_y, m_vd_z, m_vd_s, m_vd_dx, m_vd_dy, m_vd_dz, m_vd_ox, m_vd_oy, m_vd_oz, m_vd_oc);
}

template <class T>
BOOL VolumeBase<T>::loadNII(char* filename)
{
	BOOL bRes;
	//
	clear();
	//
	bRes = LoadNIIData(filename, &m_pData, m_vd_x, m_vd_y, m_vd_z, m_vd_s, m_vd_dx, m_vd_dy, m_vd_dz, m_vd_ox, m_vd_oy, m_vd_oz, m_vd_oc);
	if (bRes) {
		computeDimension();
	}
	//
	return bRes;
}

template <class T>
BOOL VolumeBase<T>::loadNIISize(char* filename)
{
	return LoadNIIDataSize(filename, m_vd_x, m_vd_y, m_vd_z, m_vd_s, m_vd_dx, m_vd_dy, m_vd_dz, m_vd_ox, m_vd_oy, m_vd_oz);
}
#endif
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
// Volume
////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------
// constructor
//------------------------------------------------------------------------------------------
template <class T>
Volume<T>::Volume()
{
	m_IsDerivativeImage = false;
	m_ColorType = DATA;
}

//------------------------------------------------------------------------------------------
// constructor with specified dimensions
//------------------------------------------------------------------------------------------
template <class T>
Volume<T>::Volume(int x, int y, int z, int s, float dx, float dy, float dz)
{
	VolumeBase<T>::VolumeBase(x, y, z, s, dx, dy, dz);
	m_IsDerivativeImage = false;
	m_ColorType = DATA;
}

template <class T>
Volume<T>::Volume(const T& value, int x, int y, int z, int s, float dx, float dy, float dz)
{
	VolumeBase<T>::VolumeBase(x, y, z, s, dx, dy, dz);
	m_IsDerivativeImage = false;
	m_ColorType = DATA;
	setValue(value);
}

//------------------------------------------------------------------------------------------
// copy constructor
//------------------------------------------------------------------------------------------
template <class T>
Volume<T>::Volume(const Volume<T>& other)
{
	VolumeBase<T>::m_pData = NULL;
	VolumeBase<T>::m_vd_x = VolumeBase<T>::m_vd_y = VolumeBase<T>::m_vd_z = VolumeBase<T>::m_vd_s = VolumeBase<T>::m_nPixels = VolumeBase<T>::m_nElements = 0;
	VolumeBase<T>::m_vd_dx = VolumeBase<T>::m_vd_dy = VolumeBase<T>::m_vd_dz = 1.0f;
#ifdef USE_MYUTILS    
	VolumeBase<T>::m_vd_oc = a75_transverse_flipped; // LPS
#endif
	m_IsDerivativeImage = false;
	m_ColorType = DATA;
	copyData(other);
}

//------------------------------------------------------------------------------------------
// destructor
//------------------------------------------------------------------------------------------
template <class T>
Volume<T>::~Volume()
{
}

template <class T>
void Volume<T>::setValue(const T &value)
{
	int i, j, k, l;
	//
	if (VolumeBase<T>::m_pData != NULL) {
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						VolumeBase<T>::m_pData[k][j][i][l] = value;
					}
				}
			}
		}
	}
}

template <class T>
void Volume<T>::setValue(const T& value, int x, int y, int z, int s, float dx, float dy, float dz)
{
	if (VolumeBase<T>::vd_x != x || VolumeBase<T>::vd_y != y || VolumeBase<T>::vd_z != z || VolumeBase<T>::vd_s != s) {
		VolumeBase<T>::allocate(x, y, z, s, dx, dy, dz);
	}
	setValue(value);
}

template <class T>
void Volume<T>::setData(T**** data)
{
	int i, j, k, l;
	//
	if (VolumeBase<T>::m_pData != NULL) {
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						VolumeBase<T>::m_pData[k][j][i][l] = data[k][j][i][l];
					}
				}
			}
		}
	}
}

template <class T>
void Volume<T>::setData(T*** data)
{
	int i, j, k, l;
	//
	if (VolumeBase<T>::m_pData != NULL) {
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					VolumeBase<T>::m_pData[k][j][i][0] = data[k][j][i];
				}
			}
		}
	}
}

template <class T>
void Volume<T>::setData3(T**** data0, T**** data1, T**** data2)
{
	int i, j, k, l;
	//
	if (VolumeBase<T>::m_pData != NULL) {
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					VolumeBase<T>::m_pData[k][j][i][0] = data0[k][j][i][0];
					VolumeBase<T>::m_pData[k][j][i][1] = data1[k][j][i][0];
					VolumeBase<T>::m_pData[k][j][i][2] = data2[k][j][i][0];
				}
			}
		}
	}
}

//------------------------------------------------------------------------------------------
// copy from other image
//------------------------------------------------------------------------------------------
template <class T>
void Volume<T>::copyData(const Volume<T>& other)
{
	int i, j, k;
	//
	if (VolumeBase<T>::m_vd_x != other.m_vd_x || VolumeBase<T>::m_vd_y != other.m_vd_y || VolumeBase<T>::m_vd_z != other.m_vd_z || VolumeBase<T>::m_vd_s != other.m_vd_s) {
		VolumeBase<T>::clear();
		//
		VolumeBase<T>::allocate(other.m_vd_x, other.m_vd_y, other.m_vd_z, other.m_vd_s, other.m_vd_dx, other.m_vd_dy, other.m_vd_dz);
	}
	//
#ifdef USE_MYUTILS
	VolumeBase<T>::m_vd_oc = other.m_vd_oc;
#endif
	//
	VolumeBase<T>::m_nPixels = other.m_nPixels;
	VolumeBase<T>::m_nElements = other.m_nElements;
	m_IsDerivativeImage = other.m_IsDerivativeImage;
	m_ColorType = other.m_ColorType;
	//
	if (VolumeBase<T>::m_nElements > 0) {
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					memcpy(VolumeBase<T>::m_pData[k][j][i], other.m_pData[k][j][i], VolumeBase<T>::m_vd_s * sizeof(T));
				}
			}
		}
	}
}

template <class T>
template <class T1>
void Volume<T>::copy(const Volume<T1>& other)
{
	int i, j, k, l;
	//
	VolumeBase<T>::clear();
	//
	VolumeBase<T>::allocate(other.m_vd_x, other.m_vd_y, other.m_vd_z, other.m_vd_s, other.m_vd_dx, other.m_vd_dy, other.m_vd_dz);
	//
#ifdef USE_MYUTILS 
	VolumeBase<T>::m_vd_oc = other.m_vd_oc;
#endif
	//
	m_IsDerivativeImage = other.m_IsDerivativeImage;
	m_ColorType = other.m_ColorType;
	//
	const T1****& srcData = other.data();
	for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
		for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
			for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
				for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
					VolumeBase<T>::m_pData[k][j][i][l] = srcData[k][j][i][l];
				}
			}
		}
	}
}

//------------------------------------------------------------------------------------------
// add other image
//------------------------------------------------------------------------------------------
template <class T>
void Volume<T>::addData(const Volume<T>& other)
{
	int i, j, k, l;
	//
	if (VolumeBase<T>::m_vd_x != other.m_vd_x || VolumeBase<T>::m_vd_y != other.m_vd_y || VolumeBase<T>::m_vd_z != other.m_vd_z || VolumeBase<T>::m_vd_s != other.m_vd_s) {
		return;
	}
	//
	if (VolumeBase<T>::m_nElements > 0) {
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						VolumeBase<T>::m_pData[k][j][i][l] += other.m_pData[k][j][i][l];
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------------------
// subtract other image
//------------------------------------------------------------------------------------------
template <class T>
void Volume<T>::subData(const Volume<T>& other)
{
	int i, j, k, l;
	//
	if (VolumeBase<T>::m_vd_x != other.m_vd_x || VolumeBase<T>::m_vd_y != other.m_vd_y || VolumeBase<T>::m_vd_z != other.m_vd_z || VolumeBase<T>::m_vd_s != other.m_vd_s) {
		return;
	}
	//
	if (VolumeBase<T>::m_nElements > 0) {
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						VolumeBase<T>::m_pData[k][j][i][l] -= other.m_pData[k][j][i][l];
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------------------
// override equal operator
//------------------------------------------------------------------------------------------
template <class T>
Volume<T>& Volume<T>::operator=(const Volume<T>& other)
{
	copyData(other);
	return *this;
}

//------------------------------------------------------------------------------------------
// override add operator
//------------------------------------------------------------------------------------------
template <class T>
Volume<T>& Volume<T>::operator+=(const Volume<T>& other)
{
	addData(other);
	return *this;
}

//------------------------------------------------------------------------------------------
// override subtract operator
//------------------------------------------------------------------------------------------
template <class T>
Volume<T>& Volume<T>::operator-=(const Volume<T>& other)
{
	subData(other);
	return *this;
}

//------------------------------------------------------------------------------------------
// resize the image
//------------------------------------------------------------------------------------------
template <class T>
bool Volume<T>::imresize(float ratio, bool bNN)
{
	Volume<T> dst;
	int vd2_x, vd2_y, vd2_z;
	int i, j, k, l;
	float fx, fy, fz;
	float fx1, fy1, fz1;
	float f1, f2, f3, f4, f5, f6, f7, f8;
	T *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *dv;
	double val;
	int ix, iy, iz, ix1, iy1, iz1;

	if (VolumeBase<T>::m_pData == NULL) {
		return false;
	}

#ifndef _TIME_CHECK
	CGProgressBar Bar("Resizing...", 100);
#endif

	//vd2_x = (int)_round(m_vd_x * ratio);
	//vd2_y = (int)_round(m_vd_y * ratio);
	//vd2_z = (int)_round(m_vd_z * ratio);
	vd2_x = (int)(VolumeBase<T>::m_vd_x * ratio);
	vd2_y = (int)(VolumeBase<T>::m_vd_y * ratio);
	vd2_z = (int)(VolumeBase<T>::m_vd_z * ratio);
	dst.allocate(vd2_x, vd2_y, vd2_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);

	for (k = 0; k < vd2_z; k++) {
		fz = k / ratio;
		iz = (int)fz;
		fz = fz - iz; 
		fz1 = 1-fz; 
		iz1 = MIN(iz+1, VolumeBase<T>::m_vd_z-1);
		for (j = 0; j < vd2_y; j++) {
			fy = j / ratio;
			iy = (int)fy;
			fy = fy - iy; 
			fy1 = 1-fy; 
			iy1 = MIN(iy+1, VolumeBase<T>::m_vd_y-1);
			for (i = 0; i < vd2_x; i++) {
				fx = i / ratio;
				ix = (int)fx;
				fx = fx - ix; 
				fx1 = 1-fx;
				ix1 = MIN(ix+1, VolumeBase<T>::m_vd_x-1);

				if (bNN) {
					if (fz < 0.5f) {
						if (fy < 0.5f) {
							if (fx < 0.5f) {
								v1 = VolumeBase<T>::m_pData[iz ][iy ][ix ];
							} else {
								v1 = VolumeBase<T>::m_pData[iz ][iy ][ix1];
							}
						} else {
							if (fx < 0.5f) {
								v1 = VolumeBase<T>::m_pData[iz ][iy1][ix ];
							} else {
								v1 = VolumeBase<T>::m_pData[iz ][iy1][ix1];
							}
						}
					} else {
						if (fy < 0.5f) {
							if (fx < 0.5f) {
								v1 = VolumeBase<T>::m_pData[iz1][iy ][ix ];
							} else {
								v1 = VolumeBase<T>::m_pData[iz1][iy ][ix1];
							}
						} else {
							if (fx < 0.5f) {
								v1 = VolumeBase<T>::m_pData[iz1][iy1][ix ];
							} else {
								v1 = VolumeBase<T>::m_pData[iz1][iy1][ix1];
							}
						}
					}
					dv = dst.m_pData[k][j][i];
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						dv[l] = v1[l];
					}
				} else {
					f1 = fx1*fy1*fz1; v1 = VolumeBase<T>::m_pData[iz ][iy ][ix ];
					f2 = fx *fy1*fz1; v2 = VolumeBase<T>::m_pData[iz ][iy ][ix1];
					f3 = fx1*fy *fz1; v3 = VolumeBase<T>::m_pData[iz ][iy1][ix ];
					f4 = fx1*fy1*fz ; v4 = VolumeBase<T>::m_pData[iz1][iy ][ix ];
					f5 = fx *fy *fz1; v5 = VolumeBase<T>::m_pData[iz ][iy1][ix1];
					f6 = fx *fy1*fz ; v6 = VolumeBase<T>::m_pData[iz1][iy ][ix1];
					f7 = fx1*fy *fz ; v7 = VolumeBase<T>::m_pData[iz1][iy1][ix ];
					f8 = fx *fy *fz ; v8 = VolumeBase<T>::m_pData[iz1][iy1][ix1];
					dv = dst.m_pData[k][j][i];
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						val  = f1 * v1[l];
						val += f2 * v2[l];
						val += f3 * v3[l];
						val += f4 * v4[l];
						val += f5 * v5[l];
						val += f6 * v6[l];
						val += f7 * v7[l];
						val += f8 * v8[l];
						dv[l] = (T)val;
					}
				}
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*k/vd2_z);
#endif
	}

	copyData(dst);

	return true;
}

template <class T>
template <class T1>
bool Volume<T>::imresize(Volume<T1>& dst, int dst_x, int dst_y, int dst_z, int dst_s, bool bNN) const
{
	int i, j, k, l;
	float fx, fy, fz;
	float fx1, fy1, fz1;
	float f1, f2, f3, f4, f5, f6, f7, f8;
	T *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *dv;
	double val;
	int ix, iy, iz, ix1, iy1, iz1;
	float xRatio = (float)dst_x / VolumeBase<T>::m_vd_x;
	float yRatio = (float)dst_y / VolumeBase<T>::m_vd_y;
	float zRatio = (float)dst_z / VolumeBase<T>::m_vd_z;

	if (VolumeBase<T>::m_pData == NULL || VolumeBase<T>::m_vd_s != dst_s) {
		return false;
	}

	if (dst.m_vd_x != dst_x || dst.m_vd_y != dst_y || dst.m_vd_z != dst_z || dst.m_vd_s != dst_s) {
		dst.allocate(dst_x, dst_y, dst_z, dst_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);
	}

#ifndef _TIME_CHECK
	CGProgressBar Bar("Resizing...", 100);
#endif

	for (k = 0; k < dst_z; k++) {
		fz = k / zRatio;
		iz = (int)fz;
		fz = fz - iz; 
		fz1 = 1-fz;
		iz1 = MIN(iz+1, VolumeBase<T>::m_vd_z-1);
		for (j = 0; j < dst_y; j++) {
			fy = j / yRatio;
			iy = (int)fy;
			fy = fy - iy; 
			fy1 = 1-fy; 
			iy1 = MIN(iy+1, VolumeBase<T>::m_vd_y-1);
			for (i = 0; i < dst_x; i++) {
				fx = i / xRatio;
				ix = (int)fx;
				fx = fx - ix; 
				fx1 = 1-fx;
				ix1 = MIN(ix+1, VolumeBase<T>::m_vd_x-1);

				if (bNN) {
					if (fz < 0.5f) {
						if (fy < 0.5f) {
							if (fx < 0.5f) {
								v1 = VolumeBase<T>::m_pData[iz ][iy ][ix ];
							} else {
								v1 = VolumeBase<T>::m_pData[iz ][iy ][ix1];
							}
						} else {
							if (fx < 0.5f) {
								v1 = VolumeBase<T>::m_pData[iz ][iy1][ix ];
							} else {
								v1 = VolumeBase<T>::m_pData[iz ][iy1][ix1];
							}
						}
					} else {
						if (fy < 0.5f) {
							if (fx < 0.5f) {
								v1 = VolumeBase<T>::m_pData[iz1][iy ][ix ];
							} else {
								v1 = VolumeBase<T>::m_pData[iz1][iy ][ix1];
							}
						} else {
							if (fx < 0.5f) {
								v1 = VolumeBase<T>::m_pData[iz1][iy1][ix ];
							} else {
								v1 = VolumeBase<T>::m_pData[iz1][iy1][ix1];
							}
						}
					}
					dv = dst.m_pData[k][j][i];
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						dv[l] = v1[l];
					}
				} else {
					f1 = fx1*fy1*fz1; v1 = VolumeBase<T>::m_pData[iz ][iy ][ix ];
					f2 = fx *fy1*fz1; v2 = VolumeBase<T>::m_pData[iz ][iy ][ix1];
					f3 = fx1*fy *fz1; v3 = VolumeBase<T>::m_pData[iz ][iy1][ix ];
					f4 = fx1*fy1*fz ; v4 = VolumeBase<T>::m_pData[iz1][iy ][ix ];
					f5 = fx *fy *fz1; v5 = VolumeBase<T>::m_pData[iz ][iy1][ix1];
					f6 = fx *fy1*fz ; v6 = VolumeBase<T>::m_pData[iz1][iy ][ix1];
					f7 = fx1*fy *fz ; v7 = VolumeBase<T>::m_pData[iz1][iy1][ix ];
					f8 = fx *fy *fz ; v8 = VolumeBase<T>::m_pData[iz1][iy1][ix1];
					dv = dst.m_pData[k][j][i];
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						val  = f1 * v1[l];
						val += f2 * v2[l];
						val += f3 * v3[l];
						val += f4 * v4[l];
						val += f5 * v5[l];
						val += f6 * v6[l];
						val += f7 * v7[l];
						val += f8 * v8[l];
						dv[l] = (T)val;
					}
				}
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos(100*k/dst_z);
#endif
	}

	return true;
}

template<class T>
void Volume<T>::ReduceVolume(Volume<T>& dst, bool bAvg)
{
	T val;
	int i, j, k, l, ii, jj, kk;
	int x, y, z, sum;
	int vd_x = VolumeBase<T>::m_vd_x >> 1;
	int vd_y = VolumeBase<T>::m_vd_y >> 1;
	int vd_z = VolumeBase<T>::m_vd_z >> 1;
	
	dst.allocate(vd_x, vd_y, vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);

	for (k = 0; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
					sum = 0;
					val = 0;
					for (kk = 0; kk < 2; kk++) {
						z = (k << 1) + kk;
						if (z >= VolumeBase<T>::m_vd_z) { continue; }
						for (jj = 0; jj < 2; jj++) {
							y = (j << 1) + jj;
							if (y >= VolumeBase<T>::m_vd_y) { continue; }
							for (ii = 0; ii < 2; ii++) {
								x = (i << 1) + ii;
								if (x >= VolumeBase<T>::m_vd_x) { continue; }
								val += VolumeBase<T>::m_pData[z][y][x][l];
								sum++;
							}
						}
					}
					if (bAvg) {
						dst.m_pData[k][j][i][l] = val / sum;
					} else {
						dst.m_pData[k][j][i][l] = val;
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------------------
// function to do Gaussian smoothing
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Volume<T>::GaussianSmoothing(Volume<T1>& vol, double sigma, int fsize) const 
{
	Volume<T1> vol1;
	int i, j, k, l, f, ii, jj, kk;
	double* gFilter;
	double w;
	int m_vd_x_1, m_vd_y_1, m_vd_z_1;
	T *sv, *dv;

	m_vd_x_1 = VolumeBase<T>::m_vd_x - 1;
	m_vd_y_1 = VolumeBase<T>::m_vd_y - 1;
	m_vd_z_1 = VolumeBase<T>::m_vd_z - 1;

	// constructing the 1D gaussian filter
	gFilter = new double[fsize*2+1];
	//
	{
		double sum = 0;
		double sigma2 = sigma*sigma*2;
		for (i = -fsize; i <= fsize; i++) {
			gFilter[i+fsize] = exp(-(double)(i*i) / sigma2);
			sum += gFilter[i+fsize];
		}
		for (i = 0; i < 2*fsize+1; i++) {
			gFilter[i] /= sum;
		}
	}

#ifndef _TIME_CHECK
	CGProgressBar Bar("Gaussian Smoothing...", 100);
#endif

	// apply filtering
	vol.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);
	vol1.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);
	//
	for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
		for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
			for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
				for (f = -fsize; f <= fsize; f++) {
					w = gFilter[f+fsize];

					//ii = __min(__max(i+f,0), m_vd_x-1);
					ii = i + f;
					if (ii < 0       ) { ii = 0;        }
					if (ii > m_vd_x_1) { ii = m_vd_x_1; }

					sv = VolumeBase<T>::m_pData[k][j][ii];
					dv = vol.m_pData[k][j][i];
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						dv[l] += (T)(w * sv[l]);
					}
				}
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos(33*k/VolumeBase<T>::m_vd_z);
#endif
	}
	//
	for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
		for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (f = -fsize; f <= fsize; f++) {
					w = gFilter[f+fsize];

					//jj = __min(__max(j+f,0), m_vd_y-1);
					jj = j + f;
					if (jj < 0       ) { jj = 0;        }
					if (jj > m_vd_y_1) { jj = m_vd_y_1; }

					sv = vol.m_pData[k][jj][i];
					dv = vol1.m_pData[k][j][i];
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						dv[l] += (T)(w * sv[l]);
					}
				}
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos(33+33*k/VolumeBase<T>::m_vd_z);
#endif
	}
	//
	vol.setValue(0);
	//
	for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
		for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
			for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
				for (f = -fsize; f <= fsize; f++) {
					w = gFilter[f+fsize];

					//kk = __min(__max(k+f,0), m_vd_z-1);
					kk = k + f;
					if (kk < 0       ) { kk = 0;        }
					if (kk > m_vd_z_1) { kk = m_vd_z_1; }

					sv = vol1.m_pData[kk][j][i];
					dv = vol.m_pData[k][j][i];
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						dv[l] += (T)(w * sv[l]);
					}
				}
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos(66+34*j/VolumeBase<T>::m_vd_y);
#endif
	}

	delete gFilter;
}

//------------------------------------------------------------------------------------------
// function to get Gradient
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Volume<T>::GetGradient(Volume<T1>& gx, Volume<T1>& gy, Volume<T1>& gz) const 
{
	int i, j, k, l;
	int m_vd_x_1, m_vd_y_1, m_vd_z_1;

	m_vd_x_1 = VolumeBase<T>::m_vd_x - 1;
	m_vd_y_1 = VolumeBase<T>::m_vd_y - 1;
	m_vd_z_1 = VolumeBase<T>::m_vd_z - 1;

	gx.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);
	gy.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);
	gz.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);

#ifndef _TIME_CHECK
	CGProgressBar Bar("Apply Sobel Mask...", 100);
#endif

	// Computing derivatives using 3D Sobel operator
	for (k = 1; k < m_vd_z_1; k++) {
		for (j = 1; j < m_vd_y_1; j++) {
			T1 q_val;
			T** p_z_0_y_1 = &VolumeBase<T>::m_pData[k-1][j  ][1];
			T** p_z_1_y_0 = &VolumeBase<T>::m_pData[k  ][j-1][1];
			T** p_z_1_y_1 = &VolumeBase<T>::m_pData[k  ][j  ][1];
			T** p_z_1_y_2 = &VolumeBase<T>::m_pData[k  ][j+1][1];
			T** p_z_2_y_1 = &VolumeBase<T>::m_pData[k+1][j  ][1];
			T1** q_gx = &gx.m_pData[k][j][1];
			T1** q_gy = &gy.m_pData[k][j][1];
			T1** q_gz = &gz.m_pData[k][j][1];
			for (i = 1; i < m_vd_x_1; i++) {
				for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
					q_val = (*(p_z_1_y_1+1)[l] - *(p_z_1_y_1-1)[l]);
					(*q_gx)[l] = q_val * 0.5;

					q_val = (*(p_z_1_y_2  )[l] - *(p_z_1_y_0  )[l]);
					(*q_gy)[l] = q_val * 0.5;

					q_val = (*(p_z_2_y_1  )[l] - *(p_z_0_y_1  )[l]);
					(*q_gz)[l] = q_val * 0.5;
				}

				             p_z_0_y_1++;
				p_z_1_y_0++; p_z_1_y_1++; p_z_1_y_2++;
				             p_z_2_y_1++;

				q_gx++; q_gy++; q_gz++;
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos((100*k)/m_vd_z);
#endif
	}
}

//------------------------------------------------------------------------------------------
// function to get Gradient
//------------------------------------------------------------------------------------------
template <class T>
template <class T1, class T2>
void Volume<T>::GetGradient(Volume<T1>& gx, Volume<T1>& gy, Volume<T1>& gz, Volume<T2>& mask, T2 mask_th) const 
{
	int i, j, k, l;
	int m_vd_x_1, m_vd_y_1, m_vd_z_1;

	m_vd_x_1 = VolumeBase<T>::m_vd_x - 1;
	m_vd_y_1 = VolumeBase<T>::m_vd_y - 1;
	m_vd_z_1 = VolumeBase<T>::m_vd_z - 1;

	gx.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);
	gy.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);
	gz.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);

#ifndef _TIME_CHECK
	CGProgressBar Bar("Apply Sobel Mask...", 100);
#endif

	// Computing derivatives using 3D Sobel operator
	for (k = 1; k < m_vd_z_1; k++) {
		for (j = 1; j < m_vd_y_1; j++) {
			T1 q_val;
			T** p_z_0_y_1 = &VolumeBase<T>::m_pData[k-1][j  ][1];
			T** p_z_1_y_0 = &VolumeBase<T>::m_pData[k  ][j-1][1];
			T** p_z_1_y_1 = &VolumeBase<T>::m_pData[k  ][j  ][1];
			T** p_z_1_y_2 = &VolumeBase<T>::m_pData[k  ][j+1][1];
			T** p_z_2_y_1 = &VolumeBase<T>::m_pData[k+1][j  ][1];
			T2** m_z_0_y_1 = &mask.m_pData[k-1][j  ][1];
			T2** m_z_1_y_0 = &mask.m_pData[k  ][j-1][1];
			T2** m_z_1_y_1 = &mask.m_pData[k  ][j  ][1];
			T2** m_z_1_y_2 = &mask.m_pData[k  ][j+1][1];
			T2** m_z_2_y_1 = &mask.m_pData[k+1][j  ][1];
			T1** q_gx = &gx.m_pData[k][j][1];
			T1** q_gy = &gy.m_pData[k][j][1];
			T1** q_gz = &gz.m_pData[k][j][1];
			for (i = 1; i < m_vd_x_1; i++) {
				for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
					if (*(m_z_1_y_1+1)[0] > mask_th && *(p_z_1_y_1-1)[0] > mask_th) {
						q_val = (*(p_z_1_y_1+1)[l] - *(p_z_1_y_1-1)[l]);
						(*q_gx)[l] = q_val * 0.5;
					}

					if (*(m_z_1_y_2  )[0] > mask_th && *(m_z_1_y_0  )[0] > mask_th) {
						q_val = (*(p_z_1_y_2  )[l] - *(p_z_1_y_0  )[l]);
						(*q_gy)[l] = q_val * 0.5;
					}

					if (*(m_z_2_y_1  )[0] > mask_th && *(m_z_0_y_1  )[0] > mask_th) {
						q_val = (*(p_z_2_y_1  )[l] - *(p_z_0_y_1  )[l]);
						(*q_gz)[l] = q_val * 0.5;
					}
				}

				             p_z_0_y_1++;
				p_z_1_y_0++; p_z_1_y_1++; p_z_1_y_2++;
				             p_z_2_y_1++;

				             m_z_0_y_1++;
				m_z_1_y_0++; m_z_1_y_1++; m_z_1_y_2++;
				             m_z_2_y_1++;

				q_gx++; q_gy++; q_gz++;
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos((100*k)/m_vd_z);
#endif
	}
}

//------------------------------------------------------------------------------------------
// function to get Gradient
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Volume<T>::GetGradientSobel(Volume<T1>& gx, Volume<T1>& gy, Volume<T1>& gz) const 
{
	int i, j, k, l;
	int m_vd_x_1, m_vd_y_1, m_vd_z_1;

	m_vd_x_1 = VolumeBase<T>::m_vd_x - 1;
	m_vd_y_1 = VolumeBase<T>::m_vd_y - 1;
	m_vd_z_1 = VolumeBase<T>::m_vd_z - 1;

	gx.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);
	gy.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);
	gz.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);

#ifndef _TIME_CHECK
	CGProgressBar Bar("Apply Sobel Mask...", 100);
#endif

	// Computing derivatives using 3D Sobel operator
	for (k = 1; k < m_vd_z_1; k++) {
		for (j = 1; j < m_vd_y_1; j++) {
			T1 q_val;
			T** p_z_0_y_0 = &VolumeBase<T>::m_pData[k-1][j-1][1];
			T** p_z_0_y_1 = &VolumeBase<T>::m_pData[k-1][j  ][1];
			T** p_z_0_y_2 = &VolumeBase<T>::m_pData[k-1][j+1][1];
			T** p_z_1_y_0 = &VolumeBase<T>::m_pData[k  ][j-1][1];
			T** p_z_1_y_1 = &VolumeBase<T>::m_pData[k  ][j  ][1];
			T** p_z_1_y_2 = &VolumeBase<T>::m_pData[k  ][j+1][1];
			T** p_z_2_y_0 = &VolumeBase<T>::m_pData[k+1][j-1][1];
			T** p_z_2_y_1 = &VolumeBase<T>::m_pData[k+1][j  ][1];
			T** p_z_2_y_2 = &VolumeBase<T>::m_pData[k+1][j+1][1];
			T1** q_gx = &gx.m_pData[k][j][1];
			T1** q_gy = &gy.m_pData[k][j][1];
			T1** q_gz = &gz.m_pData[k][j][1];
			for (i = 1; i < m_vd_x_1; i++) {
				for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
					q_val  = (*(p_z_0_y_0+1)[l] - *(p_z_0_y_0-1)[l])  ;
					q_val += (*(p_z_0_y_1+1)[l] - *(p_z_0_y_1-1)[l])*2;
					q_val += (*(p_z_0_y_2+1)[l] - *(p_z_0_y_2-1)[l])  ;
					q_val += (*(p_z_1_y_0+1)[l] - *(p_z_1_y_0-1)[l])*2;
					q_val += (*(p_z_1_y_1+1)[l] - *(p_z_1_y_1-1)[l])*4;
					q_val += (*(p_z_1_y_2+1)[l] - *(p_z_1_y_2-1)[l])*2;
					q_val += (*(p_z_2_y_0+1)[l] - *(p_z_2_y_0-1)[l])  ;
					q_val += (*(p_z_2_y_1+1)[l] - *(p_z_2_y_1-1)[l])*2;
					q_val += (*(p_z_2_y_2+1)[l] - *(p_z_2_y_2-1)[l])  ;
					(*q_gx)[l] = q_val * 0.0625;

					q_val  = (*(p_z_0_y_2-1)[l] - *(p_z_0_y_0-1)[l])  ;
					q_val += (*(p_z_0_y_2  )[l] - *(p_z_0_y_0  )[l])*2;
					q_val += (*(p_z_0_y_2+1)[l] - *(p_z_0_y_0+1)[l])  ;
					q_val += (*(p_z_1_y_2-1)[l] - *(p_z_1_y_0-1)[l])*2;
					q_val += (*(p_z_1_y_2  )[l] - *(p_z_1_y_0  )[l])*4;
					q_val += (*(p_z_1_y_2+1)[l] - *(p_z_1_y_0+1)[l])*2;
					q_val += (*(p_z_2_y_2-1)[l] - *(p_z_2_y_0-1)[l])  ;
					q_val += (*(p_z_2_y_2  )[l] - *(p_z_2_y_0  )[l])*2;
					q_val += (*(p_z_2_y_2+1)[l] - *(p_z_2_y_0+1)[l])  ;
					(*q_gy)[l] = q_val * 0.0625;

					q_val  = (*(p_z_2_y_0-1)[l] - *(p_z_0_y_0-1)[l])  ;
					q_val += (*(p_z_2_y_0  )[l] - *(p_z_0_y_0  )[l])*2;
					q_val += (*(p_z_2_y_0+1)[l] - *(p_z_0_y_0+1)[l])  ;
					q_val += (*(p_z_2_y_1-1)[l] - *(p_z_0_y_1-1)[l])*2;
					q_val += (*(p_z_2_y_1  )[l] - *(p_z_0_y_1  )[l])*4;
					q_val += (*(p_z_2_y_1+1)[l] - *(p_z_0_y_1+1)[l])*2;
					q_val += (*(p_z_2_y_2-1)[l] - *(p_z_0_y_2-1)[l])  ;
					q_val += (*(p_z_2_y_2  )[l] - *(p_z_0_y_2  )[l])*2;
					q_val += (*(p_z_2_y_2+1)[l] - *(p_z_0_y_2+1)[l])  ;
					(*q_gz)[l] = q_val * 0.0625;
				}

				p_z_0_y_0++; p_z_0_y_1++; p_z_0_y_2++;
				p_z_1_y_0++; p_z_1_y_1++; p_z_1_y_2++;
				p_z_2_y_0++; p_z_2_y_1++; p_z_2_y_2++;

				q_gx++; q_gy++; q_gz++;
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos((100*k)/m_vd_z);
#endif
	}
}

//------------------------------------------------------------------------------------------
// function to get Gradient Weight
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Volume<T>::GetGradientWeightSobel(Volume<T1>& gw) const 
{
	int i, j, k, l;
	int m_vd_x_1, m_vd_y_1, m_vd_z_1;

	m_vd_x_1 = VolumeBase<T>::m_vd_x - 1;
	m_vd_y_1 = VolumeBase<T>::m_vd_y - 1;
	m_vd_z_1 = VolumeBase<T>::m_vd_z - 1;

	gw.allocate(VolumeBase<T>::m_vd_x, VolumeBase<T>::m_vd_y, VolumeBase<T>::m_vd_z, VolumeBase<T>::m_vd_s, VolumeBase<T>::m_vd_dx, VolumeBase<T>::m_vd_dy, VolumeBase<T>::m_vd_dz);

#ifndef _TIME_CHECK
	CGProgressBar Bar("Apply Sobel Mask...", 100);
#endif

	// Computing derivatives using 3D Sobel operator
	for (k = 1; k < m_vd_z_1; k++) {
		for (j = 1; j < m_vd_y_1; j++) {
			T1 q_val;
			T1 gx, gy, gz;
			T** p_z_0_y_0 = &VolumeBase<T>::m_pData[k-1][j-1][1];
			T** p_z_0_y_1 = &VolumeBase<T>::m_pData[k-1][j  ][1];
			T** p_z_0_y_2 = &VolumeBase<T>::m_pData[k-1][j+1][1];
			T** p_z_1_y_0 = &VolumeBase<T>::m_pData[k  ][j-1][1];
			T** p_z_1_y_1 = &VolumeBase<T>::m_pData[k  ][j  ][1];
			T** p_z_1_y_2 = &VolumeBase<T>::m_pData[k  ][j+1][1];
			T** p_z_2_y_0 = &VolumeBase<T>::m_pData[k+1][j-1][1];
			T** p_z_2_y_1 = &VolumeBase<T>::m_pData[k+1][j  ][1];
			T** p_z_2_y_2 = &VolumeBase<T>::m_pData[k+1][j+1][1];
			T1** q_gw = &gw.m_pData[k][j][1];
			for (i = 1; i < m_vd_x_1; i++) {
				for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
					q_val  = (*(p_z_0_y_0+1)[l] - *(p_z_0_y_0-1)[l])  ;
					q_val += (*(p_z_0_y_1+1)[l] - *(p_z_0_y_1-1)[l])*2;
					q_val += (*(p_z_0_y_2+1)[l] - *(p_z_0_y_2-1)[l])  ;
					q_val += (*(p_z_1_y_0+1)[l] - *(p_z_1_y_0-1)[l])*2;
					q_val += (*(p_z_1_y_1+1)[l] - *(p_z_1_y_1-1)[l])*4;
					q_val += (*(p_z_1_y_2+1)[l] - *(p_z_1_y_2-1)[l])*2;
					q_val += (*(p_z_2_y_0+1)[l] - *(p_z_2_y_0-1)[l])  ;
					q_val += (*(p_z_2_y_1+1)[l] - *(p_z_2_y_1-1)[l])*2;
					q_val += (*(p_z_2_y_2+1)[l] - *(p_z_2_y_2-1)[l])  ;
					gx = q_val * 0.0625;

					q_val  = (*(p_z_0_y_2-1)[l] - *(p_z_0_y_0-1)[l])  ;
					q_val += (*(p_z_0_y_2  )[l] - *(p_z_0_y_0  )[l])*2;
					q_val += (*(p_z_0_y_2+1)[l] - *(p_z_0_y_0+1)[l])  ;
					q_val += (*(p_z_1_y_2-1)[l] - *(p_z_1_y_0-1)[l])*2;
					q_val += (*(p_z_1_y_2  )[l] - *(p_z_1_y_0  )[l])*4;
					q_val += (*(p_z_1_y_2+1)[l] - *(p_z_1_y_0+1)[l])*2;
					q_val += (*(p_z_2_y_2-1)[l] - *(p_z_2_y_0-1)[l])  ;
					q_val += (*(p_z_2_y_2  )[l] - *(p_z_2_y_0  )[l])*2;
					q_val += (*(p_z_2_y_2+1)[l] - *(p_z_2_y_0+1)[l])  ;
					gy = q_val * 0.0625;

					q_val  = (*(p_z_2_y_0-1)[l] - *(p_z_0_y_0-1)[l])  ;
					q_val += (*(p_z_2_y_0  )[l] - *(p_z_0_y_0  )[l])*2;
					q_val += (*(p_z_2_y_0+1)[l] - *(p_z_0_y_0+1)[l])  ;
					q_val += (*(p_z_2_y_1-1)[l] - *(p_z_0_y_1-1)[l])*2;
					q_val += (*(p_z_2_y_1  )[l] - *(p_z_0_y_1  )[l])*4;
					q_val += (*(p_z_2_y_1+1)[l] - *(p_z_0_y_1+1)[l])*2;
					q_val += (*(p_z_2_y_2-1)[l] - *(p_z_0_y_2-1)[l])  ;
					q_val += (*(p_z_2_y_2  )[l] - *(p_z_0_y_2  )[l])*2;
					q_val += (*(p_z_2_y_2+1)[l] - *(p_z_0_y_2+1)[l])  ;
					gz = q_val * 0.0625;

					(*q_gw)[l] = sqrt(gx*gx + gy*gy + gz*gz);
				}

				p_z_0_y_0++; p_z_0_y_1++; p_z_0_y_2++;
				p_z_1_y_0++; p_z_1_y_1++; p_z_1_y_2++;
				p_z_2_y_0++; p_z_2_y_1++; p_z_2_y_2++;

				q_gw++;
			}
		}
#ifndef _TIME_CHECK
		Bar.SetPos((100*k)/m_vd_z);
#endif
	}
}

//------------------------------------------------------------------------------------------
// Normalize Image
//------------------------------------------------------------------------------------------
template <class T>
void Volume<T>::NormalizeImage()
{
	int i, j, k, l;
	double min_val = 1e10;
	double max_val = -1e10;
	double scale;
	
	for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
		for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
			for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
				for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
					T val = VolumeBase<T>::m_pData[k][j][i][l];
					if (val < min_val) {
						min_val = val;
					}
					if (val > max_val) {
						max_val = val;
					}
				}
			}
		}
	}

	scale = max_val - min_val;
	scale = 1.0 / scale;

	for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
		for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
			for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
				for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
					T val = VolumeBase<T>::m_pData[k][j][i][l];
					VolumeBase<T>::m_pData[k][j][i][l] = (T)((val - min_val) * scale);
				}
			}
		}
	}
}

//------------------------------------------------------------------------------------------
// Normalize Size
//------------------------------------------------------------------------------------------
template <class T>
bool Volume<T>::NormalizeSize(bool bNN, bool bCrop, int wx, int wy, int wz)
{
	Volume<T> dst;
	Volume<T> dst2;
	int dst_x, dst_y, dst_z;
	int dst2_x, dst2_y, dst2_z;
	int i, j, k, l;

	if (VolumeBase<T>::m_vd_dx != 1.0f || VolumeBase<T>::m_vd_dy != 1.0f || VolumeBase<T>::m_vd_dz != 1.0f) {
		dst_x = (int)_round(VolumeBase<T>::m_vd_x * VolumeBase<T>::m_vd_dx);
		dst_y = (int)_round(VolumeBase<T>::m_vd_y * VolumeBase<T>::m_vd_dy);
		dst_z = (int)_round(VolumeBase<T>::m_vd_z * VolumeBase<T>::m_vd_dz);

		imresize(dst, dst_x, dst_y, dst_z, VolumeBase<T>::m_vd_s, bNN);

		VolumeBase<T>::m_vd_dx = 1.0f;
		VolumeBase<T>::m_vd_dy = 1.0f;
		VolumeBase<T>::m_vd_dz = 1.0f;
	} else {
		dst.copyData(*this);
	}

	/*
#ifdef USE_MYUTILS
	if (m_vd_oc == a75_transverse_flipped) {
		dst2_x = dst_x;
		dst2_y = dst_y;
		dst2_z = dst_z;
		dst2.copyData(dst);
	} else if (m_vd_oc == a75_transverse_unflipped) {
		dst2_x = dst_x;
		dst2_y = dst_y;
		dst2_z = dst_z;
		dst2.allocate(dst2_x, dst2_y, dst2_z, m_vd_s);
		for (k = 0; k < dst2_z; k++) {
			for (j = 0; j < dst2_y; j++) {
				for (i = 0; i < dst2_x; i++) {
					for (l = 0; l < m_vd_s; l++) {
						dst2.m_pData[k][j][i][l] = dst.m_pData[dst_z-k-1][j][i][l];
					}
				}
			}
		}
	} else if (m_vd_oc == a75_coronal_flipped) {
		dst2_x = dst_x;
		dst2_y = dst_z;
		dst2_z = dst_y;
		dst2.allocate(dst2_x, dst2_y, dst2_z, m_vd_s);
		for (k = 0; k < dst2_z; k++) {
			for (j = 0; j < dst2_y; j++) {
				for (i = 0; i < dst2_x; i++) {
					for (l = 0; l < m_vd_s; l++) {
						dst2.m_pData[k][dst2_y-j-1][i][l] = dst.m_pData[j][k][i][l];
					}
				}
			}
		}
	} else {
		return false;
	}

	m_vd_oc = a75_transverse_flipped;
#endif
	/*/
	dst2_x = dst_x;
	dst2_y = dst_y;
	dst2_z = dst_z;
	dst2.copyData(dst);
	//*/

	if (bCrop) {
		int cx1 = dst2_x / 2;
		int cy1 = dst2_y / 2;
		int cz1 = dst2_z / 2;
		int cx2 = wx / 2;
		int cy2 = wy / 2;
		int cz2 = wz / 2;
		int tx, ty, tz;

		// allocate -> initialize volume to 0
		dst.allocate(wx, wy, wz, VolumeBase<T>::m_vd_s);

		for (k = 0; k < wz; k++) {
			tz = k - cz2 + cz1;
			if (tz < 0 || tz >= dst2_z) { continue; }
			for (j = 0; j < wy; j++) {
				ty = j - cy2 + cy1;
				if (ty < 0 || ty >= dst2_y) { continue; }
				for (i = 0; i < wx; i++) {
					tx = i - cx2 + cx1;
					if (tx < 0 || tx >= dst2_x) { continue; }
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						dst.m_pData[k][j][i][l] = dst2.m_pData[tz][ty][tx][l];
					}
				}
			}
		}

		copyData(dst);
	} else {
		copyData(dst2);
	}

	return true;
}

template <class T>
void Volume<T>::GetAt(float fx, float fy, float fz, T* dv, bool bNN)
{
	int l;
	float fx1, fy1, fz1;
	float f1, f2, f3, f4, f5, f6, f7, f8;
	T *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8;
	double val;
	int ix, iy, iz, ix1, iy1, iz1;

	fx = MAX(0, fx);
	fy = MAX(0, fy);
	fz = MAX(0, fz);
	fx = MIN(fx, VolumeBase<T>::m_vd_x-1);
	fy = MIN(fy, VolumeBase<T>::m_vd_y-1);
	fz = MIN(fz, VolumeBase<T>::m_vd_z-1);
	//
	ix = (int)fx;
	fx = fx - ix; 
	fx1 = 1-fx;
	ix1 = MIN(ix+1, VolumeBase<T>::m_vd_x-1);
	iy = (int)fy;
	fy = fy - iy; 
	fy1 = 1-fy; 
	iy1 = MIN(iy+1, VolumeBase<T>::m_vd_y-1);
	iz = (int)fz;
	fz = fz - iz; 
	fz1 = 1-fz;
	iz1 = MIN(iz+1, VolumeBase<T>::m_vd_z-1);

	if (bNN) {
		if (fz < 0.5f) {
			if (fy < 0.5f) {
				if (fx < 0.5f) {
					v1 = VolumeBase<T>::m_pData[iz ][iy ][ix ];
				} else {
					v1 = VolumeBase<T>::m_pData[iz ][iy ][ix1];
				}
			} else {
				if (fx < 0.5f) {
					v1 = VolumeBase<T>::m_pData[iz ][iy1][ix ];
				} else {
					v1 = VolumeBase<T>::m_pData[iz ][iy1][ix1];
				}
			}
		} else {
			if (fy < 0.5f) {
				if (fx < 0.5f) {
					v1 = VolumeBase<T>::m_pData[iz1][iy ][ix ];
				} else {
					v1 = VolumeBase<T>::m_pData[iz1][iy ][ix1];
				}
			} else {
				if (fx < 0.5f) {
					v1 = VolumeBase<T>::m_pData[iz1][iy1][ix ];
				} else {
					v1 = VolumeBase<T>::m_pData[iz1][iy1][ix1];
				}
			}
		}
		for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
			dv[l] = v1[l];
		}
	} else {
		f1 = fx1*fy1*fz1; v1 = VolumeBase<T>::m_pData[iz ][iy ][ix ];
		f2 = fx *fy1*fz1; v2 = VolumeBase<T>::m_pData[iz ][iy ][ix1];
		f3 = fx1*fy *fz1; v3 = VolumeBase<T>::m_pData[iz ][iy1][ix ];
		f4 = fx1*fy1*fz ; v4 = VolumeBase<T>::m_pData[iz1][iy ][ix ];
		f5 = fx *fy *fz1; v5 = VolumeBase<T>::m_pData[iz ][iy1][ix1];
		f6 = fx *fy1*fz ; v6 = VolumeBase<T>::m_pData[iz1][iy ][ix1];
		f7 = fx1*fy *fz ; v7 = VolumeBase<T>::m_pData[iz1][iy1][ix ];
		f8 = fx *fy *fz ; v8 = VolumeBase<T>::m_pData[iz1][iy1][ix1];
		for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
			val  = f1 * v1[l];
			val += f2 * v2[l];
			val += f3 * v3[l];
			val += f4 * v4[l];
			val += f5 * v5[l];
			val += f6 * v6[l];
			val += f7 * v7[l];
			val += f8 * v8[l];
			dv[l] = (T)val;
		}
	}
}

template <class T>
void Volume<T>::MultiplyValue(float mv)
{
	int i, j, k, l;
	//
	if (VolumeBase<T>::m_pData != NULL) {
		for (k = 0; k < VolumeBase<T>::m_vd_z; k++) {
			for (j = 0; j < VolumeBase<T>::m_vd_y; j++) {
				for (i = 0; i < VolumeBase<T>::m_vd_x; i++) {
					for (l = 0; l < VolumeBase<T>::m_vd_s; l++) {
						VolumeBase<T>::m_pData[k][j][i][l] = (T)(VolumeBase<T>::m_pData[k][j][i][l] * mv);
					}
				}
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// unit is mm
template <class T1, class T2>
void GenerateBackwardWarpVolume(Volume<T1>& vdt, Volume<T1>& vd, Volume<T2>& v3, T1 pval = 0, bool bNN = false)
{
	int i, j, k, l;
	float fx, fy, fz, fx1, fy1, fz1;
	int ix, iy, iz;
	int vd_x, vd_y, vd_z, vd_s, vd_x_1, vd_y_1, vd_z_1;
	int vdt_x, vdt_y, vdt_z, vdt_s;
	double val;
	float vd_dx, vd_dy, vd_dz, _vd_dx, _vd_dy, _vd_dz;

	vd_x = vd.m_vd_x;
	vd_y = vd.m_vd_y;
	vd_z = vd.m_vd_z;
	vd_s = vd.m_vd_s;
	vd_x_1 = vd_x - 1;
	vd_y_1 = vd_y - 1;
	vd_z_1 = vd_z - 1;
	vdt_x = vdt.m_vd_x;
	vdt_y = vdt.m_vd_y;
	vdt_z = vdt.m_vd_z;
	vdt_s = vdt.m_vd_s;
	//
	vd_dx = v3.m_vd_dx;
	vd_dy = v3.m_vd_dy;
	vd_dz = v3.m_vd_dz;
	_vd_dx = 1.0f / vd_dx;
	_vd_dy = 1.0f / vd_dy;
	_vd_dz = 1.0f / vd_dz;

	for (k = 0; k < vdt_z; k++) {
		for (j = 0; j < vdt_y; j++) {
			T1** q = vdt.m_pData[k][j];
			for (i = 0; i < vdt_x; i++) {
				fx = (float)i + v3.m_pData[k][j][i][0] * _vd_dx;
				fy = (float)j + v3.m_pData[k][j][i][1] * _vd_dy;
				fz = (float)k + v3.m_pData[k][j][i][2] * _vd_dz;
				ix = (int)fx;
				iy = (int)fy;
				iz = (int)fz;
				fx = fx - ix;
				fy = fy - iy;
				fz = fz - iz;

				if ((ix >= 1) && (ix < vd_x_1) && 
					(iy >= 1) && (iy < vd_y_1) && 
					(iz >= 1) && (iz < vd_z_1)) {
					fx1 = 1-fx; 
					fy1 = 1-fy; 
					fz1 = 1-fz;

					if (bNN) {
						T1 *v1, *dv;
						if (fz < 0.5f) {
							if (fy < 0.5f) {
								if (fx < 0.5f) {
									v1 = vd.m_pData[iz  ][iy  ][ix  ];
								} else {
									v1 = vd.m_pData[iz  ][iy  ][ix+1];
								}
							} else {
								if (fx < 0.5f) {
									v1 = vd.m_pData[iz  ][iy+1][ix  ];
								} else {
									v1 = vd.m_pData[iz  ][iy+1][ix+1];
								}
							}
						} else {
							if (fy < 0.5f) {
								if (fx < 0.5f) {
									v1 = vd.m_pData[iz+1][iy  ][ix  ];
								} else {
									v1 = vd.m_pData[iz+1][iy  ][ix+1];
								}
							} else {
								if (fx < 0.5f) {
									v1 = vd.m_pData[iz+1][iy+1][ix  ];
								} else {
									v1 = vd.m_pData[iz+1][iy+1][ix+1];
								}
							}
						}
						dv = vdt.m_pData[k][j][i];
						for (l = 0; l < vd_s; l++) {
							dv[l] = v1[l];
						}
					} else {
						for (l = 0; l < vd_s; l++) {
							val  = fx1*fy1*fz1 * vd.m_pData[iz  ][iy  ][ix  ][l];
							val += fx *fy1*fz1 * vd.m_pData[iz  ][iy  ][ix+1][l];
							val += fx *fy *fz1 * vd.m_pData[iz  ][iy+1][ix+1][l];
							val += fx *fy *fz  * vd.m_pData[iz+1][iy+1][ix+1][l];
							val += fx *fy1*fz  * vd.m_pData[iz+1][iy  ][ix+1][l];
							val += fx1*fy *fz1 * vd.m_pData[iz  ][iy+1][ix  ][l];
							val += fx1*fy *fz  * vd.m_pData[iz+1][iy+1][ix  ][l];
							val += fx1*fy1*fz  * vd.m_pData[iz+1][iy  ][ix  ][l];

							q[i][l] = (T1)val;
						}
					}
				} else {
					for (l = 0; l < vd_s; l++) {
						q[i][l] = pval;
					}
				}
			}
		}
	}
}

// unit is voxel
template <class T1, class T2>
BOOL GenerateBackwardWarpVolume(Volume<T1>& vdt, Volume<T1>& vd, Volume<T2>& vx, Volume<T2>& vy, Volume<T2>& vz, T1 pval = 0, bool bNN = false)
{
	int i, j, k, l;
	float fx, fy, fz, fx1, fy1, fz1;
	int ix, iy, iz;
	int vd_x, vd_y, vd_z, vd_s, vd_x_1, vd_y_1, vd_z_1;
	int vdt_x, vdt_y, vdt_z, vdt_s;
	double val;
	float vd_dx, vd_dy, vd_dz, _vd_dx, _vd_dy, _vd_dz;

	vd_x = vd.m_vd_x;
	vd_y = vd.m_vd_y;
	vd_z = vd.m_vd_z;
	vd_s = vd.m_vd_s;
	vd_x_1 = vd_x - 1;
	vd_y_1 = vd_y - 1;
	vd_z_1 = vd_z - 1;
	vdt_x = vdt.m_vd_x;
	vdt_y = vdt.m_vd_y;
	vdt_z = vdt.m_vd_z;
	vdt_s = vdt.m_vd_s;
	//
	vd_dx = vx.m_vd_dx;
	vd_dy = vx.m_vd_dy;
	vd_dz = vx.m_vd_dz;
	_vd_dx = 1.0f / vd_dx;
	_vd_dy = 1.0f / vd_dy;
	_vd_dz = 1.0f / vd_dz;

	for (k = 0; k < vdt_z; k++) {
		for (j = 0; j < vdt_y; j++) {
			T1** q = vdt.m_pData[k][j];
			for (i = 0; i < vdt_x; i++) {
				fx = (float)i + vx.m_pData[k][j][i][0];
				fy = (float)j + vy.m_pData[k][j][i][0];
				fz = (float)k + vz.m_pData[k][j][i][0];
				ix = (int)fx;
				iy = (int)fy;
				iz = (int)fz;
				fx = fx - ix;
				fy = fy - iy;
				fz = fz - iz;

				if ((ix >= 1) && (ix < vd_x_1) && 
					(iy >= 1) && (iy < vd_y_1) && 
					(iz >= 1) && (iz < vd_z_1)) {
					fx1 = 1-fx; 
					fy1 = 1-fy; 
					fz1 = 1-fz;

					if (bNN) {
						T1 *v1, *dv;
						if (fz < 0.5f) {
							if (fy < 0.5f) {
								if (fx < 0.5f) {
									v1 = vd.m_pData[iz  ][iy  ][ix  ];
								} else {
									v1 = vd.m_pData[iz  ][iy  ][ix+1];
								}
							} else {
								if (fx < 0.5f) {
									v1 = vd.m_pData[iz  ][iy+1][ix  ];
								} else {
									v1 = vd.m_pData[iz  ][iy+1][ix+1];
								}
							}
						} else {
							if (fy < 0.5f) {
								if (fx < 0.5f) {
									v1 = vd.m_pData[iz+1][iy  ][ix  ];
								} else {
									v1 = vd.m_pData[iz+1][iy  ][ix+1];
								}
							} else {
								if (fx < 0.5f) {
									v1 = vd.m_pData[iz+1][iy+1][ix  ];
								} else {
									v1 = vd.m_pData[iz+1][iy+1][ix+1];
								}
							}
						}
						dv = vdt.m_pData[k][j][i];
						for (l = 0; l < vd_s; l++) {
							dv[l] = v1[l];
						}
					} else {
						for (l = 0; l < vd_s; l++) {
							val  = fx1*fy1*fz1 * vd.m_pData[iz  ][iy  ][ix  ][l];
							val += fx *fy1*fz1 * vd.m_pData[iz  ][iy  ][ix+1][l];
							val += fx *fy *fz1 * vd.m_pData[iz  ][iy+1][ix+1][l];
							val += fx *fy *fz  * vd.m_pData[iz+1][iy+1][ix+1][l];
							val += fx *fy1*fz  * vd.m_pData[iz+1][iy  ][ix+1][l];
							val += fx1*fy *fz1 * vd.m_pData[iz  ][iy+1][ix  ][l];
							val += fx1*fy *fz  * vd.m_pData[iz+1][iy+1][ix  ][l];
							val += fx1*fy1*fz  * vd.m_pData[iz+1][iy  ][ix  ][l];

							q[i][l] = (T1)val;
						}
					}
				} else {
					for (l = 0; l < vd_s; l++) {
						q[i][l] = pval;
					}
				}
			}
		}
	}

	return TRUE;
}

// c = b o a
// unit is voxel
template <class T>
BOOL ConcatenateFields(Volume<T>& a_x, Volume<T>& a_y, Volume<T>& a_z, Volume<T>& b_x, Volume<T>& b_y, Volume<T>& b_z, Volume<T>& c_x, Volume<T>& c_y, Volume<T>& c_z)
{
	int i, j, k;
	int vd_x, vd_y, vd_z;

	vd_x = a_x.m_vd_x;
	vd_y = a_x.m_vd_y;
	vd_z = a_x.m_vd_z;

	for (k = 0; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				T x1, y1, z1;
				T x2, y2, z2;
				T dx2, dy2, dz2;
				x1 = (T)i + a_x.m_pData[k][j][i][0];
				y1 = (T)j + a_y.m_pData[k][j][i][0];
				z1 = (T)k + a_z.m_pData[k][j][i][0];
				b_x.GetAt(x1, y1, z1, &dx2);
				b_y.GetAt(x1, y1, z1, &dy2);
				b_z.GetAt(x1, y1, z1, &dz2);
				x2 = x1 + dx2;
				y2 = y1 + dy2;
				z2 = z1 + dz2;
				c_x.m_pData[k][j][i][0] = x2 - (T)i;
				c_y.m_pData[k][j][i][0] = y2 - (T)j;
				c_z.m_pData[k][j][i][0] = z2 - (T)k;
			}
		}
	}

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void GetDiceScoreVolume(Volume<T>& vol1, Volume<T>& vol2, Volume<T>& mask, Volume<T>& vold, int* id1, int id1_num, int* id2, int id2_num, float& score, float& sens, float& spec, int sample_z = 1, int sample_z_o = 0)
{
	int sum1_in;
	int sum2_in;
	int sum2_in_true;
	int sum2_out;
	int sum2_out_true;
	int vd_x, vd_y, vd_z, vd_s;
	int i, j, k, l, d;

	vd_x = min(vol1.m_vd_x, vol2.m_vd_x);
	vd_y = min(vol1.m_vd_y, vol2.m_vd_y);
	vd_z = min(vol1.m_vd_z, vol2.m_vd_z);
	vd_s = min(vol1.m_vd_s, vol2.m_vd_s);

	vold.allocate(vd_x, vd_y, vd_z, 1, vol1.m_vd_dx, vol1.m_vd_dy, vol1.m_vd_dz);

	for (k = 0; k < vd_z; k++) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				vold.m_pData[k][j][i][0] = 0;
			}
		}
	}

	sum1_in = 0;
	sum2_in = 0;
	sum2_in_true = 0;
	sum2_out = 0;
	sum2_out_true = 0;
	for (k = sample_z_o; k < vd_z; k += sample_z) {
		for (j = 0; j < vd_y; j++) {
			for (i = 0; i < vd_x; i++) {
				if (mask.m_pData[k][j][i][0] == 0) {
					continue;
				}

				int val1 = vol1.m_pData[k][j][i][0];
				int val2 = vol2.m_pData[k][j][i][0];
				bool in1 = false;
				bool in2 = false;
				for (d = 0; d < id1_num; d++) {
					if (val1 == id1[d]) {
						in1 = true;
					}
				}
				for (d = 0; d < id2_num; d++) {
					if (val2 == id2[d]) {
						in2 = true;
					}
				}
				if (in1) {
					sum1_in++;
					//
					vold.m_pData[k][j][i][0] = 64;
					//
				}
				if (in2) {
					sum2_in++;
					//
					vold.m_pData[k][j][i][0] = 128;
					//
					if (in1) {
						sum2_in_true++;
						//
						vold.m_pData[k][j][i][0] = 255;
					}
				} else {
					sum2_out++;
					if (!in1) {
						sum2_out_true++;
					}
				}
			}
		}
	}

	score = 2.0f * sum2_in_true / (sum1_in + sum2_in);
	sens = (float)sum2_in_true / sum2_in;
	spec = (float)sum2_out_true / sum2_out;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAXNCC				(10000)

#define MERGEBLOB(tab, fold, fnew, start_xyz, end_xyz)				\
	ptab = tab + (start_xyz);										\
	end  = tab + (end_xyz);											\
	while (ptab < end) {											\
		if (*ptab == (fold)) {										\
			*ptab = (fnew);											\
		} else if ((*ptab > (fold)) && (*ptab != MAXNCC)) {			\
			(*ptab)--;												\
		}															\
		ptab++;														\
	}
#define ADJUSTSTART(start, a, b)		\
	for (k = (a); k < (b); k++)	{		\
		start[k] = start[k+1];			\
	}									

template <class T>
BOOL GetConnectedComponents(Volume<T>& img, T* fore_label, int fore_label_num, SVolume& cc, int* cc_sum, int* cc_num)
{
	short *p, FXX, FYY, FZZ, *ptab, *end, f, f_mid, f_max;
	int	pos, ncc, nl, k;
	int	*cc_start = NULL;
	short* img_f = NULL;
	int finished = 1;
	int cx, cy, cz, cx_1, cy_1, cz_1;
	int vd_x, vd_y, vd_z;
	int x, y, z, l;

	*cc_num = 0;
	cc_start = (int*)MyAlloc(MAXNCC*sizeof(int));
	for (k = 0; k < MAXNCC; k++) {
		cc_start[k] = 0;
		cc_sum[k] = 0;
	}

	vd_x = img.m_vd_x;
	vd_y = img.m_vd_y;
	vd_z = img.m_vd_z;

	cx = vd_x + 2;
	cy = vd_y + 2;
	cz = vd_z + 2;
	cx_1 = cx - 1;
	cy_1 = cy - 1;
	cz_1 = cz - 1;

	// img_f has one pixel thick picture frame
	img_f = (short*)MyAlloc(cx*cy*cz*sizeof(short));
	if (img_f == NULL) {
		goto errret;
	}

	for (z = 0; z < vd_z; z++) {
		for (y = 0; y < vd_y; y++) {
			short* q = (short*)img_f + ((z+1)*cy+y+1)*cx+1;
			for (x = 0; x < vd_x; x++) {
				T val = img.m_pData[z][y][x][0];
				BOOL bFore = FALSE;
				for (l = 0; l < fore_label_num; l++) {
					if (val == fore_label[l]) {
						bFore = TRUE;
						break;
					}
				}
				if (bFore) {
					*q++ = 1;
				} else {
					*q++ = 0;
				}
			}
		}
	}

	// draw one pixel thick picture frame (background color)
	p = (short*)img_f;
	for (z = 0; z < cz; z++) {
		for (y = 0; y < cy; y++) {
			for (x = 0; x < cx; x++) {
				if (x == 0 || x == cx_1 || y == 0 || y == cy_1 || z == 0 || z == cz_1) {
					*p = MAXNCC;
				}
				p++;
			}
		}
	}
	//
	ncc = 0; f = ncc;
	for (z = 0; z < vd_z; z++) {
		for (y = 0; y < vd_y; y++) {
			nl = ((z+1)*cy+y+1)*cx+1;
			p = img_f + nl;
			for (x = 0; x < vd_x; x++) {
				if (*p == 1) {
					FZZ = *(p - cx*cy);			// (x+0, y+0, z-1)
					FYY = *(p - cx   );			// (x+0, y-1, z+0)
					FXX = *(p - 1    );			// (x-1, y+0, z+0)

					f     = MIN(MIN(FXX, FYY), FZZ);
					f_max = MAX(MAX(FXX, FYY), FZZ);
					f_mid = FXX + FYY + FZZ - f - f_max;

					pos = nl + x;

					if (f == MAXNCC) {			// if surrounded by BACKGROUND, add new label
						ncc++;
						if (ncc >= MAXNCC) {
							finished = 0;
							goto errret; 
						}
						f = ncc;
						cc_start[f] = pos;		// cc_start[f] = first (x, y, z) having f-index.
					} else {
						if (f_max != MAXNCC && f_max != f) {
							MERGEBLOB(img_f, f_max, f, cc_start[f_max], pos);
							ADJUSTSTART(cc_start, f_max, ncc);
							ncc--;
						}
						if (f_mid != MAXNCC && f_mid != f && f_mid != f_max) {
							MERGEBLOB(img_f, f_mid, f, cc_start[f_mid], pos);
							ADJUSTSTART(cc_start, f_mid, ncc);
							ncc--;
						}
					}
					*p++ = f;
				} else {
					*p++ = MAXNCC;
				}
			}
		}
	}

	*cc_num = ncc+1;
	for (z = 0; z < vd_z; z++) {
		for (y = 0; y < vd_y; y++) {
			for (x = 0; x < vd_x; x++) {
				short p = *(img_f + ((z+1)*cy+(y+1))*cx+(x+1));
				if (p != MAXNCC) {
					cc_sum[p]++;
					cc.m_pData[z][y][x][0] = p;
				} else {
					cc.m_pData[z][y][x][0] = *cc_num;
				}
			}
		}
	}

#if 0
	cc_num_max = 0;
	for (k = 1; k <= ncc; k++) {
		if (cc_num[k] > cc_num_max) {
			cc_num_max = cc_num[k];
		}
	}
	cc_num_max_th = cc_num_max * 0.8;

	for (k = 1; k <= ncc; k++) {
		int sx, sy;

		if (cc_num[k] > cc_num_th) { continue; }
		// we do not remove relatively large blobs
		if (cc_num[k] > cc_num_max_th) { continue; }

		sx = cc_start[k] % cx;
		sy = cc_start[k] / cx;

		for (y = sy; y < cy; y++) {
			int found = 0;
			p = img_f + y*cx;
			for (x = 0; x < cx; x++) {
				if (*p == k) {
					*p = MAXNCC;
					found = 1;
				}
				p++;
			}
			if (found == 0) {
				break;
			}
		}
	}
#endif

errret:
	if (cc_start != NULL) {
		MyFree(cc_start);
	}
	if (img_f != NULL) {
		MyFree(img_f);
	}

	if (finished == 0) {
		return FALSE;
	} else {
		return TRUE;
	}
}

template <class T>
BOOL ErodeVolume(Volume<T>& img, int iter_num)
{
	int vd_x, vd_y, vd_z, vd_x_1, vd_y_1, vd_z_1;
	int i, j, k, iter;
	Volume<T> tmp;

	vd_x = img.m_vd_x;
	vd_y = img.m_vd_y;
	vd_z = img.m_vd_z;
	vd_x_1 = vd_x - 1;
	vd_y_1 = vd_y - 1;
	vd_z_1 = vd_z - 1;
	tmp.allocate(vd_x, vd_y, vd_z, 1, img.m_vd_dx, img.m_vd_dy, img.m_vd_dz);

	for (iter = 0; iter < iter_num; iter++) {
		tmp.copy(img);
		for (k = 1; k < vd_z_1; k++) {
			for (j = 1; j < vd_y_1; j++) {
				for (i = 1; i < vd_x_1; i++) {
					img.m_pData[k][j][i][0] = 0;
					if (tmp.m_pData[k][j][i][0] > 0) {
						if (tmp.m_pData[k  ][j  ][i-1][0] > 0 &&
							tmp.m_pData[k  ][j  ][i+1][0] > 0 &&
							tmp.m_pData[k  ][j-1][i  ][0] > 0 &&
							tmp.m_pData[k  ][j+1][i  ][0] > 0 &&
							tmp.m_pData[k-1][j  ][i  ][0] > 0 &&
							tmp.m_pData[k+1][j  ][i  ][0] > 0) {
							img.m_pData[k][j][i][0] = 1;
						}
					}
				}
			}
		}
	}

	return TRUE;
}
template <class T>
BOOL DilateVolume(Volume<T>& img, int iter_num)
{
	int vd_x, vd_y, vd_z, vd_x_1, vd_y_1, vd_z_1;
	int i, j, k, iter;
	Volume<T> tmp;

	vd_x = img.m_vd_x;
	vd_y = img.m_vd_y;
	vd_z = img.m_vd_z;
	vd_x_1 = vd_x - 1;
	vd_y_1 = vd_y - 1;
	vd_z_1 = vd_z - 1;
	tmp.allocate(vd_x, vd_y, vd_z, 1, img.m_vd_dx, img.m_vd_dy, img.m_vd_dz);

	for (iter = 0; iter < iter_num; iter++) {
		tmp.copy(img);
		for (k = 1; k < vd_z_1; k++) {
			for (j = 1; j < vd_y_1; j++) {
				for (i = 1; i < vd_x_1; i++) {
					if (tmp.m_pData[k][j][i][0] == 0) {
						img.m_pData[k][j][i][0] = 0;
						if (tmp.m_pData[k  ][j  ][i-1][0] > 0 ||
							tmp.m_pData[k  ][j  ][i+1][0] > 0 ||
							tmp.m_pData[k  ][j-1][i  ][0] > 0 ||
							tmp.m_pData[k  ][j+1][i  ][0] > 0 ||
							tmp.m_pData[k-1][j  ][i  ][0] > 0 ||
							tmp.m_pData[k+1][j  ][i  ][0] > 0) {
							img.m_pData[k][j][i][0] = 1;
						}
					} else {
						img.m_pData[k][j][i][0] = 1;
					}
				}
			}
		}
	}

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
