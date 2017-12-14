/*
 * ReportForm.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */


#include "ReportForm.h"

ReportForm::ReportForm(wxWindow* parent) :
        wxPanel(parent, wxID_ANY) {
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->SetMinSize(wxSize(400, 600));

    SetSizer(mainSizer);
}
ReportForm::~ReportForm() {

}

void ReportForm::setForm() {
    addReportElement(wxString("Red blood cell count"));
    addReportElement(wxString("White blood cell count"));
    addReportElement(wxString("RBC to all ratio"));

    addCommentArea();
    mainSizer->Layout();
}

void ReportForm::addReportElement(wxString const requestName) {
    wxStaticBoxSizer* reportElementSizer = new wxStaticBoxSizer(wxHORIZONTAL,
            this, requestName);
    mainSizer->Add(reportElementSizer, 1, wxEXPAND);
    wxTextCtrl* inputReportElement = new wxTextCtrl(this, wxID_ANY,
            wxT("Input report element"), wxDefaultPosition, wxDefaultSize,
            wxTE_MULTILINE | wxTE_RICH | wxTE_WORDWRAP, wxDefaultValidator,
            wxTextCtrlNameStr);
    reportElementSizer->Add(inputReportElement, 1, wxEXPAND);
}

void ReportForm::addCommentArea() {
    wxStaticBoxSizer* reportElementSizer = new wxStaticBoxSizer(wxHORIZONTAL,
            this, wxT("Report compents"));
    wxTextCtrl* inputReportComment = new wxTextCtrl(this, wxID_ANY, wxT(""),
            wxDefaultPosition, wxDefaultSize,
            wxTE_MULTILINE | wxTE_RICH | wxTE_WORDWRAP, wxDefaultValidator,
            wxTextCtrlNameStr);
    reportElementSizer->Add(inputReportComment, 1, wxEXPAND);
    mainSizer->Add(reportElementSizer, 1, wxALIGN_CENTRE | wxEXPAND, 2);
}

bool ReportForm::AcceptsFocus() {
    return true;
}
