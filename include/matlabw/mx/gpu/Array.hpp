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

#ifndef MATLABW_MX_GPU_ARRAY_HPP
#define MATLABW_MX_GPU_ARRAY_HPP

#include "../detail/include.hpp"

#include "../common.hpp"
#include "../Exception.hpp"
#include "../memory.hpp"

namespace matlabw::mx::gpu
{
  // Forward declaration
  class ArrayRef;
  class ArrayCref;

  /// @brief Array class
  class Array
  {
    public:
      /// @brief Default constructor
      Array() noexcept = default;

      /// @brief Explicitly deleted constructor from nullptr.
      Array(std::nullptr_t) = delete;

      /**
       * @brief Constructor
       * @param array mxGPUArray pointer (rvalue reference)
       */
      explicit Array(mxGPUArray*&& array) noexcept;

      /**
       * @brief Copy constructor
       * @param other Other array
       */
      explicit Array(const Array& other);

      /**
       * @brief Copy constructor from reference
       * @param other Reference to other array
       */
      explicit Array(const ArrayRef& other);

      /**
       * @brief Copy constructor from reference
       * @param other Reference to other array
       */
      explicit Array(const ArrayCref& other);

      /**
       * @brief Copy constructor from reference
       * @param other Reference to other array
       */
      explicit Array(const mx::ArrayCref& other);

      /**
       * @brief Move constructor
       * @param other Other array
       */
      Array(Array&& other) noexcept;

      /// @brief Destructor
      ~Array() noexcept;
      /**
       * @brief Copy assignment operator
       * @param other Other array
       * @return Reference to this array
       */
      Array& operator=(const Array& other);

      /**
       * @brief Copy assignment operator from reference
       * @param other Reference to other array
       * @return Reference to this array
       */
      Array& operator=(const ArrayRef& other);

      /**
       * @brief Copy assignment operator from const reference
       * @param other Const reference to other array
       * @return Reference to this array
       */
      Array& operator=(const ArrayCref& other);

      /**
       * @brief Move assignment operator
       * @param other Other array
       * @return Reference to this array
       */
      Array& operator=(Array&& other) noexcept;

      /**
       * @brief Get the rank of the array
       * @return Rank of the array
       */
      [[nodiscard]] std::size_t getRank() const;

      /**
       * @brief Get the dimensions of the array
       * @return View of the dimensions
       */
      [[nodiscard]] View<std::size_t> getDims() const;

      /**
       * @brief Get the number of elements in the array
       * @return Number of elements
       */
      [[nodiscard]] std::size_t getSize() const;

      /**
       * @brief Resize the array
       * @param dims Dimensions
       * @warning The overall number of elements in the array must not be increased
       */
      void resize(View<std::size_t> dims);

      /**
       * @brief Resize the array
       * @param m Number of rows
       * @param n Number of columns
       * @warning The overall number of elements in the array must not be increased
       */
      void resize(std::size_t m, std::size_t n);

      /**
       * @brief Is the array valid?
       * @return True if the array is valid, false otherwise
       */
      [[nodiscard]] bool isValid() const;

      /**
       * @brief Is the array a numeric array?
       * @return True if the array is a numeric array, false otherwise
       */
      [[nodiscard]] bool isNumeric() const;

      /**
       * @brief Is the array element class complex?
       * @return True if the array element class is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const;

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const;

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const;

      /**
       * @brief Is the array a double?
       * @return True if the array is a double, false otherwise
       */
      [[nodiscard]] bool isDouble() const;

      /**
       * @brief Is the array a single?
       * @return True if the array is a single, false otherwise
       */
      [[nodiscard]] bool isSingle() const;

      /**
       * @brief Is the array an int8?
       * @return True if the array is an int8, false otherwise
       */
      [[nodiscard]] bool isInt8() const;

      /**
       * @brief Is the array a uint8?
       * @return True if the array is a uint8, false otherwise
       */
      [[nodiscard]] bool isUint8() const;

      /**
       * @brief Is the array an int16?
       * @return True if the array is an int16, false otherwise
       */
      [[nodiscard]] bool isInt16() const;

      /**
       * @brief Is the array a uint16?
       * @return True if the array is a uint16, false otherwise
       */
      [[nodiscard]] bool isUint16() const;

      /**
       * @brief Is the array an int32?
       * @return True if the array is an int32, false otherwise
       */
      [[nodiscard]] bool isInt32() const;

