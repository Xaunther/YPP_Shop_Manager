cmake_minimum_required(VERSION 3.22)

# Parent project name
set(PARENT_PROJECT_NAME ${PROJECT_NAME})

# Project for tests
project(Tests LANGUAGES CXX)

include(FileList.cmake)

# Include directories
include_directories(${YPP_SM_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

# Link directories
link_directories(${YPP_SM_LIBS_DIR})

# For every test source add corresponding test
function(add_ypp_sm_test MODULE_NAME)
	foreach(TEST_SOURCE ${YPP_SM_TESTS_UNIT_${MODULE_NAME}_SOURCE})
		string(REPLACE ".cpp" "" TEST_NAME ${TEST_SOURCE})
		get_filename_component(TEST_NAME ${TEST_NAME} NAME)
		add_executable(${MODULE_NAME}_${TEST_NAME} ${TEST_SOURCE})
		target_link_libraries(${MODULE_NAME}_${TEST_NAME} PRIVATE ${PARENT_PROJECT_NAME}_${MODULE_NAME}_Static ${PARENT_PROJECT_NAME}_${PROJECT_NAME}_ENGINE_Static)
		add_test(NAME ${MODULE_NAME}_${TEST_NAME} COMMAND ${MODULE_NAME}_${TEST_NAME})
	endforeach()
endfunction()

# Add module for test engine
add_ypp_sm_object_module(${PARENT_PROJECT_NAME}_${PROJECT_NAME}_ENGINE "${YPP_SM_TESTS_ENGINE_SOURCE}")
add_ypp_sm_module(${PARENT_PROJECT_NAME}_${PROJECT_NAME}_ENGINE STATIC $<TARGET_OBJECTS:${PARENT_PROJECT_NAME}_${PROJECT_NAME}_ENGINE_Objects>)

foreach(YPP_SM_MODULE ${YPP_SM_MODULES})
	add_ypp_sm_test(${YPP_SM_MODULE})
endforeach(YPP_SM_MODULE)
