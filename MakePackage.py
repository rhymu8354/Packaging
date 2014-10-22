#!/usr/bin/env python
#
# This script constructs a ZIP file package of the contents of
# a directory tree.
#
# Adapted from http://stackoverflow.com/questions/296499/how-do-i-zip-the-contents-of-a-folder-using-python-version-2-5
#
# Copyright (c) 2008 by J.F. Sebastian
# Copyright (c) 2013-2014 by Richard Walters
#
from __future__ import with_statement
from contextlib import closing
from zipfile import ZipFile, ZIP_DEFLATED
import os

def ZipDirectory(baseDirectory, archiveName, filesToIgnore):
    assert os.path.isdir(baseDirectory)
    with closing(ZipFile(archiveName, "w", ZIP_DEFLATED)) as z:
        for root, dirs, files in os.walk(baseDirectory):
            # NOTE: ignore empty directories
            for fileName in files:
                if fileName in filesToIgnore:
                    continue
                filePath = os.path.join(root, fileName)
                zipFilePath = filePath[len(baseDirectory)+len(os.sep):] #XXX: relative path
                z.write(filePath, zipFilePath)

if __name__ == "__main__":
    import sys
    baseDirectory = sys.argv[2]
    archiveName = sys.argv[1]
    filesToIgnore = set(
        [
            "Thumbs.db",
        ]
    )
    ZipDirectory(baseDirectory, archiveName, filesToIgnore)
