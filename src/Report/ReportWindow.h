/*
 * ReportWIndow.h
 *
 *  Created on: 29 nov. 2017
 *      Author: anael
 */

#ifndef REPORTWINDOW_H_
#define REPORTWINDOW_H

#include "wx/wx.h"
#include "../CustomWindow.h"
#include "ReportForm.h"

class ReportWindow: public CustomWindow {
//-------------------Attributes
private:
    ReportForm* rF;
    wxBoxSizer *controlSizer;

//-------------------Constructors
public:
    ReportWindow(wxWindow* parent);
    ~ReportWindow();
    void keyPressed(wxKeyEvent& event);
    void backHome();
    void addReportElement();
    void displayContextualHelp();
    std::vector<std::pair<std::string, std::string>> setActionsHolder()
            override;

private:
    bool shouldNotclose;

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* REPORTWINDOW_H_ */
