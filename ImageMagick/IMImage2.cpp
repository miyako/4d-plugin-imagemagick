#include "IMImage2.h"

#include "functions_imgk.h"

IMImage2::IMImage2() : _initialized(false)
{
	_image = 0;
}

IMImage2::~IMImage2()
{
	// no need to deallocate image	
}

int IMImage2::read(C_TEXT &path)
{
	try {
			CUTF8String u;
			path.copyUTF8String(&u);
			_image.read((const char *)u.c_str());  
			_initialized = true;
			return 0;
		}
	catch(Magick::Exception &error_) 
	{
		_lastError.setUTF8String((const uint8_t *)error_.what(), strlen(error_.what()));
		return ImageMagickErrorFramework;
	}
}

int IMImage2::read(C_BLOB &data)
{
	try { 
			Magick::Blob myblob(data.getBytesPtr(), data.getBytesLength());
			_image.read(myblob);
			_initialized = true;
			return 0;
		}
	catch(Magick::Exception &error_) 
	{
		_lastError.setUTF8String((const uint8_t *)error_.what(), strlen(error_.what()));
		return ImageMagickErrorFramework;
	}
}

int IMImage2::create(int x, int y, C_TEXT &color)
{
	try { 
			CUTF8String u;
			color.copyUTF8String(&u);
			Magick::Image newimage(Magick::Geometry(x, y), Magick::Color((const char *)u.c_str()));
			_image = newimage;
			_initialized = true;
			return 0;
		}
	catch(Magick::Exception &error_) 
	{
		_lastError.setUTF8String((const uint8_t *)error_.what(), strlen(error_.what()));
		return ImageMagickErrorFramework;
	}
}

int IMImage2::write(C_TEXT &path)
{
	if (!_initialized)
		return ImageMagickErrorUnitialized;

	if (!_image.isValid())
		return ImageMagickErrorUnitialized;

	try { 
			CUTF8String u;
			path.copyUTF8String(&u);
			_image.write((const char *)u.c_str());
			return 0;
		}
	catch(Magick::Exception &error_) 
	{
		_lastError.setUTF8String((const uint8_t *)error_.what(), strlen(error_.what()));
		return ImageMagickErrorFramework;
	}
}

int IMImage2::write(C_BLOB &data)
{
	if (!_initialized)
		return ImageMagickErrorUnitialized;
	
	if (!_image.isValid())
		return ImageMagickErrorUnitialized;

	try { 
			Magick::Blob myblob;
			_image.write(&myblob);
			data.setBytes((const uint8_t *)myblob.data(), myblob.length());
			return 0;
		}
	catch(Magick::Exception &error_) 
	{
		_lastError.setUTF8String((const uint8_t *)error_.what(), strlen(error_.what()));
		return ImageMagickErrorFramework;
	}
}

int IMImage2::GetProperty(int selector, C_TEXT &stringpara, double &para1, double &para2, double &para3, double &para4)
{
	if (!_initialized)
		return ImageMagickErrorUnitialized;

	if (!_image.isValid())
		return ImageMagickErrorUnitialized;

	try { 
		para1 = para2 = para3 = para4 = 0;
	
		Magick::Geometry geo;
		Magick::Color dummyColor; 
	
		CUTF8String dummystr;
		std::string dummyColorStr;
		
		switch (selector)
		{
			case IM_Pref_Quality: 
				para1 = (double)_image.quality();
				break;

			case IM_Pref_size: 
				para1 = _image.baseColumns();
				para2 = _image.baseRows();
				break;

			case IM_Pref_Geometry: 
				para1 = _image.columns();
				para2 = _image.rows();
				para3 = _image.xResolution();
				para4 = _image.yResolution();
				break;

			case IM_Pref_Magick:
				stringpara.setUTF8String((const uint8_t *)_image.magick().c_str(), _image.magick().size());
				break;

			case IM_Pref_Attribute:
				stringpara.copyUTF8String(&dummystr);
				dummystr = CUTF8String((const uint8_t *)_image.attribute((const char *)dummystr.c_str()).c_str());
				stringpara.setUTF8String(&dummystr);
				break;

			case IM_Pref_BackgroundColor:
				dummyColor = _image.backgroundColor();
				dummyColorStr = dummyColor;
				stringpara.setUTF8String((const uint8_t *)dummyColorStr.c_str(), dummyColorStr.size());
				break;

			case IM_Pref_BorderColor:
				dummyColor = _image.borderColor();
				dummyColorStr = dummyColor;
				stringpara.setUTF8String((const uint8_t *)dummyColorStr.c_str(), dummyColorStr.size());
				break;

			case IM_Pref_BoxColor:
				dummyColor = _image.boxColor();
				dummyColorStr = dummyColor;
				stringpara.setUTF8String((const uint8_t *)dummyColorStr.c_str(), dummyColorStr.size());
				break;

			case IM_Pref_StrokeColor:
				dummyColor = _image.strokeColor();
				dummyColorStr = dummyColor;
				stringpara.setUTF8String((const uint8_t *)dummyColorStr.c_str(), dummyColorStr.size());
				break;

			case IM_Pref_FillColor:
				dummyColor = _image.fillColor();
				dummyColorStr = dummyColor;
				stringpara.setUTF8String((const uint8_t *)dummyColorStr.c_str(), dummyColorStr.size());
				break;

			case IM_Pref_StrokeWidth:
				para1 = _image.strokeWidth();
				break;

			default: 
				return ImageMagickErrorUnknownCommand;
				break;
		}
			return 0;
		}
	catch(Magick::Exception &error_) 
	{
		_lastError.setUTF8String((const uint8_t *)error_.what(), strlen(error_.what()));
		return ImageMagickErrorFramework;
	}
}

