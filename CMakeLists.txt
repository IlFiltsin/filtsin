#====----------------------------------------------------------------------====#
#
#                         		Mind - Math library
#
# © 2018 Ilya Filtsin
#
# This file is distributed under the Apache license 2.0.
# See COPYING for details.
#
#====----------------------------------------------------------------------====#

cmake_minimum_required(VERSION 3.0)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 1)
set (VERSION_PATCH 1)
set (VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

string (ASCII 27 Esc)
set (COLOUR_RESET   "${Esc}[m")
set (RED            "${Esc}[1;31m")
set (GREEN          "${Esc}[1;32m")
set (YELLOW         "${Esc}[1;33m")

project (Mind VERSION ${VERSION_FULL})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -O2 -std=c++11")

option (BUILD_STATIC_LIB "Build the static library." ON)
option (BUILD_SHARED_LIB "Build the shared library." ON)
option (MIND_STRICT  "Strict mode for Mind library." OFF)


function (message)

    list (GET ARGV 0 TYPE)

    if (TYPE STREQUAL FATAL_ERROR)
        list (REMOVE_AT ARGV 0)
        _message (${TYPE} "${RED} ${ARGV} ${COLOUR_RESET}")
    elseif (TYPE STREQUAL WARNING)
        list (REMOVE_AT ARGV 0)
        _message (${TYPE} "${YELLOW} ${ARGV} ${COLOUR_RESET}")
    elseif (TYPE STREQUAL STATUS)
        list (REMOVE_AT ARGV 0)
        _message (${TYPE} "${GREEN} ${ARGV} ${COLOUR_RESET}")
    else ()
        _message ("${ARGV}")
    endif()

endfunction()

macro (get_subdirs result curdir)
	file (GLOB children RELATIVE ${curdir} ${curdir}/*)
	set (dirList "")
	foreach (child ${children}) 
		if (IS_DIRECTORY ${curdir}/${child})
			list (APPEND dirList ${child})
		endif()
	endforeach()
	set (${result} ${dirList})
endmacro()

if (WIN32 OR WIN64 OR APPLE)
	message (WARNING "Windows OS and Apple OS is not currently officially supported.")
endif()


message (STATUS "${PROJECT_NAME} - starting cmake")
message (STATUS "${PROJECT_NAME} version: ${VERSION_FULL}")
message (STATUS "Cmake generator: ${CMAKE_GENERATOR}")

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message (FATAL_ERROR "Can not build ${PROJECT_NAME} in source folder. Choose another directory.")
endif()

if (NOT BUILD_STATIC_LIB AND NOT BUILD_SHARED_LIB)
	message (FATAL_ERROR "Can not build ${PROJECT_NAME} without specifying type of library. Choose static and/or shared type of library.")
endif()

if (MIND_STRICT)
	add_definitions (-DMIND_STRICT)
endif()

get_subdirs (SRC_DIRS "${CMAKE_SOURCE_DIR}/src")


set (SOURCES)

foreach (subdir ${SRC_DIRS})
	file (GLOB files RELATIVE "${CMAKE_SOURCE_DIR}/src/${subdir}" "${CMAKE_SOURCE_DIR}/src/${subdir}/*.cpp")
	foreach (file ${files})
		list (APPEND SOURCES "${CMAKE_SOURCE_DIR}/src/${subdir}/${file}")
	endforeach ()
endforeach()

if (BUILD_STATIC_LIB)
	add_library (${PROJECT_NAME}_S STATIC ${SOURCES})
	set_target_properties (${PROJECT_NAME}_S PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME})
	target_include_directories (${PROJECT_NAME}_S PRIVATE "${CMAKE_SOURCE_DIR}/src/"
											PUBLIC "${CMAKE_SOURCE_DIR}/include/")
	install (TARGETS ${PROJECT_NAME}_S LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif ()
if (BUILD_SHARED_LIB)
add_library (${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties (${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories (${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src/"
											PUBLIC "${CMAKE_SOURCE_DIR}/include/")
install (TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
endif()
install (DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
