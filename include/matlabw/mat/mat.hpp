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

#ifndef MATLABW_MAT_MAT_HPP
#define MATLABW_MAT_MAT_HPP

#include <mat.h>

#include <matlabw/mx/mx.hpp>

namespace matlabw::mat
{
  /// @brief File open mode.
  enum class Mode
  {
    r,    ///< Read only.
    u,    ///< Update, read and write.
    w,    ///< Write only. Deletes existing contents.
    w4,   ///< Write only. Deletes existing contents. Compatible with MATLAB 4 and earlier.
    w6,   ///< Write only. Deletes existing contents. Compatible with MATLAB 5 and earlier. Same as wL.
    wL,   ///< Write only. Deletes existing contents. Compatible with MATLAB 6 and 6.5. Same as w6.
    w7,   ///< Write only. Deletes existing contents. Compatible with MATLAB 7 and earlier. Same as wz.
    wz,   ///< Write only with compression. Deletes existing contents. Compatible with MATLAB 7 and earlier. Same as w7.
    w7_3, ///< Write only. Deletes existing contents. Uses HDF5 format for large data.
  };

  /// @brief File class. Wraps MATFile.
  class File
  {
    public:
      /// @brief Default constructor.
      File() = default;

      /**
       * @brief Constructor.
       * @param filename The filename.
       * @param mode The mode.
       */
      File(const char* filename, Mode mode)
      {
        open(filename, mode);
      }

      /**
       * @brief Constructor.
       * @param filename The filename. Must be null-terminated.
       * @param mode The mode.
       */
      File(std::string_view filename, Mode mode)
      {
        open(filename, mode);
      }

      /// @brief Copy constructor is deleted.
      File(const File&) = delete;

      /// @brief Move constructor.
      File(File&&) = default;

      /// @brief Destructor.
      ~File()
      {
        close();
      }

      /// @brief Copy assignment operator is deleted.
      File& operator=(const File&) = delete;

      /// @brief Move assignment operator.
      File& operator=(File&&) = default;

      /**
       * @brief Open a file.
       * @param filename The filename.
       * @param mode The mode.
       */
      void open(const char* filename, Mode mode)
      {
        static constexpr char id[]{"matlabw:mat:File:open"};

        auto getModeStr = [](Mode mode)
        {
          switch (mode)
          {
          case Mode::r:
            return "r";
          case Mode::u:
            return "u";
          case Mode::w:
            return "w";
          case Mode::w4:
            return "w4";
          case Mode::w6:
            return "w6";
          case Mode::w7:
            return "w7";
          case Mode::wL:
            return "wL";
          case Mode::wz:
            return "wz";
          case Mode::w7_3:
            return "w7.3";
          default:
            throw mx::Exception{id, "invalid mode"};
          }
        };

        if (mFile != nullptr)
        {
          close();
        }

        mFile = matOpen(filename, getModeStr(mode));

        if (mFile == nullptr)
        {
          throw mx::Exception{id, "failed to open MAT file"};
        }
      }

      /**
       * @brief Open a file.
       * @param filename The filename. Must be null-terminated.
       * @param mode The mode.
       */
      void open(std::string_view filename, Mode mode)
      {
        open(filename.data(), mode);
      }

      /**
       * @brief Check if the file is open.
       * @return True if the file is open, false otherwise.
       */
      [[nodiscard]] bool isOpen() const
      {
        return mFile != nullptr;
      }

      /// @brief Close the file.
      void close()
      {
        static constexpr char id[]{"matlabw:mat:File:close"};

        if (mFile != nullptr)
        {
          checkError(matClose(std::exchange(mFile, nullptr)), id);
        }
      }

      /**
       * @brief Get the file pointer.
       * @return The file pointer.
       */
      [[nodiscard]] FILE* getFilePointer()
      {
        static constexpr char id[]{"matlabw:mat:File:getFilePointer"};

        if (isOpen())
        {
          throw mx::Exception{id, "file is not open"};
        }

        FILE* fp = matGetFp(mFile);

        if (fp == nullptr)
        {
          throw mx::Exception{id, "failed to get file pointer"};
        }

        return fp;
      }