      /**
       * @brief Is the array a uint32?
       * @return True if the array is a uint32, false otherwise
       */
      [[nodiscard]] bool isUint32() const;

      /**
       * @brief Is the array an int64?
       * @return True if the array is an int64, false otherwise
       */
      [[nodiscard]] bool isInt64() const;

      /**
       * @brief Is the array a uint64?
       * @return True if the array is a uint64, false otherwise
       */
      [[nodiscard]] bool isUint64() const;

      /**
       * @brief Is the array sparse?
       * @return True if the array is sparse, false otherwise
       */
      [[nodiscard]] bool isSparse() const;

      /**
       * @brief Get the class ID of the array
       * @return Class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const;

      /**
       * @brief Get the array data
       * @return Pointer to the array data
       */
      [[nodiscard]] const void* getData() const;

      /**
       * @brief Get the array data
       * @return Pointer to the array data
       */
      [[nodiscard]] void* getData();

      /**
       * @brief Get the mxGPUArray pointer
       * @return mxGPUArray pointer
       */
      [[nodiscard]] mxGPUArray* get() noexcept;

      /**
       * @brief Get the mxGPUArray pointer
       * @return mxGPUArray pointer
       */
      [[nodiscard]] const mxGPUArray* get() const noexcept;

      /**
       * @brief Release the array
       * @return mxArray pointer
       */
      [[nodiscard]] mx::Array release() noexcept;

      /**
       * @brief Convert to ArrayRef
       * @return ArrayRef
       */
      [[nodiscard]] operator ArrayRef();

      /**
       * @brief Convert to ArrayCref
       * @return ArrayCref
       */
      [[nodiscard]] operator ArrayCref() const;
    private:
      /**
       * @brief Duplicate the array
       * @param array mxGPUArray pointer
       * @return Duplicated mxGPUArray pointer
       */
      [[nodiscard]] static mxGPUArray* duplicateArray(const mxGPUArray* array);

      /**
       * @brief Constructor
       * @param array mxArray pointer
       */
      explicit Array(const mxArray* array);

      /// @brief Check if the array is valid
      void checkValid() const;

      /// @brief Destroy the array
      void destroy() noexcept;

      /// @brief Dimensions cache, implemented as unique pointer
      using DimsCache = std::unique_ptr<const std::size_t[], mx::Deleter>;

      mxGPUArray*       mArray{}; ///< mxGPUArray pointer
      mutable DimsCache mDims{};  ///< Dimensions cache, mutable for lazy initialization
  };

  /**
   * @brief Implements a reference to an array.
   * @tparam T The const or non-const type of the array.
   */
  class ArrayRef
  {
    friend class ArrayCref;

    public:
      /// @brief Explicitly deleted default constructor.
      ArrayRef() = delete;

      /**
       * @brief Constructor from a mxGPUArray pointer.
       * @param array mxGPUArray pointer
       */
      explicit ArrayRef(Array& array)
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
       * @brief Get the rank of the array
       * @return Rank of the array
       */
      [[nodiscard]] std::size_t getRank() const
      {
        return mArray.get().getRank();
      }

      /**
       * @brief Get the dimensions of the array
       * @return View of the dimensions
       */
      [[nodiscard]] View<std::size_t> getDims() const
      {
        return mArray.get().getDims();
      }

      /**
       * @brief Get the number of elements in the array
       * @return Number of elements
       */
      [[nodiscard]] std::size_t getSize() const
      {
        return mArray.get().getSize();
      }

      /**
       * @brief Resize the array
       * @param dims Dimensions
       * @warning The overall number of elements in the array must not be increased
       */
      void resize(View<std::size_t> dims) const
      {
        return mArray.get().resize(dims);
      }

      /**
       * @brief Resize the array
       * @param m Number of rows
       * @param n Number of columns
       * @warning The overall number of elements in the array must not be increased
       */
      void resize(std::size_t m, std::size_t n) const
      {
        return mArray.get().resize(m, n);
      }

      /**
       * @brief Is the array valid?
       * @return True if the array is valid, false otherwise
       */
      [[nodiscard]] bool isValid() const
      {
        return mArray.get().isValid();
      }

      /**
       * @brief Is the array a numeric array?
       * @return True if the array is a numeric array, false otherwise
       */
      [[nodiscard]] bool isNumeric() const
      {
        return mArray.get().isNumeric();
      }

