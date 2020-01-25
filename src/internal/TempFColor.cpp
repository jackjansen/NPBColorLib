/*-------------------------------------------------------------------------
TempFColor provides a color object that represents Temp values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#include "TempFColor.h"
#include "RgbFColor.h"

inline void _clamp(float& f)
{
	if (f < 0) f = 0;
	if (f > 1) f = 1;
}

TempFColor::operator RgbFColor() const
{
	assert(0);
	return RgbFColor(0,0,0);
}

TempFColor TempFColor::Dim(float ratio) const
{
    // specifically avoids float math
    return TempFColor(Temperature, Brightness*ratio);
}

void TempFColor::Darken(float delta)
{
	Brightness -= delta;
	_clamp(Brightness);
}

void TempFColor::Lighten(float delta)
{
	Brightness += delta;
	_clamp(Brightness);

}

TempFColor TempFColor::LinearBlend(const TempFColor& left, const TempFColor& right, float progress)
{
	return TempFColor( left.Temperature + ((right.Temperature - left.Temperature) * progress),
		left.Brightness + ((right.Brightness - left.Brightness) * progress));
}

TempFColor TempFColor::BilinearBlend(const TempFColor& c00, 
    const TempFColor& c01, 
    const TempFColor& c10, 
    const TempFColor& c11, 
    float x, 
    float y)
{
    float v00 = (1.0f - x) * (1.0f - y);
    float v10 = x * (1.0f - y);
    float v01 = (1.0f - x) * y;
    float v11 = x * y;

    return TempFColor(
        c00.Temperature * v00 + c10.Temperature * v10 + c01.Temperature * v01 + c11.Temperature * v11,
        c00.Brightness * v00 + c10.Brightness * v10 + c01.Brightness * v01 + c11.Brightness * v11);
}