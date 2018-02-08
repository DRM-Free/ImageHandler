/*
 * LabelledInput.cpp
 *
 *  Created on: 7 févr. 2018
 *      Author: anael
 */

#include "LabelledInput.h"

LabelledInput::LabelledInput(wxWindow* parent, std::string label,
        std::string input) :
        wxWindow(parent, wxID_ANY), writable(false), label(this, wxID_ANY,
                label), input(
                this,
                wxID_ANY,
                input, wxDefaultPosition, wxSize(200, 25),
                wxTE_READONLY), sizer(wxVERTICAL) {

    sizer.Add(&(this->label));
    sizer.Add(&(this->input));
    SetSizerAndFit(&sizer, true);
}

LabelledInput::LabelledInput(wxWindow* parent, std::string label) :
        wxWindow(parent, wxID_ANY), writable(true), label(this, wxID_ANY,
                label), input(this, wxID_ANY, "", wxDefaultPosition,
                wxSize(200, 25)), sizer(wxVERTICAL) {

    sizer.Add(&(this->label));
    sizer.Add(&(this->input));
    SetSizerAndFit(&sizer, true);
}

LabelledInput::~LabelledInput() {
}

