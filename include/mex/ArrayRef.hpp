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

#ifndef MEX_ARRAY_REF_HPP
#define MEX_ARRAY_REF_HPP

#include <mex.h>

#include "common.hpp"
#include "typeTraits.hpp"

namespace mex
{
  /**
   * @brief Implements a reference to an array.
   * @tparam T The const or non-const type of the array.
   */
  class ArrayRef
  {
    public:
      /// @brief Explicitly deleted default constructor.
      ArrayRef() = delete;

      /// @brief Explicitly deleted constructor from nullptr.
      ArrayRef(nullptr_t) = delete;

      /**
       * @brief Constructor from a mxArray pointer.
       * @param array mxArray pointer
       */
      explicit ArrayRef(mxArray* array)
      : mArray{array}
      {}

      /**
       * @brief Copy constructor from another reference.
       * @param other Another reference
       */
      ArrayRef(const ArrayRef& other) = default;

      /// @brief Destructor.
      ~ArrayRef() = default;

      /**
       * @brief Copy assignment operator from another reference.
       * @param other Another reference
       * @return Reference to the assigned array
       */
      ArrayRef& operator=(const ArrayRef& other) = default;

      /**
       * @brief Gets the rank of the array.
       * @return The rank of the array
       */
      [[nodiscard]] std::size_t getRank() const
      {
        return mxGetNumberOfDimensions(mArray);
      }

      /**
       * @brief Gets the dimensions of the array.
       * @return The dimensions of the array
       */
      [[nodiscard]] View<std::size_t> getDims() const
      {
        return View<std::size_t>{mxGetDimensions(mArray), getRank()};
      }

      /**
       * @brief Gets the number of elements in the array.
       * @return The number of elements in the array
       */
      [[nodiscard]] std::size_t getNumElements() const
      {
        return mxGetNumberOfElements(mArray);
      }

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        return mxIsScalar(mArray);
      }

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        return mxIsEmpty(mArray);
      }

      /**
       * @brief Is the array complex?
       * @return True if the array is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        return mxIsComplex(mArray);
      }

      /**
       * @brief Gets the class ID of the array.
       * @return The class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const
      {
        return static_cast<ClassId>(mxGetClassID(mArray));
      }

      /**
       * @brief Gets the data pointer.
       * @return The data pointer
       */
      [[nodiscard]] void* getData() const
      {
        return mxGetData(mArray);
      }

      /**
       * @brief Gets the mxArray pointer.
       * @return The mxArray pointer
       */
      [[nodiscard]] mxArray* get() const noexcept
      {
        return mArray;
      }
    protected:
      mxArray* mArray{}; ///< The mxArray pointer
  };

  /**
   * @brief Implements a constant reference to an array.
   * @tparam T The const or non-const type of the array.
   */
  class ArrayCref
  {
    public:
      /// @brief Explicitly deleted default constructor.
      ArrayCref() = delete;

      /// @brief Explicitly deleted constructor from nullptr.
      ArrayCref(nullptr_t) = delete;

      /**
       * @brief Constructor from a mxArray pointer.
       * @param array mxArray pointer
       */
      explicit ArrayCref(const mxArray* array)
      : mArray{array}
      {}

      /**
       * @brief Copy constructor from another reference.
       * @param other Another reference
       */
      ArrayCref(const ArrayCref& other) = default;

      /**
       * @brief Copy constructor from another reference.
       * @param other Another reference
       */
      ArrayCref(const ArrayRef& other)
      : mArray{other.get()}
      {}

      /// @brief Destructor.
      ~ArrayCref() = default;

      /**
       * @brief Copy assignment operator from another reference.
       * @param other Another reference
       * @return Reference to the assigned array
       */
      ArrayCref& operator=(const ArrayCref& other) = default;

      /**
       * @brief Copy assignment operator from another reference.
       * @param other Another reference
       * @return Reference to the assigned array
       */
      ArrayCref& operator=(const ArrayRef& other)
      {
        mArray = other.get();
        return *this;
      }

      /**
       * @brief Gets the rank of the array.
       * @return The rank of the array
       */
      [[nodiscard]] std::size_t getRank() const
      {
        return mxGetNumberOfDimensions(mArray);
      }

      /**
       * @brief Gets the dimensions of the array.
       * @return The dimensions of the array
       */
      [[nodiscard]] View<std::size_t> getDims() const
      {
        return View<std::size_t>{mxGetDimensions(mArray), getRank()};
      }

      /**
       * @brief Gets the number of elements in the array.
       * @return The number of elements in the array
       */
      [[nodiscard]] std::size_t getNumElements() const
      {
        return mxGetNumberOfElements(mArray);
      }

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        return mxIsScalar(mArray);
      }

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        return mxIsEmpty(mArray);
      }

      /**
       * @brief Is the array complex?
       * @return True if the array is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        return mxIsComplex(mArray);
      }

      /**
       * @brief Gets the class ID of the array.
       * @return The class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const
      {
        return static_cast<ClassId>(mxGetClassID(mArray));
      }

      /**
       * @brief Gets the data pointer.
       * @return The data pointer
       */
      [[nodiscard]] const void* getData() const
      {
        return mxGetData(mArray);
      }

      /**
       * @brief Gets the mxArray pointer.
       * @return The mxArray pointer
       */
      [[nodiscard]] const mxArray* get() const noexcept
      {
        return mArray;
      }
    protected:
      const mxArray* mArray{}; ///< The mxArray pointer
  };
} // namespace mex

#endif /* MEX_ARRAY_REF_HPP */
