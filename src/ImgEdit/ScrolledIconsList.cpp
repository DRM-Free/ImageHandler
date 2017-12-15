/*
 * ScrolledIconsList.cpp
 *
 *  Created on: 18 nov. 2017
 *      Author: anael
 */

#include "ScrolledIconsList.h"
#include <string>
#include "../tools/Observed.hpp"
#include <iostream>

ScrolledIconsList::ScrolledIconsList(wxWindow* parent) :
        wxScrolledWindow(parent, wxID_ANY) {
    selectedBitmaps = new std::vector<wxBitmap*>;
    sizer = new wxBoxSizer(wxHORIZONTAL);
    SetMinClientSize(wxSize(280, 280));
    SetSizer(sizer);

    addAction<std::string, ImageWindow*>("selected",
            [this](ImageWindow* content, Observed const& observed) -> void
            {
                auto search = iWBRB.find(content);
                if(search != iWBRB.end()) {
                    //                        std::cout << "Found " << search->first << " " << search->second << '\n';
                    wxBitmap* bitmap= std::get<0>(search->second);
                    addBitmapToSelected(bitmap);
                }
                else {
                    std::cout << "The image you tried to select doesn't appear to belong here anymore !\n";
                }});

    addAction<std::string, ImageWindow*>("unselected",
            [this](ImageWindow* content, Observed const& observed) -> void
            {
                auto search = iWBRB.find(content);
                if(search != iWBRB.end()) {
//                        std::cout << "Found " << search->first << " " << search->second << '\n';
                    wxBitmap* bitmap= std::get<0>(search->second);
                    removeBitmapFromSelected(bitmap);
                }
                else {
                    std::cout << "The image you tried to unselect doesn't appear to belong here anymore !\n";
                }
            });

}

void ScrolledIconsList::appendBitmap(wxBitmap *Bitmap) {
    ImageWindow *iW = new ImageWindow(this, wxSize(280, 280));
    wxBitmap *rBm = new wxBitmap(Bitmap->ConvertToImage().Rescale(280, 280));
    iW->copyBitMap(rBm);
    sizer->Add(iW, 1, wxEXPAND);
    iW->SetMinClientSize(wxSize(280, 280));
    iW->addObserver(this);
    auto tup = std::make_tuple(Bitmap, rBm);
    //SEE Why is it not possible to replace below tuple type with auto ?
    iWBRB.insert(
            std::pair<ImageWindow*, std::tuple<wxBitmap *, wxBitmap *>>(iW,
                    tup)); //false for isSelected

    //Adding another time this image to scrolledIconsList to test scrollbar
    ImageWindow *iW2 = new ImageWindow(this, wxSize(280, 280));

    iW2->copyBitMap(rBm);
    sizer->Add(iW2, 1, wxEXPAND);
    iW2->SetMinClientSize(wxSize(300, 300));
    //End Adding another time this image
//    int scrollWidth = iWBRB.size() * 300 + 5;
//    scrollWidth *= 2; //Because there is twice the same image to fit for testing
    SetMinClientSize(wxSize(300, 300));
    int* x = new int;
    int* y = new int;
    GetSize(x, y);
    std::cout << "scrollWidth set to " << *x + 5 << std::endl;
    SetScrollbars(1, 1, *x + 5, 0, 300, 0);
    Refresh();
}

void ScrolledIconsList::addBitmapToSelected(wxBitmap* bitmap) {
    selectedBitmaps->push_back(bitmap);
}

//SEE In may not be necessary to iterate over the whole selectedBitmaps vector, unless there are duplicates.
void ScrolledIconsList::removeBitmapFromSelected(wxBitmap* bitmap) {
    auto it = selectedBitmaps->begin();
    while (it != selectedBitmaps->end()) {
        if (*it == bitmap) {
            selectedBitmaps->erase(it);
            }
        else
            ++it;
        }
}

std::vector<wxBitmap*>* ScrolledIconsList::getSelectedBitmaps() {
    return selectedBitmaps;
}

int ScrolledIconsList::numberSelected() {
    return selectedBitmaps->size();
}

ScrolledIconsList::~ScrolledIconsList() {

}
