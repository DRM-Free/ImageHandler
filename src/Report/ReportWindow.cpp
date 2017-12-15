/*
 * ReportWIndow.cpp
 *
 *  Created on: 29 nov. 2017
 *      Author: anael
 */

#include "ReportWindow.h"

ReportWindow::ReportWindow(wxWindow* parent) :
        CustomWindow(parent, WindowType::RM, "Raw data processing"), shouldNotclose {
                false } {
    setPreferredKeys();
    setActionsList();
    rF = new ReportForm(this);
    rF->setForm();
    wT = WindowType::RM;
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer = new wxBoxSizer(wxVERTICAL);
    aL = new ActionsList(this);
    aL->Bind(wxEVT_CHAR, &ReportWindow::keyPressed, this);
    aL->SetFocus();
    controlSizer->Add(aL);
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
        Hide();
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

    aH->push_back(ActionsHolder(escapeKey, "Submit report", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                //TODO call submit report
            return 0;
        }));

    key = requestKey(); //Request new available keyboard key

    aH->push_back(ActionsHolder(escapeKey, "Discard report", [this]()->bool //
            {
                return true;
            }, [this]()
            {
//TODO call discard report
            return 0;
        }));
    for (auto it = aH->begin(); it != aH->end(); ++it) {
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