      /**
       * @brief Write a variable to the file.
       * @param name The name of the variable.
       * @param array The array.
       */
      void putVariable(const char* name, mx::ArrayCref array)
      {
        static constexpr char id[]{"matlabw:mat:File:putVariable"};

        if (!isOpen())
        {
          throw mx::Exception{id, "file is not open"};
        }

        if (name == nullptr)
        {
          throw mx::Exception{id, "invalid name"};
        }

        checkError(matPutVariable(mFile, name, array.get()), id);
      }

      /**
       * @brief Write a variable to the file.
       * @param name The name of the variable. Must be null-terminated.
       * @param array The array.
       */
      void putVariable(std::string_view name, mx::ArrayCref array)
      {
        putVariable(name.data(), array);
      }

      /**
       * @brief Write a variable to the file as global.
       * @param name The name of the variable.
       * @param array The array.
       */
      void putVariableAsGlobal(const char* name, mx::ArrayCref array)
      {
        static constexpr char id[]{"matlabw:mat:File:putVariableAsGlobal"};

        if (!isOpen())
        {
          throw mx::Exception{id, "file is not open"};
        }

        if (name == nullptr)
        {
          throw mx::Exception{id, "invalid name"};
        }

        checkError(matPutVariableAsGlobal(mFile, name, array.get()), id);
      }

      /**
       * @brief Write a variable to the file as global.
       * @param name The name of the variable. Must be null-terminated.
       * @param array The array.
       */
      void putVariableAsGlobal(std::string_view name, mx::ArrayCref array)
      {
        putVariableAsGlobal(name.data(), array);
      }

      /**
       * @brief Read a variable from the file.
       * @param name The name of the variable.
       * @return The array.
       */
      [[nodiscard]] mx::Array getVariable(const char* name) const
      {
        static constexpr char id[]{"matlabw:mat:File:getVariable"};

        if (!isOpen())
        {
          throw mx::Exception{id, "file is not open"};
        }

        if (name == nullptr)
        {
          throw mx::Exception{id, "invalid name"};
        }

        mx::Array array{matGetVariable(const_cast<MATFile*>(mFile), name)};

        if (!array.isValid())
        {
          throw mx::Exception{id, "failed to get variable"};
        }

        return array;
      }

      /**
       * @brief Read a variable from the file.
       * @param name The name of the variable. Must be null-terminated.
       * @return The array.
       */
      [[nodiscard]] mx::Array getVariable(std::string_view name) const
      {
        return getVariable(name.data());
      }

      // /**
      //  * @brief Get the next variable in the file.
      //  * @return The array and the name of the variable.
      //  */
      // [[nodiscard]] std::tuple<mx::Array, const char*> getNextVariable() const
      // {
      //   static constexpr char id[]{"matlabw:mat:File:getNextVariable"};

      //   if (!isOpen())
      //   {
      //     throw mx::Exception{id, "file is not open"};
      //   }

      //   std::tuple<mx::Array, const char*> result{};

      //   std::get<0>(result) = mx::Array{matGetNextVariable(const_cast<MATFile*>(mFile), &std::get<1>(result))};

      //   if (!std::get<0>(result).isValid())
      //   {
      //     throw mx::Exception{id, "failed to get next variable"};
      //   }

      //   return result;
      // }

      // /**
      //  * @brief Gets the next variable info in the file.
      //  * @return The array and the name of the variable.
      //  */
      // [[nodiscard]] std::tuple<mx::Array, const char*> getNextVariableInfo() const
      // {
      //   static constexpr char id[]{"matlabw:mat:File:getNextVariableInfo"};

      //   if (!isOpen())
      //   {
      //     throw mx::Exception{id, "file is not open"};
      //   }

