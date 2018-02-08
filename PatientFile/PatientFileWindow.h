/*
 * PatientFileWindow.h
 *
 *  Created on: 7 févr. 2018
 *      Author: anael
 */

#ifndef PATIENTFILEWINDOW_H_
#define PATIENTFILEWINDOW_H_

#include <wx/wx.h>
#include "../src/CustomWindow.h"

class PatientFileWindow: public CustomWindow {
//-------------------Attributes
private:
    wxBoxSizer s1;
    wxBoxSizer s2;
    wxBoxSizer s3;
    wxGridSizer s4;
    wxStaticBox scrolledIcons;
    wxStaticBox actions;
    wxStaticBox reports;
    wxStaticBox patientInfos;
    wxPanel patientPhoto;


//-------------------Constructors
public:
    PatientFileWindow();
    virtual ~PatientFileWindow();
    void displayContextualHelp();
    std::vector<std::pair<std::string, std::string>> setActionsHolder();
    void backHome();
    void keyPressed(wxKeyEvent& event);

private:

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:
};

#endif /* PATIENTFILEWINDOW_H_ */
