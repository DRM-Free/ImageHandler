/*
 * ScrolledReportList.cpp
 *
 *  Created on: 8 févr. 2018
 *      Author: anael
 */

#include "ScrolledReportList.h"

ScrolledReportList::~ScrolledReportList() {
}

ScrolledReportList::ScrolledReportList(wxWindow* parent) :
        reportIcons(parent) {
    //SEE Only one report should be selected at a time, so there should be a "forbidAllSelection" in scrollediconlist
//    to prement multiple selection when necessary
}

void ScrolledReportList::setReports(fs::path reportspath) {
    for (auto &it : fs::directory_iterator(reportspath)) {
        reportIcons.appendImageWindows(
                "/home/anael/eclipse-workspace/ImageProject2/resources/file.jpg");
        }
}
