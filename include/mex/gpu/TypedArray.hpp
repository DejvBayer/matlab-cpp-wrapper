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

#ifndef MEX_GPU_TYPED_ARRAY_HPP
#define MEX_GPU_TYPED_ARRAY_HPP

#include "../detail/include.hpp"

#include "Array.hpp"
#include "TypedArrayRef.hpp"
#include "../common.hpp"

namespace mex::gpu
{
  /**
   * @brief Numeric typed array
   * @tparam T Element type
   */
  template<typename T>
  class TypedArray : public Array
  {
    static_assert(!std::is_const_v<T>, "T must be a non-const type");
    static_assert(!std::is_volatile_v<T>, "T must be a non-volatile type");
    static_assert(!std::is_reference_v<T>, "T must be a non-reference type");

    public:
      using value_type             = T;                                     ///< Element type
      using reference              = T&;                                    ///< Reference type
      using const_reference        = const T&;                              ///< Const reference type
      using pointer                = T*;                                    ///< Pointer type
      using const_pointer          = const T*;                              ///< Const pointer type
      using iterator               = pointer;                               ///< Iterator type
      using const_iterator         = const_pointer;                         ///< Const iterator type
      using reverse_iterator       = std::reverse_iterator<iterator>;       ///< Reverse iterator type
      using const_reverse_iterator = std::reverse_iterator<const_iterator>; ///< Const reverse iterator type

      /// @brief Type class ID
      static constexpr ClassId classId = TypeProperties<T>::classId;

      /// @brief Default constructor
      TypedArray() noexcept = default;

      /// @brief Explicitly deleted constructor from nullptr.
      TypedArray(std::nullptr_t) = delete;

      /**
       * @brief Constructor
       * @param array mxArray pointer (rvalue reference)
       */
      explicit TypedArray(const mex::ArrayCref& array) noexcept
      : Array{(checkArrayClass(array.getClassId()), array)}
      {}

      /**
       * @brief Copy constructor from const reference
       * @param other Const reference to other array
       */
      explicit TypedArray(const ArrayCref& other)
      : Array{(checkArrayClass(other.getClassId()), other)}
      {}

      /**
       * @brief Copy constructor
       * @param other Other array
       */
      explicit TypedArray(const TypedArray& other) = default;

      /**
       * @brief Move constructor
       * @param other Other array
       */
      TypedArray(TypedArray&& other) noexcept = default;

      /// @brief Destructor
      ~TypedArray() noexcept = default;

      /**
       * @brief Copy assignment operator from const reference
       * @param other Const reference to other array
       * @return Reference to this array
       */
      TypedArray& operator=(const ArrayCref& other)
      {
        checkArrayClass(other.getClassId());

        return Array::operator=(other);
      }

      /**
       * @brief Copy assignment operator
       * @param other Other array
       * @return Reference to this array
       */
      TypedArray& operator=(const TypedArray& other) = default;

      /**
       * @brief Move assignment operator
       * @param other Other array
       * @return Reference to this array
       */
      TypedArray& operator=(TypedArray&& other) noexcept = default;

      /**
       * @brief Gets a pointer to the data.
       * @return Pointer to the data
       */
      [[nodiscard]] const_pointer getData() const
      {
        return static_cast<const_pointer>(Array::getData());
      }

      /**
       * @brief Gets a pointer to the data.
       * @return Pointer to the data
       */
      [[nodiscard]] pointer getData()
      {
        return static_cast<pointer>(Array::getData());
      }

      /// @brief Use the Array::operator ArrayRef
      using Array::operator ArrayRef;

      /// @brief Use the Array::operator ArrayCref
      using Array::operator ArrayCref;

      /**
       * @brief Conversion operator to TypedArrayRef
       * @return Reference to the array
       */
      [[nodiscard]] operator TypedArrayRef<T>()
      {
        checkValid();
        return TypedArrayRef<T>{get()};
      }

      /**
       * @brief Conversion operator to TypedArrayCref
       * @return Const reference to the array
       */
      [[nodiscard]] operator TypedArrayCref<T>() const
      {
        checkValid();
        return TypedArrayCref<T>{get()};
      }
    private:
      /**
       * @brief Checks if the array is of the correct class.
       * @param otherClassId Class ID
       */
      void checkArrayClass(const ClassId otherClassId) const
      {
        if (otherClassId != classId)
        {
          throw Exception{"invalid class ID"};
        }
      }
  };
} // namespace mex::gpu

#endif /* MEX_GPU_TYPED_ARRAY_HPP */
