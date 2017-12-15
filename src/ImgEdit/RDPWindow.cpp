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
    aH = new std::vector<ActionsHolder>;
//    setActionsHolder();
    addPreferredKey('j');
    addPreferredKey('k');
    addPreferredKey('l');
    addPreferredKey('m');
    addPreferredKey('n');
    addPreferredKey('b');
    addPreferredKey('o');
    addPreferredKey('p');
    addPreferredKey('h');

    escapeKey = WXK_ESCAPE;

    wT = WindowType::RDP;
    SelectedImageWindows = nullptr;
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer = new wxBoxSizer(wxVERTICAL);
    iW = new ImageWindow(this, wxSize(600, 600));
    iW->forbidSelection();
    iL = new ScrolledList(this);
    aL = new ActionsList(this);
    updateActionsList();
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
    CustomWindow::keyPressed(event);
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
std::vector<std::pair<std::string, std::string>> RDPWindow::setActionsHolder() {
    std::vector<std::pair<std::string, std::string>> actionsL;

    actionsL.push_back(std::make_pair("Esc", "Back to Home"));
    aH->push_back(ActionsHolder(escapeKey, "Back to Home", [this]()->bool //
    {
        return true;
    }, [this]()
    {
                                this->backHome();
        /* SEE : Returning any doesn't allow void !! */
        return 0;
            }));

    char key = requestKey(); //Request new available keyboard key
    actionsL.push_back(
            std::make_pair(std::any_cast<std::string>(key), "Pick image"));
    aH->push_back(ActionsHolder(key, "Pick image", [this]()->bool //
                            {
                                return true;
                            }, [this]()
                            {
                                this->pickImage();
                                /* SEE : Returning any doesn't allow void !! */
                                return 0;
            }));

    return actionsL;
}

/**
 *Checks what of the added actions are now active and make changes in ActionsHolders and registeredActions map
 */

//addAction(wxString("esc"), wxString("Back to Home"));
//addAction(wxString("x"), wxString("Discard all"));
//addAction(wxString("m"), wxString("Quick report"));
//addAction(wxString("l"), wxString("Highlight features"));
//addAction(wxString("k"), wxString("Mask RBC"));



void RDPWindow::clearSelected() {

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

