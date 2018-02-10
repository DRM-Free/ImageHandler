/*
 * ScrolledReportList.h
 *
 *  Created on: 8 févr. 2018
 *      Author: anael
 */

#ifndef SCROLLEDREPORTLIST_H_
#define SCROLLEDREPORTLIST_H_
#include "../ImgEdit/ScrolledIconsList.h"
#include "wx/wx.h"
#include "experimental/filesystem"

class ScrolledReportList {
//-------------------Attributes
private:

//-------------------Constructors
public:
    ScrolledReportList(wxWindow* parent);
    virtual ~ScrolledReportList();
    void setReports(fs::path reportspath);
    ScrolledIconsList* getReportIcons();
private:
    ScrolledIconsList reportIcons;
//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* SCROLLEDREPORTLIST_H_ */
