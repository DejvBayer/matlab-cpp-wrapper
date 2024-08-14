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

#ifndef MEX_TYPED_ARRAY_HPP
#define MEX_TYPED_ARRAY_HPP

#include "detail/include.hpp"

#include "Array.hpp"
#include "common.hpp"
#include "TypedArrayRef.hpp"

namespace mex
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
      explicit TypedArray(mxArray*&& array) noexcept
      : Array{(checkArrayClass(array), std::move(array))}
      {}

      /**
       * @brief Copy constructor from reference
       * @param other Reference to other array
       */
      explicit TypedArray(const ArrayRef& other)
      : Array{(checkArrayClass(other.get()), other)}
      {}

      /**
       * @brief Copy constructor from const reference
       * @param other Const reference to other array
       */
      explicit TypedArray(const ArrayCref& other)
      : Array{(checkArrayClass(other.get()), other)}
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

      /**
       * @brief Move constructor
       * @param other Other array
       */
      TypedArray(Array&& other) noexcept
      : Array{(checkArrayClass(other.get()), std::move(other))}
      {}

      /// @brief Destructor
      ~TypedArray() noexcept = default;

      /**
       * @brief Copy assignment operator from reference
       * @param other Reference to other array
       * @return Reference to this array
       */
      TypedArray& operator=(const ArrayRef& other)
      {
        checkArrayClass(other.get());

        return Array::operator=(other);
      }

      /**
       * @brief Copy assignment operator from const reference
       * @param other Const reference to other array
       * @return Reference to this array
       */
      TypedArray& operator=(const ArrayCref& other)
      {
        checkArrayClass(other.get());

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
       * @brief Gets the data pointer
       * @return Data pointer
       */
      [[nodiscard]] pointer getData()
      {
        return static_cast<pointer>(Array::getData());
      }

      /**
       * @brief Gets the data pointer
       * @return Const data pointer
       */
      [[nodiscard]] const_pointer getData() const
      {
        return static_cast<const_pointer>(Array::getData());
      }

      /**
       * @brief Gets the element at the specified index
       * @param i Index
       * @return Reference to the element
       */
      [[nodiscard]] reference at(std::size_t i)
      {
        if (i >= getSize())
        {
          throw Exception{"index out of range"};
        }

        return getData()[i];
      }

      /**
       * @brief Gets the element at the specified index
       * @param i Index
       * @return Const reference to the element
       */
      [[nodiscard]] const_reference at(std::size_t i) const
      {
        if (i >= getSize())
        {
          throw Exception{"index out of range"};
        }

        return getData()[i];
      }

      /**
       * @brief Gets the element at the specified index
       * @param i Index
       * @return Reference to the element
       */
      [[nodiscard]] reference operator[](std::size_t i)
      {
        return getData()[i];
      }

      /**
       * @brief Gets the element at the specified index
       * @param i Index
       * @return Const reference to the element
       */
      [[nodiscard]] const_reference operator[](std::size_t i) const
      {
        return getData()[i];
      }

      /**
       * @brief Gets the iterator to the beginning
       * @return Iterator to the beginning
       */
      [[nodiscard]] iterator begin()
      {
        return getData();
      }

      /**
       * @brief Gets the const iterator to the beginning
       * @return Const iterator to the beginning
       */
      [[nodiscard]] const_iterator begin() const
      {
        return getData();
      }

      /**
       * @brief Gets the const iterator to the beginning
       * @return Const iterator to the beginning
       */
      [[nodiscard]] const_iterator cbegin() const
      {
        return getData();
      }

      /**
       * @brief Gets the iterator to the end
       * @return Iterator to the end
       */
      [[nodiscard]] iterator end()
      {
        return getData() + getSize();
      }

      /**
       * @brief Gets the const iterator to the end
       * @return Const iterator to the end
       */
      [[nodiscard]] const_iterator end() const
      {
        return getData() + getSize();
      }

      /**
       * @brief Gets the const iterator to the end
       * @return Const iterator to the end
       */
      [[nodiscard]] const_iterator cend() const
      {
        return getData() + getSize();
      }

      /**
       * @brief Gets the reverse iterator to the beginning
       * @return Reverse iterator to the beginning
       */
      [[nodiscard]] reverse_iterator rbegin()
      {
        return reverse_iterator{end()};
      }

      /**
       * @brief Gets the const reverse iterator to the beginning
       * @return Const reverse iterator to the beginning
       */
      [[nodiscard]] const_reverse_iterator rbegin() const
      {
        return const_reverse_iterator{end()};
      }

      /**
       * @brief Gets the const reverse iterator to the beginning
       * @return Const reverse iterator to the beginning
       */
      [[nodiscard]] const_reverse_iterator crbegin() const
      {
        return const_reverse_iterator{end()};
      }

      /**
       * @brief Gets the reverse iterator to the end
       * @return Reverse iterator to the end
       */
      [[nodiscard]] reverse_iterator rend()
      {
        return reverse_iterator{begin()};
      }

      /**
       * @brief Gets the const reverse iterator to the end
       * @return Const reverse iterator to the end
       */
      [[nodiscard]] const_reverse_iterator rend() const
      {
        return const_reverse_iterator{begin()};
      }

      /**
       * @brief Gets the const reverse iterator to the end
       * @return Const reverse iterator to the end
       */
      [[nodiscard]] const_reverse_iterator crend() const
      {
        return const_reverse_iterator{begin()};
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
       * @brief Check the array class
       * @param array mxArray pointer
       */
      void checkArrayClass(const mxArray* array) const
      {
        return detail::checkArrayClass<classId>(array);
      }
  };
} // namespace mex

#endif /* MEX_TYPED_ARRAY_HPP */
