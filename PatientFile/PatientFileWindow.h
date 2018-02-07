/*
 * PatientFileWindow.h
 *
 *  Created on: 7 févr. 2018
 *      Author: anael
 */

#ifndef PATIENTFILEWINDOW_H_
#define PATIENTFILEWINDOW_H_

#include <wx/wx.h>


class PatientFileWindow: public wxFrame {
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
//    wxStaticBox patientBox;
//    wxStaticBox imagesBox;


//-------------------Constructors
public:
    PatientFileWindow();
    virtual ~PatientFileWindow();

private:

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* PATIENTFILEWINDOW_H_ */
