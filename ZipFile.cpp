/**
 * @file ZipFile.cpp
 *
 * This module contains the implementation of the Packaging::ZipFile class.
 *
 * Copyright (c) 2013-2014 by Richard Walters
 */

#include "ZipFile.h"

#include <algorithm>
#include <stdint.h>
#include <unzip.h>
#include <vector>

namespace Packaging {

    ZipFile::ZipFile()
        : _zipFile(NULL)
    {
    }

    ZipFile::~ZipFile() {
        Close();
    }

    bool ZipFile::Open(const std::string& zipFileName) {
        Close();
        _zipFile = unzOpen(zipFileName.c_str());
        return (_zipFile != NULL);
    }

    void ZipFile::Close() {
        if (_zipFile != NULL) {
            (void)unzClose(_zipFile);
            _zipFile = NULL;
        }
    }

    uint64_t ZipFile::Size(const std::string& fileName) {
        if (_zipFile == NULL) {
            return 0;
        }
        int result = unzLocateFile(_zipFile, fileName.c_str(), 0);
        if (result != UNZ_OK) {
            return 0;
        }
        unz_file_info fileInfo;
        result = unzGetCurrentFileInfo(_zipFile, &fileInfo, NULL, 0, NULL, 0, NULL, 0);
        if (result != UNZ_OK) {
            return 0;
        }
        return (uint64_t)fileInfo.uncompressed_size;
    }

    bool ZipFile::Read(const std::string& fileName, std::vector< uint8_t >& fileContents) {
        fileContents.clear();
        if (_zipFile == NULL) {
            return false;
        }
        int result = unzLocateFile(_zipFile, fileName.c_str(), 0);
        if (result != UNZ_OK) {
            return false;
        }
        unz_file_info fileInfo;
        result = unzGetCurrentFileInfo(_zipFile, &fileInfo, NULL, 0, NULL, 0, NULL, 0);
        if (result != UNZ_OK) {
            return false;
        }
        if (fileInfo.uncompressed_size > 0) {
            result = unzOpenCurrentFile(_zipFile);
            if (result != UNZ_OK) {
                return false;
            }
            fileContents.resize(fileInfo.uncompressed_size);
            int bytesRead = unzReadCurrentFile(_zipFile, &fileContents[0], (int)fileContents.size());
            (void)unzCloseCurrentFile(_zipFile);
            if (bytesRead != (int)fileContents.size()) {
                return false;
            }
        }
        return true;
    }

    bool ZipFile::Read(const std::string& fileName, void* fileContents, size_t maxFileContents) {
        if (_zipFile == NULL) {
            return false;
        }
        int result = unzLocateFile(_zipFile, fileName.c_str(), 0);
        if (result != UNZ_OK) {
            return false;
        }
        unz_file_info fileInfo;
        result = unzGetCurrentFileInfo(_zipFile, &fileInfo, NULL, 0, NULL, 0, NULL, 0);
        if (result != UNZ_OK) {
            return false;
        }
        const size_t bytesToRead(std::min(maxFileContents, (size_t)fileInfo.uncompressed_size));
        if (bytesToRead > 0) {
            result = unzOpenCurrentFile(_zipFile);
            if (result != UNZ_OK) {
                return false;
            }
            result = unzReadCurrentFile(_zipFile, fileContents, (unsigned int)bytesToRead);
            (void)unzCloseCurrentFile(_zipFile);
            if (result != UNZ_OK) {
                return false;
            }
        }
        return true;
    }

}