      //   std::tuple<mx::Array, const char*> result{};

      //   std::get<0>(result) = mx::Array{matGetNextVariableInfo(const_cast<MATFile*>(mFile), &std::get<1>(result))};

      //   if (!std::get<0>(result).isValid())
      //   {
      //     throw mx::Exception{id, "failed to get next variable info"};
      //   }

      //   return result;
      // }

      /**
       * @brief Gets the variable info in the file.
       * @param name The name of the variable.
       * @return The array and the name of the variable.
       */
      [[nodiscard]] mx::Array getVariableInfo(const char* name) const
      {
        static constexpr char id[]{"matlabw:mat:File:getVariableInfo"};

        if (!isOpen())
        {
          throw mx::Exception{id, "file is not open"};
        }

        if (name == nullptr)
        {
          throw mx::Exception{id, "invalid name"};
        }

        mx::Array array{matGetVariableInfo(const_cast<MATFile*>(mFile), name)};

        if (!array.isValid())
        {
          throw mx::Exception{id, "failed to get variable info"};
        }

        return array;
      }

      /**
       * @brief Gets the variable info in the file.
       * @param name The name of the variable. Must be null-terminated.
       * @return The array and the name of the variable.
       */
      [[nodiscard]] mx::Array getVariableInfo(std::string_view name) const
      {
        return getVariableInfo(name.data());
      }

      /**
       * @brief Removes a variable from the file.
       * @param name The name of the variable.
       */
      void removeVariable(const char* name)
      {
        static constexpr char id[]{"matlabw:mat:File:removeVariable"};

        if (!isOpen())
        {
          throw mx::Exception{id, "file is not open"};
        }

        if (name == nullptr)
        {
          throw mx::Exception{id, "invalid name"};
        }

        checkError(matDeleteVariable(mFile, name), id);
      }

      /**
       * @brief Removes a variable from the file.
       * @param name The name of the variable. Must be null-terminated.
       */
      void removeVariable(std::string_view name)
      {
        removeVariable(name.data());
      }

      /**
       * @brief Get the file contents.
       * @return Pair of variable names array and the number of variables.
       */
      [[nodiscard]] std::tuple<std::unique_ptr<const char*[], mx::Deleter>, std::size_t> getVariableNames() const
      {
        static constexpr char id[]{"matlabw:mat:File:getVariableNames"};

        if (!isOpen())
        {
          throw mx::Exception{id, "file is not open"};
        }

        int num{};

        char** names = matGetDir(mFile, &num);

        if (names == nullptr)
        {
          throw mx::Exception{id, "failed to get directory"};
        }

        return {std::unique_ptr<const char*[], mx::Deleter>{names}, static_cast<std::size_t>(num)};
      }

      /**
       * @brief Get the underlying MATFile pointer.
       * @return The underlying MATFile pointer.
       */
      [[nodiscard]] const MATFile* get() const
      {
        return mFile;
      }

