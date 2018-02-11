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
    std::vector<ScrolledIconsList*> scrolledIconsLists;
//-------------------Constructors
public:
    ScrolledList(wxWindow* parent);
    virtual ~ScrolledList();
    int size();

private:

//-------------------Methods
public:
    void addScrolledIconsList(ScrolledIconsList*);
//  void updateSelectedImageWindows();
    std::vector<ImageWindow*> getSelectedImageWindows() const;
    void clearSelected();

private:
    void setScrolls();

//-------------------Getters&Setters
public:

private:

};

#endif /* SCROLLEDLIST_H_ */
