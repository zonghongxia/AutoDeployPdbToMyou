#ifndef _RENAME_H
#define _RENAME_H

#include <stdio.h>
#include <iostream>

const int _TMP_LENGTH = 128;

static const char* SUFFIX_RENAME = ".zip";

void Rename(char *oldname, char *newname);

void GetUnzipFolderPath(char *path);

void GetZipFolderPath(char *path, const char *changefoldername);//D://zipfile/sym      symbols

void GetZipPath(char *path);


#endif
