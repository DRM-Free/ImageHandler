/*
 * HomeWindow.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */


#include "HomeWindow.h"
#include "Report/ReportWindow.h"

HomeWindow::HomeWindow() :
        CustomWindow(((wxFrame *) NULL), WindowType::HOME_WINDOW,
                "Home Window") {
    actionWindow = new wxWindow(this, wxID_ANY);
    aL = new ActionsList(actionWindow);
    aL->setList(WindowType::HOME_WINDOW);
    aL->Bind(wxEVT_CHAR, &HomeWindow::keyPressed, this);
    aL->SetFocus(); //Gives focus to aL, so user doesn't have to first click home window
    Centre();
}


HomeWindow::~HomeWindow() {

}

void HomeWindow::keyPressed(wxKeyEvent& event) {

    wxChar pressedKey = event.GetUnicodeKey();
    if (pressedKey != WXK_NONE) {

        if (pressedKey >= 32) {
//            wxLogMessage
//            ("You pressed '%c'", pressedKey);

         if (pressedKey == 'h') {
                displayContextualHelp();
            }

            if (pressedKey == 'l') {
                ReportWindow *addWindow = new ReportWindow(this);
                setChanged();
                try {
                    notifyObserver(std::string("frameRequest"),
                            dynamic_cast<CustomWindow*>(addWindow));
                } catch (std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
                Hide();
            }



            if (pressedKey == 'm') {
                RDPWindow *addWindow = new RDPWindow(this);
                setChanged();
                try {
                    notifyObserver(std::string("frameRequest"),
                            dynamic_cast<CustomWindow*>(addWindow));
                } catch (std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
                Hide();

         }
         if (pressedKey == 'P') {
         }

         if (pressedKey == 'O') {

         }

         }

         if (pressedKey == WXK_ESCAPE) {
         Close();
        }
        Fit();
    }
}

void HomeWindow::displayContextualHelp() {
    std::cout << "This helps" << std::endl;
}

void HomeWindow::setActionsHolder() {

}
