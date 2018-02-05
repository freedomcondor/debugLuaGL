cmake_minimum_required(VERSION 3.5)

project(debugGL)

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")  
	  
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
	MESSAGE(STATUS "current platform: Linux ")  
	#add_definitions(-Dlinux)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")  
	MESSAGE(STATUS "current platform: Windows")  
	add_definitions(-Dwindows)
	SET(CMAKE_EXE_LINKER_FLAGS "/SAFESEH:NO")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")  
	MESSAGE(STATUS "current platform: FreeBSD")  

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")  
	MESSAGE(STATUS "current platform: Darwin(mac?)")  
	add_definitions(-Dmac)

ELSE ()  
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")  
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")  

set(CMAKE_BUILD_TYPE Debug)

add_executable(main src/debug_opengl.cpp
					src/function_opengl.cpp
			  )

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
#my windows does not need to find package
ELSE()
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

find_package(Lua REQUIRED)
#${LUA_INCLUDE_DIR}
#${LUA_LIBRARIES}

MESSAGE(STATUS "opengl lib: ${OPENGL_LIBRARIES}")  
MESSAGE(STATUS "glut lib: ${GLUT_LIBRARY}")  

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS}
					${LUA_INCLUDE_DIR}
		)

target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
							${LUA_LIBRARIES}
		)
