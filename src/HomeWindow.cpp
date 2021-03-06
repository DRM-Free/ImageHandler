/*
 * HomeWindow.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */


#include "HomeWindow.h"
#include "Report/ReportWindow.h"

HomeWindow::HomeWindow() :
        CustomWindow(WindowType::HOME_WINDOW,
                "Home Window") {
//    actionWindow = new wxWindow(this, wxID_ANY);
//    aL = new ActionsList(actionWindow);
    //SEE One can't call pure virtual method in child constructor !
    //setActionsList can't be called right now, as it calls pure virtual method setActionsHolder before creation of the object
//    setActionsList();
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(getAl()->getShownList());
    getAl()->getShownList()->Bind(wxEVT_CHAR, &HomeWindow::keyPressed, this);
}

/**
 *
 * @return a vector that will be used to fill in the actions list displayed to the user
 * In the mean time, sets the list of actions possible for HomeWindow
 */
std::vector<std::pair<std::string, std::string>> HomeWindow::setActionsHolder() {
    std::vector<std::pair<std::string, std::string>> actionsL;

//    actionsL.push_back(std::make_pair("h", "Display contextual help"));
    aH.push_back(
            ActionsHolder(escapeKey, "Quit application", "", [this]()->bool //
                    {
                        return true;
                    }, [this]()
                    {
                this->Close(true);
                        return 0;
                    }));

    char key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "New report", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                setChanged();
                try {
                    notifyObserver(std::string("report"),
                            dynamic_cast<CustomWindow*>(this));
                } catch (std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(
            ActionsHolder(key, "Display contextual help", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                displayContextualHelp();
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Process raw data", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
            setChanged();
            try {
                notifyObserver(std::string("improc"),
                        dynamic_cast<CustomWindow*>(this));
            } catch (std::exception& e) {
                std::cerr << e.what() << '\n';
            }
            return 0;
        }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Browse patient data", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
//                RDPWindow *addWindow = new RDPWindow(this);
                setChanged();
                try {
                notifyObserver(std::string("patientFile"),
                        dynamic_cast<CustomWindow*>(this));
                } catch (std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
                return 0;
            }));



    for (auto it = aH.begin(); it != aH.end(); ++it) {
        actionsL.push_back((*it).generateActionLabels());
    }

    return actionsL;
}


void HomeWindow::displayContextualHelp() {
    std::cout << "This helps" << std::endl;
}


HomeWindow::~HomeWindow() {

}
