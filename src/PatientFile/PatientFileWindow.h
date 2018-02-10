/*
 * PatientFileWindow.h
 *
 *  Created on: 7 févr. 2018
 *      Author: anael
 */

#ifndef PATIENTFILEWINDOW_H_
#define PATIENTFILEWINDOW_H_

#include <wx/wx.h>
#include "../CustomWindow.h"
#include "../ImgEdit/ScrolledIconsList.h"
#include "ScrolledReportList.h"
#include <string>
#include <experimental/filesystem>

class PatientFileWindow: public CustomWindow {
//-------------------Attributes
private:
    wxBoxSizer s1;
    wxBoxSizer s2;
    wxBoxSizer s3;
    wxGridSizer s4;
//    wxStaticBox scrolledIcons;
    wxStaticBox actions;
    wxStaticBox reports;
    wxStaticBox patientInfos;
    wxPanel patientPhoto;
    ScrolledIconsList sIL;
    ScrolledReportList sRL;

//-------------------Constructors
public:
    PatientFileWindow();
    virtual ~PatientFileWindow();
    void displayContextualHelp();
    std::vector<std::pair<std::string, std::string>> setActionsHolder();
    void backHome();
    void keyPressed(wxKeyEvent& event);
    void pickPatient();

private:

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:
};

#endif /* PATIENTFILEWINDOW_H_ */
