/*
 * MainFrame.h
 *
 *  Created on: 25 oct. 2017
 *      Author: anael
 */

#ifndef HOMEWINDOW_H_
#define HOMEWINDOW_H_


//#include <stddef.h>
//#include <wx/chartype.h>
//#include <wx/containr.h>
//#include <wx/defs.h>
//#include <wx/event.h>
//#include <wx/gdicmn.h>
//#include <wx/gtk/frame.h>
#include <iostream>
#include <wx/wx.h>
#include "ImgEdit/ImageWindow.h"
#include "General/WindowType.h"
#include "CustomWindow.h"
#include "General/ActionsList.h"
#include "ImgEdit/RDPWindow.h"


class HomeWindow: public CustomWindow {
public:
    HomeWindow();
    ~HomeWindow();
    void displayContextualHelp() override;
    void keyPressed(wxKeyEvent& event) override;
    void setActionsHolder() override;
private:
    WindowType const id = WindowType::HOME_WINDOW;
//    wxFlexGridSizer *mainSizer; //For welcome window only

};



#endif /* HOMEWINDOW_H_ */
