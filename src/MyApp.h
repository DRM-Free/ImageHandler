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
    virtual bool OnInit() {
    wxInitAllImageHandlers();
        mainWindow = new HomeWindow();
        frameManager = new FramesManager(mainWindow);
        mainWindow->addObserver(frameManager);
        SetTopWindow(mainWindow);
        mainWindow->Show();
    return true;
    }
};

#endif /* MYAPP_H_ */
