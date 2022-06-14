#ifndef BASETYPES_H
#define BASETYPES_H

#include <map>
#include <string>

typedef std::map<std::string, std::string> ioif_attr;

struct color_t {
    unsigned char r=0, g=0, b=0, v=0;
    color_t() {}
    color_t(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
    color_t(unsigned char v) : v(v) {}
};

#endif // BASETYPES_H
