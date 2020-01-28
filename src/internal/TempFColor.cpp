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
  // Algorithm from http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code
  // as adapted by Renaud Bédard for https://www.shadertoy.com/view/lsSXW1
  float r, g, b;
  float temp = Temperature;
  if (temp < 1000) temp = 1000;
  if (temp > 40000) temp = 40000;
  float t = temp / 100;
  if (t < 66) {
    r = 1;
    g = 0.39008157876901960784 * log(t) - 0.63184144378862745098;
  } else {
    r = 1.29293618606274509804 * pow(t-60, -0.1332047592);
    g = 1.12989086089529411765 * pow(t-60, -0.0755148492);
  }
  if (t >= 66) {
    b = 1;
  } else if (t <= 19) {
    b = 0;
  } else {
    b = 0.54320678911019607843 * log(t - 10.0) - 1.19625408914;
  }
  r *= Brightness;
  _clamp(r);
  g *= Brightness;
  _clamp(g);
  b *= Brightness;
  _clamp(b);
  return RgbFColor(r, g, b);
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