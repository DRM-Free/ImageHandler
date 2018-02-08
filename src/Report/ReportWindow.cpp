/*
 * ReportWIndow.cpp
 *
 *  Created on: 29 nov. 2017
 *      Author: anael
 */

#include "ReportWindow.h"

ReportWindow::ReportWindow() :
        CustomWindow(WindowType::RM, "Raw data processing"), rF(
                new ReportForm(this)), controlSizer(
                new wxBoxSizer(wxVERTICAL)), shouldNotclose {
                false } {
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    setPreferredKeys("jklmopuinbghty");
    rF->setForm();
    wT = WindowType::RM;
    getAl()->getShownList()->Bind(wxEVT_CHAR, &ReportWindow::keyPressed, this);
    controlSizer->Add(getAl()->getShownList());
    mainSizer->Add(controlSizer);
    mainSizer->Add(rF);
    SetSizerAndFit(mainSizer);
}

void ReportWindow::backHome() {
    if (!shouldNotclose) {
        setChanged();
        try {
            notifyObserver(std::string("backHome"),
                    dynamic_cast<CustomWindow*>(this));
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}
void ReportWindow::addReportElement() {

}

void ReportWindow::displayContextualHelp() {

}

void ReportWindow::keyPressed(wxKeyEvent& event) {
    CustomWindow::keyPressed(event);
}

std::vector<std::pair<std::string, std::string>> ReportWindow::setActionsHolder() {
    std::vector<std::pair<std::string, std::string>> actionsL;


    aH.push_back(
            ActionsHolder(escapeKey, "Back Home", [this]()->bool //
                    {
                        return true;
                    }, [this]()
                    {
                backHome();
                        return 0;
                    }));

    char key = requestKey(); //Request new available keyboard key

    aH.push_back(ActionsHolder(key, "Submit report", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                //TODO call submit report
            return 0;
        }));

    key = requestKey(); //Request new available keyboard key

    aH.push_back(ActionsHolder(key, "Display contextual help", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                this->displayContextualHelp();
                return 0;
            }));


    key = requestKey(); //Request new available keyboard key

    aH.push_back(ActionsHolder(key, "Discard report", [this]()->bool //
            {
                return true;
            }, [this]()
            {

                return 0;
        }));
    for (auto it = aH.begin(); it != aH.end(); ++it) {
        actionsL.push_back((*it).generateActionLabels());
    }

//    actionsL.push_back(
//            std::make_pair(std::any_cast<std::string>(key), "Submit report"));
//    actionsL.push_back(
//            std::make_pair(std::any_cast<std::string>(key), "Discard report"));
    return actionsL;
}


ReportWindow::~ReportWindow() {
}

