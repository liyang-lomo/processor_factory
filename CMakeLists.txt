PROJECT(test)
#ADD_SUBDIRECTORY(src bin)
#ADD_SUBDIRECTORY(Test)

# AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SRC_LIST)
ADD_COMPILE_OPTIONS(-g -std=c++11 -Wall -O2 -DDEBUG -DTIXML_USE_STL -fPIC)

SET (CMAKE_C_COMPILER             "/usr/bin/clang")
SET (CMAKE_C_FLAGS                "-Wall ")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS                "-Wall ")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

SET (CMAKE_AR      "/usr/bin/llvm-ar")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
SET (CMAKE_NM      "/usr/bin/llvm-nm")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")

INCLUDE_DIRECTORIES(
	$ENV{BASE_MYAPI_PATH}/include/mytools
	$ENV{BASE_3PARTY_PATH}/boost/include
	)

SET(THIRD_PARTY $ENV{BASE_3PARTY_PATH})	
LINK_DIRECTORIES(
	/usr/local/lib
	${THIRD_PARTY}/jsoncpp/lib
	)   #库目录必须是绝对路径
INCLUDE_DIRECTORIES(${THIRD_PARTY}/jsoncpp/include)
IF (WIN32)
	MESSAGE(STATUS "Now is windows")
	LINK_LIBRARIES(ws2_32 wsock32 event  event_core  event_extra)
	ADD_COMPILE_OPTIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
	
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
ELSEIF (UNIX)
	MESSAGE(STATUS "Now is UNIX-like OS's.")
	LINK_LIBRARIES(protobuf pthread jsoncpp)
	#ADD_COMPILE_OPTIONS(-g -fPIC -fstack-protector -fstack-protector-all -fno-omit-frame-pointer -fno-strict-aliasing -Wall -Wpointer-arith -m64 -std=c++11  -O0 )
ENDIF ()


# ADD_EXECUTABLE(test.exe  ${SRC_LIST} )  
ADD_EXECUTABLE(demo.exe   demo.cpp ) 



