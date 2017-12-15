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

void ActionsList::resetList(
        std::vector<std::pair<std::string, std::string>> actions) {
    DeleteAllItems();
    setList(actions);
}

ActionsList::~ActionsList() {

}



void ActionsList::setList(
        std::vector<std::pair<std::string, std::string>> actions) {
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        addAction(it->first, it->second);
    }
}

void ActionsList::addAction(wxString key, wxString description) {
    long itemIndex1 = InsertItem(0, key); //want this for col. 1
    SetItem(itemIndex1, 1, description); //want this for col. 2


}

void setImageTransforms(int numberSelected) {

}
//SEE report window possible actions
//        addAction(wxString("x"), wxString("Discard all"));
//        addAction(wxString("m"), wxString("Submit report"));
//        addAction(wxString("l"), wxString("Add report element"));
//        addAction(wxString("esc"), wxString("Back to Home"));
