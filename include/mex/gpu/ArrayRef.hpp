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

#ifndef MEX_GPU_ARRAY_REF_HPP
#define MEX_GPU_ARRAY_REF_HPP

#include <mex.h>
#include <gpu/mxGPUArray.h>

#include "../common.hpp"

namespace mex::gpu
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
       * @brief Constructor from a mxGPUArray pointer.
       * @param array mxGPUArray pointer
       */
      explicit ArrayRef(mxGPUArray* array)
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
        return mxGPUGetNumberOfDimensions(mArray);
      }

      /**
       * @brief Gets the dimensions of the array.
       * @return The dimensions of the array
       */
      [[nodiscard]] View<std::size_t> getDims() const
      {
        return View<std::size_t>{mxGPUGetDimensions(mArray), getRank()};
      }

      /**
       * @brief Gets the number of elements in the array.
       * @return The number of elements in the array
       */
      [[nodiscard]] std::size_t getNumElements() const
      {
        return mxGPUGetNumberOfElements(mArray);
      }

      /**
       * @brief Is the array a numeric array?
       * @return True if the array is a numeric array, false otherwise
       */
      [[nodiscard]] bool isNumeric() const
      {        
        switch (getClassId())
        {
          case ClassId::_double:
          case ClassId::single:
          case ClassId::int8:
          case ClassId::uint8:
          case ClassId::int16:
          case ClassId::uint16:
          case ClassId::int32:
          case ClassId::uint32:
          case ClassId::int64:
          case ClassId::uint64:
            return true;
          default:
            return false;
        }
      }

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        return getNumElements() == 1;
      }

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        return getNumElements() == 0;
      }

      /**
       * @brief Is the array complex?
       * @return True if the array is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        return mxGPUGetComplexity(mArray) == mxCOMPLEX;
      }

      /**
       * @brief Gets the class ID of the array.
       * @return The class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const
      {
        return static_cast<ClassId>(mxGPUGetClassID(mArray));
      }

      /**
       * @brief Gets the data pointer.
       * @return The data pointer
       */
      [[nodiscard]] void* getData() const
      {
        return mxGPUGetData(mArray);
      }

      /**
       * @brief Gets the mxGPUArray pointer.
       * @return The mxGPUArray pointer
       */
      [[nodiscard]] mxGPUArray* get() const noexcept
      {
        return mArray;
      }
    protected:
      mxGPUArray* mArray{}; ///< The mxGPUArray pointer
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
       * @brief Constructor from a mxGPUArray pointer.
       * @param array mxGPUArray pointer
       */
      explicit ArrayCref(const mxGPUArray* array)
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
        return mxGPUGetNumberOfDimensions(mArray);
      }

      /**
       * @brief Gets the dimensions of the array.
       * @return The dimensions of the array
       */
      [[nodiscard]] View<std::size_t> getDims() const
      {
        return View<std::size_t>{mxGPUGetDimensions(mArray), getRank()};
      }

      /**
       * @brief Gets the number of elements in the array.
       * @return The number of elements in the array
       */
      [[nodiscard]] std::size_t getNumElements() const
      {
        return mxGPUGetNumberOfElements(mArray);
      }

      /**
       * @brief Is the array a numeric array?
       * @return True if the array is a numeric array, false otherwise
       */
      [[nodiscard]] bool isNumeric() const
      {        
        switch (getClassId())
        {
          case ClassId::_double:
          case ClassId::single:
          case ClassId::int8:
          case ClassId::uint8:
          case ClassId::int16:
          case ClassId::uint16:
          case ClassId::int32:
          case ClassId::uint32:
          case ClassId::int64:
          case ClassId::uint64:
            return true;
          default:
            return false;
        }
      }

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        return getNumElements() == 1;
      }

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        return getNumElements() == 0;
      }

      /**
       * @brief Is the array complex?
       * @return True if the array is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        return mxGPUGetComplexity(mArray) == mxCOMPLEX;
      }

      /**
       * @brief Gets the class ID of the array.
       * @return The class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const
      {
        return static_cast<ClassId>(mxGPUGetClassID(mArray));
      }

      /**
       * @brief Gets the data pointer.
       * @return The data pointer
       */
      [[nodiscard]] const void* getData() const
      {
        return mxGPUGetDataReadOnly(mArray);
      }

      /**
       * @brief Gets the mxGPUArray pointer.
       * @return The mxGPUArray pointer
       */
      [[nodiscard]] const mxGPUArray* get() const noexcept
      {
        return mArray;
      }
    protected:
      const mxGPUArray* mArray{}; ///< The mxGPUArray pointer
  };
} // namespace mex::gpu


#endif /* MEX_GPU_ARRAY_REF_HPP */
