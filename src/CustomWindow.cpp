/*
 * CustomWindow.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */


#include "CustomWindow.h"


CustomWindow::CustomWindow(wxWindow* parent, WindowType winType,
        char const * name) :
        wxFrame(parent, -1, name,
                wxDefaultPosition, wxDefaultSize,
        wxSTAY_ON_TOP) {
    wT = winType;
    actionWindow = new wxWindow(this, wxID_ANY);
    aL = new ActionsList(actionWindow);
    aL->setList(wT);
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(actionWindow);
    SetSizerAndFit (mainSizer);
}

ActionsList* CustomWindow::getAL() {
    return aL;
}

CustomWindow::~CustomWindow() {

}
