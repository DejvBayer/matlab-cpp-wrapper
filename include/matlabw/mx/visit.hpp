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

#ifndef MATLABW_MX_VISIT_HPP
#define MATLABW_MX_VISIT_HPP

#include "detail/include.hpp"

#include "CellArrayRef.hpp"
#include "CharArrayRef.hpp"
#include "NumericArrayRef.hpp"
#include "StructArrayRef.hpp"

namespace matlabw::mx
{
namespace detail
{
  /**
   * @brief Helper function for the visitor.
   * @tparam Constaints The constraints.
   * @tparam ArrayRefT The array ref type (const or nonconst).
   * @tparam Fn The callable type.
   * @param arrayRef The array ref (const or nonconst).
   * @param fn The callable.
   * @return The result of the callable.
   */
  template<template<typename> typename... Constaints, typename ArrayRefT, typename Fn>
  auto visitorHelper(ArrayRefT arrayRef, Fn&& fn)
  {
    if constexpr (std::conjunction_v<Constaints<ArrayRefT>...>)
    {
      return std::forward<Fn>(fn)(arrayRef);
    }
    else
    {
      throw Exception{"matlabw:mx:visit", "visitor constraints not satisfied"};
    }
  }

  /**
   * @brief Helper function for the numeric visitor.
   * @tparam T The numeric type.
   * @tparam Constraints The constraints.
   * @tparam Fn The callable type.
   * @param arrayRef The array ref.
   * @param fn The callable.
   * @return The result of the callable.
   */
  template<typename T, template<typename> typename... Constraints, typename Fn>
  auto numericVisitorHelper(ArrayRef arrayRef, Fn&& fn)
  {
    if (arrayRef.isComplex())
    {
      return visitorHelper<Constraints...>(NumericArrayRef<std::complex<T>>{arrayRef}, std::forward<Fn>(fn));
    }
    else
    {
      return visitorHelper<Constraints...>(NumericArrayRef<T>{arrayRef}, std::forward<Fn>(fn));
    }
  }

  /**
   * @brief Helper function for the numeric visitor.
   * @tparam T The numeric type.
   * @tparam Constraints The constraints.
   * @tparam Fn The callable type.
   * @param arrayCref The array cref.
   * @param fn The callable.
   * @return The result of the callable.
   */
  template<typename T, template<typename> typename... Constraints, typename Fn>
  auto numericVisitorHelper(ArrayCref arrayCref, Fn&& fn)
  {
    if (arrayCref.isComplex())
    {
      return visitorHelper<Constraints...>(NumericArrayCref<std::complex<T>>{arrayCref}, std::forward<Fn>(fn));
    }
    else
    {
      return visitorHelper<Constraints...>(NumericArrayCref<T>{arrayCref}, std::forward<Fn>(fn));
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

  /**
   * @brief Deduction guide for the Visitor class.
   * @tparam Callables The callables.
   */
  template<class... Callables>
  Visitor(Callables...) -> Visitor<Callables...>;

  /**
   * @brief Visit the array cref with the specified callable.
   * @tparam Constraints The constraints.
   * @tparam Fn The callable type.
   * @param arrayRef The array ref.
   * @param fn The callable.
   * @return The result of the callable.
   */
  template<template<typename> typename... Constraints, typename Fn>
  auto visit(ArrayRef arrayRef, Fn&& fn)
  {
    switch (arrayRef.getClassId())
    {
    case ClassId::cell:
      return detail::visitorHelper<Constraints...>(CellArrayCref{arrayRef}, std::forward<Fn>(fn));
    case ClassId::_struct:
      return detail::visitorHelper<Constraints...>(StructArrayCref{arrayRef}, std::forward<Fn>(fn));
    case ClassId::logical:
      return detail::visitorHelper<bool, Constraints...>(TypedArrayRef<bool>{arrayRef}, std::forward<Fn>(fn));
    case ClassId::_char:
      return detail::visitorHelper<char16_t, Constraints...>(CharArrayCref{arrayRef}, std::forward<Fn>(fn));
    case ClassId::_double:
      return detail::numericVisitorHelper<double, Constraints...>(arrayRef, std::forward<Fn>(fn));
    case ClassId::single:
      return detail::numericVisitorHelper<float, Constraints...>(arrayRef, std::forward<Fn>(fn));
    case ClassId::int8:
      return detail::numericVisitorHelper<std::int8_t, Constraints...>(arrayRef, std::forward<Fn>(fn));
    case ClassId::uint8:
      return detail::numericVisitorHelper<std::uint8_t, Constraints...>(arrayRef, std::forward<Fn>(fn));
    case ClassId::int16:
      return detail::numericVisitorHelper<std::int16_t, Constraints...>(arrayRef, std::forward<Fn>(fn));
    case ClassId::uint16:
      return detail::numericVisitorHelper<std::uint16_t, Constraints...>(arrayRef, std::forward<Fn>(fn));
    case ClassId::int32:
      return detail::numericVisitorHelper<std::int32_t, Constraints...>(arrayRef, std::forward<Fn>(fn));
    case ClassId::uint32:
      return detail::numericVisitorHelper<std::uint32_t, Constraints...>(arrayRef, std::forward<Fn>(fn));
    case ClassId::int64:
      return detail::numericVisitorHelper<std::int64_t, Constraints...>(arrayRef, std::forward<Fn>(fn));
    case ClassId::uint64:
      return detail::numericVisitorHelper<std::uint64_t, Constraints...>(arrayRef, std::forward<Fn>(fn));
    default:
      throw Exception{"matlabw:mx:visit", "unknown class ID"};
    }
  }

  /**
   * @brief Visit the array cref with the specified callable.
   * @tparam Constraints The constraints.
   * @tparam Fn The callable type.
   * @param arrayCref The array cref.
   * @param fn The callable.
   * @return The result of the callable.
   */
  template<template<typename> typename... Constraints, typename Fn>
  auto visit(ArrayCref arrayCref, Fn&& fn)
  {
    switch (arrayCref.getClassId())
    {
    case ClassId::cell:
      return detail::visitorHelper<Constraints...>(CellArrayCref{arrayCref}, std::forward<Fn>(fn));
    case ClassId::_struct:
      return detail::visitorHelper<Constraints...>(StructArrayCref{arrayCref}, std::forward<Fn>(fn));
    case ClassId::logical:
      return detail::visitorHelper<bool, Constraints...>(TypedArray<bool>{arrayCref}, std::forward<Fn>(fn));
    case ClassId::_char:
      return detail::visitorHelper<char16_t, Constraints...>(CharArrayCref{arrayCref}, std::forward<Fn>(fn));
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
    default:
      throw Exception{"matlabw:mx:visit", "unknown class ID"};
    }
  }
} // namespace matlabw::mx

#endif /* MATLABW_MX_VISIT_HPP */
