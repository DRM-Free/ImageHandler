/*
 * ScrolledList.cpp
 *
 *  Created on: 18 nov. 2017
 *      Author: anael
 */

#include "ScrolledList.h"
#include <iostream>

ScrolledList::ScrolledList(wxWindow* parent) :
        wxScrolledWindow(parent, wxID_ANY) {
    selectedBitmaps = new std::vector<wxBitmap*>;
    AlwaysShowScrollbars(false, true);
    sizer = new wxBoxSizer(wxVERTICAL);
    scrolledIconsLists = new std::vector<ScrolledIconsList*>;
    SetMinClientSize(wxSize(300, 500));
    SetSizer(sizer);
    int* x = new int;
    int* y = new int;
    GetSize(x, y);
    SetScrollbars(0, 1, 0, *y + 5, 0, 0);
}

void ScrolledList::addScrolledIconsList(ScrolledIconsList* list) {
    scrolledIconsLists->push_back(list);
    sizer->Add(list, 1, wxEXPAND);
    int* x = new int;
    int* y = new int;
    GetSize(x, y);
    std::cout << "scrollHeight set to " << *y + 5 << std::endl;
    SetScrollbars(0, 1, 0, *y + 5, 0, 0);
    Refresh();
}

/**
 *
 * @return pointer vecor to all selected bitmaps within sublists
 */
std::vector<wxBitmap*>* ScrolledList::getSelectedBitmaps() {
    return selectedBitmaps;
}

void ScrolledList::updateSelectedBitmaps() {
    auto it = scrolledIconsLists->begin();
    if (it != scrolledIconsLists->end()) {
        *selectedBitmaps = *(*it)->getSelectedBitmaps();
        std::vector<wxBitmap*> toMerge = *(*it)->getSelectedBitmaps();
    while (it != scrolledIconsLists->end()) {
        ++it;
        selectedBitmaps->reserve(selectedBitmaps->size() + toMerge.size()); // preallocate memory
        selectedBitmaps->insert(selectedBitmaps->end(), toMerge.begin(),
                toMerge.end());
    }
    }
}

int ScrolledList::numberSelected() {
    updateSelectedBitmaps();
    return selectedBitmaps->size();
}

ScrolledList::~ScrolledList() {
}

