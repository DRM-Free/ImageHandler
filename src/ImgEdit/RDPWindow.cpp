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
                false }, actions(this, wxID_ANY, "available actions") {
    //Initialisations
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer = new wxBoxSizer(wxVERTICAL);
    iW = new ImageWindow(this);
    iL = new ScrolledList(this);
    wT = WindowType::RDP;
    SetSize(wxSize(1800, 1000));

    getAl()->getShownList()->SetParent(&actions);
    actions.SetMinSize(wxSize(300, 400));
    wxBoxSizer *actionsSizer = new wxBoxSizer(wxVERTICAL);
    actions.SetSizer(actionsSizer);
    actionsSizer->Add(getAl()->getShownList(), 1, wxALL, 20);

    //Initialisations

    //Mise en page

    mainSizer->Add(controlSizer, 1, wxEXPAND);
    mainSizer->Add(iW, 7, wxEXPAND);
    controlSizer->Add(&actions);
    controlSizer->Add(iL, 1, wxEXPAND);
    SetSizer(mainSizer);
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
    ScrolledIconsList* sIL = new ScrolledIconsList(iL);
    sIL->appendImageWindows(imPath);
    iW->setBitmap(sIL->getLastImageWindow()->getImPath());
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

    aH.push_back(ActionsHolder(escapeKey, "Back to Home", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                backHome();
                return 0;
            }));

    char key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Pick image", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                this->pickImage();
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(ActionsHolder(key, "Report results", "", [this]()->bool //
            {
                return true;
            }, [this]()
            {
                if (isAllowedToClose()) {
                    setChanged();
                    try {
                        notifyObserver(std::string("report"),
                                dynamic_cast<CustomWindow*>(this));
                    } catch (std::exception& e) {
                        std::cerr << e.what() << '\n';
                    }
                }
                return 0;
            }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(
            ActionsHolder(key, "Clear selected", "No image selected",
                    [this]()->bool //
                    {
                        return iL->getSelectedImageWindows().size()>=1;
                    }, [this]()
                    {
                        this->iL->clearSelected();
                        return 0;
                    }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(
            ActionsHolder(key, "Enhance blood features",
                    "At least one image should be selected", [this]()->bool //
                    {
                        return iL->getSelectedImageWindows().size()>=1;
                    }, [this]()
                    {
                        featuresEnhancement();
                        return 0;
                    }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(
            ActionsHolder(key, "Display cells counts",
                    "At least one image should be selected", [this]()->bool //
                    {
                        return iL->getSelectedImageWindows().size()>=1;
                    }, [this]()
                    {
                        std::vector<std::vector<int>> counts = countBC();

//                        for (uint32_t i = 0; i < counts.size(); ++i) {
                    std::function<void(int, int)> showMod = [&](int imgNo, int size) {
                        if (imgNo < size) {
                            stringstream sstr;
                            sstr << "Image " << imgNo + 1 << " features : " << '\n';
                            sstr << "White blood cells count : " << counts.at(imgNo).at(0)<<'\n';
                            sstr << "Red blood cells count : " << counts.at(imgNo).at(1)<<'\n';
                            sstr << "THR blood cells count : " << counts.at(imgNo).at(2)<<'\n';
                            wxMessageDialog* dia = new wxMessageDialog(nullptr, sstr.str(),
                                    "Ok", wxSTAY_ON_TOP);
                            dia->ShowWindowModalThenDo([imgNo, size, showMod, dia](int retCode) {
                                        if (retCode == wxID_OK) {
                                            showMod(imgNo+1, size);
                                        }
                                        dia->Destroy();
                                    });
                        }
                    };
                    showMod(0, counts.size());
//                        }
                    return 0;
                }));

    key = requestKey(); //Request new available keyboard key
    aH.push_back(
            ActionsHolder(key, "Make tuple",
                    "At least two images should be selected", [this]()->bool //
                    {
                        return iL->getSelectedImageWindows().size()>=2;
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
