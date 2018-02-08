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
                reportFrame->Show(true);
                content->Hide();
            });


    addAction<string, CustomWindow*>("backHome",
            [this](CustomWindow* content, Observed const& observed) -> void
            {
                homeFrame->Show();
                content->Hide();
            });

}

FramesManager::~FramesManager() {
}