      /**
       * @brief Is the array element class complex?
       * @return True if the array element class is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        return mArray.get().isComplex();
      }

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        return mArray.get().isEmpty();
      }

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        return mArray.get().isScalar();
      }

      /**
       * @brief Is the array a double?
       * @return True if the array is a double, false otherwise
       */
      [[nodiscard]] bool isDouble() const
      {
        return mArray.get().isDouble();
      }

      /**
       * @brief Is the array a single?
       * @return True if the array is a single, false otherwise
       */
      [[nodiscard]] bool isSingle() const
      {
        return mArray.get().isSingle();
      }

      /**
       * @brief Is the array an int8?
       * @return True if the array is an int8, false otherwise
       */
      [[nodiscard]] bool isInt8() const
      {
        return mArray.get().isInt8();
      }

      /**
       * @brief Is the array a uint8?
       * @return True if the array is a uint8, false otherwise
       */
      [[nodiscard]] bool isUint8() const
      {
        return mArray.get().isUint8();
      }

      /**
       * @brief Is the array an int16?
       * @return True if the array is an int16, false otherwise
       */
      [[nodiscard]] bool isInt16() const
      {
        return mArray.get().isInt16();
      }

      /**
       * @brief Is the array a uint16?
       * @return True if the array is a uint16, false otherwise
       */
      [[nodiscard]] bool isUint16() const
      {
        return mArray.get().isUint16();
      }

      /**
       * @brief Is the array an int32?
       * @return True if the array is an int32, false otherwise
       */
      [[nodiscard]] bool isInt32() const
      {
        return mArray.get().isInt32();
      }

      /**
       * @brief Is the array a uint32?
       * @return True if the array is a uint32, false otherwise
       */
      [[nodiscard]] bool isUint32() const
      {
        return mArray.get().isUint32();
      }

      /**
       * @brief Is the array an int64?
       * @return True if the array is an int64, false otherwise
       */
      [[nodiscard]] bool isInt64() const
      {
        return mArray.get().isInt64();
      }

      /**
       * @brief Is the array a uint64?
       * @return True if the array is a uint64, false otherwise
       */
      [[nodiscard]] bool isUint64() const
      {
        return mArray.get().isUint64();
      }

      /**
       * @brief Is the array sparse?
       * @return True if the array is sparse, false otherwise
       */
      [[nodiscard]] bool isSparse() const
      {
        return mArray.get().isSparse();
      }

      /**
       * @brief Get the class ID of the array
       * @return Class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const
      {
        return mArray.get().getClassId();
      }

      /**
       * @brief Get the array data
       * @return Pointer to the array data
       */
      [[nodiscard]] void* getData() const
      {
        return mArray.get().getData();
      }

      /**
       * @brief Get the mxGPUArray pointer
       * @return mxGPUArray pointer
       */
      [[nodiscard]] mxGPUArray* get() const noexcept
      {
        return mArray.get().get();
      }
    protected:
      std::reference_wrapper<Array> mArray; ///< The mxGPUArray pointer
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

      /**
       * @brief Constructor from a Array.
       * @param array array.
       */
      explicit ArrayCref(const Array& array)
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
      : mArray{other.mArray}
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
        mArray = other.mArray;
        return *this;
      }

      /**
       * @brief Get the rank of the array
       * @return Rank of the array
       */
      [[nodiscard]] std::size_t getRank() const
      {
        return mArray.get().getRank();
      }

      /**
       * @brief Get the dimensions of the array
       * @return View of the dimensions
       */
      [[nodiscard]] View<std::size_t> getDims() const
      {
        return mArray.get().getDims();
      }

      /**
       * @brief Get the number of elements in the array
       * @return Number of elements
       */
      [[nodiscard]] std::size_t getSize() const
      {
        return mArray.get().getSize();
      }

      /**
       * @brief Is the array valid?
       * @return True if the array is valid, false otherwise
       */
      [[nodiscard]] bool isValid() const
      {
        return mArray.get().isValid();
      }

      /**
       * @brief Is the array a numeric array?
       * @return True if the array is a numeric array, false otherwise
       */
      [[nodiscard]] bool isNumeric() const
      {
        return mArray.get().isNumeric();
      }

      /**
       * @brief Is the array element class complex?
       * @return True if the array element class is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        return mArray.get().isComplex();
      }

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        return mArray.get().isEmpty();
      }

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        return mArray.get().isScalar();
      }

      /**
       * @brief Is the array a double?
       * @return True if the array is a double, false otherwise
       */
      [[nodiscard]] bool isDouble() const
      {
        return mArray.get().isDouble();
      }

