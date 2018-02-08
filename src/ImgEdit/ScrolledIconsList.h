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
#include <experimental/filesystem>


class ScrolledIconsList: public wxScrolledWindow {
//-------------------Attributes
private:
    //Map for quick data retrieval by iW*
    //SEE iWBEB to be removed
    std::vector<ImageWindow*> imageWindows;
    wxBoxSizer *sizer;
//-------------------Constructors
public:
    ScrolledIconsList(wxWindow* parent);
    ~ScrolledIconsList();

private:
//-------------------Methods
public:
    void appendImageWindows(fs::path const& imPath); //adds images from all files in a directory or single file
    void addImageWindowsToSelected(ImageWindow* iW);
    void removeImageWindowsFromSelected(ImageWindow* iW);

private:
    void setScrolls();
//-------------------Getters&Setters
public:

private:

};

#endif /* SCROLLEDICONSLIST_H_ */
