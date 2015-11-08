
set(NAONLM3D_SOURCES stdafx.cpp stdafx.h MyUtils.cpp MyUtils.h naonlm3d.cpp)

add_executable(naonlm3d ${NAONLM3D_SOURCES})

set(NAONLM3D_LIBRARIES NIFTI zlib)

if(WIN32)
	target_link_libraries(naonlm3d ${NAONLM3D_LIBRARIES})
elseif(APPLE)	
	target_link_libraries(naonlm3d ${NAONLM3D_LIBRARIES})
else()
	target_link_libraries(naonlm3d ${NAONLM3D_LIBRARIES} -lrt)
endif()

set_target_properties(naonlm3d PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install(TARGETS naonlm3d DESTINATION bin)
