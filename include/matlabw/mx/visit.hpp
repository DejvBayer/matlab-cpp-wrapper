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

#ifndef MATLABW_MEX_VISIT_HPP
#define MATLABW_MEX_VISIT_HPP

#include "detail/include.hpp"

#include "Array.hpp"
#include "ArrayRef.hpp"

namespace matlabw::mex
{
namespace detail
{
  template<typename T, template<typename> typename... Constraints, typename Fn>
  auto numericVisitorHelper(ArrayCref arrayCref, Fn&& fn)
  {
    if (arrayCref.isComplex())
    {
      using ComplexT = std::complex<T>;
    } 
  }
} // namespace detail

  /**
   * @brief A visitor class that calls the callables with the specified arguments.
   * @tparam Callables The callables.
   */
  template<typename... Callables>
  struct Visitor : Callables...
  {
    using Callables::operator()...;
  };

  template<template<typename> typename... Constraints, typename Fn>
  auto visit(ArrayCref arrayCref, Fn&& fn)
  {
    switch (arrayCref.getClassId())
    {
    // case ClassId::unknown:
    // case ClassId::cell:
    case ClassId::_struct:

    case ClassId::logical:
      return detail::numericVisitorHelper<bool, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::_char:
      return detail::numericVisitorHelper<char16_t, Constraints...>(arrayCref, std::forward<Fn>(fn));
    // case ClassId::_void:
    case ClassId::_double:
      return detail::numericVisitorHelper<double, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::single:
      return detail::numericVisitorHelper<float, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::int8:
      return detail::numericVisitorHelper<std::int8_t, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::uint8:
      return detail::numericVisitorHelper<std::uint8_t, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::int16:
      return detail::numericVisitorHelper<std::int16_t, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::uint16:
      return detail::numericVisitorHelper<std::uint16_t, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::int32:
      return detail::numericVisitorHelper<std::int32_t, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::uint32:
      return detail::numericVisitorHelper<std::uint32_t, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::int64:
      return detail::numericVisitorHelper<std::int64_t, Constraints...>(arrayCref, std::forward<Fn>(fn));
    case ClassId::uint64:
      return detail::numericVisitorHelper<std::uint64_t, Constraints...>(arrayCref, std::forward<Fn>(fn));
    // case ClassId::function:
    // case ClassId::opaque:
    case ClassId::index:
      return detail::visitorHelper<Index, Constraints...>(arrayCref, std::forward<Fn>(fn));
    default:
      throw Exception{"Unsupported class ID"};
    }
  }
} // namespace matlabw::mex

#endif /* MATLABW_MEX_VISIT_HPP */
