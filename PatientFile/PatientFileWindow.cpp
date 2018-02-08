/*
 * PatientFileWindow.cpp
 *
 *  Created on: 7 févr. 2018
 *      Author: anael
 */

#include "PatientFileWindow.h"
#include "LabelledInput.h"
#include "../src/General/WindowType.h"

PatientFileWindow::PatientFileWindow() :
        CustomWindow(nullptr, WindowType::PATIENT_MANAGER, "Patient manager"), s1(
                wxVERTICAL), s2(wxHORIZONTAL), s3(wxVERTICAL), s4(1,
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

    s4.Add(new LabelledInput(&patientInfos, "first name :", "Pierre-Jean"));
    s4.Add(new LabelledInput(&patientInfos, "last name :", "Lartaud"));
    s4.Add(new LabelledInput(&patientInfos, "birth date:", "Unknown"));
    s4.Add(new LabelledInput(&patientInfos, "unique ID:", "00OLOLO"));
    patientInfos.Fit();


}

PatientFileWindow::~PatientFileWindow() {
}

void PatientFileWindow::displayContextualHelp() {
}

std::vector<std::pair<std::string, std::string>> PatientFileWindow::setActionsHolder() {
    std::vector<std::pair<std::string, std::string>> actionsL;

    aH.push_back(ActionsHolder(escapeKey, "Back Home", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                backHome();
                /* SEE : Returning any doesn't allow void !! */
                return 0;
            }));

    char key = requestKey(); //Request new available keyboard key

    aH.push_back(ActionsHolder(key, "new report", [this]()->bool //
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
                /* SEE : Returning any doesn't allow void !! */
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key

    aH.push_back(ActionsHolder(key, "Pick patient", [this]()->bool //
            {
                return true;
            }, [this]()
            {
//TODO call discard report
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

void PatientFileWindow::backHome() {
//    if (!shouldNotclose) {
        setChanged();
        try {
            notifyObserver(std::string("backHome"),
                    dynamic_cast<CustomWindow*>(this));
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        Hide();
//    }
}
