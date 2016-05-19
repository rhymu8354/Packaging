﻿"""
SConscript

This file is used by SCons to learn what to build for this project, along
with metadata about the interface and dependencies of the project.
"""

import os

# Import the default build environments for all supported build platforms.
Import("platformEnvironments")

# Import other projects in the workspace on which this project depends.
Import("assimp")

# This is the name of the project, used to form the names of build products.
name = "Packaging"

# List directories containing external interfaces here.
interface = [
    Dir("..")
]

# If the project depends on libraries from another project
# in the workspace, list their product trees here.
deps = [
    assimp,
]

# List all supported platforms here.
# For each one, list any platform-specific environment variables.
platforms = {
    "Linux": {
        "LIBS": [
        ],
    },
}

# Build the project for every supported platform.  The platform must be
# listed in this project in the platforms list and must have a
# corresponding platform build environment in order for the project
# to be built for that platform.
products = {}
for platform in platforms:
    if platform not in platformEnvironments:
        continue
    env = platformEnvironments[platform].Clone()
    env.AppendUnique(**platforms[platform])
    products[platform] = env.LibraryProject(
        name,
        platform,
        interface,
        deps
    )
Return("products")
