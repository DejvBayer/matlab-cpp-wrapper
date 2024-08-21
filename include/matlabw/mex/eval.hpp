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

#ifndef MATLABW_MEX_EVAL_HPP
#define MATLABW_MEX_EVAL_HPP

#include "detail/include.hpp"
#include "detail/MException.hpp"

namespace matlabw::mex
{
  /**
   * @brief Calls a MATLAB function.
   * @param lhs The left-hand side arguments.
   * @param rhs The right-hand side arguments.
   * @param functionName The name of the function to call. Must be null-terminated.
   */
  inline void call(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs, const char* functionName)
  {
    if (!std::empty(lhs) && std::data(lhs) == nullptr)
    {
      throw mx::Exception{"invalid output"};
    }

    if (!std::empty(rhs) && std::data(rhs) == nullptr)
    {
      throw mx::Exception{"invalid input"};
    }

    if (functionName == nullptr)
    {
      throw mx::Exception{"invalid function name"};
    }

    // Reinterpret trick requires that the array wrappers have the same size as mxArray*.
    static_assert(sizeof(mxArray*) == sizeof(mx::Array));
    static_assert(sizeof(const mxArray*) == sizeof(mx::ArrayCref));

    // Set lhs
    const int nlhs = static_cast<int>(lhs.size());
    mxArray** plhs = reinterpret_cast<mxArray**>(lhs.data());

    // Set rhs
    const int nrhs = static_cast<int>(rhs.size());
    mxArray** prhs = reinterpret_cast<mxArray**>(const_cast<mx::ArrayCref*>(std::data(rhs)));

    // Call the function
    detail::handleMException(mexCallMATLABWithTrap(nlhs, plhs, nrhs, prhs, functionName));
  }

  /**
   * @brief Calls a MATLAB function.
   * @param lhs The left-hand side arguments.
   * @param rhs The right-hand side arguments.
   * @param functionName The name of the function to call. Must be null-terminated.
   */
  inline void call(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs, std::string_view functionName)
  {
    call(lhs, rhs, functionName.data());
  }

  /**
   * @brief Calls a MATLAB function.
   * @param rhs The input arguments.
   * @param functionName The name of the function to call. Must be null-terminated.
   */
  inline void call(mx::View<mx::ArrayCref> rhs, const char* functionName)
  {
    call({}, rhs, functionName);
  }

  /**
   * @brief Calls a MATLAB function.
   * @param rhs The input arguments.
   * @param functionName The name of the function to call. Must be null-terminated.
   */
  inline void call(mx::View<mx::ArrayCref> rhs, std::string_view functionName)
  {
    call(rhs, functionName.data());
  }

  /**
   * @brief Evaluates a MATLAB expression.
   * @param expr The expression to evaluate. Must be null-terminated.
   */
  inline void eval(const char* expr)
  {
    if (expr == nullptr)
    {
      throw mx::Exception{"invalid expression"};
    }

    detail::handleMException(mexEvalStringWithTrap(expr));
  }

  /**
   * @brief Evaluates a MATLAB expression.
   * @param expr The expression to evaluate. Must be null-terminated.
   */
  inline void eval(std::string_view expr)
  {
    eval(expr.data());
  }
} // namespace matlabw::mex

#endif /* MATLABW_MEX_EVAL_HPP */
