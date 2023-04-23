#include "../includes/utils.hpp"


bool fileExists(const char* path) {
    return access(path, F_OK) != -1;
}
bool fileRead(const char* path) {
    return access(path, R_OK) != -1;
}

bool is_Directory(const char* path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return false;
    }
    return S_ISDIR(statbuf.st_mode);
}
