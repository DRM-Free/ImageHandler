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
    aH = new std::vector<ActionsHolder>;
    escapeKey = WXK_ESCAPE;
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

void CustomWindow::addPreferredKey(char c) {
    preferredKeys.push_back(std::pair<char, bool>(c, false));

}

/**
 * tries to find a non allocated key in preferredKeys. If found, marks the said key as allocated and gives the key to allocate
 * @return a yet not allocated key
 */
char CustomWindow::requestKey() {
    for (auto it = preferredKeys.begin(); it != preferredKeys.end(); ++it) {
        if ((*it).second == false)
            (*it).second = true;
        return (*it).first;
    }
    return '\0';
}

void CustomWindow::freeKey(char c) {
    for (auto it = preferredKeys.begin(); it != preferredKeys.end(); ++it) {
        if ((*it).first == c) {
            (*it).second = false;
        }
    }
}

CustomWindow::~CustomWindow() {

}
