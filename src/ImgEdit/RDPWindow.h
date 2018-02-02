/*
 * RDPWindow.h
 *
 *  Created on: 13 nov. 2017
 *      Author: anael
 */

#ifndef RDPWINDOW_H_
#define RDPWINDOW_H_

#include "wx/wx.h"
#include "ImageWindow.h"
#include "../General/ActionsList.h"
#include "../General/ActionsHolder.h"
#include <wx/sizer.h>
#include "../CustomWindow.h"
#include "../General/WindowType.h"
#include "ScrolledList.h"
#include <vector>
#include <functional>
#include <string>
#include "../process/image_processing.h"
#include <experimental/filesystem>
#include <future>
#include <thread>

class RDPWindow: public CustomWindow {

public:
    RDPWindow(wxWindow* parent);
    std::string askJPG();
    void displayContextualHelp() override;
    void keyPressed(wxKeyEvent& event);
    void pickImage();
    void addImage(std::string imPath);
    void addImage(std::vector<std::string> imPath);
    void backHome();
    void makeTuple();
    bool isAllowedToClose();
    void checkSelected(); //Processes and updates the number of selected images
    std::vector<std::pair<std::string, std::string>> setActionsHolder()
            override;
    std::vector<std::vector<int>> countBC();
    void featuresEnhancement();
    std::vector<ImageWindow> getSelectedImg();

    //Test function
    static bool returnTrue() {
        return true;
    }
;
    //TODO: add one "Make Tuple" method that puts selected images in a common set for quicker transformations involving this set of images
//TODO: add one pickImage method that takes a path as parameter, to be called after an image processing so that it can be displayed in application
    //TODO : add methods for adding selected images to report
    //TODO : add preview report method and edit report text method
private:
    bool shouldNotclose;
    wxBoxSizer* controlSizer;
    ImageWindow* iW;
    ScrolledList* iL;
    std::vector<ImageWindow*> SelectedImageWindows;
};


#endif /* RDPWINDOW_H_ */
