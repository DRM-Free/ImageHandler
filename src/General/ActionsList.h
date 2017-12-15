/*
 * ActionsList.h
 *
 *  Created on: 25 oct. 2017
 *      Author: anael
 */

#ifndef ACTIONSLIST_H_
#define ACTIONSLIST_H_

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "WindowType.h"
#include <string>
#include <vector>

class ActionsList: public wxListCtrl {
public:
    ActionsList(wxWindow* parent);
    ~ActionsList();
    void setList(std::vector<std::pair<std::string, std::string>> actions);
    void resetList(std::vector<std::pair<std::string, std::string>> actions);
    void addAction(wxString key, wxString description);
    void setImageTransforms(int numberSelected);
private:
    wxListItem col0;
    wxListItem col1;
};


#endif /* ACTIONSLIST_H_ */
