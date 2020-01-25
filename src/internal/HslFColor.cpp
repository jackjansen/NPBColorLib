/*-------------------------------------------------------------------------
HslFColor provides a color object that represents Hsl values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#include "HslFColor.h"
#include "RgbFColor.h"

inline void _clamp(float& f)
{
	if (f < 0) f = 0;
	if (f > 1) f = 1;
}

HslFColor::operator RgbFColor() const
{
	assert(0);
	return RgbFColor(0, 0, 0);
}

HslFColor::HslFColor(RgbFColor const&src)
{
	assert(0);
}

HslFColor HslFColor::Dim(float ratio) const
{
    // specifically avoids float math
    return HslFColor(H, S, L * ratio);
}

void HslFColor::Darken(float delta)
{

	L -= delta;
	_clamp(L);
}

void HslFColor::Lighten(float delta)
{
	L += delta;
	_clamp(L);
}

HslFColor HslFColor::LinearBlend(const HslFColor& left, const HslFColor& right, float progress)
{
	return HslFColor( left.H + ((right.H - left.H) * progress),
		left.S + ((right.S - left.S) * progress),
		left.L + ((right.L - left.L) * progress));
}

HslFColor HslFColor::BilinearBlend(const HslFColor& c00, 
    const HslFColor& c01, 
    const HslFColor& c10, 
    const HslFColor& c11, 
    float x, 
    float y)
{
    float v00 = (1.0f - x) * (1.0f - y);
    float v10 = x * (1.0f - y);
    float v01 = (1.0f - x) * y;
    float v11 = x * y;

    return HslFColor(
        c00.H * v00 + c10.H * v10 + c01.H * v01 + c11.H * v11,
        c00.S * v00 + c10.S * v10 + c01.S * v01 + c11.S * v11,
        c00.L * v00 + c10.L * v10 + c01.L * v01 + c11.L * v11);
}