      /**
       * @brief Get the underlying MATFile pointer.
       * @return The underlying MATFile pointer.
       */
      [[nodiscard]] MATFile* get()
      {
        return mFile;
      }
    private:
      /**
       * @brief Check the error.
       * @param err The error.
       * @param id The message identifier.
       */
      static void checkError(matError err, const char* id)
      {
        // Import the error enum.
        enum
        {
          mat_NO_ERROR = 0,
          mat_UNKNOWN_ERROR,
          mat_GENERIC_READ_ERROR,
          mat_GENERIC_WRITE_ERROR,
          mat_INDEX_TOO_BIG,
          mat_FILE_FORMAT_VIOLATION,
          mat_FAIL_TO_IDENTIFY,
          mat_BAD_ARGUMENT,
          mat_OUTPUT_BAD_DATA,
          mat_FULL_OBJECT_OUTPUT_CONVERT,
          mat_PART_OBJECT_OUTPUT_CONVERT,
          mat_FULL_OBJECT_INPUT_CONVERT,
          mat_PART_OBJECT_INPUT_CONVERT,
          mat_OPERATION_NOT_SUPPORTED,
          mat_OUT_OF_MEMORY,
          mat_BAD_VARIABLE_NAME,
          mat_OPERATION_PROHIBITED_IN_WRITE_MODE,
          mat_OPERATION_PROHIBITED_IN_READ_MODE,
          mat_WRITE_VARIABLE_DOES_NOT_EXIST,
          mat_READ_VARIABLE_DOES_NOT_EXIST,
          mat_FILESYSTEM_COULD_NOT_OPEN,
          mat_FILESYSTEM_COULD_NOT_OPEN_TEMPORARY,
          mat_FILESYSTEM_COULD_NOT_REOPEN,
          mat_BAD_OPEN_MODE,
          mat_FILESYSTEM_ERROR_ON_CLOSE,
        };

        switch (err)
        {
        case mat_NO_ERROR:
          return;
        case mat_GENERIC_READ_ERROR:
          throw mx::Exception{id, "generic read error"};
        case mat_GENERIC_WRITE_ERROR:
          throw mx::Exception{id, "generic write error"};
        case mat_INDEX_TOO_BIG:
          throw mx::Exception{id, "index too big"};
        case mat_FILE_FORMAT_VIOLATION:
          throw mx::Exception{id, "file format violation"};
        case mat_FAIL_TO_IDENTIFY:
          throw mx::Exception{id, "fail to identify"};
        case mat_BAD_ARGUMENT:
          throw mx::Exception{id, "bad argument"};
        case mat_OUTPUT_BAD_DATA:
          throw mx::Exception{id, "output bad data"};
        case mat_FULL_OBJECT_OUTPUT_CONVERT:
          throw mx::Exception{id, "full object output convert"};
        case mat_PART_OBJECT_OUTPUT_CONVERT:
          throw mx::Exception{id, "part object output convert"};
        case mat_FULL_OBJECT_INPUT_CONVERT:
          throw mx::Exception{id, "full object input convert"};
        case mat_PART_OBJECT_INPUT_CONVERT:
          throw mx::Exception{id, "part object input convert"};
        case mat_OPERATION_NOT_SUPPORTED:
          throw mx::Exception{id, "operation not supported"};
        case mat_OUT_OF_MEMORY:
          throw mx::Exception{id, "out of memory"};
        case mat_BAD_VARIABLE_NAME:
          throw mx::Exception{id, "bad variable name"};
        case mat_OPERATION_PROHIBITED_IN_WRITE_MODE:
          throw mx::Exception{id, "operation prohibited in write mode"};
        case mat_OPERATION_PROHIBITED_IN_READ_MODE:
          throw mx::Exception{id, "operation prohibited in read mode"};
        case mat_WRITE_VARIABLE_DOES_NOT_EXIST:
          throw mx::Exception{id, "write variable does not exist"};
        case mat_READ_VARIABLE_DOES_NOT_EXIST:
          throw mx::Exception{id, "read variable does not exist"};
        case mat_FILESYSTEM_COULD_NOT_OPEN:
          throw mx::Exception{id, "filesystem could not open"};
        case mat_FILESYSTEM_COULD_NOT_OPEN_TEMPORARY:
          throw mx::Exception{id, "filesystem could not open temporary"};
        case mat_FILESYSTEM_COULD_NOT_REOPEN:
          throw mx::Exception{id, "filesystem could not reopen"};
        case mat_BAD_OPEN_MODE:
          throw mx::Exception{id, "bad open mode"};
        case mat_FILESYSTEM_ERROR_ON_CLOSE:
          throw mx::Exception{id, "filesystem error on close"};
        case mat_UNKNOWN_ERROR:
        default:
          throw mx::Exception{id, "unknown error"};
        }
      }

      MATFile* mFile{};
  };
} // namespace matlabw::mat

#endif /* MATLABW_MAT_MAT_HPP */
