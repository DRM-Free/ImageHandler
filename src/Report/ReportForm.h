/*
 * ReportForm.h
 *
 *  Created on: 25 oct. 2017
 *      Author: anael
 */

#ifndef REPORTFORM_H_
#define REPORTFORM_H_

#include "wx/wx.h"

#include "../General/WindowType.h"

class ReportForm: public wxPanel {
public:
    ReportForm(wxWindow* parent);
    ~ReportForm();
    void setForm();
    void addReportElement(wxString const requestName);
    void addCommentArea();
    bool AcceptsFocus();
private:
    wxBoxSizer* mainSizer;
};

#endif /* REPORTFORM_H_ */
