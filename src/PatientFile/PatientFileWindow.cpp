/*
 * PatientFileWindow.cpp
 *
 *  Created on: 7 févr. 2018
 *      Author: anael
 */

#include "PatientFileWindow.h"
#include "LabelledInput.h"
#include "../General/WindowType.h"
#include "../ImgEdit/ImageWindow.h"

PatientFileWindow::PatientFileWindow() :
        CustomWindow(WindowType::PATIENT_MANAGER, "Patient manager"), s1(
                wxVERTICAL), s2(wxHORIZONTAL), s3(wxVERTICAL), s4(2,
                0, 0), actions(
                this, wxID_ANY,
                "Actions list"), patientInfos(
                this, wxID_ANY, "Patient infos"), patientPhoto(
                this), patientImages(this), patientReports(
                this) {
    getAl()->getShownList()->Bind(wxEVT_CHAR, &PatientFileWindow::keyPressed,
            this);


    patientImages.SetMinSize(wxSize(100, 100));
    patientPhoto.SetSize(wxSize(200, 200));

    actions.SetMinSize(wxSize(300, 200));

    wxBoxSizer *actionsSizer = new wxBoxSizer(wxVERTICAL);
    actions.SetSizer(actionsSizer);
    actionsSizer->Add(getAl()->getShownList(), 1, wxALL, 20);
//tests
    SetSize(wxSize(1800, 1000));
    Center();

    SetSizer(&s1, true);
    s1.Add(&s2, 1);
    s1.Add(&patientImages, 1, wxEXPAND);
    s1.Add(patientReports.getReportIcons(), 1, wxEXPAND);

    s2.Add(&s3, 1, wxEXPAND);
    s2.Add(&patientInfos, 1, wxEXPAND);
    s2.Add(&patientPhoto, 2, wxEXPAND);


    s3.Add(&actions, 1);


    patientInfos.SetSizer(&s4, true);

    Layout();
}

PatientFileWindow::~PatientFileWindow() {
}

void PatientFileWindow::displayContextualHelp() {
}

std::vector<std::pair<std::string, std::string>> PatientFileWindow::setActionsHolder() {
    std::vector<std::pair<std::string, std::string>> actionsL;

    aH.push_back(ActionsHolder(escapeKey, "Back Home", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                backHome();
                return 0;
            }));

    char key = requestKey(); //Request new available keyboard key

    aH.push_back(ActionsHolder(key, "new report", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
            return 0;
        }));

    key = requestKey(); //Request new available keyboard key

    aH.push_back(
            ActionsHolder(key, "Display contextual help", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                this->displayContextualHelp();
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key

    aH.push_back(ActionsHolder(key, "Pick patient", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                pickPatient();
            return 0;
        }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Go to data processing", "", [this]()->bool //
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


    for (auto it = aH.begin(); it != aH.end(); ++it) {
        actionsL.push_back((*it).generateActionLabels());
    }

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


void PatientFileWindow::keyPressed(wxKeyEvent& event) {
    CustomWindow::keyPressed(event);
}

void PatientFileWindow::pickPatient() {
    s4.Clear(0); // 1?
    s4.Add(new LabelledInput(&patientInfos, "first name :", "Pierre-Jean"));
    s4.Add(new LabelledInput(&patientInfos, "last name :", "Lartaud"));
    s4.Add(new LabelledInput(&patientInfos, "birth date:", "Unknown"));
    s4.Add(new LabelledInput(&patientInfos, "unique ID:", "00OLOLO"));

    setPatientPath(
            "/home/anael/eclipse-workspace/ImageProject2/resources/DemoPatient/RawData");

    fs::path demoImgPath =
            "/home/anael/eclipse-workspace/ImageProject2/resources/DemoPatient/RawData";
    patientImages.reset();
    patientImages.appendImageWindows(demoImgPath);
    fs::path demoReportPath =
            "/home/anael/eclipse-workspace/ImageProject2/resources/DemoPatient/Reports";
    patientReports.getReportIcons()->reset();
    patientReports.setReports(demoReportPath);
    fs::path demoPhotoPath =
            "/home/anael/eclipse-workspace/ImageProject2/resources/DemoPatient/face.jpg";
    setPatientPhoto(demoPhotoPath);
    Layout();
}

void PatientFileWindow::setPatientPhoto(fs::path photoPath) {
    patientPhoto.setBitmap(photoPath);
    patientPhoto.iconize(wxSize(250, 200));

}
