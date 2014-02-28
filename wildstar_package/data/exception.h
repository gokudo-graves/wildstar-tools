#ifndef WILDSTAR_DATA_EXCEPTION_H
#define WILDSTAR_DATA_EXCEPTION_H

#include <exception>

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        class EInvalidFile : public std::exception
        {
        public:
            EInvalidFile() {}
            virtual ~EInvalidFile() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file.";
            }
        };

        //----------------------------------------------------------------------
        class EInvalidFileNotExist : public EInvalidFile
        {
        public:
            EInvalidFileNotExist() {}
            virtual ~EInvalidFileNotExist() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file, file does not exist.";
            }
        };

        //----------------------------------------------------------------------
        class EInvalidFileSize : public EInvalidFile
        {
        public:
            EInvalidFileSize() {}
            virtual ~EInvalidFileSize() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file format, file size to small.";
            }
        };

        //----------------------------------------------------------------------
        class EInvalidFileNotReadable : public EInvalidFile
        {
        public:
            EInvalidFileNotReadable() {}
            virtual ~EInvalidFileNotReadable() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file, file not readable.";
            }
        };

        //----------------------------------------------------------------------
        class EInvalidFileSignature : public EInvalidFile
        {
        public:
            EInvalidFileSignature() {}
            virtual ~EInvalidFileSignature() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file signature.";
            }
        };

        //----------------------------------------------------------------------
        class EInvalidFileVersion : public EInvalidFile
        {
        public:
            EInvalidFileVersion() {}
            virtual ~EInvalidFileVersion() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file version.";
            }
        };

        //----------------------------------------------------------------------
        class EInvalidFileHeader : public EInvalidFile
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
