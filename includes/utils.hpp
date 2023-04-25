#ifndef UTILS_HPP
#define UTILS_HPP
#include "webserv.hpp"

template < class T >
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
        if (it == v.begin())
            os << *it;
        else
            os << ", " << *it;
    }
    return os;
}

bool fileExists(const char* path);
bool fileRead(const char* path);
bool isDirectory(const char* path);

#endif
