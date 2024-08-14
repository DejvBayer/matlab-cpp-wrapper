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

#ifndef MEX_TYPE_TRAITS_HPP
#define MEX_TYPE_TRAITS_HPP

#include "detail/include.hpp"

#include "common.hpp"

namespace mex
{
  namespace detail
  {
    /**
     * @brief Helper for IsComplex.
     * @tparam T Type.
     */
    template<typename T>
    struct IsComplexHelper;
  } // namespace detail

  /**
   * @brief Generic IsComplexHelper.
   * @tparam T Type.
   */
  template<typename T>
  struct detail::IsComplexHelper : std::false_type {};

  /**
   * @brief Specialization of IsComplexHelper for std::complex<T>.
   * @tparam T Type.
   */
  template<typename T>
  struct detail::IsComplexHelper<std::complex<T>> : std::true_type {};

  /**
   * @brief IsComplex trait.
   * @tparam T Type.
   */
  template<typename T>
  struct IsComplex : detail::IsComplexHelper<std::remove_cv_t<T>> {};

  /**
   * @brief isComplex value.
   * @tparam T Type.
   */
  template<typename T>
  inline constexpr bool isComplex = IsComplex<T>::value;

  namespace detail
  {
    /**
     * @brief Helper for IsNumeric.
     * @tparam T Type.
     */
    template<typename T>
    struct IsNumericHelper;
  } // namespace detail

  /**
   * @brief IsNumericHelper trait.
   * @tparam T Type.
   */
  template<typename T>
  struct detail::IsNumericHelper
    : std::bool_constant<std::is_arithmetic_v<T> && !std::is_same_v<T, bool>> {};

  /**
   * @brief Specialization of IsNumericHelper for std::complex<T>.
   * @tparam T Type.
   */
  template<typename T>
  struct detail::IsNumericHelper<std::complex<T>>
    : std::bool_constant<std::is_arithmetic_v<T> && !std::is_same_v<T, bool>> {};

  /**
   * @brief IsNumeric trait.
   * @tparam T Type.
   */
  template<typename T>
  struct IsNumeric : detail::IsNumericHelper<std::remove_cv_t<T>> {};

  /**
   * @brief isNumeric value.
   * @tparam T Type.
   */
  template<typename T>
  inline constexpr bool isNumeric = IsNumeric<T>::value;

  /**
   * @brief Class ID constant.
   * @tparam _classId Class ID.
   */
  template<ClassId _classId>
  struct ClassIdConstant
  {
    static constexpr ClassId classId = _classId;
  };

  /**
   * @brief Complexity constant.
   * @tparam _complexity Complexity.
   */
  template<Complexity _complexity>
  struct ComplexityConstant
  {
    static constexpr Complexity complexity = _complexity;
  };

  namespace detail
  {
    /**
     * @brief Helper for type properties.
     * @tparam T Type.
     */
    template<typename T>
    struct TypePropertiesHelper;
  } // namespace detail

  /// @brief Specialization of TypePropertiesHelper for Cell.
  template<>
  struct detail::TypePropertiesHelper<Cell>
    : ClassIdConstant<ClassId::cell> {};

  /// @brief Specialization of TypePropertiesHelper for bool.
  template<>
  struct detail::TypePropertiesHelper<bool>
    : ClassIdConstant<ClassId::logical>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for char.
  template<>
  struct detail::TypePropertiesHelper<char16_t>
    : ClassIdConstant<ClassId::_char>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for void.
  template<>
  struct detail::TypePropertiesHelper<void>
    : ClassIdConstant<ClassId::_void>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for double.
  template<>
  struct detail::TypePropertiesHelper<double>
    : ClassIdConstant<ClassId::_double>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for float.
  template<>
  struct detail::TypePropertiesHelper<float>
    : ClassIdConstant<ClassId::single>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for int8_t.
  template<>
  struct detail::TypePropertiesHelper<std::int8_t>
    : ClassIdConstant<ClassId::int8>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for uint8_t.
  template<>
  struct detail::TypePropertiesHelper<std::uint8_t>
    : ClassIdConstant<ClassId::uint8>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for int16_t.
  template<>
  struct detail::TypePropertiesHelper<std::int16_t>
    : ClassIdConstant<ClassId::int16>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for uint16_t.
  template<>
  struct detail::TypePropertiesHelper<std::uint16_t>
    : ClassIdConstant<ClassId::uint16>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for int32_t.
  template<>
  struct detail::TypePropertiesHelper<std::int32_t>
    : ClassIdConstant<ClassId::int32>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for uint32_t.
  template<>
  struct detail::TypePropertiesHelper<std::uint32_t>
    : ClassIdConstant<ClassId::uint32>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for int64_t.
  template<>
  struct detail::TypePropertiesHelper<std::int64_t>
    : ClassIdConstant<ClassId::int64>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for uint64_t.
  template<>
  struct detail::TypePropertiesHelper<std::uint64_t>
    : ClassIdConstant<ClassId::uint64>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<double>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<double>>
    : ClassIdConstant<ClassId::_double>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<float>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<float>>
    : ClassIdConstant<ClassId::single>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<int8_t>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<std::int8_t>>
    : ClassIdConstant<ClassId::int8>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<uint8_t>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<std::uint8_t>>
    : ClassIdConstant<ClassId::uint8>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<int16_t>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<std::int16_t>>
    : ClassIdConstant<ClassId::int16>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<uint16_t>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<std::uint16_t>>
    : ClassIdConstant<ClassId::uint16>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<int32_t>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<std::int32_t>>
    : ClassIdConstant<ClassId::int32>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<uint32_t>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<std::uint32_t>>
    : ClassIdConstant<ClassId::uint32>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<int64_t>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<std::int64_t>>
    : ClassIdConstant<ClassId::int64>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for std::complex<uint64_t>.
  template<>
  struct detail::TypePropertiesHelper<std::complex<std::uint64_t>>
    : ClassIdConstant<ClassId::uint64>, ComplexityConstant<Complexity::complex> {};

  /// @brief Specialization of TypePropertiesHelper for Index.
  template<>
  struct detail::TypePropertiesHelper<Index>
    : ClassIdConstant<ClassId::index>, ComplexityConstant<Complexity::real> {};

  /// @brief Specialization of TypePropertiesHelper for Struct.
  template<>
  struct detail::TypePropertiesHelper<Struct>
    : ClassIdConstant<ClassId::_struct> {};

  /**
   * @brief Type properties for a given type.
   * @tparam T Type.
   */
  template<typename T>
  struct TypeProperties : detail::TypePropertiesHelper<std::remove_cv_t<T>> {};
} // namespace mex

#endif /* MEX_TYPE_TRAITS_HPP */
