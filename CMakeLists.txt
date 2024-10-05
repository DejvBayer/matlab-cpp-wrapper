##
# This file is part of matlab-cpp-wrapper library.
#
# Copyright (c) 2024 David Bayer
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
##

cmake_minimum_required(VERSION 3.22)

project(matlab-cpp-wrapper VERSION 0.0.1 LANGUAGES CXX)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
  set(MATLABW_TOP_LEVEL_PROJECT ON)
endif()

option(MATLABW_BUILD_EXAMPLES "Build examples"     ${MATLABW_TOP_LEVEL_PROJECT})
option(MATLABW_ENABLE_GPU     "Enable GPU support" OFF)

if(MATLABW_TOP_LEVEL_PROJECT)
  find_package(Matlab REQUIRED COMPONENTS MEX_COMPILER MAT_LIBRARY)
else()
  if(NOT Matlab_FOUND)
    message(FATAL_ERROR "MATLAB package is required be found before including matlabw library")
  endif()
endif()

if(WIN32)
  set(MATLABW_ARCH "win64")
elseif(APPLE)
  if(CMAKE_APPLE_SILICON_PROCESSOR OR CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(MATLABW_ARCH "maca64")
  else()
    set(MATLABW_ARCH "maci64")
  endif()
elseif(LINUX)
  set(MATLABW_ARCH "glnxa64")
else()
  message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

set(MATLABW_ARCH ${MATLABW_ARCH} PARENT_SCOPE)

add_library(matlabw INTERFACE)
add_library(matlabw::matlabw ALIAS matlabw)
target_compile_features(matlabw INTERFACE cxx_std_20)
target_include_directories(matlabw INTERFACE include)

if(MATLABW_ENABLE_GPU)
  set(MATLAB_GPU_INCLUDE_DIR "${Matlab_ROOT_DIR}/toolbox/parallel/gpu/extern/include")

  if(NOT EXISTS ${MATLAB_GPU_INCLUDE_DIR}/gpu/mxGPUArray.h)
    message(FATAL_ERROR "Matlab Parallel Computing Toolbox is required for GPU support")
  endif()

  find_library(MW_GPU_MEX_BINDER_LIB
    NAMES mwgpumexbinder gpumexbinder
    PATHS "${Matlab_ROOT_DIR}/bin/${MATLABW_ARCH}"
    REQUIRED
    NO_DEFAULT_PATH)

  add_library(matlabw-gpu INTERFACE)
  add_library(matlabw::matlabw-gpu ALIAS matlabw-gpu)
  target_compile_definitions(matlabw-gpu INTERFACE MATLABW_ENABLE_GPU)
  target_include_directories(matlabw-gpu INTERFACE ${MATLAB_GPU_INCLUDE_DIR})
  target_link_libraries(matlabw-gpu INTERFACE matlabw::matlabw ${MW_GPU_MEX_BINDER_LIB})
endif()

if(MATLABW_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
