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

#ifndef MATLABW_MX_STRUCT_ARRAY_HPP
#define MATLABW_MX_STRUCT_ARRAY_HPP

#include "detail/include.hpp"

#include "common.hpp"
#include "Exception.hpp"
#include "TypedArray.hpp"
#include "StructArrayRef.hpp"

namespace matlabw::mx
{
  /// @brief StructArray class
  class StructArray : public TypedArray<Struct>
  {
    public:
      /// @brief Inherit constructors from TypedArray<Struct>
      using TypedArray<Struct>::TypedArray;

      /// @brief Default destructor
      ~StructArray() = default;

      /// @brief Use the TypedArray<Struct>::operator=
      using TypedArray<Struct>::operator=;

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayRef> getField(std::size_t i, const char* fieldName)
      {
        return getField(i, getFieldIndex(fieldName));
      }

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field. Must be null-terminated.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayRef> getField(std::size_t i, std::string_view fieldName)
      {
        return getField(i, fieldName.data());
      }

      /**
       * @brief Get the field of the structure array at index 0.
       * @param fieldName The name of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayRef> getField(const char* fieldName)
      {
        return getField(0, fieldName);
      }

      /**
       * @brief Get the field of the structure array at index 0.
       * @param fieldName The name of the field. Must be null-terminated.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayRef> getField(std::string_view fieldName)
      {
        return getField(fieldName.data());
      }

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldIndex The index of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayRef> getField(std::size_t i, FieldIndex fieldIndex)
      {
        checkValid("matlabw::mx::StructArray::getField");

        if (fieldIndex == FieldIndex::invalid)
        {
          return std::nullopt;
        }

        if (static_cast<std::size_t>(fieldIndex) >= getFieldCount())
        {
          throw Exception("field index out of range");
        }

        mxArray* field = mxGetFieldByNumber(get(), i, static_cast<int>(fieldIndex));

        if (field == nullptr)
        {
          return std::nullopt;
        }

        return ArrayRef{field};
      }

      /**
       * @brief Get the field of the structure array at index 0.
       * @param fieldIndex The index of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayRef> getField(FieldIndex fieldIndex)
      {
        return getField(0, fieldIndex);
      }

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(std::size_t i, const char* fieldName) const
      {
        return getField(i, getFieldIndex(fieldName));
      }

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field. Must be null-terminated.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(std::size_t i, std::string_view fieldName) const
      {
        return getField(i, fieldName.data());
      }

      /**
       * @brief Get the field of the structure array at index 0.
       * @param fieldName The name of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(const char* fieldName) const
      {
        return getField(0, fieldName);
      }

      /**
       * @brief Get the field of the structure array at index 0.
       * @param fieldName The name of the field. Must be null-terminated.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(std::string_view fieldName) const
      {
        return getField(fieldName.data());
      }

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldIndex The index of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(std::size_t i, FieldIndex fieldIndex) const
      {
        checkValid("matlabw::mx::StructArray::getField");

        if (fieldIndex == FieldIndex::invalid)
        {
          return std::nullopt;
        }
        
        if (static_cast<std::size_t>(fieldIndex) >= getFieldCount())
        {
          throw Exception("field index out of range");
        }

        const mxArray* field = mxGetFieldByNumber(get(), i, static_cast<int>(fieldIndex));

        if (field == nullptr)
        {
          return std::nullopt;
        }

        return ArrayCref{field};
      }

      /**
       * @brief Get the field of the structure array at index 0.
       * @param fieldIndex The index of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(FieldIndex fieldIndex) const
      {
        return getField(0, fieldIndex);
      }

      /**
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @param value The value.
       */
      void setField(std::size_t i, const char* fieldName, ArrayCref value)
      {
        setField(i, getFieldIndex(fieldName), value);
      }

      /**
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field. Must be null-terminated.
       * @param value The value.
       */
      void setField(std::size_t i, std::string_view fieldName, ArrayCref value)
      {
        setField(i, fieldName.data(), value);
      }