int IMImage2::SetProperty(int selector, C_TEXT &stringpara, double para1, double para2, double para3, double para4)
{
	if (!_initialized)
		return ImageMagickErrorUnitialized;

	if (!_image.isValid())
		return ImageMagickErrorUnitialized;

	try {
		
		Magick::Geometry geo;
		CUTF8String dummystr;

		_image.modifyImage();

		switch (selector)
		{
			case IM_Pref_Quality: 
				_image.quality((const unsigned int) para1);
				break;
				
			case IM_Pref_Magick:
				stringpara.copyUTF8String(&dummystr);
				_image.magick((const char *)dummystr.c_str());
				break;

			case IM_Pref_Attribute:
				{
					std::string Tag, Content, Original;
					std::string::size_type pos;
					
					stringpara.copyUTF8String(&dummystr);
					
					Original = (const char *)dummystr.c_str();
					
					stringpara.setUTF8String((const uint8_t *)"", 0);
					
					char tab = 9;
					pos = Original.find(tab, 0);
					
					if (pos == std::string::npos)
						return 0;
					
					Tag = Original.substr(0, pos);
					Content = Original.substr(pos+1, Original.length()-pos-1);
					_image.attribute(Tag, Content);
				}
				break;

			case IM_Pref_BackgroundColor:
				stringpara.copyUTF8String(&dummystr);
				_image.backgroundColor((const char *)dummystr.c_str());
				break;

			case IM_Pref_BorderColor:
				stringpara.copyUTF8String(&dummystr);
				_image.borderColor((const char *)dummystr.c_str());
				break;

			case IM_Pref_BoxColor:
				stringpara.copyUTF8String(&dummystr);
				_image.boxColor((const char *)dummystr.c_str());
				break;

			case IM_Pref_StrokeColor:
				stringpara.copyUTF8String(&dummystr);
				_image.strokeColor((const char *)dummystr.c_str());
				break;

			case IM_Pref_FillColor:
				stringpara.copyUTF8String(&dummystr);
				_image.fillColor((const char *)dummystr.c_str());
				break;

			case IM_Pref_StrokeWidth:
				_image.strokeWidth(para1);
				break;

			default: 
				return ImageMagickErrorUnknownCommand;
				break;
		}
			return 0;
		}
	catch(Magick::Exception &error_) 
	{
		_lastError.setUTF8String((const uint8_t *)error_.what(), strlen(error_.what()));
		return ImageMagickErrorFramework;
	}
}

