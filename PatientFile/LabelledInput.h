/*
 * LabelledInput.h
 *
 *  Created on: 7 févr. 2018
 *      Author: anael
 */

#ifndef LABELLEDINPUT_H_
#define LABELLEDINPUT_H_
#include "wx/wx.h"
#include "string"

class LabelledInput: public wxWindow {
//-------------------Attributes
private:
    bool writable;
    wxStaticText label;
    wxTextCtrl input;
    wxBoxSizer sizer;
//-------------------Constructors
public:
    LabelledInput(wxWindow* parent, std::string label, std::string input);
    LabelledInput(wxWindow* parent, std::string label);
    virtual ~LabelledInput();

private:

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* LABELLEDINPUT_H_ */
