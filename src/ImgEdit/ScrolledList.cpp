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
    SetScrollbars(1, 1, 500, 500, 0, 0);

    SetSizer(sizer);
}

void ScrolledList::addScrolledIconsList(ScrolledIconsList* list) {
    scrolledIconsLists->push_back(list);
    sizer->Add(list, 1, wxEXPAND);
    int scrollHeight = (scrolledIconsLists->size()) * 280 + 10;
    std::cout << "scrollHeight set to " << scrollHeight << std::endl;
    SetScrollbars(0, 1, 0, scrollHeight, 0, 0);

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
    }
    while (it != scrolledIconsLists->end()) {
        ++it;
        std::vector<wxBitmap*> toMerge = *(*it)->getSelectedBitmaps();
        selectedBitmaps->reserve(selectedBitmaps->size() + toMerge.size()); // preallocate memory
        selectedBitmaps->insert(selectedBitmaps->end(), toMerge.begin(),
                toMerge.end());
    }
}

int ScrolledList::numberSelected() {
    return selectedBitmaps->size();
}

ScrolledList::~ScrolledList() {
}

