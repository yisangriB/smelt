cmake_minimum_required(VERSION 3.0)

project(smelt LANGUAGES CXX)

# Require C++11-compliant compiler
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(CMakeParseArguments)

# General compile settings
IF (NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Debug")
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
ENDIF (NOT CMAKE_BUILD_TYPE)

# Provide option for building testing
option(BUILD_TESTING "Enable testing for smelt" ON)
option(BUILD_STATIC_LIBS "Build the static library" ON)
option(BUILD_SHARED_LIBS "Build the shared library" OFF)

# CMake Modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Bring in dependencies from Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Include directories
include_directories(BEFORE
	${CONAN_INCLUDE_DIRS}
	)
include_directories(BEFORE
	${PROJECT_SOURCE_DIR}/include/
	)

# Set sources
set(SOURCES
  ${PROJECT_SOURCE_DIR}/src/numeric_utils.cc
  ${PROJECT_SOURCE_DIR}/src/normal_multivar.cc
  ${PROJECT_SOURCE_DIR}/src/normal_dist.cc
  ${PROJECT_SOURCE_DIR}/src/lognormal_dist.cc
  ${PROJECT_SOURCE_DIR}/src/beta_dist.cc
  ${PROJECT_SOURCE_DIR}/src/inv_gauss_dist.cc
  ${PROJECT_SOURCE_DIR}/src/students_t_dist.cc
  ${PROJECT_SOURCE_DIR}/src/json_object.cc
  ${PROJECT_SOURCE_DIR}/src/vlachos_et_al.cc
  ${PROJECT_SOURCE_DIR}/src/configure.cc
  ${PROJECT_SOURCE_DIR}/src/wittig_sinha.cc
  ${PROJECT_SOURCE_DIR}/src/filter.cc
  ${PROJECT_SOURCE_DIR}/src/wind_profile.cc
  ${PROJECT_SOURCE_DIR}/src/uniform_dist.cc
  ${PROJECT_SOURCE_DIR}/src/dabaghi_der_kiureghian.cc
  ${PROJECT_SOURCE_DIR}/src/nelder_mead.cc  
  )

# Add library as target and add libraries to link target to
if (BUILD_STATIC_LIBS)
  add_library(smelt_static STATIC ${SOURCES})
  set_target_properties(smelt_static PROPERTIES OUTPUT_NAME smelt) 
  # target_link_libraries(smelt_static CONAN_PKG::ipp-static CONAN_PKG::mkl-static)    
endif()

if (BUILD_SHARED_LIBS)
  if (WIN32)  
    add_library(smelt_shared STATIC ${SOURCES})
  else()
    add_library(smelt_shared SHARED ${SOURCES})    
  endif()
  
  set_target_properties(smelt_shared PROPERTIES OUTPUT_NAME smelt)
  # target_link_libraries(smelt_shared CONAN_PKG::ipp-shared CONAN_PKG::mkl-shared)    
endif()

# Adding MATH defines for M_PI when building on Windows
if (WIN32)
  add_compile_definitions(_USE_MATH_DEFINES)
endif()

# Unit testing
#if (BUILD_TESTING) 
#  set(TEST_SOURCES
#    ${PROJECT_SOURCE_DIR}/test/test_main.cc
#    ${PROJECT_SOURCE_DIR}/test/multi_var_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/factory_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/distribution_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/window_func_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/dispatcher_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/numeric_utils_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/filter_func_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/json_object_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/stochastic_model_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/wind_profile_tests.cc
#    ${PROJECT_SOURCE_DIR}/test/optimization_tests.cc    
#  )

#  if (BUILD_STATIC_LIBS)
#    add_executable(unit_tests_static ${TEST_SOURCES})    
#    target_link_libraries(unit_tests_static smelt_static CONAN_PKG::ipp-static CONAN_PKG::mkl-static)    
#    add_test(NAME run_static_unit_tests COMMAND unit_tests_static)    
#  endif()

  # if (BUILD_SHARED_LIBS)
  #   add_executable(unit_tests_shared ${TEST_SOURCES})
  #   target_link_libraries(unit_tests_shared smelt_shared)    
  #   add_test(NAME run_shared_unit_tests COMMAND unit_tests_shared)
  # endif()

#  enable_testing()
#endif()  
