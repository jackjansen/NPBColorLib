/*-------------------------------------------------------------------------
TempFColor provides a color object that represents Temp values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#pragma once

#include <Arduino.h>
#include <NeoPixelBus.h>

#include "TempFColor.h"
#include "RgbFColor.h"

struct RgbFColor;
struct HslFColor;
struct RgbwFColor;
struct RgbColor;
struct RgbwColor;

// ------------------------------------------------------------------------
// Colorspace represents a specific type of RGBW pixels and their use. 
// In the constructor you specify the temperature and relative intensity
// of the white LED, and whether to give priority to hue correctness or
// brightness correctness. If temperature or intensity is 0 the W channel
// will not be used.
// Colorspace objects contain converter methods that convert any color
// type to RGBW values.
// For sake of API completeness colors can also be converted to RGB values,
// in which case the constructur arguments are ignored.
// ------------------------------------------------------------------------
struct Colorspace
{
    // ------------------------------------------------------------------------
    // Construct a Colorspace using Temperature (Kelvin), Brightness (0-1) and usage
    // ------------------------------------------------------------------------
    Colorspace(float temperatureW=6500, float brightnessW=0, bool huePriority=true, bool gamma=true);

    // ------------------------------------------------------------------------
    // Converters between all reasonable colorspaces
    // ------------------------------------------------------------------------
    void Convert(const RgbFColor& from, RgbColor& to);
    void Convert(const RgbFColor& from, RgbwColor& to);
    void Convert(const TempFColor& from, RgbColor& to);
    void Convert(const TempFColor& from, RgbwColor& to);
    void Convert(const HslFColor& from, RgbColor& to);
    void Convert(const HslFColor& from, RgbwColor& to);
    RgbColor toRgb(RgbFColor from);
    RgbwColor toRgbw(RgbFColor from);
    RgbColor toRgb(TempFColor from);
    RgbwColor toRgbw(TempFColor from);
    RgbColor toRgb(HslFColor from);
    RgbwColor toRgbw(HslFColor from);

    // ------------------------------------------------------------------------
    // Members
    // ------------------------------------------------------------------------
    float WTemperature;
    float WBrightness;
protected:
    void _extractWhiteChannel(RgbwFColor& color);
    bool huePriority;
    RgbFColor whiteColor;
    bool gammaConvert;
};

