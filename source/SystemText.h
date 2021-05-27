#ifndef SYSTEMTEXT_H
#define SYSTEMTEXT_H

#define FONTDATA_WIDTH  (1408)
#define FONTDATA_HEIGHT (8)

#define FONTCHR_WIDTH  (8)
#define FONTCHR_HEIGHT (8)

/*  Call this macro repeatedly.  After each use, the pixel data can be extracted  */
static unsigned char fontPixelData[] = {
	0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,0,0,1,1,0,1,1,0,0,
	0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,
	0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,
	0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,
	0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
	0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,
	0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,
	0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,0,
	0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,
	1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,
	1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,
	1,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,
	0,0,0,1,1,1,1,0,1,1,1,0,0,1,1,0,
	1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,
	1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,
	0,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,
	1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,
	1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,
	0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,
	0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,
	0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,
	0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,
	1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,
	0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,
	0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,
	1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,
	1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,1,1,1,0,0,0,0,1,1,0,0,1,1,0,
	1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,
	0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,
	0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,
	0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,
	0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,
	0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,
	1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,
	0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,
	0,1,1,0,0,0,1,1,1,1,0,1,1,0,1,1,
	1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,
	0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,
	1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,1,
	0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,
	0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,
	0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,
	0,0,1,1,1,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,
	0,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,
	0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,1,1,0,1,1,0,0,
	0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,
	0,1,1,0,1,1,0,0,0,1,1,0,0,0,1,0,
	0,1,1,0,0,0,1,0,0,1,1,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,
	0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,0,
	1,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,
	0,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	1,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,
	0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,0,1,1,0,0,1,0,0,0,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,
	1,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,
	0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,
	1,1,0,1,1,1,0,0,1,1,0,1,1,1,0,0,
	0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,
	1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,
	0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,
	1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,
	0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	1,1,1,0,0,1,1,1,0,1,1,0,0,1,1,0,
	1,0,0,1,1,0,0,1,0,0,0,0,1,1,1,1,
	0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,
	0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,
	1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,
	0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,
	1,1,0,1,1,0,1,1,0,0,1,1,1,1,0,0,
	0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,
	0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,
	0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,
	0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,
	0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,
	0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,
	0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,
	1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,
	0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,
	1,1,0,1,1,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,
	0,1,1,0,0,1,1,0,0,1,1,0,1,0,0,0,
	0,1,1,0,1,0,0,0,1,1,0,0,0,0,0,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,
	0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,
	1,1,1,1,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,1,0,1,1,0,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,
	1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,
	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,0,
	0,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,
	0,0,0,1,1,0,0,0,1,1,1,0,1,1,0,0,
	1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,
	1,1,0,1,1,1,0,0,0,1,1,1,0,1,1,0,
	1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,0,
	1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
	1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,
	0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,
	0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,
	1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,
	1,1,0,0,1,1,0,0,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,0,1,1,0,0,1,1,0,1,1,0,0,
	1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,
	0,1,1,0,0,1,0,0,0,0,1,1,1,1,0,0,
	1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,
	0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,
	0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,0,
	0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,
	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,
	1,1,0,0,0,0,1,1,0,1,0,0,0,0,1,0,
	1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,
	0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,
	0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,
	0,1,1,1,1,0,1,1,0,1,1,0,0,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,
	1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
	0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,
	0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,
	1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,
	1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,
	1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,
	0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,
	0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,
	1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,
	0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,
	1,1,0,1,1,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,
	0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,
	0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,
	0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,
	1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,
	0,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,0,1,1,0,0,
	0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,
	0,1,1,1,0,1,1,0,1,1,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,
	0,1,1,0,1,1,0,0,1,1,0,0,0,1,1,0,
	0,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,
	0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,
	1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,
	0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,
	0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	1,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,
	1,1,1,1,1,0,1,0,0,0,1,1,1,1,0,0,
	0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,
	1,1,0,1,1,1,0,0,1,1,1,0,0,1,1,0,
	0,0,1,1,1,1,1,0,0,0,1,1,1,0,0,0,
	0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,
	0,1,1,1,1,0,1,0,0,0,0,1,1,0,0,0,
	1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,
	0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,
	1,1,0,0,0,0,1,1,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,
	1,1,0,0,0,0,1,1,0,1,0,0,0,0,1,0,
	1,0,1,1,1,1,0,1,1,1,0,0,1,1,0,0,
	0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,
	0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,
	1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,
	0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,
	0,0,0,1,1,0,1,1,0,1,1,0,0,1,1,0,
	0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,
	0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,
	1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,
	0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,
	0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,
	1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	1,1,0,1,1,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,
	0,1,1,0,0,1,1,0,0,1,1,0,1,0,0,0,
	0,1,1,0,1,0,0,0,1,1,0,0,1,1,1,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,
	0,1,1,0,0,0,1,0,1,1,0,1,0,1,1,0,
	1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,
	0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,
	0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,
	0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,0,
	0,0,1,1,0,0,1,0,0,0,1,1,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,
	1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,
	0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,
	0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,
	0,0,0,1,1,0,0,0,1,1,0,1,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,
	0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,
	0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,
	0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,
	1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,
	1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,
	1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,
	0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,
	0,1,1,0,0,1,1,0,1,1,1,1,0,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,
	0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,
	0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,
	0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,
	1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,
	0,0,1,1,1,0,0,0,1,1,0,1,0,1,1,0,
	0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	1,1,1,0,0,1,1,1,0,1,1,0,0,1,1,0,
	1,0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,
	0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,
	0,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,
	1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,
	0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,1,1,0,0,1,1,1,1,0,0,
	0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,
	0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,
	0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,
	1,1,1,1,1,1,1,0,0,0,1,0,0,1,0,0,
	1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,
	0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,
	0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
	1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,
	0,1,1,0,1,1,0,0,0,1,1,0,0,0,1,0,
	0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,0,
	0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,
	0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,
	0,1,1,0,1,1,0,0,1,1,1,1,1,1,1,0,
	1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,
	0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,
	0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,
	0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,
	0,0,0,1,1,0,0,0,1,1,0,1,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,
	0,0,1,1,0,1,1,0,1,1,0,0,1,1,0,0,
	0,1,1,0,1,1,0,0,1,1,1,1,1,1,1,0,
	0,1,1,0,1,1,0,0,0,1,1,1,1,1,1,0,
	0,0,1,1,0,0,1,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,
	0,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,
	1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,0,
	1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
	1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,
	1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,
	0,1,1,1,1,1,1,0,0,1,1,0,1,1,0,0,
	1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,
	0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,
	1,1,0,0,1,1,1,1,1,1,0,1,1,0,0,0,
	1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,
	0,1,1,0,0,1,1,0,1,1,0,1,1,1,1,0,
	0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,
	0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,
	0,1,1,0,1,0,1,0,0,0,1,1,1,1,0,0,
	0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,
	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,
	0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,
	1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,
	0,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,
	1,1,1,0,0,1,1,0,1,1,0,1,1,0,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
	0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,
	0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,
	0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,
	0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,
	0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,
	0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,
	0,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,
	1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,
	1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,
	1,1,1,1,0,0,0,0,0,0,1,1,1,0,1,0,
	1,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,
	0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,0,
	1,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,
	1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,
	1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,
	1,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,
	0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,0,
	1,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,
	1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,
	0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,
	1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,1,1,1,0,1,1,0,0,1,1,1,1,1,0,0,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,
	1,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,
	0,1,1,0,0,1,1,0,1,1,1,0,0,1,1,0,
	0,0,1,1,1,1,0,0,1,1,0,1,0,1,1,0,
	0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,
	0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,
	1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,
	0,0,0,1,1,1,0,0,0,1,1,1,0,1,1,0,
	0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,0,
	1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,
	0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,
	0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,
	0,0,0,0,1,1,0,0,0,1,1,1,0,1,1,0,
	0,1,1,1,1,1,0,0,0,1,1,1,0,1,1,0,
	0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,
	0,1,1,1,0,1,1,0,0,0,0,0,1,1,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,
	0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,
	1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,
	1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,
	1,1,0,0,1,1,1,0,0,1,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,
	0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,
	0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,
	0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
	1,1,0,0,0,1,1,0,0,1,1,1,0,0,0,0,
	0,1,1,1,0,1,1,0,0,0,1,1,1,1,0,0,
	0,1,1,1,1,1,0,0,0,1,1,1,0,1,1,0,
	0,1,1,0,0,1,1,0,1,1,0,0,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,
	1,1,0,1,1,1,1,1,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,
	0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
	1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};

#endif