/*
 * ActionsList.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */

#include "ActionsList.h"
#include <iostream>

ActionsList::ActionsList(wxWindow* parent) :
        wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxLC_REPORT) {
    //Set columns labels
    col0.SetId(0);
    col0.SetText(_("Key"));
    col0.SetWidth(50);
    InsertColumn(0, col0);

    col1.SetId(1);
    col1.SetText(_("Available action"));
    col1.SetWidth(200);
    InsertColumn(1, col1);
}

ActionsList::~ActionsList() {

}



void ActionsList::setList(WindowType wT) {
    DeleteAllItems();
    switch (wT) {

    case WindowType::HOME_WINDOW:
        addAction(wxString("m"), wxString("Process raw data"));
        addAction(wxString("l"), wxString("Manage reports"));
        addAction(wxString("k"), wxString("Manage patients"));
        addAction(wxString("esc"), wxString("Exit"));
        break;

    case WindowType::RDP:
        addAction(wxString("x"), wxString("Discard all"));
        addAction(wxString("m"), wxString("Quick report"));
        addAction(wxString("l"), wxString("Highlight features"));
        addAction(wxString("k"), wxString("Mask RBC"));
        addAction(wxString("j"), wxString("Select starting image"));
        addAction(wxString("esc"), wxString("Back to Home"));
        break;
    case WindowType::RM:
        addAction(wxString("x"), wxString("Discard all"));
        addAction(wxString("m"), wxString("Submit report"));
        addAction(wxString("l"), wxString("Add report element"));
        addAction(wxString("esc"), wxString("Back to Home"));
        break;
    default:
        break;
    }
}

void ActionsList::addAction(wxString key, wxString description) {
    long itemIndex1 = InsertItem(0, key); //want this for col. 1
    SetItem(itemIndex1, 1, description); //want this for col. 2
}

void setImageTransforms(int numberSelected) {

}
