/*
 * ScrolledList.h
 *
 *  Created on: 18 nov. 2017
 *      Author: anael
 */

#ifndef SCROLLEDLIST_H_
#define SCROLLEDLIST_H_

#include "wx/wx.h"
#include "ScrolledIconsList.h"
#include <vector>

class ScrolledList: public wxScrolledWindow {
//-------------------Attributes
private:
    wxBoxSizer *sizer;
    std::vector<ScrolledIconsList*> *scrolledIconsLists;
    std::vector<wxBitmap*>* selectedBitmaps;
//-------------------Constructors
public:
    ScrolledList(wxWindow* parent);
    void addScrolledIconsList(ScrolledIconsList*);
    void updateSelectedBitmaps();
    std::vector<wxBitmap*>* getSelectedBitmaps();
    int numberSelected();
    virtual ~ScrolledList();

private:

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* SCROLLEDLIST_H_ */
