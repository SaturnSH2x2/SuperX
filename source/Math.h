#ifndef MATH_H
#define MATH_H

typedef struct {
	int pixel;
	u8 subpixel;
} Coord;

inline float SubpixelToDecimal(u8 subpixel) {
	return (float) subpixel / 256.0f;
}

inline u8 DecimalToSubpixel(float decimal) {
	decimal = decimal - floor(decimal);
	return (u8) decimal * 256;
}

inline float CoordToFloat(Coord p) {
	return (float) p.pixel + SubpixelToDecimal(p.subpixel);
}

inline Coord FloatToCoord(float f) {
	Coord p;
	p.pixel = (int) f;
	p.subpixel = DecimalToSubpixel(f);

	return p;
}

#endif