int IMImage2::Draw(int selector, C_TEXT &stringpara, double para1, double para2, double para3, double para4, double para5, double para6)
{
	if (!_initialized)
		return ImageMagickErrorUnitialized;

	if (!_image.isValid())
		return ImageMagickErrorUnitialized;

	try { 
			Magick::Geometry geo;
			CUTF8String dummystr;
			_image.modifyImage();

		switch (selector)
		{
			case IM_Draw_Circle: 
				_image.draw(Magick::DrawableCircle(para1, para2, para3, para4));
				break;			

			case IM_Draw_Rectangle: 
				_image.draw(Magick::DrawableRectangle(para1, para2, para3, para4));
				break;			

			case IM_Draw_Arc: 
				_image.draw(Magick::DrawableArc(para1, para2, para3, para4, para5, para6));
				break;			

			case IM_Draw_Color: 
				{
					int pm = (int) para3;
					_image.draw(Magick::DrawableColor(para1, para2, (Magick::PaintMethod) pm));
				}
				break;			

			case IM_Draw_Composite: 
				// "", Imageobject, x, y, width, height, composition
				// or
				// Path, 0, x, y, width, height, composition
				{
					int Composition = (int) para6;
					
					if (para1)
					{						
						IMImage2 *newImage = _objectGet(para1);
												
						if (newImage)
							_image.draw(Magick::DrawableCompositeImage(para2, para3, para4, para5, newImage->_image, (Magick::CompositeOperator) Composition));
						else
							return ImageMagickErrorUnknownObject;
						 
					}else{
							stringpara.copyUTF8String(&dummystr);
							_image.draw(Magick::DrawableCompositeImage(para2, para3, para4, para5, (const char *)dummystr.c_str(), (Magick::CompositeOperator) Composition));
					}
				}
				break;			

			case IM_Draw_Ellipse: 
				_image.draw(Magick::DrawableEllipse(para1, para2, para3, para4, para5, para6));
				break;			

			case IM_Draw_Line: 
				_image.draw(Magick::DrawableLine(para1, para2, para3, para4));
				break;			

			case IM_Draw_Matte: 
				{
					int paint = (int) para3;
					_image.draw(Magick::DrawableMatte(para1, para2, (Magick::PaintMethod) paint));
				}
				break;			

			case IM_Draw_Point: 
				_image.draw(Magick::DrawablePoint(para1, para2));
				break;			

			case IM_Draw_RoundRectangle: 
				_image.draw(Magick::DrawableRoundRectangle(para1, para2, para3, para4, para5, para6));
				break;			

			case IM_Draw_Text: 
				{
					_image.font("Arial");
					_image.draw(Magick::DrawableFont("Arial"));
					_image.fontPointsize(para3);
					_image.penColor("black");
					_image.backgroundColor("white");
		
					stringpara.copyUTF8String(&dummystr);
					_image.draw(Magick::DrawableText(para1, para2, (const char *)dummystr.c_str()));
				}
				break;		 

			default: 
				return ImageMagickErrorUnknownCommand;
				break;
		}
		return 0;
		}
	catch(Magick::Exception &error_) 
	{
		_lastError.setUTF8String((const uint8_t *)error_.what(), strlen(error_.what()));
		return ImageMagickErrorFramework;
	}
}

