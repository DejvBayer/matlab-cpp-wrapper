/*
  This file is part of mex-cpp-wrapper library.

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

#ifndef MEX_EVAL_HPP
#define MEX_EVAL_HPP

#include "detail/include.hpp"

#include "Array.hpp"
#include "ArrayRef.hpp"
#include "common.hpp"
#include "detail/MException.hpp"

namespace mex
{
  /**
   * @brief Calls a MATLAB function.
   * @param lhs The left-hand side arguments.
   * @param rhs The right-hand side arguments.
   * @param functionName The name of the function to call.
   */
  inline void call(Span<Array> lhs, View<ArrayCref> rhs, const char* functionName)
  {
    if (!std::empty(lhs) && std::data(lhs) == nullptr)
    {
      throw Exception{"invalid output"};
    }

    if (!std::empty(rhs) && std::data(rhs) == nullptr)
    {
      throw Exception{"invalid input"};
    }

    if (functionName == nullptr)
    {
      throw Exception{"invalid function name"};
    }

    // Reinterpret trick requires that the array wrappers have the same size as mxArray*.
    static_assert(sizeof(mxArray*) == sizeof(mex::Array));
    static_assert(sizeof(const mxArray*) == sizeof(mex::ArrayCref));

    // Set lhs
    const int nlhs = static_cast<int>(lhs.size());
    mxArray** plhs = reinterpret_cast<mxArray**>(lhs.data());

    // Set rhs
    const int nrhs = static_cast<int>(rhs.size());
    mxArray** prhs = reinterpret_cast<mxArray**>(const_cast<ArrayCref*>(std::data(rhs)));

    // Call the function
    detail::handleMException(mexCallMATLABWithTrap(nlhs, plhs, nrhs, prhs, functionName));

    // Make lhs arrays persistent if the call was successful to get consistent behavior.
    std::for_each(lhs.begin(), lhs.end(), [](Array& array)
    {
      if (array.get() != nullptr)
      {
        mexMakeArrayPersistent(array.get());
      }
    });
  }

  /**
   * @brief Calls a MATLAB function.
   * @param rhs The input arguments.
   * @param functionName The name of the function to call.
   */
  inline void call(View<ArrayCref> rhs, const char* functionName)
  {
    call({}, rhs, functionName);
  }

  /**
   * @brief Evaluates a MATLAB expression.
   * @param expr The expression to evaluate.
   */
  inline void eval(const char* expr)
  {
    if (expr == nullptr)
    {
      throw Exception{"invalid expression"};
    }

    detail::handleMException(mexEvalStringWithTrap(expr));
  }
} // namespace mex

#endif /* MEX_EVAL_HPP */
