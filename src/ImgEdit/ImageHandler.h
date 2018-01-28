/*
 * ImagesHandler.h
 *
 *  Created on: 15 déc. 2017
 *      Author: anael
 */

#ifndef IMAGEHANDLER_H_
#define IMAGEHANDLER_H_

#include "wx/wx.h"
#include <string>

//This class is meant to keep track of the path of an image associated to a bitmap for further processing
class ImageHandler {
//-------------------Attributes
private:
    wxBitmap* bitmap;
    std::string* imPath;
//-------------------Constructors
public:
    ImageHandler(wxBitmap* bitmap, std::string* imPath);
    virtual ~ImageHandler();

private:

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* IMAGEHANDLER_H_ */
