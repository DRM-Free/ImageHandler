/*
 * ScrolledIconsList.h
 *
 *  Created on: 18 nov. 2017
 *      Author: anael
 */

#ifndef SCROLLEDICONSLIST_H_
#define SCROLLEDICONSLIST_H_

#include "wx/wx.h"
#include "ImageWindow.h"
#include <vector>
#include <tuple>
#include "../tools/Observer.hpp"
#include <map>

class ScrolledIconsList: public wxScrolledWindow, Observer {
//-------------------Attributes
private:
    //Map for quick data retrieval by iW*
    std::map<ImageWindow*, std::tuple<wxBitmap*, wxBitmap*>> iWBRB; //Image Window Bitmap Reduced Bitmap
    std::vector<wxBitmap*>* selectedBitmaps;
    wxBoxSizer *sizer;
//-------------------Constructors
public:
    ScrolledIconsList(wxWindow* parent);
    void appendBitmap(wxBitmap *BitMap);
    std::vector<wxBitmap*>* getSelectedBitmaps();
    void addBitmapToSelected(wxBitmap*);
    void removeBitmapFromSelected(wxBitmap*);
    int numberSelected();
    ~ScrolledIconsList();

private:
//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* SCROLLEDICONSLIST_H_ */
