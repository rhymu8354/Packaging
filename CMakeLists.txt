# CMakeLists.txt for Packaging
#
# © 2018 by Richard Walters

cmake_minimum_required(VERSION 3.8)
set(This Packaging)

set(Headers
    include/Packaging/ZipFile.hpp
)

set(Sources
    src/ZipFile.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)

target_include_directories(${This} PUBLIC include)

target_link_libraries(${This} PUBLIC
    minizip
    SystemAbstractions
)

set(PACKAGING_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/MakePackage.py PARENT_SCOPE)
