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

void ScrolledIconsList::appendImageWindows(ImageWindow const& window) {
    ImageWindow* reducedWindow = new ImageWindow(this, window.getImPath());
    reducedWindow->iconize();
    imageWindows.push_back(reducedWindow);
//    reducedWindow->SetMinClientSize(wxSize(280, 280));
    reducedWindow->addObserver(dynamic_cast<ScrolledList*>(GetParent()));
    sizer->Add(reducedWindow, 1, wxALL, 10);

    FitInside();
    setScrolls();
}


void ScrolledIconsList::setScrolls() {
    int* x = new int;
    int* y = new int;
    GetSize(x, y);
    SetScrollbars(1, 1, *x + 5, 0, 300, 0);
    std::cout << "scrollWidth set to " << *x + 5 << std::endl;
}


ScrolledIconsList::~ScrolledIconsList() {

}
