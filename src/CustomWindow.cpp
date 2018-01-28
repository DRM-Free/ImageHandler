/*
 * CustomWindow.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */

#include "CustomWindow.h"

CustomWindow::CustomWindow(wxWindow* parent, WindowType winType,
        char const * name) :
        wxFrame(parent, -1, name, wxDefaultPosition, wxDefaultSize,
        wxSTAY_ON_TOP) {
    //Initialisations
//    actionWindow = new wxWindow(this, wxID_ANY);
    aL = new ActionsList(this);
    escapeKey = WXK_ESCAPE;
    wT = winType;
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    //Initialisations

    //Mise en page

//    mainSizer->Add(actionWindow);
//    SetSizerAndFit(mainSizer);
    Centre();
    //Mise en page

    aL->SetFocus(); //Gives focus to aL, so user doesn't have to first click home window
    setPreferredKeys();
}

CustomWindow::~CustomWindow() {

}

void CustomWindow::setPreferredKeys() {
    addPreferredKey('j');
    addPreferredKey('k');
    addPreferredKey('l');
    addPreferredKey('m');
    addPreferredKey('n');
    addPreferredKey('b');
    addPreferredKey('o');
    addPreferredKey('p');
    addPreferredKey('h');
}

void CustomWindow::keyPressed(wxKeyEvent& event) {
    wxChar pressedKey = event.GetUnicodeKey();
    if (pressedKey != WXK_NONE) {
        doAction(pressedKey);
    }

}

void CustomWindow::addPreferredKey(char c) {
    preferredKeys.push_back(std::pair<char, bool>(c, true));
}

std::vector<std::pair<std::string, std::string>> CustomWindow::updateActionsHolder() {
    std::vector<std::pair<std::string, std::string>> actionsL;
    for (auto it = aH.begin(); it != aH.end(); ++it) {
        if ((*it).checkActive() && (*it).getKey() == '\0') {
            char key = requestKey();
            (*it).setKey(key);
        } else if ((!(*it).checkActive()) && (*it).getKey() != '\0') {
            freeKey((*it).getKey());
            (*it).setKey('\0');
        }

        actionsL.push_back((*it).generateActionLabels());
    }
    return actionsL;
}

void CustomWindow::setActionsList() {
    aL->setList(setActionsHolder());
}

void CustomWindow::updateActionsList() {
    aL->resetList(setActionsHolder());
}

/**
 * tries to find a non allocated key in preferredKeys. If found, marks the said key as allocated and gives the key to allocate
 * @return a yet not allocated key
 */
char CustomWindow::requestKey() {
    for (auto it = preferredKeys.begin(); it != preferredKeys.end(); ++it) {
        if ((*it).second == true) {
            (*it).second = false;
            return (*it).first;
        }
    }
    std::cerr << "Unable to allocate keyboard key : no more free keys !\n";
    return '\0';
}

void CustomWindow::freeKey(char c) {
    for (auto it = preferredKeys.begin(); it != preferredKeys.end(); ++it) {
        if ((*it).first == c) {
            (*it).second = false;
        }
    }
}

void CustomWindow::doAction(char c) {
    for (auto it = aH.begin(); it != aH.end(); ++it) {
        if ((*it).getKey() == c) {
            (*it).doBehaviour();
        }
    }
}

ActionsList* CustomWindow::getAl() {
    return aL;
}
