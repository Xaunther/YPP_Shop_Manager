cmake_minimum_required(VERSION 3.22)

# YPPShopManager project data
project(YPP_SM DESCRIPTION "A command-line shop manager for Puzzle Pirates" HOMEPAGE_URL "https://github.com/Xaunther/YPP_Shop_Manager" LANGUAGES CXX)

# C++ 20 required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Option to build documentation
option(BUILD_DOCUMENTATION "Rule to build documentation" true)

# Option to build tests
option(BUILD_TESTS "Rule to build tests" true)

# Names of relevant directories
set(YPP_SM_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(YPP_SM_BINARY_DIR ${YPP_SM_DIR}/bin)
set(YPP_SM_INCLUDE_DIR ${YPP_SM_DIR}/include)
set(YPP_SM_LIBS_DIR ${YPP_SM_DIR}/lib)

# Default build is "release"
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_COMPILER_IS_GNUCC CACHE STRING "Choose the build type (Debug, Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "-W4 -WX -EHsc /Zc:preprocessor")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DJSON_USE_IMPLICIT_CONVERSIONS=0")

set(CMAKE_CXX_FLAGS_RELEASE "-Os")

# Always export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find json package
find_package(nlohmann_json 3.11 REQUIRED)

# Find git package
find_package(Git)

# Function to add a new object module
function(add_ypp_sm_object_module MODULE_NAME SOURCES)
	add_Library(${MODULE_NAME}_Objects OBJECT ${SOURCES} ${ARGN})
	set_target_properties(${MODULE_NAME}_Objects PROPERTIES
		POSITION_INDEPENDENT_CODE true
		ARCHIVE_OUTPUT_DIRECTORY ${YPP_SM_LIBS_DIR}
		LIBRARY_OUTPUT_DIRECTORY ${YPP_SM_LIBS_DIR}
		RUNTIME_OUTPUT_DIRECTORY ${YPP_SM_LIBS_DIR})
	message(STATUS "Added object module ${MODULE_NAME}")
endfunction()

# Function to add a new module
function(add_ypp_sm_module MODULE_NAME MODULE_TYPE SOURCES)
	if(MODULE_TYPE STREQUAL SHARED)
		set(MODULE_SUFFIX "Shared")
	elseif(MODULE_TYPE STREQUAL STATIC)
		set(MODULE_SUFFIX "Static")
	else()
		message(FATAL_ERROR "Module type ${MODULE_TYPE} not recognized. Only 'STATIC' and 'SHARED' are allowed.")
	endif()

	add_Library(${MODULE_NAME}_${MODULE_SUFFIX} ${MODULE_TYPE} ${SOURCES} ${ARGN})
	set_target_properties(${MODULE_NAME}_${MODULE_SUFFIX} PROPERTIES
		POSITION_INDEPENDENT_CODE true
		ARCHIVE_OUTPUT_DIRECTORY ${YPP_SM_LIBS_DIR}
		LIBRARY_OUTPUT_DIRECTORY ${YPP_SM_LIBS_DIR}
		RUNTIME_OUTPUT_DIRECTORY ${YPP_SM_LIBS_DIR})
	target_link_libraries(${MODULE_NAME}_${MODULE_SUFFIX} PRIVATE nlohmann_json::nlohmann_json)
	message(STATUS "Added ${MODULE_TYPE} module ${MODULE_NAME}")
endfunction()

# List of source files
include(FileList.cmake)

# Include directories
find_path(JSON_INCLUDE_DIR NAMES nlohmann)
include_directories(${YPP_SM_INCLUDE_DIR} ${YPP_SM_DIR}/src ${JSON_INCLUDE_DIR})

# Link directories
link_directories(${YPP_SM_LIBS_DIR})

# Build YPP Shop Manager modules
set(YPP_SM_MODULES
	CORE
)

foreach(YPP_SM_MODULE ${YPP_SM_MODULES})
	add_ypp_sm_object_module(${PROJECT_NAME}_${YPP_SM_MODULE} "${${PROJECT_NAME}_${YPP_SM_MODULE}_SOURCE}")
	set(YPP_SM_${YPP_SM_MODULE}_OBJECTS $<TARGET_OBJECTS:${PROJECT_NAME}_${YPP_SM_MODULE}_Objects>)

	if(NOT YPP_SM_MODULE STREQUAL CORE)
		list(APPEND YPP_SM_${YPP_SM_MODULE}_OBJECTS ${YPP_SM_CORE_OBJECTS})
	endif()

	# Final build step. All objects must have been appended to YPP_SM_OBJECTS.
	add_ypp_sm_module(${PROJECT_NAME}_${YPP_SM_MODULE} STATIC ${YPP_SM_${YPP_SM_MODULE}_OBJECTS})

	if(LIB_YPP_SM_SHARED)
		add_ypp_sm_module(${PROJECT_NAME}_${YPP_SM_MODULE} SHARED ${YPP_SM_${YPP_SM_MODULE}_OBJECTS})
	endif()
endforeach(YPP_SM_MODULE)

# Set version file path
set( VERSION_FILE ${YPP_SM_DIR}/VERSION )

# Print build version
add_custom_target(PrintBuild ALL
		COMMAND ${CMAKE_COMMAND} -D GIT_EXECUTABLE=${GIT_EXECUTABLE}
		-D VERSION_FILE=${VERSION_FILE}
		-P ${YPP_SM_DIR}/PrintVersion.cmake
		)

# Configure Config.h
add_custom_target(Config ALL
		COMMAND ${CMAKE_COMMAND} -D SRC=${YPP_SM_INCLUDE_DIR}/Config.h.in
		-D DST=${YPP_SM_INCLUDE_DIR}/Config.h
		-D VERSION_FILE=${VERSION_FILE}
		-P ${YPP_SM_DIR}/GenerateVersionHeader.cmake
		DEPENDS PrintBuild
		)
add_dependencies(YPP_SM_CORE_Objects Config)

# Build documentation
if(BUILD_DOCUMENTATION)
	add_subdirectory(doc)
endif()

# Build tests
if(BUILD_TESTS)
	include(CTest)
	enable_testing()
	add_subdirectory(tests)
endif()

# Compile solver binary
add_executable(YPP_Shop_Manager ${CMAKE_SOURCE_DIR}/src/frontend/YPP_Shop_Manager.cpp ${YPP_SM_CORE_OBJECTS} )
