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
    void keyPressed(wxKeyEvent& event);
    void addPreferredKey(char c);
    char requestKey();
    void freeKey(char);
    virtual std::vector<std::pair<std::string, std::string>> setActionsHolder() =0;
    void setActionsList();
    void updateActionsList(); //This calls updateActionsHolder by itself
    void doAction(char c);
    ~CustomWindow();
private:
protected:
    wxWindow* actionWindow;
    wxListCtrl actionsCtrl;
    ActionsList* aL;
    wxBoxSizer *mainSizer; //For welcome window only
    WindowType wT;
    std::vector<std::pair<char, bool>> preferredKeys;
    std::vector<ActionsHolder>* aH;
    char escapeKey;

    //Getters and setters
public:
    ActionsList* getAL();
};

#endif /* CUSTOMWINDOW_H_ */
