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

option(MATLABW_BUILD_EXAMPLES "Build examples"     OFF)
option(MATLABW_ENABLE_GPU     "Enable GPU support" OFF)

if(WIN32)
  set(MATLAB_BIN_PLATFORM_DIR_NAME "win64")
elseif(APPLE)
  if(CMAKE_APPLE_SILICON_PROCESSOR OR CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(MATLAB_BIN_PLATFORM_DIR_NAME "maca64")
  else()
    set(MATLAB_BIN_PLATFORM_DIR_NAME "maci64")
  endif()
elseif(LINUX)
  set(MATLAB_BIN_PLATFORM_DIR_NAME "glnxa64")
else()
  message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

find_package(Matlab REQUIRED COMPONENTS MEX_COMPILER)

add_library(matlabw INTERFACE)
add_library(matlabw::matlabw ALIAS matlabw)
target_compile_features(matlabw INTERFACE cxx_std_20)
target_include_directories(matlabw INTERFACE include)
target_link_libraries(matlabw INTERFACE Matlab::mex)

if(MATLABW_ENABLE_GPU)
  set(MATLAB_GPU_INCLUDE_DIR "${Matlab_ROOT_DIR}/toolbox/parallel/gpu/extern/include")

  if(NOT EXISTS ${MATLAB_GPU_INCLUDE_DIR}/gpu/mxGPUArray.h)
    message(FATAL_ERROR "Matlab Parallel Computing Toolbox is required for GPU support")
  endif()

  find_library(MW_GPU_MEX_BINDER_LIB
    NAMES mwgpumexbinder
    PATHS "${Matlab_ROOT_DIR}/bin/${MATLAB_BIN_PLATFORM_DIR_NAME}"
    REQUIRED)

  add_library(matlabw-gpu INTERFACE)
  add_library(matlabw::matlabw-gpu ALIAS matlabw-gpu)
  target_compile_definitions(matlabw-gpu INTERFACE MATLABW_ENABLE_GPU)
  target_include_directories(matlabw-gpu INTERFACE ${MATLAB_GPU_INCLUDE_DIR})
  target_link_libraries(matlabw-gpu INTERFACE matlabw::matlabw ${MW_GPU_MEX_BINDER_LIB})
endif()

if(MATLABW_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
