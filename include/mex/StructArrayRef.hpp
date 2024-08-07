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

#ifndef MEX_STRUCT_ARRAY_REF_HPP
#define MEX_STRUCT_ARRAY_REF_HPP

#include "detail/include.hpp"

#include "Array.hpp"
#include "TypedArrayRef.hpp"
#include "detail/utils.hpp"

namespace mex
{
  /// @brief FieldIndex type.
  enum class FieldIndex : std::size_t {};

  /// @brief StructArrayRef class
  class StructArrayRef : public TypedArrayRef<Struct>
  {
    public:
      /// @brief Inherit constructors from TypedArrayRef<Struct>
      using TypedArrayRef<Struct>::TypedArrayRef;

      /// @brief Default destructor
      ~StructArrayRef() = default;

      /// @brief Use the TypedArrayRef<Struct>::operator=
      using TypedArrayRef<Struct>::operator=;

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayRef> getField(std::size_t i, const char* fieldName)
      {
        const FieldIndex fieldIdx = getFieldIndex(fieldName);

        return getField(i, fieldIdx);
      }

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldIndex The index of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayRef> getField(std::size_t i, FieldIndex fieldIndex)
      {
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
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(std::size_t i, const char* fieldName) const
      {
        const FieldIndex fieldIdx = getFieldIndex(fieldName);

        return getField(i, fieldIdx);
      }

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldIndex The index of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(std::size_t i, FieldIndex fieldIndex) const
      {
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
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @param value The value.
       */
      void setField(std::size_t i, const char* fieldName, ArrayCref value)
      {
        const FieldIndex fieldIdx = getFieldIndex(fieldName);

        setField(i, fieldIdx, value);
      }

      /**
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldIndex The index of the field.
       * @param value The value.
       */
      void setField(std::size_t i, FieldIndex fieldIndex, ArrayCref value)
      {
        if (static_cast<std::size_t>(fieldIndex) >= getFieldCount())
        {
          throw Exception("field index out of range");
        }

        mxArray* valueDup = detail::duplicateArray(value.get(), NonPersistent{});

        mxSetFieldByNumber(get(), i, static_cast<int>(fieldIndex), valueDup);
      }

      /**
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @param value The value.
       */
      void setField(std::size_t i, const char* fieldName, Array&& value)
      {
        const FieldIndex fieldIdx = getFieldIndex(fieldName);

        setField(i, fieldIdx, std::move(value));
      }

      /**
       * @brief Set the field of the structure array.
       * @param i The index of the structure.
       * @param fieldIndex The index of the field.
       * @param value The value.
       */
      void setField(std::size_t i, FieldIndex fieldIndex, Array&& value)
      {
        if (static_cast<std::size_t>(fieldIndex) >= getFieldCount())
        {
          throw Exception("field index out of range");
        }

        mxSetFieldByNumber(get(), i, static_cast<int>(fieldIndex), value.release());
      }

      /**
       * @brief Gets the number of fields.
       * @return The number of fields.
       */
      [[nodiscard]] std::size_t getFieldCount() const
      {
        return mxGetNumberOfFields(get());
      }

      /**
       * @brief Gets the field name from the field index.
       * @param fieldIdx The field index.
       * @return The field name.
       */
      [[nodiscard]] const char* getFieldName(FieldIndex fieldIdx) const
      {        
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
        int fieldIdx = mxGetFieldNumber(get(), fieldName);

        if (fieldIdx == -1)
        {
          throw Exception("failed to get field index");
        }

        return static_cast<FieldIndex>(fieldIdx);
      }

      /**
       * @brief Adds a field to the structure array.
       * @param fieldName The field name.
       */
      void addField(const char* fieldName)
      {
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
       * @brief Removes a field from the structure array.
       * @param fieldName The field name.
       */
      void removeField(const char* fieldName)
      {
        if (fieldName == nullptr)
        {
          throw Exception("invalid field name");
        }

        removeField(getFieldIndex(fieldName));
      }

      /**
       * @brief Removes a field from the structure array.
       * @param fieldIndex The field index.
       */
      void removeField(FieldIndex fieldIndex)
      {
        if (static_cast<std::size_t>(fieldIndex) >= getFieldCount())
        {
          throw Exception("field index out of range");
        }

        mxRemoveField(get(), static_cast<int>(fieldIndex));
      }
  };

  /// @brief StructArrayCref class
  class StructArrayCref : public TypedArrayCref<Struct>
  {
    public:
      /// @brief Inherit constructors from TypedArrayCref<Struct>
      using TypedArrayCref<Struct>::TypedArrayCref;

      /// @brief Default destructor
      ~StructArrayCref() = default;

      /// @brief Use the TypedArrayCref<Struct>::operator=
      using TypedArrayCref<Struct>::operator=;

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldName The name of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(std::size_t i, const char* fieldName) const
      {
        const FieldIndex fieldIdx = getFieldIndex(fieldName);

        return getField(i, fieldIdx);
      }

      /**
       * @brief Get the field of the structure array.
       * @param i The index of the structure.
       * @param fieldIndex The index of the field.
       * @return The field.
       */
      [[nodiscard]] std::optional<ArrayCref> getField(std::size_t i, FieldIndex fieldIndex) const
      {
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
       * @brief Gets the number of fields.
       * @return The number of fields.
       */
      [[nodiscard]] std::size_t getFieldCount() const
      {
        return mxGetNumberOfFields(get());
      }

      /**
       * @brief Gets the field name from the field index.
       * @param fieldIdx The field index.
       * @return The field name.
       */
      [[nodiscard]] const char* getFieldName(FieldIndex fieldIdx) const
      {        
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
        int fieldIdx = mxGetFieldNumber(get(), fieldName);

        if (fieldIdx == -1)
        {
          throw Exception("failed to get field index");
        }

        return static_cast<FieldIndex>(fieldIdx);
      }
  };
} // namespace mex

#endif /* MEX_STRUCT_ARRAY_REF_HPP */
