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
    rF = new ReportForm(this);
    rF->setForm();
    wT = WindowType::RM;
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer = new wxBoxSizer(wxVERTICAL);
    aL = new ActionsList(this);
    aL->setList(wT);
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
    wxChar pressedKey = event.GetUnicodeKey();

    if (pressedKey != WXK_NONE) {

        if (pressedKey >= 32) {
            if (pressedKey == 'l') {
                addReportElement();
            }
        }
        if (pressedKey == WXK_ESCAPE) {
            backHome();
        }
    }
}

void ReportWindow::setActionsHolder() {

}


ReportWindow::~ReportWindow() {
}

