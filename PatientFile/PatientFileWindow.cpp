/*
 * PatientFileWindow.cpp
 *
 *  Created on: 7 févr. 2018
 *      Author: anael
 */

#include "PatientFileWindow.h"
#include "LabelledInput.h"

PatientFileWindow::PatientFileWindow() :
        wxFrame(nullptr, -1, "Patient file", wxDefaultPosition, wxDefaultSize,
        wxSTAY_ON_TOP), s1(wxVERTICAL), s2(wxHORIZONTAL), s3(wxVERTICAL), s4(1,
                0, 0), scrolledIcons(
                this, wxID_ANY,
                "Images in patient folder"), actions(this, wxID_ANY,
                "Actions list"), reports(this, wxID_ANY, "Saved reports"), patientInfos(
                this, wxID_ANY, "Patient infos"), patientPhoto(this) {
    scrolledIcons.SetMinSize(wxSize(100, 100));
    actions.SetMinSize(wxSize(100, 100));
    reports.SetMinSize(wxSize(100, 100));
//    patientInfos.SetMinSize(wxSize(300, 100));

    SetSize(wxSize(1500, 800));
    Center();

    SetSizer(&s1, true);
    s1.Add(&s2, 1, wxEXPAND);
    s1.Add(&scrolledIcons, 1, wxEXPAND);

    s2.Add(&s3, 1, wxEXPAND);
    s2.Add(&patientInfos, 1, wxEXPAND);
    s2.Add(&patientPhoto, 2, wxEXPAND);


    s3.Add(&actions, 1, wxEXPAND);
    s3.Add(&reports, 1, wxEXPAND);

    patientInfos.SetSizer(&s4, true);
//    wxStaticText *fn = new wxStaticText(&patientInfos, wxID_ANY,
//            "first name : ");
//    wxStaticText *ln = new wxStaticText(&patientInfos, wxID_ANY,
//            "last name : ");
//    wxStaticText *bd = new wxStaticText(&patientInfos, wxID_ANY,
//            "birth date : ");
//    wxStaticText *id = new wxStaticText(&patientInfos, wxID_ANY,
//            "unique ID : ");
//
//
//    wxTextCtrl *firstName = new wxTextCtrl(&patientInfos, wxID_ANY,
//            "Pierre-Jean", wxDefaultPosition, wxSize(200, 25),
//            wxTE_READONLY);
//    wxTextCtrl *lastName = new wxTextCtrl(&patientInfos, wxID_ANY,
//            "Lartaud",
//            wxDefaultPosition, wxSize(200, 25),
//            wxTE_READONLY);
//    wxTextCtrl *birthDate = new wxTextCtrl(&patientInfos, wxID_ANY,
//            "unknown",
//            wxDefaultPosition, wxSize(200, 25),
//            wxTE_READONLY);
//    wxTextCtrl *uniqueID = new wxTextCtrl(&patientInfos, wxID_ANY,
//            "000000000LOLOLO", wxDefaultPosition, wxSize(200, 25),
//            wxTE_READONLY);
//    s4.Add(fn);
//    s4.Add(firstName);
//    s4.Add(ln);
//    s4.Add(lastName);
//    s4.Add(bd);
//    s4.Add(birthDate);
//    s4.Add(id);
//    s4.Add(uniqueID);

    s4.Add(new LabelledInput(&patientInfos, "first name :", "Pierre-Jean"));
    s4.Add(new LabelledInput(&patientInfos, "last name :", "Lartaud"));
    s4.Add(new LabelledInput(&patientInfos, "birth date:", "Unknown"));
    s4.Add(new LabelledInput(&patientInfos, "unique ID:", "00OLOLO"));
    patientInfos.Fit();

//    wxStaticBox *imagesContour = new wxStaticBox(&scrolledIcons, wxID_ANY,
//            "Patient images");
//    wxBoxSizer *s5 = new wxBoxSizer(wxHORIZONTAL);
//    scrolledIcons.SetSizer(s5, true);
//    s5->Add(imagesContour, wxEXPAND);
//    wxTextCtrl *text = new wxTextCtrl(imagesContour, wxID_ANY, "This is text");


}

PatientFileWindow::~PatientFileWindow() {
}

