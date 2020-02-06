/*-------------------------------------------------------------------------
HslFColor provides a color object that represents HSL values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#pragma once

#include <Arduino.h>
#include <NeoPixelBus.h>

struct RgbFColor;

// ------------------------------------------------------------------------
// HslFColor represents a color object that is represented by Hue, Saturation
// and Lightness component values.  
// ------------------------------------------------------------------------
struct HslFColor
{
    // ------------------------------------------------------------------------
    // Construct a HslFColor using H, S, L values (0-1)
    // ------------------------------------------------------------------------
    HslFColor(float h, float s, float l) :
        H(h), S(s), L(l)
    {
    };

    // ------------------------------------------------------------------------
    // Construct a HslFColor using a single brightness value (0-1)
    // ------------------------------------------------------------------------
    HslFColor(float brightness) :
        H(0), S(0), L(brightness)
    {
    };

    // ------------------------------------------------------------------------
    // Construct a HslFColor using RgbFColor
    // ------------------------------------------------------------------------
    HslFColor(const RgbFColor& color);

    // ------------------------------------------------------------------------
    // Construct a HslFColor that will have its values set in latter operations
    // CAUTION:  The R,G,B members are not initialized and may not be consistent
    // ------------------------------------------------------------------------
    HslFColor()
    {
    };

    // ------------------------------------------------------------------------
    // Cast HslFColor to RgbFColor
    // ------------------------------------------------------------------------
    operator RgbFColor() const;

    // ------------------------------------------------------------------------
    // Comparison operators
    // ------------------------------------------------------------------------
    bool operator==(const HslFColor& other) const
    {
        if (L == 0 || L == 1) return L == other.L;
        return (H == other.H && S == other.S && L == other.L);
    };

    bool operator!=(const HslFColor& other) const
    {
        return !(*this == other);
    };

    // ------------------------------------------------------------------------
    // CalculateBrightness will calculate the overall brightness
    // NOTE: This is a simple linear brightness
    // ------------------------------------------------------------------------
    float CalculateBrightness() const { return L; }

    // ------------------------------------------------------------------------
    // Dim will return a new color that is blended to black with the given ratio
    // ratio - (0-255) where 255 will return the original color and 0 will return black
    // 
    // NOTE: This is a simple linear blend
    // ------------------------------------------------------------------------
    HslFColor Dim(float ratio) const;

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
    static HslFColor LinearBlend(const HslFColor& left, const HslFColor& right, float progress);
    
    // ------------------------------------------------------------------------
    // BilinearBlend between four colors by the amount defined by 2d variable
    // c00 - upper left quadrant color
    // c01 - upper right quadrant color
    // c10 - lower left quadrant color
    // c11 - lower right quadrant color
    // x - unit value (0.0 - 1.0) that defines the blend progress in horizontal space
    // y - unit value (0.0 - 1.0) that defines the blend progress in vertical space
    // ------------------------------------------------------------------------
    static HslFColor BilinearBlend(const HslFColor& c00, 
        const HslFColor& c01, 
        const HslFColor& c10, 
        const HslFColor& c11, 
        float x, 
        float y);

    // ------------------------------------------------------------------------
    // Hue, Saturation and Lightness color members (0-1)
    // ------------------------------------------------------------------------
    float H;
    float S;
    float L;
};

