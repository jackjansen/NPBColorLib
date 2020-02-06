/*-------------------------------------------------------------------------
RgbFColor provides a color object that represents RGB values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#pragma once

#include <Arduino.h>
#include <NeoPixelBus.h>

// ------------------------------------------------------------------------
// RgbFColor represents a color object that is represented by Red, Green, Blue
// component values.  It contains helpful color routines to manipulate the 
// color.
// ------------------------------------------------------------------------
struct RgbFColor
{
    // ------------------------------------------------------------------------
    // Construct a RgbFColor using R, G, B values (0-1)
    // ------------------------------------------------------------------------
    RgbFColor(float r, float g, float b) :
        R(r), G(g), B(b)
    {
    };

    // ------------------------------------------------------------------------
    // Construct a RgbFColor using a single brightness value (0-1)
    // ------------------------------------------------------------------------
    RgbFColor(float brightness) :
        R(brightness), G(brightness), B(brightness)
    {
    };

    // ------------------------------------------------------------------------
    // Construct a RgbFColor using RgbColor
    // ------------------------------------------------------------------------
    RgbFColor(const RgbColor& color);

    // ------------------------------------------------------------------------
    // Construct a RgbFColor that will have its values set in latter operations
    // CAUTION:  The R,G,B members are not initialized and may not be consistent
    // ------------------------------------------------------------------------
    RgbFColor()
    {
    };

    // ------------------------------------------------------------------------
    // Cast RgbFColor to RgbColor
    // ------------------------------------------------------------------------
    operator RgbColor() const;

    // ------------------------------------------------------------------------
    // Comparison operators
    // ------------------------------------------------------------------------
    bool operator==(const RgbFColor& other) const
    {
        return (R == other.R && G == other.G && B == other.B);
    };

    bool operator!=(const RgbFColor& other) const
    {
        return !(*this == other);
    };

    // ------------------------------------------------------------------------
    // CalculateBrightness will calculate the overall brightness
    // NOTE: This is a simple linear brightness
    // ------------------------------------------------------------------------
    float CalculateBrightness() const;

    // ------------------------------------------------------------------------
    // Dim will return a new color that is blended to black with the given ratio
    // ratio - (0-255) where 255 will return the original color and 0 will return black
    // 
    // NOTE: This is a simple linear blend
    // ------------------------------------------------------------------------
    RgbFColor Dim(float ratio) const;

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
    static RgbFColor LinearBlend(const RgbFColor& left, const RgbFColor& right, float progress);
    
    // ------------------------------------------------------------------------
    // BilinearBlend between four colors by the amount defined by 2d variable
    // c00 - upper left quadrant color
    // c01 - upper right quadrant color
    // c10 - lower left quadrant color
    // c11 - lower right quadrant color
    // x - unit value (0.0 - 1.0) that defines the blend progress in horizontal space
    // y - unit value (0.0 - 1.0) that defines the blend progress in vertical space
    // ------------------------------------------------------------------------
    static RgbFColor BilinearBlend(const RgbFColor& c00, 
        const RgbFColor& c01, 
        const RgbFColor& c10, 
        const RgbFColor& c11, 
        float x, 
        float y);

    // ------------------------------------------------------------------------
    // Red, Green, Blue color members (0-255) where 
    // (0,0,0) is black and (255,255,255) is white
    // ------------------------------------------------------------------------
    float R;
    float G;
    float B;
};

