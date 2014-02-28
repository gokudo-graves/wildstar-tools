#ifndef WILDSTAR_DATA_EXCEPTION_H
#define WILDSTAR_DATA_EXCEPTION_H

#include <exception>

#include "global.h"

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        class WILDSTAR_DATA_SHARED EInvalidFile : public std::exception
        {
        public:
            EInvalidFile() {}
            virtual ~EInvalidFile() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file.";
            }
        };

        //----------------------------------------------------------------------
        class WILDSTAR_DATA_SHARED EInvalidFileNotExist : public EInvalidFile
        {
        public:
            EInvalidFileNotExist() {}
            virtual ~EInvalidFileNotExist() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file, file does not exist.";
            }
        };

        //----------------------------------------------------------------------
        class WILDSTAR_DATA_SHARED EInvalidFileSize : public EInvalidFile
        {
        public:
            EInvalidFileSize() {}
            virtual ~EInvalidFileSize() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file format, file size to small.";
            }
        };

        //----------------------------------------------------------------------
        class WILDSTAR_DATA_SHARED EInvalidFileNotReadable : public EInvalidFile
        {
        public:
            EInvalidFileNotReadable() {}
            virtual ~EInvalidFileNotReadable() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file, file not readable.";
            }
        };

        //----------------------------------------------------------------------
        class WILDSTAR_DATA_SHARED EInvalidFileSignature : public EInvalidFile
        {
        public:
            EInvalidFileSignature() {}
            virtual ~EInvalidFileSignature() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file signature.";
            }
        };

        //----------------------------------------------------------------------
        class WILDSTAR_DATA_SHARED EInvalidFileVersion : public EInvalidFile
        {
        public:
            EInvalidFileVersion() {}
            virtual ~EInvalidFileVersion() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file version.";
            }
        };

        //----------------------------------------------------------------------
        class WILDSTAR_DATA_SHARED EInvalidFileHeader : public EInvalidFile
        {
        public:
            EInvalidFileHeader() {}
            virtual ~EInvalidFileHeader() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file header.";
            }
        };

        //----------------------------------------------------------------------
    }
}
#endif // WILDSTAR_DATA_EXCEPTION_H
