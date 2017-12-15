/*
 * FramesManager.cpp
 *
 *  Created on: 18 nov. 2017
 *      Author: anael
 */

#include "FramesManager.h"

#include <wx/wx.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include "CustomWindow.h"

#include "tools/Observed.hpp"

FramesManager::FramesManager(wxFrame* firstFrame) {
    using namespace std;
    frames.push_back(firstFrame);
    addAction<string, CustomWindow*>("frameRequest",
            [this](CustomWindow* content, Observed const& observed) -> void
            {
                frames.push_back(content);
                content->addObserver(this);
                content->Center();
                content->setActionsList();
                content->Show(true);
            });

    addAction<string, CustomWindow*>("backHome",
            [this](CustomWindow* content, Observed const& observed) -> void
            {
                frames[0]->Show();
            });
}

FramesManager::~FramesManager() {
}

