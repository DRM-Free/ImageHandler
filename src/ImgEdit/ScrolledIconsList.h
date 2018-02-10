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

class ScrolledIconsList: public wxScrolledWindow, public Observer {
//-------------------Attributes
private:
    //Map for quick data retrieval by iW*
    //SEE iWBEB to be removed
    std::vector<ImageWindow*> imageWindows;
    std::vector<ImageWindow*> selectedImageWindows;
    wxBoxSizer *sizer;
//-------------------Constructors
public:
    ScrolledIconsList(wxWindow* parent);
    ~ScrolledIconsList();

private:
//-------------------Methods
public:
    void appendImageWindows(fs::path const& imPath); //adds images from all files in a directory or single file
    void appendOneImageWindow(fs::path const& imPath);
    void addImageWindowsToSelected(ImageWindow* iW);
    void removeImageWindowsFromSelected(ImageWindow* iW);
    void reset(); //clears all children
    std::vector<ImageWindow*> const& getSelectedImages() const;
    void clearSelected();
private:
    void setScrolls();
//-------------------Getters&Setters
public:
    ImageWindow* getLastImageWindow();
private:

};

#endif /* SCROLLEDICONSLIST_H_ */
