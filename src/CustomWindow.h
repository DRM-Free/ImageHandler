/*
 * CustomWindow.h
 *
 *  Created on: 13 nov. 2017
 *      Author: anael
 */

#ifndef CUSTOMWINDOW_H_
#define CUSTOMWINDOW_H_

#include "wx/wx.h"
#include "General/ActionsList.h"
#include "General/ActionsHolder.h"
#include "tools/Observed.hpp"
#include <vector>
#include "General/ActionsHolder.h"
#include <functional>

class CustomWindow: public wxFrame, public Observed {

public:
    CustomWindow(wxWindow* parent, WindowType winType, char const * name);
//SEE Virtual method must be implemented in child class
    virtual void displayContextualHelp() =0;
    virtual void keyPressed(wxKeyEvent& event) =0;
    virtual void setActionsHolder() =0;
    ActionsList* getAL();
    ~CustomWindow();

    //new member functions
    char requestKey();
    void freeKey(char);
    void addPreferredKey(char c);
private:
protected:
    wxWindow* actionWindow;
    wxListCtrl actionsCtrl;
    ActionsList* aL;
    wxBoxSizer *mainSizer; //For welcome window only
    WindowType wT;

    //New members
    std::vector<std::pair<char, bool>> preferredKeys;
    std::vector<ActionsHolder>* aH;
    char escapeKey;

};

#endif /* CUSTOMWINDOW_H_ */
