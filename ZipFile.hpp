#ifndef PACKAGING_ZIP_FILE_HPP
#define PACKAGING_ZIP_FILE_HPP

/**
 * @file ZipFile.hpp
 *
 * This module declares the Packaging::ZipFile class.
 *
 * Copyright (c) 2013-2016 by Richard Walters
 */

#include <Files/IFileCollection.hpp>
#include <mutex>
#include <stdint.h>
#include <string>
#include <unzip.h>
#include <vector>

namespace Packaging {

    /**
     * This class manages a single ZIP file and provides methods for
     * retrieving the contents of any file contained within it.
     */
    class ZipFile : public Files::IFileCollection {
        // Public Methods
    public:
        /**
         * This is the object destructor.
         */
        ~ZipFile();

        /**
         * This method opens the given ZIP file and prepares to deliver
         * file contents from it.
         *
         * @param[in] zipFileName
         *     This is the name of the ZIP file to open.
         *
         * @return
         *     An indication of whether or not the file was opened
         *     successfully is returned.
         *
         * @note
         *     Any ZIP file previously opened with this object is closed.
         */
        bool Open(const std::string& zipFileName);

        /**
         * This method closes the ZIP file currently open, if any.
         */
        void Close();

        // Files::IFileCollection
    public:
        virtual uint64_t Size(const std::string& fileName) override;
        virtual bool Read(const std::string& fileName, std::vector< uint8_t >& fileContents) override;
        virtual bool Read(const std::string& fileName, void* fileContents, size_t maxFileContents) override;
        virtual void ListDirectory(const std::string& directory, std::vector< std::string >& list) override;

        // Private Properties
    private:
        /**
         * This is the handle of the currently open ZIP file.
         */
        unzFile _zipFile = nullptr;

        /**
         * This is used to make sure all accesses to the ZIP file
         * are made thread-safe.
         */
        std::mutex _zipFileLock;
    };

}

#endif /* PACKAGING_ZIP_FILE_HPP */
