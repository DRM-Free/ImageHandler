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

class RDPWindow: public CustomWindow {

public:
    RDPWindow(wxWindow* parent);
    std::string askJPG();
    void displayContextualHelp() override;
    void keyPressed(wxKeyEvent& event);
    void pickImage();
    void backHome();
    bool isAllowedToClose();
    void checkSelected(); //Processes and updates the number of selected images
    std::vector<std::pair<std::string, std::string>> setActionsHolder()
            override;
    void processImage();
    std::vector<ImageWindow> getSelectedImg();

    //Test function
    static bool returnTrue() {
        return true;
    }
;
    //TODO: add one "Make Tuple" method that puts selected images in a common set for quicker transformations involving this set of images
private:
    bool shouldNotclose;
    wxBoxSizer* controlSizer;
    ImageWindow* iW;
    ScrolledList* iL;
    std::vector<ImageWindow*> SelectedImageWindows;
};


#endif /* RDPWINDOW_H_ */
