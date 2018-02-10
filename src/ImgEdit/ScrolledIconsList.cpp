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
        wxScrolledWindow(parent, wxID_ANY, wxPoint(1, 1), wxSize(-1, -1))/*,
         wxBORDER_SIMPLE) */{

    sizer = new wxBoxSizer(wxHORIZONTAL);
    SetMinClientSize(wxSize(300, 300));
    SetSizer(sizer);

    addAction<std::string, ImageWindow*>("select",
            [this](ImageWindow* content, Observed const& observed) -> void
            {
                if (content->isSelected()) {
                    selectedImageWindows.push_back(content);
                } else {
                    selectedImageWindows.erase(std::find(selectedImageWindows.begin(), selectedImageWindows.end(), content));
                }
            });

}

void ScrolledIconsList::appendOneImageWindow(fs::path const & imPath) {
    ImageWindow* reducedWindow = new ImageWindow(this, imPath);
    reducedWindow->iconize(wxSize(280, 280));
    imageWindows.push_back(reducedWindow);
    reducedWindow->addObserver(this);
    sizer->Add(reducedWindow, 1, wxALL, 10);
}

/**
 *
 * @param imPath is a path to image or image folder
 */
void ScrolledIconsList::appendImageWindows(fs::path const& imPath) {
    if (imPath.has_extension()) {
//    if (false) {
        appendOneImageWindow(imPath);
    }

    else {
        for (auto &it : fs::directory_iterator(imPath)) {
            appendOneImageWindow(it);
        }
    }
    FitInside();
    setScrolls();
}

void ScrolledIconsList::clearSelected() {
    while (!selectedImageWindows.empty()) {
        selectedImageWindows.back()->switchSelected();
        selectedImageWindows.pop_back();
    }
}




void ScrolledIconsList::setScrolls() {
    int* x = new int;
    int* y = new int;
    GetSize(x, y);
    SetScrollbars(1, 1, *x + 5, 0, 300, 0);
}


ScrolledIconsList::~ScrolledIconsList() {

}

std::vector<ImageWindow*> const& ScrolledIconsList::getSelectedImages() const {
    return selectedImageWindows;
}
