/*
 * FramesManager.h
 *
 *  Created on: 18 nov. 2017
 *      Author: anael
 */

#ifndef FRAMESMANAGER_H_
#define FRAMESMANAGER_H_

#include "tools/Observer.hpp"
#include <vector>
#include "wx/wx.h"
#include "CustomWindow.h"
#include "ImgEdit/RDPWindow.h"
#include "../PatientFile/PatientFileWindow.h"
#include "HomeWindow.h"
#include "Report/ReportWindow.h"

class FramesManager: public Observer {
//-------------------Attributes
private:
//    std::vector<wxFrame*> frames;
    HomeWindow *homeFrame;
    RDPWindow *improcFrame;
    PatientFileWindow *patientFileFrame;
    ReportWindow *reportFrame;
//-------------------Constructors
public:
    FramesManager(HomeWindow* firstFrame);
    virtual ~FramesManager();

private:

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* FRAMESMANAGER_H_ */
