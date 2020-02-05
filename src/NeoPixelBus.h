#pragma once

typedef unsigned char uint8_t;

struct RgbColor {
    RgbColor(uint8_t _R, uint8_t _G, uint8_t _B) : R(_R), G(_G), B(_B) {}
    RgbColor(){}
    uint8_t R, G, B;
};

struct RgbwColor {
    RgbwColor(uint8_t _R, uint8_t _G, uint8_t _B, uint8_t _W) : R(_R), G(_G), B(_B), W(_W) {}
    RgbwColor(){}
    uint8_t R, G, B, W;
};

class NeoGammaEquationMethod {};

template <class T> class NeoGamma {
public:
    RgbColor Correct(RgbColor src) { return src; }
    RgbwColor Correct(RgbwColor src) { return src; }
};

