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

cmake_minimum_required(VERSION 3.0.2)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 1)
set (VERSION_PATCH 4)
set (VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

project (mind VERSION ${VERSION_FULL})

if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE Release)
endif ()

add_definitions(-std=c++11)
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

option (BUILD_STATIC_LIB "Build the static library." ON)
option (BUILD_SHARED_LIB "Build the shared library." ON)
option (BUILD_TEST "Build the test." OFF)
option (MIND_STRICT  "Strict mode for Mind library." OFF)

if (WIN32 OR APPLE)
	message (WARNING "Windows OS and Apple OS is not currently officially supported.")
endif()

# Print information
message (STATUS "${PROJECT_NAME}")
message (STATUS "Version: ${VERSION_FULL}")
message (STATUS "Cmake generator: ${CMAKE_GENERATOR}")

# Check build folder
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message (FATAL_ERROR "Can not build ${PROJECT_NAME} in source folder. Choose another directory.")
endif()

# Check type of library
if (NOT BUILD_STATIC_LIB AND NOT BUILD_SHARED_LIB)
	message (FATAL_ERROR "Can not build ${PROJECT_NAME} without specifying type of library. Choose static and/or shared type of library.")
endif()

# Check for strict mode
if (MIND_STRICT)
	add_definitions (-DMIND_STRICT)
endif()

set (HEADER_DIR ${CMAKE_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set (SOURCES

	${SOURCE_DIR}/math/digit.cpp
	${SOURCE_DIR}/math/math.cpp
	${SOURCE_DIR}/math/number.cpp

	${SOURCE_DIR}/other/common.cpp

	)

if (BUILD_STATIC_LIB)
	add_library (${PROJECT_NAME}_S STATIC ${SOURCES})
	set_target_properties (${PROJECT_NAME}_S PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME})
	target_include_directories (${PROJECT_NAME}_S PRIVATE "${SOURCE_DIR}"
												  PUBLIC "${HEADER_DIR}")
	install (TARGETS ${PROJECT_NAME}_S LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif ()

if (BUILD_SHARED_LIB)
add_library (${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties (${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories (${PROJECT_NAME} PRIVATE "${SOURCE_DIR}"
											PUBLIC "${HEADER_DIR}")
	if (WIN32)
		install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION lib)
	else ()
		install (TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
	endif()
endif()

install (DIRECTORY ${HEADER_DIR}/mind DESTINATION include)

if (BUILD_TEST)
	enable_testing()

	find_library(GTEST gtest REQUIRED)
	find_library(GTESTM gtest_main REQUIRED)

	set (TEST_DIR ${CMAKE_SOURCE_DIR}/test)

	set (TEST_SOURCES

		# Number test
		${TEST_DIR}/testNumberSum.cpp
		${TEST_DIR}/testNumberSub.cpp
		${TEST_DIR}/testNumberMul.cpp
		${TEST_DIR}/testNumberDiv.cpp
		${TEST_DIR}/testNumberMod.cpp

		# Math test
		${TEST_DIR}/testMathSgn.cpp
		${TEST_DIR}/testMathAbs.cpp
		${TEST_DIR}/testMathCnt.cpp
		${TEST_DIR}/testMathPow.cpp

		)

	if (BUILD_SHARED_LIB)
		set (MINDLIB ${PROJECT_NAME})
	else()
		set (MINDLIB ${PROJECT_NAME}_S)
	endif()

	add_executable (TEST ${TEST_SOURCES})
	target_link_libraries (TEST ${GTEST} ${GTESTM} ${MINDLIB} pthread)
	target_include_directories (TEST PUBLIC ${CMAKE_SOURCE_DIR}/tests)

	add_test(NAME test COMMAND TEST)
endif()
