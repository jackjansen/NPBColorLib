/*-------------------------------------------------------------------------
RgbwFColor provides a color object that represents RGBW values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/
#pragma once

#include "Arduino.h"
#include "NeoPixelBus.h"

struct RgbFColor;

// ------------------------------------------------------------------------
// RgbwFColor represents a color object that is represented by Red, Green, Blue
// and White component values.  It contains helpful color routines to manipulate the 
// color.
// ------------------------------------------------------------------------
struct RgbwFColor
{
    // ------------------------------------------------------------------------
    // Construct a RgbwFColor using R, G, B, W values (0-1)
    // ------------------------------------------------------------------------
    RgbwFColor(float r, float g, float b, float w=0) :
        R(r), G(g), B(b), W(w)
    {
    };

    // ------------------------------------------------------------------------
    // Construct a RgbwFColor using a single brightness value (0-1)
    // ------------------------------------------------------------------------
    RgbwFColor(float brightness) :
        R(0), G(0), B(0), W(brightness)
    {
    };

    // ------------------------------------------------------------------------
    // Construct a RgbwFColor using RgbwColor
    // ------------------------------------------------------------------------
    RgbwFColor(const RgbwColor& color);

    // ------------------------------------------------------------------------
    // Construct a RgbwFColor using RgbFColor
    // ------------------------------------------------------------------------
    RgbwFColor(const RgbFColor& color);

    // ------------------------------------------------------------------------
    // Construct a RgbwFColor that will have its values set in latter operations
    // CAUTION:  The R,G,B members are not initialized and may not be consistent
    // ------------------------------------------------------------------------
    RgbwFColor()
    {
    };

    // ------------------------------------------------------------------------
    // Cast RgbwFColor to RgbwColor
    // ------------------------------------------------------------------------
    operator RgbwColor() const;

    // ------------------------------------------------------------------------
    // Comparison operators
    // ------------------------------------------------------------------------
    bool operator==(const RgbwFColor& other) const
    {
        return (R == other.R && G == other.G && B == other.B && W == other.W);
    };

    bool operator!=(const RgbwFColor& other) const
    {
        return !(*this == other);
    };

    // ------------------------------------------------------------------------
    // Returns if the color is grey, all values are equal other than white
    // ------------------------------------------------------------------------
    bool IsMonotone() const
    {
        return (R == B && R == G);
    };

    // ------------------------------------------------------------------------
    // Returns if the color components are all zero, the white component maybe 
    // anything
    // ------------------------------------------------------------------------
    bool IsColorLess() const
    {
        return (R == 0 && B == 0 && G == 0);
    };

    // ------------------------------------------------------------------------
    // CalculateBrightness will calculate the overall brightness
    // NOTE: This is a simple linear brightness
    // ------------------------------------------------------------------------
    float CalculateBrightness() const;

    // ------------------------------------------------------------------------
    // Dim will return a new color that is blended to black with the given ratio
    // 
    // NOTE: This is a simple linear blend
    // ------------------------------------------------------------------------
    RgbwFColor Dim(float ratio) const;

    // ------------------------------------------------------------------------
    // Darken will adjust the color by the given delta toward black
    // NOTE: This is a simple linear change
    // ------------------------------------------------------------------------
    void Darken(float delta);

    // ------------------------------------------------------------------------
    // Lighten will adjust the color by the given delta toward white
    // NOTE: This is a simple linear change
    // ------------------------------------------------------------------------
    void Lighten(float delta);

    // ------------------------------------------------------------------------
    // LinearBlend between two colors by the amount defined by progress variable
    // left - the color to start the blend at
    // right - the color to end the blend at
    // progress - (0.0 - 1.0) value where 0 will return left and 1.0 will return right
    //     and a value between will blend the color weighted linearly between them
    // ------------------------------------------------------------------------
    static RgbwFColor LinearBlend(const RgbwFColor& left, const RgbwFColor& right, float progress);
    
    // ------------------------------------------------------------------------
    // BilinearBlend between four colors by the amount defined by 2d variable
    // c00 - upper left quadrant color
    // c01 - upper right quadrant color
    // c10 - lower left quadrant color
    // c11 - lower right quadrant color
    // x - unit value (0.0 - 1.0) that defines the blend progress in horizontal space
    // y - unit value (0.0 - 1.0) that defines the blend progress in vertical space
    // ------------------------------------------------------------------------
    static RgbwFColor BilinearBlend(const RgbwFColor& c00, 
        const RgbwFColor& c01, 
        const RgbwFColor& c10, 
        const RgbwFColor& c11, 
        float x, 
        float y);

    // ------------------------------------------------------------------------
    // Red, Green, Blue and White color members (0-1) where 
    // (0,0,0,0) is black and (1,1,1,1) is white
    // ------------------------------------------------------------------------
    float R;
    float G;
    float B;
    float W;
};

