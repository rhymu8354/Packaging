# Packaging

This is a library containing tools useful for constructing and reading ZIP
files used to package up directories and files for archival or transmission.

## Usage

The `Packaging::ZipFile` class uses the `minizip` library from `zlib` to manage
a single ZIP file and provides methods for retrieving the contents of any file
contained within it.

The `MakePackage.py` Python script can be used to construct a ZIP file from
a directory of files, optionally merging in a pre-existing ZIP file.

## Supported platforms / recommended toolchains

This contains a Python script along with a portable C++11 library which depends
only on the C++11 compiler, the C and C++ standard libraries, and other C++11
libraries with similar dependencies, so it should be supported on almost any
platform.  The following are recommended toolchains for popular platforms.

* Windows -- [Visual Studio](https://www.visualstudio.com/) (Microsoft Visual C++)
* Linux -- clang or gcc
* MacOS -- Xcode (clang)

## Building

The C++ library is not intended to stand alone.  It is intended to be included
in a larger solution which uses [CMake](https://cmake.org/) to generate the
build system and build applications which will link with the library.

There are two distinct steps in the build process:

1. Generation of the build system, using CMake
2. Compiling, linking, etc., using CMake-compatible toolchain

### Prerequisites

* [CMake](https://cmake.org/) version 3.8 or newer
* C++11 toolchain compatible with CMake for your development platform (e.g. [Visual Studio](https://www.visualstudio.com/) on Windows)
* [minizip](https://github.com/rhymu8354/zlib/tree/master/contrib/minizip) -
  part of [zlib](https://github.com/rhymu8354/zlib), a popular compression
  library; `minizip` provides a wrapper for using `zlib` to read ZIP files
* [SystemAbstractions](https://github.com/rhymu8354/SystemAbstractions.git) - a
  cross-platform adapter library for system services whose APIs vary from one
  operating system to another

### Build system generation

Generate the build system using [CMake](https://cmake.org/) from the solution
root.  For example:

```bash
mkdir build
cd build
cmake -G "Visual Studio 15 2017" -A "x64" ..
```

### Compiling, linking, et cetera

Either use [CMake](https://cmake.org/) or your toolchain's IDE to build.
For [CMake](https://cmake.org/):

```bash
cd build
cmake --build . --config Release
```
