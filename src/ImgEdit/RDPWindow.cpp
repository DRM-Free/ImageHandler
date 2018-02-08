/*
 * RDPWindow.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */

#include "RDPWindow.h"
#include "../process/image_processing.h"
#include <exception>

RDPWindow::RDPWindow() :
        CustomWindow(WindowType::RDP, "Raw data processing"), shouldNotclose {
                false } {
    //Initialisations
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer = new wxBoxSizer(wxVERTICAL);
    iW = new ImageWindow(this);
    iL = new ScrolledList(this);
    wT = WindowType::RDP;

    //Initialisations

    //Mise en page

    mainSizer->Add(controlSizer);
    mainSizer->Add(iW, 3, wxEXPAND);
    controlSizer->Add(getAl()->getShownList());
    controlSizer->Add(iL, 1, wxEXPAND);
    SetSizerAndFit(mainSizer);
    iW->forbidSelection();
    escapeKey = WXK_ESCAPE;
    setPreferredKeys("jklmopuinbghty");

    getAl()->getShownList()->Bind(wxEVT_CHAR, &RDPWindow::keyPressed, this);
    iW->Bind(wxEVT_CHAR, &RDPWindow::keyPressed, this);
    iW->SetFocus();
}

void RDPWindow::displayContextualHelp() {
    std::cout << "This helps" << std::endl;
}

void RDPWindow::keyPressed(wxKeyEvent& event) {
    CustomWindow::keyPressed(event);
}

void RDPWindow::pickImage() { //Crashes in pickimage
    shouldNotclose = true;
    try {
        addImage(askJPG());
//        ScrolledIconsList* sIL = new ScrolledIconsList(iL);
//        iL->addScrolledIconsList(sIL);
//        sIL->appendImageWindows(*iW);
//        Refresh();
    } catch (std::runtime_error const& e) {
        std::cout << e.what();
    }
    shouldNotclose = false;
}

void RDPWindow::addImage(std::string imPath) {
    iW->setBitmap(imPath);
    ScrolledIconsList* sIL = new ScrolledIconsList(iL);
    sIL->appendImageWindows(imPath);

    iL->addScrolledIconsList(sIL);
    Refresh();
}

void RDPWindow::addImage(std::vector<std::string> const& imPaths) {
    ScrolledIconsList* sIL = new ScrolledIconsList(iL);
    for (uint32_t i = 0; i < imPaths.size(); ++i) {
//        imWin = new ImageWindow(sIL);
//        imWin->setBitmap(imPaths.at(i));
        sIL->appendImageWindows(imPaths.at(i));
    }
    iL->addScrolledIconsList(sIL);
    iW->setBitmap(imPaths.at(imPaths.size() - 1));
    Refresh();
}


std::string RDPWindow::askJPG() {
    wxFileDialog openFileDialog(this, _("Pick an image"), "", "",
            "jpg files (*.jpg)|*.jpg", wxFD_OPEN);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        throw std::runtime_error("User cancelled image selection");
    }

    return openFileDialog.GetPath().ToStdString();
}

/**
 * Time to associate all actionHolders to their RDPWindow member functions
 *
 */
std::vector<std::pair<std::string, std::string>> RDPWindow::setActionsHolder() {
    std::vector<std::pair<std::string, std::string>> actionsL;

    //###################### ADD NEW ACTIONS DOWN HERE ######################

    aH.push_back(ActionsHolder(escapeKey, "Back to Home", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                backHome();
                /* SEE : Returning any doesn't allow void !! */
                return 0;
            }));

    char key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Pick image", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                this->pickImage();
                /* SEE : Returning any doesn't allow void !! */
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Clear selected", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                this->iL->clearSelected();
                /* SEE : Returning any doesn't allow void !! */
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Enhance blood features", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                featuresEnhancement();
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Display cells counts", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                std::vector<std::vector<int>> counts = countBC();

                for (int i = 0; i<counts.size(); ++i) {
                    std::cout<< i << "th image features : " << '\n';
                            std::cout<< "White blood cells count" << counts.at(i).at(0)<<'\n';
                            std::cout<< "Red blood cells count" << counts.at(i).at(1)<<'\n';
                            std::cout<< "THR blood cells count" << counts.at(i).at(2)<<'\n';
                }
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Make tuple", [this]()->bool //
            {
                return true;
            }, [this]
            {
                makeTuple();
                return 0;
            }));
    //###################### ADD NEW ACTIONS UP HERE ######################

    for (auto it = aH.begin(); it != aH.end(); ++it) {
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
    }
}

std::vector<std::vector<int>> RDPWindow::countBC() {
    std::vector<std::vector<int>> counts;
    for (ImageWindow* im : iL->getSelectedImageWindows()) {
        counts.push_back(numeration(im->getImPath()));
    }
    return counts;
}

void RDPWindow::makeTuple() {
    std::vector<std::string> imPaths;
    for (ImageWindow* im : iL->getSelectedImageWindows()) {
        imPaths.push_back(im->getImPath());
    }
    addImage(imPaths);
    iL->clearSelected();
}

void RDPWindow::featuresEnhancement() {

    std::string outName = "";
    fs::path outFolder = "";
    fs::path imPath = "";
    fs::path outputPath =
            "/home/anael/eclipse-workspace/ImageProject2/Images/ProcessedData";
    std::vector<std::string> imPaths;
    for (ImageWindow* im : iL->getSelectedImageWindows()) {
        imPath = im->getImPath();
        outName = imPath.stem().concat("_enhanced").concat(
                imPath.extension().string());
        outFolder = outputPath.parent_path();
        outFolder.append("ProcessedData");
        outFolder.append(outName);
        gommageGR(imPath, outFolder);
        imPaths.push_back(outFolder.string());
    }
    std::cout << "Processed images have been saved" << '\n';
    addImage(imPaths);
    iL->clearSelected();
}
