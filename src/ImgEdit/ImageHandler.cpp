/*
 * ImagesHandler.cpp
 *
 *  Created on: 15 déc. 2017
 *      Author: anael
 */

#include "ImageHandler.h"

ImageHandler::ImageHandler(wxBitmap* bitmap, std::string* imPath) {
    this->bitmap = bitmap;
    this->imPath = imPath;
}

ImageHandler::~ImageHandler() {
}

