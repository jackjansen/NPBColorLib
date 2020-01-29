/*-------------------------------------------------------------------------
TempFColor provides a color object that represents Temp values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#pragma once

#include <Arduino.h>
#include <NeoPixelBus.h>

struct RgbFColor;
struct TempFColor;
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
    Colorspace(float temperatureW, float brightnessW, bool huePriority=false) :
        Temperature(temperatureW), Brightness(brightnessW), HuePriority(huePriority)
    {
    };

    // ------------------------------------------------------------------------
    // Construct a Colorspace that will have its values set in latter operations
    // CAUTION:  The members are not initialized and may not be consistent
    // ------------------------------------------------------------------------
    Colorspace()
    {
    };

    // ------------------------------------------------------------------------
    // TempFColor -> RgbwFColor
    // ------------------------------------------------------------------------
    RgbwFColor toRgbwFColor(TempFColor src);

    // ------------------------------------------------------------------------
    // TempFColor -> RgbwColor
    // ------------------------------------------------------------------------
    RgbwColor toRgbwColor(TempFColor src);

    // ------------------------------------------------------------------------
    // TempFColor -> RgbwFColor
    // ------------------------------------------------------------------------
    RgbFColor toRgbFColor(TempFColor src);

    // ------------------------------------------------------------------------
    // TempFColor -> RgbwColor
    // ------------------------------------------------------------------------
    RgbColor toRgbColor(TempFColor src);

    // ------------------------------------------------------------------------
    // HslFColor -> RgbwFColor
    // ------------------------------------------------------------------------
    RgbwFColor toRgbwFColor(HslFColor src);
    
    // ------------------------------------------------------------------------
    // HslFColor -> RgbwColor
    // ------------------------------------------------------------------------
    RgbwColor toRgbwColor(HslFColor src);

    // ------------------------------------------------------------------------
    // HslFColor -> RgbwFColor
    // ------------------------------------------------------------------------
    RgbFColor toRgbFColor(HslFColor src);
    
    // ------------------------------------------------------------------------
    // HslFColor -> RgbwColor
    // ------------------------------------------------------------------------
    RgbColor toRgbColor(HslFColor src);

    // ------------------------------------------------------------------------
    // RgbFColor -> RgbwFColor
    // ------------------------------------------------------------------------
    RgbwFColor toRgbwFColor(RgbFColor src);
    
    // ------------------------------------------------------------------------
    // RgbFColor -> RgbwColor
    // ------------------------------------------------------------------------
    RgbwColor toRgbwColor(RgbFColor src);

    // ------------------------------------------------------------------------
    // RgbFColor -> RgbwFColor
    // ------------------------------------------------------------------------
    RgbFColor toRgbFColor(RgbFColor src);
    
    // ------------------------------------------------------------------------
    // RgbFColor -> RgbwColor
    // ------------------------------------------------------------------------
    RgbColor toRgbColor(RgbFColor src);



    // ------------------------------------------------------------------------
    // Members
    // ------------------------------------------------------------------------
    float Temperature;
    float Brightness;
    bool HuePriority;
};

