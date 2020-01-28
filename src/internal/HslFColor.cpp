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
	float chroma = (1 - abs(2*L - 1)) * S;
	float hprime = fmod(H, 360.0) / 60;
	float x = chroma * (1-abs(fmod(hprime, 2.0)-1));
	float r1, g1, b1;
	r1 = g1 = b1 = 0;
	if (0 <= hprime && hprime <= 1) {
		r1 = chroma;
		g1 = x;
		b1 = 0;
	} else
	if (1 <= hprime && hprime <= 2) {
		r1 = x;
		g1 = chroma;
		b1 = 0;
	} else
	if (2 <= hprime && hprime <= 3) {
		r1 = 0;
		g1 = chroma;
		b1 = x;
	} else
	if (3 <= hprime && hprime <= 4) {
		r1 = 0;
		g1 = x;
		b1 = chroma;
	} else
	if (4 <= hprime && hprime <= 5) {
		r1 = x;
		g1 = 0;
		b1 = chroma;
	} else
	if (5 <= hprime && hprime <= 6) {
		r1 = chroma;
		g1 = 0;
		b1 = x;
	}
	float m = L - (chroma/2);
	return RgbFColor(r1+m, g1+m, b1+m);
}

HslFColor::HslFColor(RgbFColor const&src)
{
	float minColor = min(src.R, min(src.G, src.B));
	float maxColor = max(src.R, max(src.G, src.B));
	L = (minColor + maxColor) / 2;
	if (minColor == maxColor) {
		H = 0;
		S = 0;
		return;
	}
	if (L < 0.5) {
		S = (maxColor-minColor)/(maxColor+minColor);
	} else {
		S = (maxColor-minColor)/(2-maxColor-minColor);
	}
	if (maxColor == src.R) {
		H = 60 * (src.G - src.B) / (maxColor-minColor);
	} else if (maxColor == src.G) {
		H = 60 * (src.B - src.R) / (maxColor-minColor);
	} else {
		H = 60 * (src.R - src.G) / (maxColor-minColor);
	}
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