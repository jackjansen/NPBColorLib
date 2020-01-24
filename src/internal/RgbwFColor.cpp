/*-------------------------------------------------------------------------
RgbwFColor provides a color object that represents RGBW values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/


#include "RgbwFColor.h"
#include "RgbFColor.h"

inline void _clamp(float& f)
{
	if (f < 0) f = 0;
	if (f > 1) f = 1;
}

RgbwFColor::operator RgbwColor() const
{
	return RgbwColor((uint8_t)(R*255), (uint8_t)(G*255), (uint8_t)(B*255), (uint8_t)(W*255));
}

RgbwFColor::RgbwFColor(RgbwColor const&src)
{
	R = src.R/255.0;
	G = src.G/255.0;
	B = src.B/255.0;
	W = src.W/255.0;
}

RgbwFColor::RgbwFColor(RgbFColor const&src)
{
	R = src.R;
	G = src.G;
	B = src.B;
	W = 0;
}

float RgbwFColor::CalculateBrightness() const
{
	float rgbBrightness = (R + G + B) / 3;
	if (W > rgbBrightness) return W;
	return rgbBrightness;
}

RgbwFColor RgbwFColor::Dim(float ratio) const
{
    // specifically avoids float math
    return RgbwFColor(R * ratio, G * ratio, B * ratio, W * ratio);
}

void RgbwFColor::Darken(float delta)
{
	R -= delta;
	_clamp(R);
	G -= delta;
	_clamp(G);
	B -= delta;
	_clamp(B);
}

void RgbwFColor::Lighten(float delta)
{
	if (IsColorLess()) {
		W += delta;
		_clamp(W);
		return;
	}
	R += delta;
	_clamp(R);
	G += delta;
	_clamp(G);
	B += delta;
	_clamp(B);
}

RgbwFColor RgbwFColor::LinearBlend(const RgbwFColor& left, const RgbwFColor& right, float progress)
{
	return RgbwFColor( left.R + ((right.R - left.R) * progress),
		left.G + ((right.G - left.G) * progress),
		left.B + ((right.B - left.B) * progress),
		left.W + ((right.W - left.W) * progress));
}

RgbwFColor RgbwFColor::BilinearBlend(const RgbwFColor& c00, 
    const RgbwFColor& c01, 
    const RgbwFColor& c10, 
    const RgbwFColor& c11, 
    float x, 
    float y)
{
    float v00 = (1.0f - x) * (1.0f - y);
    float v10 = x * (1.0f - y);
    float v01 = (1.0f - x) * y;
    float v11 = x * y;

    return RgbwFColor(
        c00.R * v00 + c10.R * v10 + c01.R * v01 + c11.R * v11,
        c00.G * v00 + c10.G * v10 + c01.G * v01 + c11.G * v11,
        c00.B * v00 + c10.B * v10 + c01.B * v01 + c11.B * v11,
		c00.W * v00 + c10.W * v10 + c01.W * v01 + c11.W * v11);
}