/*
 * MainFrame.h
 *
 *  Created on: 25 oct. 2017
 *      Author: anael
 */

#ifndef HOMEWINDOW_H_
#define HOMEWINDOW_H_

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
    void displayContextualHelp() override;
    std::vector<std::pair<std::string, std::string>> setActionsHolder()
            override;
    ~HomeWindow();

private:
    WindowType const id = WindowType::HOME_WINDOW;

};



#endif /* HOMEWINDOW_H_ */
