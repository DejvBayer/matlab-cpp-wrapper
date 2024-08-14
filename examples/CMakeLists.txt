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
  # Get all C++ examples
  file(GLOB EXAMPLES "${dir}/*.cpp")

  # Set output directory for mex libraries
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}")

  # Compile all examples
  foreach(EXAMPLE ${EXAMPLES})
    # Get name of example
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
    
    # Add mex library
    matlab_add_mex(
      NAME        ${EXAMPLE_NAME}
      SRC         ${EXAMPLE}
      OUTPUT_NAME ${EXAMPLE_NAME}
      LINK_TO     mexw::mexw
      R2018a)
  endforeach()
endfunction()

add_examples("matlab/mex")
add_examples("matlab/mx")
add_examples("matlab/refbook")

if(MEXW_ENABLE_GPU)
  add_subdirectory(gpu)
endif()
