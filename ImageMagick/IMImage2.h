#pragma once

#include "4DPluginAPI.h"
#include "Magick++.h"

#if WIN32
//#include "magick/magic.h"
#else
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#endif

#define ImageMagickErrorUnknownObject	-1
#define ImageMagickErrorFramework		-2
#define ImageMagickErrorUnitialized		-3
#define ImageMagickErrorUnknownCommand	-4

//using namespace Magick; 

class IMImage2
{
	private:
	
	Magick::Image _image;
	
	C_TEXT _lastError;
	bool _initialized;
	
	public:
	
	IMImage2(void);
	~IMImage2(void);
	
	int read(C_TEXT &path);
	int read(C_BLOB &data);
	
	int create(int x, int y, C_TEXT &color);
	
	int write(C_TEXT &path);
	int write(C_BLOB &data);
	
	int GetProperty(int selector, C_TEXT &stringpara, double &para1, double &para2, double &para3, double &para4);
	int SetProperty(int selector, C_TEXT &stringpara, double para1, double para2, double para3, double para4);

	int ModifyImage(int selector, C_TEXT &stringpara, double para1, double para2, double para3, double para4, double para5, double para6);

	int Draw(int selector, C_TEXT &stringpara, double para1, double para2, double para3, double para4, double para5, double para6);

	void GetLastError(C_TEXT &stringpara);
};

/*  define all constants to be used as preferences for Get/Set Image Properties 
 err := Get Image Properties(long Image; long Property; string; real1; real2; real3; real4)
 */

// with explicite number assignment, to make documentation for 4D constants easier...
enum {
	IM_Pref_Quality = 1,  // -;quality;-;-;-;-
	IM_Pref_size = 2,  // read only    -;x;y;-;-
	IM_Pref_Geometry = 3,  // read only   -;x;y;resX;resY
	IM_Pref_Magick = 4,  // string
	IM_Pref_Attribute = 5, // string
	IM_Pref_BackgroundColor = 6,
	IM_Pref_BorderColor = 7,
	IM_Pref_BoxColor = 8,
	IM_Pref_StrokeColor = 9,
	IM_Pref_FillColor = 10,
	IM_Pref_StrokeWidth = 11
} ;

enum {
	IM_Draw_Circle = 1,
	IM_Draw_Rectangle = 2,
	IM_Draw_Arc = 3,
	IM_Draw_Color = 4,
	IM_Draw_Composite = 5,
	IM_Draw_Ellipse = 6,
	IM_Draw_Line = 7,
	IM_Draw_Matte = 8,
	IM_Draw_Point = 9,
	IM_Draw_RoundRectangle = 10,
	IM_Draw_Text = 11
};

enum  {
	IM_Mod_addNoise=1,
	IM_Mod_flip=2,
	IM_Mod_flop=3,
	IM_Mod_implode=4,
	IM_Mod_rotate=5,
	IM_Mod_crop=6,
	IM_Mod_blur=7,
	IM_Mod_contrast=8,
	IM_Mod_despeckle=9,
	IM_Mod_adaptiveThreshold=10,
	IM_Mod_Unused=11,
	IM_Mod_Zoom=12,
	IM_Mod_Edge=13,
	IM_Mod_Emboss=14,
	IM_Mod_Enhance=15,
	IM_Mod_Equalize=16,
	IM_Mod_Frame=17,
	IM_Mod_Gamma=18,
	IM_Mod_GaussianBlur=19,
	IM_Mod_Level=20,
	IM_Mod_Magnify=21,
	IM_Mod_Minify=22,
	IM_Mod_MedianFilter=23,
	IM_Mod_Modulate=24,
	IM_Mod_Negate=25,
	IM_Mod_Normalize=26,
	IM_Mod_OilPaint=27,
	IM_Mod_Raise=28,
	IM_Mod_ReduceNoise=29,
	IM_Mod_Roll=30,
	IM_Mod_Sample=31,
	IM_Mod_Scale=32,
	IM_Mod_Segment=33,
	IM_Mod_Shade=34,
	IM_Mod_Sharpen=35,
	IM_Mod_Shave=36,
	IM_Mod_Shear=37,
	IM_Mod_Solarize=38,
	IM_Mod_Spread=39,
	IM_Mod_Swirl=40,
	IM_Mod_Threshold=41,
	IM_Mod_Trim=42,
	IM_Mod_Unsharpmask=43,
	IM_Mod_Wave=44
};
