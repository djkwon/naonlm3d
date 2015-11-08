cmake_minimum_required(VERSION 2.8)

# set default build mode
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)
if(WIN32)
	mark_as_advanced(CLEAR CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "")
endif(WIN32)

project(NAONLM3D)

find_package(OpenMP)
if(OPENMP_FOUND)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else(OPENMP_FOUND)
	message("OpenMP is disabled.")
endif(OPENMP_FOUND)

# remove some MSVC flags
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
endif(MSVC)

# get revision
if(EXISTS ${PROJECT_SOURCE_DIR}/.svn)
    find_package(Subversion)
    if(Subversion_FOUND)
        Subversion_WC_INFO(${PROJECT_SOURCE_DIR} Project)
        message("Current revision is ${Project_WC_REVISION}.")
        add_definitions(-DSW_REV="${Project_WC_REVISION}")
    else(Subversion_FOUND)
        if(WIN32)
            include(${PROJECT_SOURCE_DIR}/config/FindTortoiseSVN.cmake)
            if(TortoiseSVN_FOUND)
                TortoiseSVN_WC_INFO(${PROJECT_SOURCE_DIR} Project)
                message("Current revision is ${Project_WC_REVISION}.")
                add_definitions(-DSW_REV="${Project_WC_REVISION}")
            endif(TortoiseSVN_FOUND)
        endif(WIN32)
    endif(Subversion_FOUND)
endif()

# set version
add_definitions(-DSW_VER="2.0")

add_definitions(-DDLONG)

if(WIN32)
	add_definitions(-DWIN64)
	add_definitions(-D_WIN64)
endif(WIN32)

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/NIFTI)
include_directories(${PROJECT_SOURCE_DIR}/lib/zlib)

link_directories(${PROJECT_BINARY_DIR}/lib) 
link_directories(${PROJECT_BINARY_DIR}/lib/NIFTI) 
link_directories(${PROJECT_BINARY_DIR}/lib/zlib) 

add_subdirectory(lib)
add_subdirectory(src)
