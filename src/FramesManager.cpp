/*
 * FramesManager.cpp
 *
 *  Created on: 18 nov. 2017
 *      Author: anael
 */

#include "FramesManager.h"

#include <wx/wx.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include "General/WindowType.h"
#include "tools/Observed.hpp"

FramesManager::FramesManager(HomeWindow* firstFrame) :
        homeFrame(firstFrame), improcFrame(nullptr), patientFileFrame(nullptr), reportFrame(
                nullptr) {
    using namespace std;
    addAction<string, CustomWindow*>("improc",
            [this](CustomWindow* content, Observed const& observed) -> void
            {
                if (improcFrame==nullptr) {
                    improcFrame = new RDPWindow();
                    improcFrame->addObserver(this);
                    improcFrame->setActionsList();
                }
                improcFrame->Center();
                improcFrame->setFocus();
                dynamic_cast<CustomWindow*> (improcFrame)->setPatientPath(dynamic_cast<CustomWindow*> (content)->getPatientPath());
                improcFrame->Show(true);
                content->Hide();
            });
    addAction<string, CustomWindow*>("patientFile",
            [this](CustomWindow* content, Observed const& observed) -> void
            {
                if (patientFileFrame==nullptr) {
                    patientFileFrame = new PatientFileWindow();
                    patientFileFrame->addObserver(this);
                    patientFileFrame->setActionsList();
                }
                patientFileFrame->Center();
                patientFileFrame->setFocus();
                dynamic_cast<CustomWindow*> (patientFileFrame)->setPatientPath(dynamic_cast<CustomWindow*> (content)->getPatientPath());
                patientFileFrame->Show(true);
                content->Hide();
            });

    addAction<string, CustomWindow*>("report",
            [this](CustomWindow* content, Observed const& observed) -> void
            {
                if (reportFrame==nullptr) {
                    reportFrame = new ReportWindow();
                    reportFrame->addObserver(this);
                    reportFrame->setActionsList();
                }
                reportFrame->Center();
                reportFrame->setFocus();
                dynamic_cast<CustomWindow*> (reportFrame)->setPatientPath(dynamic_cast<CustomWindow*> (content)->getPatientPath());
                reportFrame->Show(true);
                content->Hide();
            });


    addAction<string, CustomWindow*>("backHome",
            [this](CustomWindow* content, Observed const& observed) -> void
            {
                homeFrame->setFocus();
                dynamic_cast<CustomWindow*> (homeFrame)->setPatientPath(dynamic_cast<CustomWindow*> (content)->getPatientPath());
                homeFrame->Show();
                content->Hide();
            });

}

FramesManager::~FramesManager() {
}

