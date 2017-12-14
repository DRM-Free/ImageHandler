/*
 * RDPWindow.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */


#include "RDPWindow.h"

RDPWindow::RDPWindow(wxWindow* parent) :
        CustomWindow(parent, WindowType::RDP, "Raw data processing"), shouldNotclose {
                false }, selectedImages { 0 } {
//    setActionsHolder();
    allocatedKeys = 0;
    preferredKeys.push_back('j');
    preferredKeys.push_back('k');
    preferredKeys.push_back('l');
    preferredKeys.push_back('m');
    preferredKeys.push_back('o');
    preferredKeys.push_back('p');
    preferredKeys.push_back('b');
    preferredKeys.push_back('n');
    escapeKey = WXK_ESCAPE;

    wT = WindowType::RDP;
    SelectedImageWindows = nullptr;
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer = new wxBoxSizer(wxVERTICAL);
    iW = new ImageWindow(this, wxSize(600, 600));
    iW->forbidSelection();
    iL = new ScrolledList(this);
    aL = new ActionsList(this);
    aL->setList(wT);
    aL->Bind(wxEVT_CHAR, &RDPWindow::keyPressed, this);
    iW->Bind(wxEVT_CHAR, &RDPWindow::keyPressed, this);
    iW->SetFocus();
    mainSizer->Add(controlSizer);
    mainSizer->Add(iW, 3, wxEXPAND);
    controlSizer->Add(aL);
    controlSizer->Add(iL, 1, wxEXPAND);
    SetSizerAndFit(mainSizer);
}

void RDPWindow::displayContextualHelp() {
    std::cout << "This helps" << std::endl;
}

void RDPWindow::keyPressed(wxKeyEvent& event) {
    wxChar pressedKey = event.GetUnicodeKey();

    if (pressedKey != WXK_NONE) {

        if (pressedKey >= 32) {
            //            wxLogMessage
            //            ("You pressed '%c'", pressedKey);
            if (pressedKey == 'j') {
                pickImage();
            }
            if (pressedKey == 'k') {
            }
            if (pressedKey == 'l') {
            }
            if (pressedKey == 'm') {
            }
            if (pressedKey == 'x') {
            }
        }
            if (pressedKey == WXK_ESCAPE) {
            backHome();
            }
        checkSelected();
        setActionsHolder();
    }

    iL->updateSelectedBitmaps();
}

void RDPWindow::pickImage() {
    shouldNotclose = true;
    iW->setBitMap();
    ScrolledIconsList *sIL = new ScrolledIconsList(iL);
    iL->addScrolledIconsList(sIL);
    sIL->appendBitmap(iW->getBitmap());
    shouldNotclose = false;
}

void RDPWindow::resumeImage(wxBitmap* bitmap) {
    iW->copyBitMap(bitmap);
}

void RDPWindow::checkSelected() {
    //TODO fill checkSelected !
}

/**
 * Time to associate all actionHolders to their RDPWindow member functions
 *
 */
void RDPWindow::setActionsHolder() {

    auto myLambda = [this]()->bool
    {
        return true;
    };
//TODO here replace first key string with a call to allocatekey
    auto tuple = std::tuple<std::string, std::string, std::function<bool()>>(
            "esc", "Back to home", myLambda);
//    auto myFunction = dynamic_cast<std::function<void*()>>(*backHome());
//    addAction(myFunction, tuple);
    addAction([this]() {
        backHome();
    }, tuple);


//    addAction(
//            std::tuple<std::string, std::string, std::function<bool()>>("esc",
//                    "Back to home", [this]()->bool
//                    {
//                        return (selectedImages > 0);
//                    }));

}



//addAction(wxString("x"), wxString("Discard all"));
//addAction(wxString("m"), wxString("Quick report"));
//addAction(wxString("l"), wxString("Highlight features"));
//addAction(wxString("k"), wxString("Mask RBC"));
//addAction(wxString("j"), wxString("Select starting image"));
//addAction(wxString("esc"), wxString("Back to Home"));

void RDPWindow::maskRBC() {

}
void RDPWindow::highlightFeatures() {

}

void RDPWindow::clearSelected() {

}

void RDPWindow::discardAll() {

}

bool RDPWindow::isAllowedToClose() {
    return shouldNotclose;
}

void RDPWindow::backHome() {
    if (!shouldNotclose) {
        setChanged();
        try {
            notifyObserver(std::string("backHome"),
                    dynamic_cast<CustomWindow*>(this));
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        Hide();
    }
}

