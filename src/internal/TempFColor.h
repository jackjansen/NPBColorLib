/*-------------------------------------------------------------------------
TempFColor provides a color object that represents Temp values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#pragma once

#include <Arduino.h>
#include <NeoPixelBus.h>

struct RgbFColor;

// ------------------------------------------------------------------------
// TempFColor represents a color object that is represented by Red, Green, Blue
// component values.  It contains helpful color routines to manipulate the 
// color.
// ------------------------------------------------------------------------
struct TempFColor
{
    // ------------------------------------------------------------------------
    // Construct a TempFColor using Temperature (Kelvin) and Brightness (0-1)
    // ------------------------------------------------------------------------
    TempFColor(float temp, float brightness) :
        Temperature(temp), Brightness(brightness)
    {
    };

    // ------------------------------------------------------------------------
    // Construct a TempFColor that will have its values set in latter operations
    // CAUTION:  The R,G,B members are not initialized and may not be consistent
    // ------------------------------------------------------------------------
    TempFColor()
    {
    };

    // ------------------------------------------------------------------------
    // Cast TempFColor to RgbFColor
    // ------------------------------------------------------------------------
    operator RgbFColor() const;

    // ------------------------------------------------------------------------
    // Comparison operators
    // ------------------------------------------------------------------------
    bool operator==(const TempFColor& other) const
    {
        return (Temperature == other.Temperature && Brightness == other.Brightness);
    };

    bool operator!=(const TempFColor& other) const
    {
        return !(*this == other);
    };

    // ------------------------------------------------------------------------
    // CalculateBrightness will return the overall brightness
    // ------------------------------------------------------------------------
    float CalculateBrightness() const { return Brightness; }

    // ------------------------------------------------------------------------
    // Dim will return a new color that is blended to black with the given ratio
    // ratio - (0-255) where 255 will return the original color and 0 will return black
    // 
    // NOTE: This is a simple linear blend
    // ------------------------------------------------------------------------
    TempFColor Dim(float ratio) const;

    // ------------------------------------------------------------------------
    // Darken will adjust the color by the given delta toward black
    // NOTE: This is a simple linear change
    // delta - (0-255) the amount to dim the color
    // ------------------------------------------------------------------------
    void Darken(float delta);

    // ------------------------------------------------------------------------
    // Lighten will adjust the color by the given delta toward white
    // NOTE: This is a simple linear change
    // delta - (0-255) the amount to lighten the color
    // ------------------------------------------------------------------------
    void Lighten(float delta);

    // ------------------------------------------------------------------------
    // LinearBlend between two colors by the amount defined by progress variable
    // left - the color to start the blend at
    // right - the color to end the blend at
    // progress - (0.0 - 1.0) value where 0 will return left and 1.0 will return right
    //     and a value between will blend the color weighted linearly between them
    // ------------------------------------------------------------------------
    static TempFColor LinearBlend(const TempFColor& left, const TempFColor& right, float progress);
    
    // ------------------------------------------------------------------------
    // BilinearBlend between four colors by the amount defined by 2d variable
    // c00 - upper left quadrant color
    // c01 - upper right quadrant color
    // c10 - lower left quadrant color
    // c11 - lower right quadrant color
    // x - unit value (0.0 - 1.0) that defines the blend progress in horizontal space
    // y - unit value (0.0 - 1.0) that defines the blend progress in vertical space
    // ------------------------------------------------------------------------
    static TempFColor BilinearBlend(const TempFColor& c00, 
        const TempFColor& c01, 
        const TempFColor& c10, 
        const TempFColor& c11, 
        float x, 
        float y);

    // ------------------------------------------------------------------------
    // Members
    // ------------------------------------------------------------------------
    float Temperature;
    float Brightness;
};

