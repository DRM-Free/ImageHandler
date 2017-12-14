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
#include <map>
#include <functional>

class CustomWindow: public wxFrame, public Observed {

    using voidFunction = std::function<void()>;

public:
    CustomWindow(wxWindow* parent, WindowType winType, char const * name);
//SEE Virtual method must be implemented in child class
    virtual void displayContextualHelp() =0;
    virtual void keyPressed(wxKeyEvent& event) =0;
    virtual void setActionsHolder() =0;
    ActionsList* getAL();
    ~CustomWindow();

    //new member functions
    void addAction(voidFunction func, ActionsHolder act);
private:
protected:
    wxWindow* actionWindow;
    wxListCtrl actionsCtrl;
    ActionsList* aL;
    wxBoxSizer *mainSizer; //For welcome window only
    WindowType wT;

    //New members
    std::vector<char> preferredKeys;
    char escapeKey;
    /**
     * actions will contain associations between member methods and associated ActionHolder
     * which includes keyboard key, action description and the activation function for the said action
     * The function returns void* which is a generic pointer (any return type)
     */
    std::map<voidFunction, ActionsHolder> actions;
    int allocatedKeys;
};

#endif /* CUSTOMWINDOW_H_ */
