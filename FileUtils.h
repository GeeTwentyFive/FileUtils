/*
Copyright (c) 2025 Amar Alic

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H

#include <sys/stat.h>

#ifdef _WIN32
#include <Windows.h>
#endif



typedef enum {
        FileUtils__SUCCESS,
        FileUtils__ERROR_FAILED
} FileUtils__Error;



int FileUtils__DirectoryExists(char* path) {
        struct stat st;
        if (stat(path, &st) != 0) return 0;
        if (!(st.st_mode & S_IFDIR)) return 0;
        return 1;
}



int FileUtils__FileExists(char* path) {
        struct stat st;
        if (stat(path, &st) != 0) return 0;
        if (!(st.st_mode & S_IFMT)) return 0;
        return 1;
}



FileUtils__Error FileUtils__CreateDirectory(char* path) {
        #ifdef _WIN32
        if (!CreateDirectoryA(path, NULL)) return FileUtils__ERROR_FAILED;
        #else
        if (mkdir(path, 0777)) return FileUtils__ERROR_FAILED;
        #endif
        return FileUtils__SUCCESS;
}



#endif // _FILE_UTILS_H