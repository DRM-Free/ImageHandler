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

//SEE Setting "Observed" inheritances public is important so that observer can call Observed methods
class ImageWindow: public wxScrolledWindow, public Observed {

private:
    wxBitmap* bitmap;
    int w, h;
    int minWidth = 600;
    int minwHeight = 600;
    bool isSelected;
    bool isSelectible;

public:
    ImageWindow(wxWindow* parent, wxSize const & minSize);
    ~ImageWindow();
    void OnDraw(wxDC& dc) override;
    void keyPressed(wxKeyEvent& event);
    wxSize setBitMap();
    wxSize setBitMap(wxString);
    wxSize copyBitMap(wxBitmap*);
    wxSize getSize();
    wxBitmap* getBitmap();
    void switchSelected(wxMouseEvent& event);
    void forbidSelection();
//    void OnSize(wxSizeEvent& event);
};
#endif
