/*
 * MyApp.h
 *
 *  Created on: 14 nov. 2017
 *      Author: anael
 */

#ifndef MYAPP_H_
#define MYAPP_H_

#include "HomeWindow.h"
#include "wx/wx.h"
#include "FramesManager.h"

class MyApp: public wxApp {
private:
    HomeWindow *mainWindow;
    FramesManager* frameManager;
public:
    virtual bool OnInit() override {
        wxInitAllImageHandlers();
        mainWindow = new HomeWindow();
        mainWindow->setActionsList();
        frameManager = new FramesManager(mainWindow);
        mainWindow->addObserver(frameManager);
        SetTopWindow(mainWindow);
        mainWindow->Show();
        return true;
    }

    virtual int OnExit() override {
        delete frameManager;
        return true;
    }
};

#endif /* MYAPP_H_ */
