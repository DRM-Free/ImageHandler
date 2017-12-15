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
    setPreferredKeys();
    escapeKey = WXK_ESCAPE;
    wT = WindowType::RDP;
    SelectedImageWindows = nullptr;
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer = new wxBoxSizer(wxVERTICAL);
    iW = new ImageWindow(this, wxSize(600, 600));
    iW->forbidSelection();
    iL = new ScrolledList(this);
    aL = new ActionsList(this);
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
    selectedImages = iL->numberSelected();
}

/**
 * Time to associate all actionHolders to their RDPWindow member functions
 *
 */
std::vector<std::pair<std::string, std::string>> RDPWindow::setActionsHolder() {
    std::vector<std::pair<std::string, std::string>> actionsL;

    aH->push_back(ActionsHolder(escapeKey, "Back to Home", [this]()->bool //
    {
        return true;
    }, [this]()
    {
                backHome();
        /* SEE : Returning any doesn't allow void !! */
        return 0;
            }));

    char key = requestKey(); //Request new available keyboard key
    aH->push_back(ActionsHolder(key, "Pick image", [this]()->bool //
                            {
                                return true;
                            }, [this]()
                            {
                                this->pickImage();
                                /* SEE : Returning any doesn't allow void !! */
                return 0;
            }));

    for (auto it = aH->begin(); it != aH->end(); ++it) {
        actionsL.push_back((*it).generateActionLabels());
    }
    //SEE the above loop must do the same as comments below :
//    actionsL.push_back(std::make_pair("Esc", "Back to Home"));
//    actionsL.push_back(
//            std::make_pair(std::any_cast<std::string>(key), "Pick image"));

    return actionsL;
}

/**
 *Checks what of the added actions are now active and make changes in ActionsHolders and registeredActions map
 */


void RDPWindow::clearSelected() {

}


bool RDPWindow::isAllowedToClose() {
    return !shouldNotclose;
}

void RDPWindow::backHome() {
    if (isAllowedToClose()) {
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

