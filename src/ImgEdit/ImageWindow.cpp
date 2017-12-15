/*
 * ImageWindow.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: anael
 */



#include "ImageWindow.h"
#include <wx/colour.h>
#include <wx/graphics.h>
#include <wx/event.h>
#include <algorithm>

ImageWindow::ImageWindow(wxWindow* parent,
        wxSize const & minSize = wxSize(600, 600)) :
        wxScrolledWindow(parent, wxID_ANY), isSelected { false }, isSelectible {
                true } {
    bitmap = nullptr;
    w = 0;
    h = 0;
    SetMinClientSize(minSize);
//    wxScrolledWindow* scrolledThis = dynamic_cast<wxScrolledWindow*>(this);
    //SEE A successful bind involves a correct event name (usually beginning with wxEVT) and that the bound method accepts the corresponding event as argument
    Bind(wxEVT_LEFT_DOWN, &ImageWindow::switchSelected, this);


//    Bind(wxEVT_CHAR, &HomeWindow::keyPressed, this);
}

ImageWindow::~ImageWindow() {
    delete bitmap;
}

void ImageWindow::OnDraw(wxDC& dc) {

    if (bitmap == nullptr) {
        dc.SetBrush(wxNullBrush); // blue filling
        dc.SetPen(wxPen(wxColour(110, 20, 240), 10));
        dc.DrawRectangle((minWidth - 200) / 2, (minwHeight - 50) / 2,
                200, 50);
        dc.DrawText(wxT("Pick an image to get started !"),
                (minWidth - 200) / 2 + 10, (minwHeight - 50) / 2 + 10);

    } else {
        int* x = new int;
        int* y = new int;

        GetSize(x, y);
        int yScroll = GetScrollPos(wxVERTICAL);
        int xScroll = GetScrollPos(wxHORIZONTAL);

        dc.SetClippingRegion(xScroll, yScroll, *x + xScroll, *y + yScroll); //Will not draw outside clipping region, increases performances
        dc.DrawBitmap(*bitmap, 0, 0, false);

        if (isSelected) {
        //####Test code for alpha painting####
            wxPaintDC paintDc(this);
            wxGraphicsContext *gc = wxGraphicsContext::Create(paintDc);
            if (gc) {
                gc->SetPen(wxPen(wxColour(250, 5, 5), 5));
//            wxPen (const wxColour &colour, int width=1, wxPenStyle style=wxPENSTYLE_SOLID)
                wxGraphicsPath path = gc->CreatePath();
            double regularSize=30.0;
                //Regularpositionw =0 -> Position on the left
                //SEE GetVirtualSize gives total size including scrolled unvisible parts of the window. GetSize gives only onscreen window size
                double regularPositionw = std::min(
                        int(GetSize().GetWidth() - regularSize - 50),
                        int(w - regularSize - 50));
                //Regularpositionh =0 -> Position on top
                double regularPositionh = 50;
            //Draw vertical line
            path.MoveToPoint(regularPositionw+regularSize/2, regularPositionh);
            path.AddLineToPoint(regularPositionw+regularSize/2, regularPositionh+regularSize);
            //Draw horizontal line
            path.MoveToPoint(regularPositionw, regularPositionh+regularSize/2);
            path.AddLineToPoint(regularPositionw+regularSize, regularPositionh+regularSize/2);
            //Draw circle
            path.AddCircle(regularPositionw+regularSize/2,regularPositionh+regularSize/2,regularSize);
            path.CloseSubpath();
            //Draw rectangle
            path.AddRectangle(regularPositionw, regularPositionh, regularSize, regularSize);
                gc->StrokePath(path);
                delete gc;
            }
        //####Test code for alpha painting####
        }
    }
}

wxSize ImageWindow::setBitMap() {

    wxFileDialog openFileDialog(this, _("Pick an image"), "", "",
            "png files (*.png)|*.png", wxFD_OPEN);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return wxSize(w, h);     // the user changed idea...

    if (bitmap != nullptr) {
        delete bitmap;
        bitmap = nullptr;
    }

    bitmap = new wxBitmap(openFileDialog.GetPath(), wxBITMAP_DEFAULT_TYPE);
    w = bitmap->GetWidth();
    h = bitmap->GetHeight();
    SetScrollbars(1, 1, w, h, 0, 0);
    Refresh();
    return wxSize(w, h);
}

wxSize ImageWindow::setBitMap(wxString imgPath) {
    if (bitmap != nullptr) {
        delete bitmap;
        bitmap = nullptr;
    }
    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:

    bitmap = new wxBitmap(imgPath, wxBITMAP_DEFAULT_TYPE);
    if (!(bitmap->IsOk())) {
        std::cout << "image not successfully loaded" << std::endl;
    }
    w = bitmap->GetWidth();
    h = bitmap->GetHeight();
//    SetMinClientSize(wxSize(w, h));
    SetScrollbars(1, 1, w, h, 0, 0);
    Refresh();
    return wxSize(w, h);
}

wxSize ImageWindow::copyBitMap(wxBitmap* bm) {
    delete bitmap;
    bitmap = bm;
    w = bitmap->GetWidth();
    h = bitmap->GetHeight();
    SetMinClientSize(wxSize(w, h));
    return getSize();

}

wxSize ImageWindow::getSize() {
    return wxSize(w, h);
}

void ImageWindow::switchSelected(wxMouseEvent& event) {
    if (isSelectible) {
    isSelected = !isSelected;
        if (isSelected) {
            setChanged();
            try {
                notifyObserver(std::string("selected"), this);
            } catch (std::exception& e) {
                std::cerr << e.what() << '\n';
            }
        } else {
            setChanged();
            try {
                notifyObserver(std::string("unselected"), this);
            } catch (std::exception& e) {
                std::cerr << e.what() << '\n';
            }
        }
        Refresh();
    }
    if (isSelected) {
        std::cout << "Image selected" << std::endl;
    } else
        std::cout << "Image unselected" << std::endl;
}

void ImageWindow::forbidSelection() {
    isSelectible = false;
}
wxBitmap* ImageWindow::getBitmap() {
    return bitmap;
}
