/*-------------------------------------------------------------------------
RgbFColor provides a color object that represents RGB values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#include "RgbFColor.h"

inline void _clamp(float& f)
{
	if (f < 0) f = 0;
	if (f > 1) f = 1;
}

RgbFColor::operator RgbColor() const
{
	return RgbColor((uint8_t)(R*255), (uint8_t)(G*255), (uint8_t)(B*255));
}
RgbFColor::RgbFColor(RgbColor const&src)
{
	R = src.R/255.0;
	G = src.G/255.0;
	B = src.B/255.0;
}

float RgbFColor::CalculateBrightness() const
{
	return (R + G + B) / 3;
}

RgbFColor RgbFColor::Dim(float ratio) const
{
    // specifically avoids float math
    return RgbFColor(R * ratio, G * ratio, B * ratio);
}

void RgbFColor::Darken(float delta)
{
	R -= delta;
	_clamp(R);
	G -= delta;
	_clamp(G);
	B -= delta;
	_clamp(B);
}

void RgbFColor::Lighten(float delta)
{
	R += delta;
	_clamp(R);
	G += delta;
	_clamp(G);
	B += delta;
	_clamp(B);
}

RgbFColor RgbFColor::LinearBlend(const RgbFColor& left, const RgbFColor& right, float progress)
{
	return RgbFColor( left.R + ((right.R - left.R) * progress),
		left.G + ((right.G - left.G) * progress),
		left.B + ((right.B - left.B) * progress));
}

RgbFColor RgbFColor::BilinearBlend(const RgbFColor& c00, 
    const RgbFColor& c01, 
    const RgbFColor& c10, 
    const RgbFColor& c11, 
    float x, 
    float y)
{
    float v00 = (1.0f - x) * (1.0f - y);
    float v10 = x * (1.0f - y);
    float v01 = (1.0f - x) * y;
    float v11 = x * y;

    return RgbFColor(
        c00.R * v00 + c10.R * v10 + c01.R * v01 + c11.R * v11,
        c00.G * v00 + c10.G * v10 + c01.G * v01 + c11.G * v11,
        c00.B * v00 + c10.B * v10 + c01.B * v01 + c11.B * v11);
}