/*
 * HomeWindow.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */


#include "HomeWindow.h"
#include "Report/ReportWindow.h"

HomeWindow::HomeWindow() :
        CustomWindow(((wxFrame *) NULL), WindowType::HOME_WINDOW,
                "Home Window") {
    actionWindow = new wxWindow(this, wxID_ANY);
    aL = new ActionsList(actionWindow);
    setActionsList();
    aL->Bind(wxEVT_CHAR, &HomeWindow::keyPressed, this);
    aL->SetFocus(); //Gives focus to aL, so user doesn't have to first click home window
    Centre();
}

/**
 *
 * @return a vector that will be used to fill in the actions list displayed to the user
 * In the mean time, sets the list of actions possible for HomeWindow
 */
std::vector<std::pair<std::string, std::string>> HomeWindow::setActionsHolder() {
    std::vector<std::pair<std::string, std::string>> actionsL;

    actionsL.push_back(std::make_pair("h", "Display contextual help"));
    aH->push_back(
            ActionsHolder(escapeKey, "Display contextual help", [this]()->bool //
                    {
                        return true;
                    }, [this]()
                    {
                        this->displayContextualHelp();
                        /* SEE : Returning any doesn't allow void !! */
                        return 0;
                    }));

    char key = requestKey(); //Request new available keyboard key
    actionsL.push_back(
            std::make_pair(std::any_cast<std::string>(key), "New report"));
    aH->push_back(ActionsHolder(key, "New report", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                ReportWindow *addWindow = new ReportWindow(this);
                setChanged();
                try {
                    notifyObserver(std::string("frameRequest"),
                            dynamic_cast<CustomWindow*>(addWindow));
                } catch (std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
                Hide();
                /* SEE : Returning any doesn't allow void !! */
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key
    actionsL.push_back(
            std::make_pair(std::any_cast<std::string>(key),
                    "Process raw data"));
    aH->push_back(ActionsHolder(key, "Process raw data", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                RDPWindow *addWindow = new RDPWindow(this);
                setChanged();
                try {
                    notifyObserver(std::string("frameRequest"),
                            dynamic_cast<CustomWindow*>(addWindow));
                } catch (std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
                Hide();
                /* SEE : Returning any doesn't allow void !! */
                return 0;
            }));

    return actionsL;
}


void HomeWindow::displayContextualHelp() {
    std::cout << "This helps" << std::endl;
}


HomeWindow::~HomeWindow() {

}
