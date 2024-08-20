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

#ifndef MATLABW_MX_ARRAY_REF_HPP
#define MATLABW_MX_ARRAY_REF_HPP

#include "detail/include.hpp"

#include "common.hpp"
#include "Exception.hpp"
#include "typeTraits.hpp"

namespace matlabw::mx
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
      ArrayRef(std::nullptr_t) = delete;

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
       * @brief Get the number of rows
       * @return Number of rows
       */
      [[nodiscard]] std::size_t getDimM() const
      {
        return mxGetM(mArray);
      }

      /**
       * @brief Get the number of columns
       * @return Number of columns
       */
      [[nodiscard]] std::size_t getDimN() const
      {
        return mxGetN(mArray);
      }

      /**
       * @brief Gets the number of elements in the array.
       * @return The number of elements in the array
       */
      [[nodiscard]] std::size_t getSize() const
      {
        return mxGetNumberOfElements(mArray);
      }

      /**
       * @brief Gets the size of the element in bytes
       * @return Size of the element in bytes
       */
      [[nodiscard]] std::size_t getSizeOfElement() const
      {
        return mxGetElementSize(mArray);
      }

      /**
       * @brief Resize the array
       * @param dims Dimensions
       */
      void resize(View<std::size_t> dims) const
      {
        if (mxSetDimensions(mArray, dims.data(), dims.size()))
        {
          throw Exception{"failed to resize array"};
        }
      }

      /**
       * @brief Resize the array
       * @param m Number of rows
       * @param n Number of columns
       */
      void resize(std::size_t m, std::size_t n)
      {
        resize({{m, n}});
      }

#   ifdef MATLABW_ENABLE_GPU
      /**
       * @brief Is the array a GPU array?
       * @return True if the array is a GPU array, false otherwise
       */
      [[nodiscard]] bool isGpuArray() const
      {
        return mxIsGPUArray(mArray);
      }