      /**
       * @brief Is the array a single?
       * @return True if the array is a single, false otherwise
       */
      [[nodiscard]] bool isSingle() const
      {
        return mArray.get().isSingle();
      }

      /**
       * @brief Is the array an int8?
       * @return True if the array is an int8, false otherwise
       */
      [[nodiscard]] bool isInt8() const
      {
        return mArray.get().isInt8();
      }

      /**
       * @brief Is the array a uint8?
       * @return True if the array is a uint8, false otherwise
       */
      [[nodiscard]] bool isUint8() const
      {
        return mArray.get().isUint8();
      }

      /**
       * @brief Is the array an int16?
       * @return True if the array is an int16, false otherwise
       */
      [[nodiscard]] bool isInt16() const
      {
        return mArray.get().isInt16();
      }

      /**
       * @brief Is the array a uint16?
       * @return True if the array is a uint16, false otherwise
       */
      [[nodiscard]] bool isUint16() const
      {
        return mArray.get().isUint16();
      }

      /**
       * @brief Is the array an int32?
       * @return True if the array is an int32, false otherwise
       */
      [[nodiscard]] bool isInt32() const
      {
        return mArray.get().isInt32();
      }

      /**
       * @brief Is the array a uint32?
       * @return True if the array is a uint32, false otherwise
       */
      [[nodiscard]] bool isUint32() const
      {
        return mArray.get().isUint32();
      }

      /**
       * @brief Is the array an int64?
       * @return True if the array is an int64, false otherwise
       */
      [[nodiscard]] bool isInt64() const
      {
        return mArray.get().isInt64();
      }

      /**
       * @brief Is the array a uint64?
       * @return True if the array is a uint64, false otherwise
       */
      [[nodiscard]] bool isUint64() const
      {
        return mArray.get().isUint64();
      }

      /**
       * @brief Is the array sparse?
       * @return True if the array is sparse, false otherwise
       */
      [[nodiscard]] bool isSparse() const
      {
        return mArray.get().isSparse();
      }

      /**
       * @brief Get the class ID of the array
       * @return Class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const
      {
        return mArray.get().getClassId();
      }

      /**
       * @brief Get the array data
       * @return Pointer to the array data
       */
      [[nodiscard]] const void* getData() const
      {
        return mArray.get().getData();
      }