int IMImage2::ModifyImage(int selector, C_TEXT &stringpara, double para1, double para2, double para3, double para4, double para5, double para6)
{
	if (!_initialized)
		return ImageMagickErrorUnitialized;

	if (!_image.isValid())
		return ImageMagickErrorUnitialized;

	try { 
			Magick::Geometry geo;

			_image.modifyImage();

		switch (selector)
		{
			case IM_Mod_addNoise: 
				_image.addNoise((const MagickCore::NoiseType)(long)para1);
				break;

			case IM_Mod_flip: 
				_image.flip();
				break;

			case IM_Mod_flop: 
				_image.flop();
				break;

			case IM_Mod_implode: // double 0..2
				_image.implode(para1);
				break;

			case IM_Mod_rotate:  // 0-360
				_image.rotate(para1);
				break;

			case IM_Mod_crop:  //  x1, y1, x2, y2
				geo.xOff((long)para1);
				geo.yOff((long)para2);
				geo.width((long)(para3-para1));
				geo.height((long)(para4-para2));
				_image.crop(geo);
				break;

			case IM_Mod_blur:  // const double radius_ = 1, const double sigma_ = 0.5
				if(para2 != 0)
					_image.blur(para1, para2);
				else
					_image.blur(para1);
				break;

			case IM_Mod_contrast:  //sharpen
				_image.contrast((long)para1);
				break;

			case IM_Mod_despeckle:  
				_image.despeckle();
				break;

			case IM_Mod_adaptiveThreshold:  //  unsigned int width, unsigned int height, unsigned offset = 0
				_image.adaptiveThreshold((long)para1, (long)para2, (long)para3);
				break;

			case IM_Mod_Zoom:
				geo.width((long)para1);
				geo.height((long)para2);
				_image.zoom(geo);
				break;
				
			case IM_Mod_Edge:
				_image.edge((long)para1);
				break;		
				
			case IM_Mod_Emboss:
				_image.emboss(para1, para2);
				break;
				
			case IM_Mod_Enhance:  
				_image.enhance();
				break;

			case IM_Mod_Equalize:  
				_image.equalize();
				break;
				
			case IM_Mod_Frame:
				_image.frame((long)para1, (long)para2, (long)para3, (long)para4);
				break;	
				
			case IM_Mod_Gamma:
				if (para1==0)
					_image.gamma(para2, para3, para4);
				else
					_image.gamma(para1);
				break;
				
			case IM_Mod_GaussianBlur:
				_image.gaussianBlur(para1, para2);
				break;
				
			case IM_Mod_Level:
				_image.level((_image.quantizeColors() / 100 * para1), (_image.quantizeColors() / 100 * para2), para3);
				break;
				
			case IM_Mod_Magnify:
				_image.magnify();
				break;
				
			case IM_Mod_Minify:
				_image.minify();
				break;
				
			case IM_Mod_MedianFilter:
				_image.medianFilter(para1);
				break;
				
			case IM_Mod_Modulate:
				_image.modulate(para1, para2, para3);
				break;
				
			case IM_Mod_Negate:
				_image.negate(para1 != 0);
				break;
				
			case IM_Mod_Normalize:
				_image.normalize();
				break;
				
			case IM_Mod_OilPaint:
				_image.oilPaint(para1);
				break;
				
			case IM_Mod_Raise:
				geo.width((long)(para1));
				geo.height((long)(para2));
				geo.xOff((long)para3);
				geo.yOff((long)para4);				
				_image.raise(geo, (para5 != 0));
				break;
				
			case IM_Mod_ReduceNoise:
				if (para1 != 0)
					_image.reduceNoise(para1);
				else
					_image.reduceNoise();
				break;
				
			case IM_Mod_Roll:
				_image.roll((long)para1, (long)para2);
				break;
				
			case IM_Mod_Sample:
				geo.width((long)para1);
				geo.height((long)para2);				
				_image.sample(geo);
				break;
				
			case IM_Mod_Scale:
				geo.width((long)para1);
				geo.height((long)para2);				
				_image.scale(geo);
				break;
				
			case IM_Mod_Segment:
				_image.segment(para1, para2);
				break;
				
			case IM_Mod_Shade:
				_image.shade(para1, para2, (para3 != 0));
				break;
				
			case IM_Mod_Sharpen:
				_image.sharpen(para1, para2);
				break;
				
			case IM_Mod_Shave:
				geo.width((long)para1);
				geo.height((long)para2);				
				_image.shave(geo);
				break;
				
			case IM_Mod_Shear:
				_image.shear(para1, para2);
				break;
				
			case IM_Mod_Solarize:
				_image.solarize(para1);
				break;
				
			case IM_Mod_Spread:
				_image.spread((int)para1);
				break;
				
			case IM_Mod_Swirl:
				_image.swirl(para1);
				break;
				
			case IM_Mod_Threshold:
				_image.threshold(para1);
				break;
				
			case IM_Mod_Trim:
				_image.trim();
				break;
				
			case IM_Mod_Unsharpmask:
				_image.unsharpmask(para1, para2, para3, para4);
				break;
				
			case IM_Mod_Wave:
				_image.wave(para1, para2);
				break;
				
			default: 
				return ImageMagickErrorUnknownCommand;
				break;
		}
		return 0;
		}
	catch(Magick::Exception &error_) 
	{
		_lastError.setUTF8String((const uint8_t *)error_.what(), strlen(error_.what()));
		return ImageMagickErrorFramework;
	}
}

void IMImage2::GetLastError(C_TEXT &stringpara)
{
	stringpara.setUTF16String(_lastError.getUTF16StringPtr(), _lastError.getUTF16Length());
}