      /**
       * @brief Set the field of the structure array at index 0.
       * @param fieldName The name of the field.
       * @param value The value.
       */
      void setField(const char* fieldName, ArrayCref value)
      {
        setField(0, fieldName, value);
      }

      /**
       * @brief Set the field of the structure array at index 0.
       * @param fieldName The name of the field. Must be null-terminated.
       * @param value The value.
       */
      void setField(std::string_view fieldName, ArrayCref value)
      {
        setField(fieldName.data(), value);
      }

      /**
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldIndex The index of the field.
       * @param value The value.
       */
      void setField(std::size_t i, FieldIndex fieldIndex, ArrayCref value)
      {
        checkValid("matlabw::mx::StructArray::setField");

        if (fieldIndex == FieldIndex::invalid || static_cast<std::size_t>(fieldIndex) >= getFieldCount())
        {
          throw Exception("invalid field index");
        }

        mxSetFieldByNumber(get(), i, static_cast<int>(fieldIndex), Array{value}.release());
      }

      /**
       * @brief Set the field of the structure array at index 0.
       * @param fieldIndex The index of the field.
       * @param value The value.
       */
      void setField(FieldIndex fieldIndex, ArrayCref value)
      {
        setField(0, fieldIndex, value);
      }

      /**
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @param value The value.
       */
      void setField(std::size_t i, const char* fieldName, Array&& value)
      {
        setField(i, getFieldIndex(fieldName), std::move(value));
      }

      /**
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @param value The value.
       */
      void setField(std::size_t i, std::string_view fieldName, Array&& value)
      {
        setField(i, fieldName.data(), std::move(value));
      }

      /**
       * @brief Set the field of the structure array at index 0.
       * @param fieldName The name of the field.
       * @param value The value.
       */
      void setField(const char* fieldName, Array&& value)
      {
        setField(0, fieldName, std::move(value));
      }

      /**
       * @brief Set the field of the structure array at index 0.
       * @param fieldName The name of the field. Must be null-terminated.
       * @param value The value.
       */
      void setField(std::string_view fieldName, Array&& value)
      {
        setField(fieldName.data(), std::move(value));
      }

      /**
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldIndex The index of the field.
       * @param value The value.
       */
      void setField(std::size_t i, FieldIndex fieldIndex, Array&& value)
      {
        checkValid("matlabw::mx::StructArray::setField");

        if (fieldIndex == FieldIndex::invalid || static_cast<std::size_t>(fieldIndex) >= getFieldCount())
        {
          throw Exception("invalid field index");
        }

        mxSetFieldByNumber(get(), i, static_cast<int>(fieldIndex), value.release());
      }

      /**
       * @brief Set the field of the structure array at index 0.
       * @param fieldIndex The index of the field.
       * @param value The value.
       */
      void setField(FieldIndex fieldIndex, Array&& value)
      {
        setField(0, fieldIndex, std::move(value));
      }

      /**
       * @brief Gets the number of fields.
       * @return The number of fields.
       */
      [[nodiscard]] std::size_t getFieldCount() const
      {
        checkValid("matlabw::mx::StructArray::getFieldCount");
        return static_cast<std::size_t>(mxGetNumberOfFields(get()));
      }

      /**
       * @brief Gets the field name from the field index.
       * @param fieldIdx The field index.
       * @return The field name.
       */
      [[nodiscard]] const char* getFieldName(FieldIndex fieldIdx) const
      {
        checkValid("matlabw::mx::StructArray::getFieldName");
        
        const char* fieldName = mxGetFieldNameByNumber(get(), static_cast<int>(fieldIdx));

        if (fieldName == nullptr)
        {
          throw Exception("failed to get field name");
        }

        return fieldName;
      }

      /**
       * @brief Gets the field index from the field name.
       * @param fieldName The field name.
       * @return The field index.
       */
      [[nodiscard]] FieldIndex getFieldIndex(const char* fieldName) const
      {
        checkValid("matlabw::mx::StructArray::getFieldIndex");

        int fieldIdx = mxGetFieldNumber(get(), fieldName);

        if (fieldIdx == -1)
        {
          return FieldIndex::invalid;
        }

        return static_cast<FieldIndex>(fieldIdx);
      }

