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

class RDPWindow: public CustomWindow {

public:
    //TODO Change what actions are available depending on what number of images is selected (no image selected / one or more...)
    RDPWindow(wxWindow* parent);
    void displayContextualHelp() override;
    void keyPressed(wxKeyEvent& event) override;
    void setActionsHolder() override;
    void pickImage();
    void resumeImage(wxBitmap* bitmap);
    void backHome();
    void clearSelected();
    bool isAllowedToClose();
    void checkSelected(); //Processes and updates the number of selected images
    void updateActionsList();
    void updateActionsHolder();


    //Test function
    static bool returnTrue() {
        return true;
    }
;
    //TODO: display different kind of processing options depending on which images are selected
    //TODO: add one "Make Tuple" method that puts selected images in a common set for quicker transformations involving this set of images
private:
    bool shouldNotclose;
    int selectedImages;
    ImageWindow *iW;
    ScrolledList *iL;
    wxBoxSizer *controlSizer;
    std::vector<ImageWindow*> *SelectedImageWindows;
};


#endif /* RDPWINDOW_H_ */
