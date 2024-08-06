##
# This file is part of mex-cpp-wrapper library.
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

function(add_examples dir)
  set(EXAMPLES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${dir}")
  file(GLOB EXAMPLES "${EXAMPLES_DIR}/*.cpp")

  foreach(EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
    
    matlab_add_mex(
      NAME        ${EXAMPLE_NAME}
      SRC         ${EXAMPLE}
      OUTPUT_NAME ${EXAMPLE_NAME}
      LINK_TO     mexw::mexw
      R2018a)
  endforeach()
endfunction()

add_examples("matlab/mex")

if (MEXW_ENABLE_GPU)
  add_subdirectory(gpu)
endif()
