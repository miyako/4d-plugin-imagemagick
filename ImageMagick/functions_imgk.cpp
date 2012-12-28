#include "functions_imgk.h"

#pragma mark -

std::map<uint32_t, IMImage2*> _objects;

IMImage2 *_objectCreate(unsigned int *index)
{
	Magick::Image _image;
	
	IMImage2 *obj = new(IMImage2);
	
	unsigned int i = 1;
	
	while (_objects.find(i) != _objects.end())
	{
		i++;
	}
	
	_objects.insert(std::map<uint32_t, IMImage2*>::value_type(i, obj));
	
	*index = i; 
	
	return obj;
}

void _objectDelete(unsigned int i)
{	
	std::map<uint32_t, IMImage2*>::iterator pos = _objects.find(i);
	
	if(pos != _objects.end()) 
	{
		delete pos->second;
		_objects.erase(pos);
	}
}

IMImage2 *_objectGet(unsigned int i)
{	
	IMImage2 *obj = NULL;
	
	std::map<uint32_t, IMImage2*>::iterator pos = _objects.find(i);
	
	if(pos != _objects.end()) 
	{
		obj = pos->second;
	}
	
	return obj;
}

#pragma mark -

#include <list>

// --------------------------------- Image Object ---------------------------------


void IM_New_Object(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT returnValue;
	
	unsigned int i = 0;
	
	_objectCreate(&i);
	
	returnValue.setIntValue(i);
	returnValue.setReturn(pResult);
}

void IM_Clear_Object(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);

	if(_objectGet(Param1.getIntValue()))
	{
		_objectDelete(Param1.getIntValue());	
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);
	}
	   
	returnValue.setReturn(pResult);
}

void IM_Copy(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	IMImage2 *oldImage = _objectGet(Param2.getIntValue());
	
	if((newImage) && (oldImage))
	{
		*newImage = *oldImage;
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}
	
	returnValue.setReturn(pResult);
}

void IM_Create(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_TEXT Param4;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
	{
		returnValue.setIntValue(newImage->create(Param2.getIntValue(), 
												 Param3.getIntValue(), 
												 Param4));
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}
	
	returnValue.setReturn(pResult);
}

// ---------------------------------- Image Usage ---------------------------------

void IM_Open_File(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
#if VERSIONMAC
	Param2.convertPath();
#endif	
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
	{
		returnValue.setIntValue(newImage->read(Param2));
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}	
	
	returnValue.setReturn(pResult);
}

void IM_Save_File(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
#if VERSIONMAC
	Param2.convertPath();
#endif	
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
	{
		returnValue.setIntValue(newImage->write(Param2));
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}	
	
	returnValue.setReturn(pResult);
}

void IM_Get_Image_Properties(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT Param2;
	C_TEXT Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
	{
		double para1, para2, para3, para4;
		para1 = para2 = para3 = para4 = 0;
		
		returnValue.setIntValue(newImage->GetProperty(Param2.getIntValue(), 
													  Param3, 
													  para1, 
													  para2, 
													  para3, 
													  para4));

		if(!returnValue.getIntValue())
		{
			Param4.setDoubleValue(para1);			
			Param5.setDoubleValue(para2);		
			Param6.setDoubleValue(para3);	
			Param7.setDoubleValue(para4);
		}

	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}	
	
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
	Param5.toParamAtIndex(pParams, 5);
	Param6.toParamAtIndex(pParams, 6);
	Param7.toParamAtIndex(pParams, 7);
	
	returnValue.setReturn(pResult);
}

void IM_Set_Image_Properties(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT Param2;
	C_TEXT Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
	{		
		returnValue.setIntValue(newImage->SetProperty(Param2.getIntValue(), 
													  Param3, 
													  Param4.getDoubleValue(), 
													  Param5.getDoubleValue(), 
													  Param6.getDoubleValue(), 
													  Param7.getDoubleValue()));
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}
	
	returnValue.setReturn(pResult);
}

void IM_Modify_Image(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT Param2;
	C_TEXT Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	C_REAL Param8;
	C_REAL Param9;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	Param8.fromParamAtIndex(pParams, 8);
	Param9.fromParamAtIndex(pParams, 9);
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
	{		
		returnValue.setIntValue(newImage->ModifyImage(Param2.getIntValue(), 
													  Param3, 
													  Param4.getDoubleValue(), 
													  Param5.getDoubleValue(), 
													  Param6.getDoubleValue(), 
													  Param7.getDoubleValue(),
													  Param8.getDoubleValue(),
													  Param9.getDoubleValue()));
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}
	
	returnValue.setReturn(pResult);
}

void IM_Open_Blob(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_BLOB Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
	{
		returnValue.setIntValue(newImage->read(Param2));
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}	
	
	returnValue.setReturn(pResult);
}

void IM_Save_Blob(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_BLOB Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
	{
		returnValue.setIntValue(newImage->write(Param2));
		
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}	
	
	Param2.toParamAtIndex(pParams, 2);
	returnValue.setReturn(pResult);
}

void IM_Draw(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT Param2;
	C_TEXT Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	C_REAL Param8;
	C_REAL Param9;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	Param8.fromParamAtIndex(pParams, 8);
	Param9.fromParamAtIndex(pParams, 9);
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
	{		
		returnValue.setIntValue(newImage->Draw(Param2.getIntValue(), 
											   Param3,
											   Param4.getDoubleValue(), 
											   Param5.getDoubleValue(), 
											   Param6.getDoubleValue(), 
											   Param7.getDoubleValue(),
											   Param8.getDoubleValue(),
											   Param9.getDoubleValue()));
	}else{
		returnValue.setIntValue(ImageMagickErrorUnknownObject);	
	}
	
	returnValue.setReturn(pResult);
}

// ----------------------------------- Utilities ----------------------------------


void IM_Get_Last_Error(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	IMImage2 *newImage = _objectGet(Param1.getIntValue());
	
	if(newImage)
		newImage->GetLastError(returnValue);
	
	returnValue.setReturn(pResult);
}
	   
void IM_Get_Format_List(sLONG_PTR *pResult, PackagePtr pParams)
{
	ARRAY_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param1.setSize(1);
	
	std::list<Magick::CoderInfo> coderList;
	
	Magick::coderInfoList( &coderList,				// Reference to output list
				  Magick::CoderInfo::TrueMatch,		// Match readable formats
				  Magick::CoderInfo::AnyMatch,		// Don't care about writable formats
				  Magick::CoderInfo::AnyMatch);		// Don't care about multi-frame support
	
	std::list<Magick::CoderInfo>::iterator entry = coderList.begin(); 
	
	std::string formatdesc;
	
	while(entry != coderList.end()) 
	{
		formatdesc = entry->name() + " (" + entry->description() + ") ";
		
		if (entry->isReadable())
			formatdesc += "r";
		else
			formatdesc += " ";
		if (entry->isWritable())
			formatdesc += "w";
		else
			formatdesc += " ";
		if (entry->isMultiFrame())
			formatdesc += "m";
		else
			formatdesc += " ";
		
		Param1.appendUTF8String((const uint8_t *)formatdesc.c_str(), formatdesc.size());
		
		entry ++;
	}
	
	Param1.toParamAtIndex(pParams, 1);
	returnValue.setReturn(pResult);
}
