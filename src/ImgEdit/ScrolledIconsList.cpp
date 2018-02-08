/*
 * ScrolledIconsList.cpp
 *
 *  Created on: 18 nov. 2017
 *      Author: anael
 */

#include "ScrolledIconsList.h"
#include "ScrolledList.h"
#include <string>
#include "../tools/Observed.hpp"
#include <iostream>

ScrolledIconsList::ScrolledIconsList(wxWindow* parent) :
        wxScrolledWindow(parent, wxID_ANY) {

    sizer = new wxBoxSizer(wxHORIZONTAL);
    SetMinClientSize(wxSize(300, 300));
    SetSizer(sizer);

}

/**
 *
 * @param imPath is a path to image or image folder
 */
void ScrolledIconsList::appendImageWindows(fs::path const& imPath) {
    //TEST icons creation is shunted
    if (imPath.has_extension()) {
//    if (false) {
    ImageWindow* reducedWindow = new ImageWindow(this, imPath);
    reducedWindow->iconize();
    imageWindows.push_back(reducedWindow);
//    reducedWindow->SetMinClientSize(wxSize(280, 280));
    reducedWindow->addObserver(dynamic_cast<ScrolledList*>(GetParent()));
    sizer->Add(reducedWindow, 1, wxALL, 10);
    }

    else {
        //FIXME In this case, images are not created properly
        for (auto &it : fs::directory_iterator(imPath)) {
            ImageWindow* reducedWindow = new ImageWindow(this, it);
            reducedWindow->iconize();
            imageWindows.push_back(reducedWindow);
            //    reducedWindow->SetMinClientSize(wxSize(280, 280));
            reducedWindow->addObserver(
                    dynamic_cast<ScrolledList*>(GetParent()));
            sizer->Add(reducedWindow, 1, wxALL, 10);
        }
    }
    FitInside();
    setScrolls();
}

//void appendImageWindows(fs::path path) {
//
//}


void ScrolledIconsList::setScrolls() {
    int* x = new int;
    int* y = new int;
    GetSize(x, y);
    SetScrollbars(1, 1, *x + 5, 0, 300, 0);
}


ScrolledIconsList::~ScrolledIconsList() {

}

//void ScrolledIconsList::appendImageWindows(fs::path path) {
//}
