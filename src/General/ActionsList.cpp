/*
 * ActionsList.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */

#include "ActionsList.h"
#include <iostream>

ActionsList::ActionsList(wxWindow* parent) :
        shownList(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxLC_REPORT) {
    //Set columns labels
    col0.SetId(0);
    col0.SetText(_("Key"));
    col0.SetWidth(50);
    shownList.InsertColumn(0, col0);

    col1.SetId(1);
    col1.SetText(_("Available action"));
    col1.SetWidth(200);
    shownList.InsertColumn(1, col1);
}

void ActionsList::resetList(
        std::vector<std::pair<std::string, std::string>> actions) {
    shownList.DeleteAllItems();
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
    long itemIndex1 = shownList.InsertItem(0, key); //want this for col. 1
    shownList.SetItem(itemIndex1, 1, description); //want this for col. 2


}

void setImageTransforms(int numberSelected) {

}

wxListCtrl* ActionsList::getShownList() {
    return &shownList;
}
