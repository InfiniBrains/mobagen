#include "ColorT.h"
#include <stdexcept>

Color32::Color32(uint32_t packed) {
    this->a = packed >> 24;
    this->r = (packed << 8) >> 24;
    this->g = (packed << 16) >> 24;
    this->b = (packed << 24) >> 24;
}

Color32::Color32(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    this->a = a;
    this->r = r;
    this->g = g;
    this->b = b;
}

Color32 &Color32::operator=(const Colorf &rhs) {
    a = (uint8_t)(rhs.a*255);
    r = (uint8_t)(rhs.r*255);
    g = (uint8_t)(rhs.g*255);
    b = (uint8_t)(rhs.b*255);
    return *this;
}

bool Color32::operator==(const Color32 &rhs) const {
    return a == rhs.a &&
           r == rhs.r &&
           g == rhs.g &&
           b == rhs.b;
}

bool Color32::operator!=(const Color32 &rhs) const {
    return !(rhs == *this);
}

uint8_t &Color32::operator[](const int &i) {
    if (i < 0 || i > 4) throw std::out_of_range("Out of color range\n");
    switch (i) {
        default:
        case 0:
            return a;
        case 1:
            return r;
        case 2:
            return g;
        case 3:
            return b;
    }
}

const uint8_t &Color32::operator[](const int &i) const {
    if (i < 0 || i > 4) throw std::out_of_range("Out of color range\n");
    switch (i) {
        default:
        case 0:
            return a;
        case 1:
            return r;
        case 2:
            return g;
        case 3:
            return b;
    }
}

Colorf::Colorf(uint32_t packed) {
    this->a = ((float)(packed >> 24))/255;
    this->r = ((float)((packed << 8) >> 24))/255;
    this->g = ((float)((packed << 16) >> 24))/255;
    this->b = ((float)((packed << 16) >> 24))/255;
}

Colorf &Colorf::operator=(const Color32 &rhs) {
    a = rhs.a/255.f;
    r = rhs.r/255.f;
    g = rhs.g/255.f;
    b = rhs.b/255.f;
    return *this;
}

Colorf::Colorf(float r, float g, float b, float a = 1) {
    this->a=a;
    this->r=r;
    this->g=g;
    this->b=b;
}

