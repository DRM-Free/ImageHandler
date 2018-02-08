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
#include <utility>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class CustomWindow: public wxFrame, public Observed {

public:
    CustomWindow(WindowType winType, char const * name);
//SEE Virtual method must be implemented in child class
    virtual void displayContextualHelp() =0;
    void keyPressed(wxKeyEvent& event);
    void addPreferredKey(char c);
    char requestKey();
    void freeKey(char);
    virtual std::vector<std::pair<std::string, std::string>> setActionsHolder() =0;
    std::vector<std::pair<std::string, std::string>> updateActionsHolder();
    void setActionsList();
    void updateActionsList(); //This calls updateActionsHolder by itself
    void doAction(char c);
    void setPreferredKeys(std::string keys);
    virtual ~CustomWindow();
    void setFocus();

private:
//    wxWindow* actionWindow;
    ActionsList* aL;
protected:
    ActionsList* getAl();

    //SEE no attribute should be protected nor public
//    wxListCtrl* actionsCtrl;
    WindowType wT;
    std::vector<std::pair<char, bool>> preferredKeys; //bool true if key is available
    std::vector<ActionsHolder> aH;
    char escapeKey;

    //Getters and setters
public:
};

#endif /* CUSTOMWINDOW_H_ */