      /**
       * @brief Get the mxGPUArray pointer
       * @return mxGPUArray pointer
       */
      [[nodiscard]] const mxGPUArray* get() const noexcept
      {
        return mArray.get().get();
      }
    protected:
      std::reference_wrapper<const Array> mArray; ///< The mxGPUArray pointer
  };

  /**
   * @brief Constructor
   * @param array mxGPUArray pointer (rvalue reference)
   */
  inline Array::Array(mxGPUArray*&& array) noexcept
  : mArray{array}
  {}

  /**
   * @brief Constructor
   * @param array mxArray pointer
   */
  inline Array::Array(const mxArray* array)
  : mArray{mxGPUCopyFromMxArray(array)}
  {
    if (mArray == nullptr)
    {
      throw Exception{"failed to create array from mxArray"};
    }
  }

  /**
   * @brief Copy constructor
   * @param other Other array
   */
  inline Array::Array(const Array& other)
  : Array{duplicateArray(other.get())}
  {}

  /**
   * @brief Copy constructor from reference
   * @param other Reference to other array
   */
  inline Array::Array(const ArrayRef& other)
  : Array{duplicateArray(other.get())}
  {}

  /**
   * @brief Copy constructor from reference
   * @param other Reference to other array
   */
  inline Array::Array(const ArrayCref& other)
  : Array{duplicateArray(other.get())}
  {}

  /**
   * @brief Copy constructor from reference
   * @param other Reference to other array
   */
  inline Array::Array(const mx::ArrayCref& other)
  : Array{other.get()}
  {}

  /**
   * @brief Move constructor
   * @param other Other array
   */
  inline Array::Array(Array&& other) noexcept
  : mArray{std::exchange(other.mArray, nullptr)},
    mDims{std::move(other.mDims)}
  {}

  /// @brief Destructor
  inline Array::~Array() noexcept
  {
    destroy();
  }

  /**
   * @brief Copy assignment operator
   * @param other Other array
   * @return Reference to this array
   */
  inline Array& Array::operator=(const Array& other)
  {
    if (this != &other)
    {
      destroy();
      mArray = duplicateArray(other.get());
    }

    return *this;
  }

  /**
   * @brief Copy assignment operator from reference
   * @param other Reference to other array
   * @return Reference to this array
   */
  inline Array& Array::operator=(const ArrayRef& other)
  {
    if (other.get() != get())
    {
      destroy();
      mArray = duplicateArray(other.get());
    }

    return *this;
  }

  /**
   * @brief Copy assignment operator from const reference
   * @param other Const reference to other array
   * @return Reference to this array
   */
  inline Array& Array::operator=(const ArrayCref& other)
  {
    if (other.get() != get())
    {
      destroy();
      mArray = duplicateArray(other.get());
    }

    return *this;
  }

  /**
   * @brief Move assignment operator
   * @param other Other array
   * @return Reference to this array
   */
  inline Array& Array::operator=(Array&& other) noexcept
  {
    if (this != &other)
    {
      destroy();
      mArray = std::exchange(other.mArray, nullptr);
      mDims  = std::move(other.mDims);
    }

    return *this;
  }

  /**
   * @brief Get the rank of the array
   * @return Rank of the array
   */
  [[nodiscard]] inline std::size_t Array::getRank() const
  {
    checkValid();
    return mxGPUGetNumberOfDimensions(mArray);
  }

  /**
   * @brief Get the dimensions of the array
   * @return View of the dimensions
   */
  [[nodiscard]] inline View<std::size_t> Array::getDims() const
  {
    checkValid();
    
    if (mDims == nullptr)
    {
      mDims.reset(mxGPUGetDimensions(mArray));
    }

    return {mDims.get(), getRank()};
  }

  /**
   * @brief Get the number of elements in the array
   * @return Number of elements
   */
  [[nodiscard]] inline std::size_t Array::getSize() const
  {
    checkValid();
    return mxGPUGetNumberOfElements(mArray);
  }

  /**
   * @brief Resize the array
   * @param dims Dimensions
   * @warning The overall number of elements in the array must not be increased
   */
  inline void Array::resize(View<std::size_t> dims)
  {
    checkValid();

    if (getSize() < std::accumulate(dims.begin(), dims.end(), std::size_t{1}, std::multiplies<>{}))
    {
      throw Exception{"number of elements in the array must not be increased"};
    }

    mxGPUSetDimensions(mArray, dims.data(), dims.size());
    mDims.reset();
  }

  /**
   * @brief Resize the array
   * @param m Number of rows
   * @param n Number of columns
   * @warning The overall number of elements in the array must not be increased
   */
  inline void Array::resize(std::size_t m, std::size_t n)
  {
    resize({{m, n}});
  }

  /**
   * @brief Is the array valid?
   * @return True if the array is valid, false otherwise
   */
  [[nodiscard]] inline bool Array::isValid() const
  {
    return mArray != nullptr;
  }

  /**
   * @brief Is the array a numeric array?
   * @return True if the array is a numeric array, false otherwise
   */
  [[nodiscard]] inline bool Array::isNumeric() const
  {
    checkValid();
    
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
   * @brief Is the array element class complex?
   * @return True if the array element class is complex, false otherwise
   */
  [[nodiscard]] inline bool Array::isComplex() const
  {
    checkValid();
    return mxGPUGetComplexity(mArray) == mxCOMPLEX;
  }

  /**
   * @brief Is the array empty?
   * @return True if the array is empty, false otherwise
   */
  [[nodiscard]] inline bool Array::isEmpty() const
  {
    return getSize() == 0;
  }

  /**
   * @brief Is the array a scalar?
   * @return True if the array is a scalar, false otherwise
   */
  [[nodiscard]] inline bool Array::isScalar() const
  {
    return getSize() == 1;
  }

  /**
   * @brief Is the array a double?
   * @return True if the array is a double, false otherwise
   */
  [[nodiscard]] inline bool Array::isDouble() const
  {
    return getClassId() == ClassId::_double;
  }

  /**
   * @brief Is the array a single?
   * @return True if the array is a single, false otherwise
   */
  [[nodiscard]] inline bool Array::isSingle() const
  {
    return getClassId() == ClassId::single;
  }

  /**
   * @brief Is the array an int8?
   * @return True if the array is an int8, false otherwise
   */
  [[nodiscard]] inline bool Array::isInt8() const
  {
    return getClassId() == ClassId::int8;
  }

  /**
   * @brief Is the array a uint8?
   * @return True if the array is a uint8, false otherwise
   */
  [[nodiscard]] inline bool Array::isUint8() const
  {
    return getClassId() == ClassId::uint8;
  }

  /**
   * @brief Is the array an int16?
   * @return True if the array is an int16, false otherwise
   */
  [[nodiscard]] inline bool Array::isInt16() const
  {
    return getClassId() == ClassId::int16;
  }

  /**
   * @brief Is the array a uint16?
   * @return True if the array is a uint16, false otherwise
   */
  [[nodiscard]] inline bool Array::isUint16() const
  {
    return getClassId() == ClassId::uint16;
  }

  /**
   * @brief Is the array an int32?
   * @return True if the array is an int32, false otherwise
   */
  [[nodiscard]] inline bool Array::isInt32() const
  {
    return getClassId() == ClassId::int32;
  }

  /**
   * @brief Is the array a uint32?
   * @return True if the array is a uint32, false otherwise
   */
  [[nodiscard]] inline bool Array::isUint32() const
  {
    return getClassId() == ClassId::uint32;
  }

  /**
   * @brief Is the array an int64?
   * @return True if the array is an int64, false otherwise
   */
  [[nodiscard]] inline bool Array::isInt64() const
  {
    return getClassId() == ClassId::int64;
  }

  /**
   * @brief Is the array a uint64?
   * @return True if the array is a uint64, false otherwise
   */
  [[nodiscard]] inline bool Array::isUint64() const
  {
    return getClassId() == ClassId::uint64;
  }

  /**
   * @brief Is the array sparse?
   * @return True if the array is sparse, false otherwise
   */
  [[nodiscard]] inline bool Array::isSparse() const
  {
    checkValid();
    return mxGPUIsSparse(mArray);
  }

  /**
   * @brief Get the class ID of the array
   * @return Class ID of the array
   */
  [[nodiscard]] inline ClassId Array::getClassId() const
  {
    checkValid();
    return static_cast<ClassId>(mxGPUGetClassID(mArray));
  }

  /**
   * @brief Get the array data
   * @return Pointer to the array data
   */
  [[nodiscard]] inline const void* Array::getData() const
  {
    checkValid();
    return mxGPUGetDataReadOnly(mArray);
  }

  /**
   * @brief Get the array data
   * @return Pointer to the array data
   */
  [[nodiscard]] inline void* Array::getData()
  {
    checkValid();
    return mxGPUGetData(mArray);
  }

  /**
   * @brief Get the mxGPUArray pointer
   * @return mxGPUArray pointer
   */
  [[nodiscard]] inline mxGPUArray* Array::get() noexcept
  {
    return mArray;
  }

  /**
   * @brief Get the mxGPUArray pointer
   * @return mxGPUArray pointer
   */
  [[nodiscard]] inline const mxGPUArray* Array::get() const noexcept
  {
    return mArray;
  }

  /**
   * @brief Release the array
   * @return mxArray pointer
   */
  [[nodiscard]] inline mx::Array Array::release() noexcept
  {
    mxArray* array = mxGPUCreateMxArrayOnGPU(mArray);

    destroy();

    return mx::Array{std::move(array)};
  }

  /**
   * @brief Convert to ArrayRef
   * @return ArrayRef
   */
  [[nodiscard]] inline Array::operator ArrayRef()
  {
    checkValid();
    return ArrayRef{*this};
  }

  /**
   * @brief Convert to ArrayCref
   * @return ArrayCref
   */
  [[nodiscard]] inline Array::operator ArrayCref() const
  {
    checkValid();
    return ArrayCref{*this};
  }

  /**
   * @brief Duplicate the array
   * @param array mxGPUArray pointer
   * @return Duplicated mxGPUArray pointer
   */
  [[nodiscard]] inline mxGPUArray* Array::duplicateArray(const mxGPUArray* array)
  {
    mxGPUArray* arrayDup{};

    if (array != nullptr)
    {
      arrayDup = mxGPUCopyGPUArray(array);

      if (arrayDup == nullptr)
      {
        throw Exception{"failed to duplicate array"};
      }
    }
    
    return arrayDup;
  }

  /// @brief Check if the array is valid
  inline void Array::checkValid() const
  {
    if (!isValid())
    {
      throw Exception{"accessing invalid array"};
    }
  }

  /// @brief Destroy the array
  inline void Array::destroy() noexcept
  {
    mxGPUDestroyGPUArray(std::exchange(mArray, nullptr));
    mDims.reset();
  }
} // namespace matlabw::mx::gpu


#endif /* MATLABW_MX_GPU_ARRAY_HPP */
