/*
 * ScrolledList.cpp
 *
 *  Created on: 18 nov. 2017
 *      Author: anael
 */

#include "ScrolledList.h"
#include <algorithm>
#include <iostream>

ScrolledList::ScrolledList(wxWindow* parent) :
        wxScrolledWindow(parent, wxID_ANY) {
    AlwaysShowScrollbars(false, true);
    sizer = new wxBoxSizer(wxVERTICAL);
    SetMinClientSize(wxSize(300, 500));
    SetSizer(sizer);
    setScrolls();

}

/**
 * Adds a new list of images to be displayed in a raw.
 * @param list
 */
void ScrolledList::addScrolledIconsList(ScrolledIconsList* list) {
    scrolledIconsLists.push_back(list);
    sizer->Add(list, 1, wxALIGN_TOP);
    FitInside(); //Forces scrollbar to scroll properly whole range.
    setScrolls();
}

/**
 *
 * @return pointer vecor to all selected bitmaps within sublists
 */
std::vector<ImageWindow*> ScrolledList::getSelectedImageWindows() const {
    std::vector<ImageWindow*> ret;
    for (auto iL : scrolledIconsLists) {
        std::vector<ImageWindow*> const& vecTmp = iL->getSelectedImages();
        ret.insert(ret.end(), vecTmp.begin(), vecTmp.end());
    }
    return ret;
}

void ScrolledList::setScrolls() {
    int x = 0;
    int y = 0;
    GetVirtualSize(&x, &y);
    SetScrollbars(0, 1, 0, y + 5, 0, 0);
}

ScrolledList::~ScrolledList() {
}

void ScrolledList::clearSelected() {
    for (auto iL : scrolledIconsLists) {
        iL->clearSelected();
    }
}

int ScrolledList::size() {
    return scrolledIconsLists.size();
}
