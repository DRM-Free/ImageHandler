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
    RDPWindow();
    std::string askJPG();
    void displayContextualHelp() override;
    void keyPressed(wxKeyEvent& event);
    void pickImage();
    void addImage(std::string imPath);
    void addImage(std::vector<std::string> const& imPath);
    void backHome();
    void makeTuple();
    bool isAllowedToClose();
    void checkSelected(); //Processes and updates the number of selected images
    std::vector<std::pair<std::string, std::string>> setActionsHolder()
            override;
    std::vector<std::vector<int>> countBC();
    void featuresEnhancement();
    std::vector<ImageWindow> getSelectedImg();
;
    //TODO : add methods for adding selected images to report
private:
    bool shouldNotclose;
    wxBoxSizer* controlSizer;
    ImageWindow* iW;
    ScrolledList* iL;
    wxBoxSizer* mainSizer;
    wxStaticBox actions;

};


#endif /* RDPWINDOW_H_ */