#   endif

      /**
       * @brief Is the array a numeric array?
       * @return True if the array is a numeric array, false otherwise
       */
      [[nodiscard]] bool isNumeric() const
      {
        return mxIsNumeric(mArray);
      }

      /**
       * @brief Is the array element class complex?
       * @return True if the array element class is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        return mxIsComplex(mArray);
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
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        return mxIsScalar(mArray);
      }

      /**
       * @brief Is the array a double?
       * @return True if the array is a double, false otherwise
       */
      [[nodiscard]] bool isDouble() const
      {
        return mxIsDouble(mArray);
      }

      /**
       * @brief Is the array a single?
       * @return True if the array is a single, false otherwise
       */
      [[nodiscard]] bool isSingle() const
      {
        return mxIsSingle(mArray);
      }

      /**
       * @brief Is the array an int8?
       * @return True if the array is an int8, false otherwise
       */
      [[nodiscard]] bool isInt8() const
      {
        return mxIsInt8(mArray);
      }

      /**
       * @brief Is the array a uint8?
       * @return True if the array is a uint8, false otherwise
       */
      [[nodiscard]] bool isUint8() const
      {
        return mxIsUint8(mArray);
      }

      /**
       * @brief Is the array an int16?
       * @return True if the array is an int16, false otherwise
       */
      [[nodiscard]] bool isInt16() const
      {
        return mxIsInt16(mArray);
      }

      /**
       * @brief Is the array a uint16?
       * @return True if the array is a uint16, false otherwise
       */
      [[nodiscard]] bool isUint16() const
      {
        return mxIsUint16(mArray);
      }

      /**
       * @brief Is the array an int32?
       * @return True if the array is an int32, false otherwise
       */
      [[nodiscard]] bool isInt32() const
      {
        return mxIsInt32(mArray);
      }

      /**
       * @brief Is the array a uint32?
       * @return True if the array is a uint32, false otherwise
       */
      [[nodiscard]] bool isUint32() const
      {
        return mxIsUint32(mArray);
      }

      /**
       * @brief Is the array an int64?
       * @return True if the array is an int64, false otherwise
       */
      [[nodiscard]] bool isInt64() const
      {
        return mxIsInt64(mArray);
      }

      /**
       * @brief Is the array a uint64?
       * @return True if the array is a uint64, false otherwise
       */
      [[nodiscard]] bool isUint64() const
      {
        return mxIsUint64(mArray);
      }

      /**
       * @brief Is the array sparse?
       * @return True if the array is sparse, false otherwise
       */
      [[nodiscard]] bool isSparse() const
      {
        return mxIsSparse(mArray);
      }

      /**
       * @brief Is the array char?
       * @return True if the array is char, false otherwise
       */
      [[nodiscard]] bool isChar() const
      {
        return mxIsChar(mArray);
      }

      /**
       * @brief Is the array a logical?
       * @return True if the array is a logical, false otherwise
       */
      [[nodiscard]] bool isLogical() const
      {
        return mxIsLogical(mArray);
      }

      /**
       * @brief Is the array a logical scalar?
       * @return True if the array is a logical scalar, false otherwise
       */
      [[nodiscard]] bool isLogicalScalar() const
      {
        return mxIsLogicalScalar(mArray);
      }

      /**
       * @brief Is the array a true logical scalar?
       * @return True if the array is a true logical scalar, false otherwise
       */
      [[nodiscard]] bool isLogicalScalarTrue() const
      {
        return mxIsLogicalScalarTrue(mArray);
      }

      /**
       * @brief Is the array a class?
       * @param name Class name
       * @return True if the array is a class, false otherwise
       */
      [[nodiscard]] bool isClass(const char* name) const
      {
        if (name == nullptr)
        {
          throw Exception{"invalid class name"};
        }

        return mxIsClass(mArray, name);
      }

      /**
       * @brief Is the array a class?
       * @param name Class name. Must be null-terminated.
       * @return True if the array is a class, false otherwise
       */
      [[nodiscard]] bool isClass(std::string_view name) const
      {
        return isClass(name.data());
      }

      /**
       * @brief Is the array a struct?
       * @return True if the array is a struct, false otherwise
       */
      [[nodiscard]] bool isStruct() const
      {
        return mxIsStruct(mArray);
      }

      /**
       * @brief Is the array a cell?
       * @return True if the array is a cell, false otherwise
       */
      [[nodiscard]] bool isCell() const
      {
        return mxIsCell(mArray);
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
       * @brief Get the class name of the array
       * @return Class name of the array
       */
      [[nodiscard]] const char* getClassName() const
      {
        return mxGetClassName(mArray);
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
       * @brief Get the array data as a specific type
       * @tparam T Type
       * @return Pointer to the array data
       */
      template<typename T>
      [[nodiscard]] T* getDataAs() const
      {
        if (getClassId() != TypeProperties<T>::classId)
        {
          throw Exception{"mx:Array:getDataAs", "type must match the array class ID"};
        }

        return static_cast<T*>(getData());
      }

      /**
       * @brief Get the array data as a specific type
       * @tparam T Type
       * @return Reference to the array data
       */
      template<typename T>
      [[nodiscard]] T getScalarAs() const
      {
        return *getDataAs<T>();
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
      ArrayCref(std::nullptr_t) = delete;

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
       * @brief Get the number of rows
       * @return Number of rows
       */
      [[nodiscard]] std::size_t getDimM() const
      {
        return mxGetM(mArray);
      }

      /**
       * @brief Get the number of columns
       * @return Number of columns
       */
      [[nodiscard]] std::size_t getDimN() const
      {
        return mxGetN(mArray);
      }

      /**
       * @brief Gets the number of elements in the array.
       * @return The number of elements in the array
       */
      [[nodiscard]] std::size_t getSize() const
      {
        return mxGetNumberOfElements(mArray);
      }

      /**
       * @brief Gets the size of the element in bytes
       * @return Size of the element in bytes
       */
      [[nodiscard]] std::size_t getSizeOfElement() const
      {
        return mxGetElementSize(mArray);
      }

#   ifdef MATLABW_ENABLE_GPU
      /**
       * @brief Is the array a GPU array?
       * @return True if the array is a GPU array, false otherwise
       */
      [[nodiscard]] bool isGpuArray() const
      {
        return mxIsGPUArray(mArray);
      }
#   endif

      /**
       * @brief Is the array a numeric array?
       * @return True if the array is a numeric array, false otherwise
       */
      [[nodiscard]] bool isNumeric() const
      {
        return mxIsNumeric(mArray);
      }

      /**
       * @brief Is the array element class complex?
       * @return True if the array element class is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        return mxIsComplex(mArray);
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
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        return mxIsScalar(mArray);
      }

      /**
       * @brief Is the array a double?
       * @return True if the array is a double, false otherwise
       */
      [[nodiscard]] bool isDouble() const
      {
        return mxIsDouble(mArray);
      }

      /**
       * @brief Is the array a single?
       * @return True if the array is a single, false otherwise
       */
      [[nodiscard]] bool isSingle() const
      {
        return mxIsSingle(mArray);
      }

      /**
       * @brief Is the array an int8?
       * @return True if the array is an int8, false otherwise
       */
      [[nodiscard]] bool isInt8() const
      {
        return mxIsInt8(mArray);
      }

      /**
       * @brief Is the array a uint8?
       * @return True if the array is a uint8, false otherwise
       */
      [[nodiscard]] bool isUint8() const
      {
        return mxIsUint8(mArray);
      }

      /**
       * @brief Is the array an int16?
       * @return True if the array is an int16, false otherwise
       */
      [[nodiscard]] bool isInt16() const
      {
        return mxIsInt16(mArray);
      }

      /**
       * @brief Is the array a uint16?
       * @return True if the array is a uint16, false otherwise
       */
      [[nodiscard]] bool isUint16() const
      {
        return mxIsUint16(mArray);
      }

      /**
       * @brief Is the array an int32?
       * @return True if the array is an int32, false otherwise
       */
      [[nodiscard]] bool isInt32() const
      {
        return mxIsInt32(mArray);
      }

      /**
       * @brief Is the array a uint32?
       * @return True if the array is a uint32, false otherwise
       */
      [[nodiscard]] bool isUint32() const
      {
        return mxIsUint32(mArray);
      }

      /**
       * @brief Is the array an int64?
       * @return True if the array is an int64, false otherwise
       */
      [[nodiscard]] bool isInt64() const
      {
        return mxIsInt64(mArray);
      }

      /**
       * @brief Is the array a uint64?
       * @return True if the array is a uint64, false otherwise
       */
      [[nodiscard]] bool isUint64() const
      {
        return mxIsUint64(mArray);
      }

      /**
       * @brief Is the array sparse?
       * @return True if the array is sparse, false otherwise
       */
      [[nodiscard]] bool isSparse() const
      {
        return mxIsSparse(mArray);
      }

      /**
       * @brief Is the array char?
       * @return True if the array is char, false otherwise
       */
      [[nodiscard]] bool isChar() const
      {
        return mxIsChar(mArray);
      }

      /**
       * @brief Is the array a logical?
       * @return True if the array is a logical, false otherwise
       */
      [[nodiscard]] bool isLogical() const
      {
        return mxIsLogical(mArray);
      }

      /**
       * @brief Is the array a logical scalar?
       * @return True if the array is a logical scalar, false otherwise
       */
      [[nodiscard]] bool isLogicalScalar() const
      {
        return mxIsLogicalScalar(mArray);
      }

      /**
       * @brief Is the array a true logical scalar?
       * @return True if the array is a true logical scalar, false otherwise
       */
      [[nodiscard]] bool isLogicalScalarTrue() const
      {
        return mxIsLogicalScalarTrue(mArray);
      }

      /**
       * @brief Is the array a class?
       * @param name Class name
       * @return True if the array is a class, false otherwise
       */
      [[nodiscard]] bool isClass(const char* name) const
      {
        if (name == nullptr)
        {
          throw Exception{"invalid class name"};
        }

        return mxIsClass(mArray, name);
      }

      /**
       * @brief Is the array a class?
       * @param name Class name. Must be null-terminated.
       * @return True if the array is a class, false otherwise
       */
      [[nodiscard]] bool isClass(std::string_view name) const
      {
        return isClass(name.data());
      }

      /**
       * @brief Is the array a struct?
       * @return True if the array is a struct, false otherwise
       */
      [[nodiscard]] bool isStruct() const
      {
        return mxIsStruct(mArray);
      }

      /**
       * @brief Is the array a cell?
       * @return True if the array is a cell, false otherwise
       */
      [[nodiscard]] bool isCell() const
      {
        return mxIsCell(mArray);
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
       * @brief Get the class name of the array
       * @return Class name of the array
       */
      [[nodiscard]] const char* getClassName() const
      {
        return mxGetClassName(mArray);
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
       * @brief Get the array data as a specific type
       * @tparam T Type
       * @return Pointer to the array data
       */
      template<typename T>
      [[nodiscard]] const T* getDataAs() const
      {
        if (getClassId() != TypeProperties<T>::classId)
        {
          throw Exception{"mx:Array:getDataAs", "type must match the array class ID"};
        }

        return static_cast<const T*>(getData());
      }

      /**
       * @brief Get the array data as a specific type
       * @tparam T Type
       * @return Reference to the array data
       */
      template<typename T>
      [[nodiscard]] T getScalarAs() const
      {
        return *getDataAs<T>();
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

  /**
   * @brief Calculate the linear index of a multi-dimensional subscript.
   * @param array Array
   * @param subs Subscripts
   * @return Linear index
   */
  [[nodiscard]] inline std::size_t calcSingleSubscript(const ArrayCref array, View<std::size_t> subs)
  {
    return mxCalcSingleSubscript(array.get(), subs.size(), subs.data());
  }
} // namespace matlabw::mx

#endif /* MATLABW_MX_ARRAY_REF_HPP */
