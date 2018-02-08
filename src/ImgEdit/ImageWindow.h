/*
 * ScrolledImageComponent.cpp
 *
 *  Created on: 21 oct. 2017
 *      Author: anael
 */
#ifndef SCROLLED_IMAGE_COMPONENT
#define SCROLLED_IMAGE_COMPONENT

#include "wx/wx.h"
#include <iostream>

#include "../General/WindowType.h"
#include "../CustomWindow.h"
#include "../tools/Observed.hpp"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


//SEE Setting "Observed" inheritances public is important so that observer can call Observed methods
class ImageWindow: public wxScrolledWindow, public Observed {

private:
    wxBitmap bitmap;
    fs::path imPath; //Path to the original image, for processing purpose
    bool selected;
    bool selectible;

public:
    ImageWindow(wxWindow* parent, fs::path path = "");
    ~ImageWindow();
    void OnDraw(wxDC& dc) override;
    void switchSelected();
    void forbidSelection();
    void iconize(wxSize size = wxSize(280, 280));
    void setBitmap(fs::path path);
    bool hasImage() const;
    fs::path getImPath() const;
    bool isSelected() const;
};
#endif
