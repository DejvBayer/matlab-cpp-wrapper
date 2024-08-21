/*
  This file is part of matlab-cpp-wrapper library.

  Copyright (c) 2024 David Bayer

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef MATLABW_MEX_FUNCTION_HPP
#define MATLABW_MEX_FUNCTION_HPP

#include "detail/include.hpp"

namespace matlabw::mex
{
  /// @brief Function object that wraps the user-defined function.
  class Function
  {
    friend void ::mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

    public:
      /**
       * @brief Gets the name of the function.
       * @return The name of the function.
       */
      [[nodiscard]] const char* getName() const noexcept
      {
        return mexFunctionName();
      }

      /// @brief Locks the function.
      void lock() noexcept
      {
        mexLock();
      }

      /// @brief Unlocks the function.
      void unlock() noexcept
      {
        mexUnlock();
      }

      /**
       * @brief Checks if the function is locked.
       * @return True if the function is locked, false otherwise.
       */
      [[nodiscard]] bool isLocked() const noexcept
      {
        return mexIsLocked();
      }

      /**
       * @brief Implementation of the user-defined function.
       * @param lhs Left-hand side arguments.
       * @param rhs Right-hand side arguments.
       */
      void operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs);
    private:
      /// @brief Default constructor
      Function() noexcept = default;

      /// @brief Explicitly deleted copy constructor.
      Function(const Function&) = delete;

      /// @brief Explicitly deleted move constructor.
      Function(Function&&) = delete;

      /// @brief Destructor
      ~Function() noexcept = default;

      /// @brief Explicitly deleted copy assignment operator.
      Function& operator=(const Function&) = delete;

      /// @brief Explicitly deleted move assignment operator.
      Function& operator=(Function&&) = delete;
  };
} // namespace matlabw::mex

/// @brief Entry point for the MEX function. This function is called by MATLAB.
extern "C" void
mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  using namespace matlabw;
  
  const char* errorId{};  // Error ID string
  const char* errorMsg{}; // Error message string

  // Helper function to assign error id and message. Pointer needn't be freed.
  auto assignErrorStr = [](const char*& dst, const char* src)
  {
    const std::size_t size = std::char_traits<char>::length(src);

    auto dstPtr = static_cast<char*>(mx::malloc(size + 1));

    if (dstPtr != nullptr)
    {
      std::char_traits<char>::copy(dstPtr, src, size);
      dstPtr[size] = '\0';
      dst = dstPtr;
    }
  };

  try
  {
    // Initialize the GPU if enabled.
# ifdef MATLABW_ENABLE_GPU
    if (mxInitGPU() != MX_GPU_SUCCESS)
    {
      throw mx::Exception{"mex:gpu", "An error occurred while initializing the GPU."};
    }
# endif

    // Reinterpret trick requires that the array wrappers have the same size as mxArray*.
    static_assert(sizeof(mxArray*) == sizeof(mx::Array));
    static_assert(sizeof(const mxArray*) == sizeof(mx::ArrayCref));

    // Call the user-defined function.
    mex::Function{}(mx::Span<mx::Array>(reinterpret_cast<mx::Array*>(plhs), static_cast<std::size_t>(nlhs)),
                    mx::View<mx::ArrayCref>(reinterpret_cast<mx::ArrayCref*>(prhs), static_cast<std::size_t>(nrhs)));

    // Return if no exception occurred.
    return;
  }
  catch (const mx::Exception& e)
  {
    if (e.hasId())
    {
      assignErrorStr(errorId, e.id());
    }
    
    assignErrorStr(errorMsg, e.what());
  }
  catch (const std::exception& e)
  {
    errorId = "mex:std";
    assignErrorStr(errorMsg, e.what());
  }
  catch (...)
  {
    errorId  = "mex:unknown";
    // Error message will be assigned in the next block.
  }

  // If error message is not assigned, assign a default message.
  if (errorMsg == nullptr)
  {
    errorMsg = "An unknown error occurred.";
  }

  if (errorId == nullptr)
  {
    mexErrMsgTxt(errorMsg);
  }
  else
  {
    mexErrMsgIdAndTxt(errorId, errorMsg);
  }
}

#endif /* MATLABW_MEX_FUNCTION_HPP */
