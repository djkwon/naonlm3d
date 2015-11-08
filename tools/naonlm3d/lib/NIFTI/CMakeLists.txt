
add_definitions(-DHAVE_ZLIB)

add_library(NIFTI nifti1_io.c znzlib.c)