      /**
       * @brief Gets the field index from the field name.
       * @param fieldName The field name.
       * @return The field index.
       */
      [[nodiscard]] FieldIndex getFieldIndex(std::string_view fieldName) const
      {
        return getFieldIndex(fieldName.data());
      }

      /**
       * @brief Adds a field to the structure array.
       * @param fieldName The field name.
       */
      void addField(const char* fieldName)
      {
        checkValid("matlabw::mx::StructArray::addField");

        if (fieldName == nullptr)
        {
          throw Exception("invalid field name");
        }

        if (!mxAddField(get(), fieldName))
        {
          throw Exception("failed to add field");
        }
      }

      /**
       * @brief Adds a field to the structure array.
       * @param fieldName The field name. Must be null-terminated.
       */
      void addField(std::string_view fieldName)
      {
        return addField(fieldName.data());
      }

      /**
       * @brief Removes a field from the structure array.
       * @param fieldName The field name.
       */
      void removeField(const char* fieldName)
      {
        checkValid("matlabw::mx::StructArray::removeField");

        removeField(getFieldIndex(fieldName));
      }

      /**
       * @brief Removes a field from the structure array.
       * @param fieldName The field name. Must be null-terminated.
       */
      void removeField(std::string_view fieldName)
      {
        return removeField(fieldName.data());
      }

      /**
       * @brief Removes a field from the structure array.
       * @param fieldIndex The field index.
       */
      void removeField(FieldIndex fieldIndex)
      {
        checkValid("matlabw::mx::StructArray::removeField");

        if (fieldIndex != FieldIndex::invalid)
        {
          if (static_cast<std::size_t>(fieldIndex) >= getFieldCount())
          {
            throw Exception("field index out of range");
          }

          mxRemoveField(get(), static_cast<int>(fieldIndex));
        }
      }

      /// @brief Use the TypedArray<Struct>::operator ArrayRef
      using TypedArray<Struct>::operator ArrayRef;

      /// @brief Use the TypedArray<Struct>::operator ArrayCref
      using TypedArray<Struct>::operator ArrayCref;

      /// @brief Use the TypedArray<Struct>::operator TypedArrayRef
      using TypedArray<Struct>::operator TypedArrayRef<Struct>;

      /// @brief Use the TypedArray<Struct>::operator TypedArrayCref
      using TypedArray<Struct>::operator TypedArrayCref<Struct>;

      /**
       * @brief Operator StructArrayRef
       * @return The StructArrayRef.
       */
      [[nodiscard]] operator StructArrayRef()
      {
        return StructArrayRef{get()};
      }

      /**
       * @brief Operator StructArrayCref
       * @return The StructArrayCref.
       */
      [[nodiscard]] operator StructArrayCref() const
      {
        return StructArrayCref{get()};
      }
  };

  /**
   * @brief Create a structure array.
   * @param dims The dimensions of the array.
   * @param fieldNames The field names.
   * @return The structure array.
   */
  [[nodiscard]] inline StructArray makeStructArray(View<std::size_t> dims, View<const char*> fieldNames)
  {
    mxArray* array = mxCreateStructArray(dims.size(),
                                         dims.data(),
                                         static_cast<int>(fieldNames.size()),
                                         const_cast<const char**>(fieldNames.data()));

    if (array == nullptr)
    {
      throw Exception("failed to create struct array");
    }

    return StructArray{std::move(array)};
  }

  /**
   * @brief Create a structure array.
   * @param m The number of rows.
   * @param n The number of columns.
   * @param fieldNames The field names.
   * @return The structure array.
   */
  [[nodiscard]] inline StructArray makeStructArray(std::size_t m, std::size_t n, View<const char*> fieldNames)
  {
    return makeStructArray({{m, n}}, fieldNames);
  }
} // namespace matlabw::mx

#endif /* MATLABW_MX_STRUCT_ARRAY_HPP */
