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
#include <exception>

ImageWindow::ImageWindow(wxWindow* parent, std::string path) :
        wxScrolledWindow(parent, wxID_ANY), imPath(path), selected(false), selectible(
                true) {
    setBitmap(path);
    SetMinClientSize(wxSize(600, 600));
    Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent& event) {
        switchSelected();
        try {
            notifyObserver(std::string("select"), this);
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    });

}

ImageWindow::~ImageWindow() {
}

void ImageWindow::OnDraw(wxDC& dc) {

    if (!hasImage()) {
        dc.SetBrush(wxNullBrush); // blue filling
        dc.SetPen(wxPen(wxColour(110, 20, 240), 10));

        auto minSize = GetMinClientSize();
        dc.DrawRectangle((minSize.GetWidth() - 200) / 2,
                (minSize.GetHeight() - 50) / 2, 200, 50);
        dc.DrawText(wxT("Pick an image to get started !"),
                (minSize.GetWidth() - 200) / 2 + 10,
                (minSize.GetHeight() - 50) / 2 + 10);

    } else {
        int* x = new int;
        int* y = new int;

        GetSize(x, y);
        int yScroll = GetScrollPos(wxVERTICAL);
        int xScroll = GetScrollPos(wxHORIZONTAL);

        dc.SetClippingRegion(xScroll, yScroll, *x + xScroll, *y + yScroll); //Will not draw outside clipping region, increases performances
        dc.DrawBitmap(bitmap, 0, 0, false);

        if (selected) {
            //####Test code for alpha painting####
            wxPaintDC paintDc(this);
            wxGraphicsContext *gc = wxGraphicsContext::Create(paintDc);
            if (gc) {
                gc->SetPen(wxPen(wxColour(250, 5, 5), 5));
//            wxPen (const wxColour &colour, int width=1, wxPenStyle style=wxPENSTYLE_SOLID)
                wxGraphicsPath path = gc->CreatePath();
                double regularSize = 30.0;
                //Regularpositionw =0 -> Position on the left
                //SEE GetVirtualSize gives total size including scrolled unvisible parts of the window. GetSize gives only onscreen window size
                double regularPositionw = std::min(
                        int(GetSize().GetWidth() - regularSize - 50),
                        int(bitmap.GetWidth() - regularSize - 50));
                //Regularpositionh =0 -> Position on top
                double regularPositionh = 50;
                //Draw vertical line
                path.MoveToPoint(regularPositionw + regularSize / 2,
                        regularPositionh);
                path.AddLineToPoint(regularPositionw + regularSize / 2,
                        regularPositionh + regularSize);
                //Draw horizontal line
                path.MoveToPoint(regularPositionw,
                        regularPositionh + regularSize / 2);
                path.AddLineToPoint(regularPositionw + regularSize,
                        regularPositionh + regularSize / 2);
                //Draw circle
                path.AddCircle(regularPositionw + regularSize / 2,
                        regularPositionh + regularSize / 2, regularSize);
                path.CloseSubpath();
                //Draw rectangle
                path.AddRectangle(regularPositionw, regularPositionh,
                        regularSize, regularSize);
                gc->StrokePath(path);
                delete gc;
            }
            //####Test code for alpha painting####
        }
    }
}

void ImageWindow::switchSelected() {
    clearChanged();
    if (selectible) {
        setChanged();
        selected = !selected;

        Refresh();
        if (selected) {
            std::cout << "Image selected" << std::endl;
        } else
            std::cout << "Image unselected" << std::endl;
    }
}

void ImageWindow::forbidSelection() {
    selectible = false;
}

void ImageWindow::iconize(wxSize size) {
    bitmap = bitmap.ConvertToImage().Rescale(size.GetWidth(), size.GetHeight());
    SetScrollbars(0, 0, 0, 0, 0, 0);
    SetMinClientSize(size); //So that scrollbars are not needed
}

/**
 *
 * @param path chemin vers l'image ou "" pour pas d'image
 */
void ImageWindow::setBitmap(std::string path) {

    if (path != "") {
        bitmap.LoadFile(path);
        if (!(this->bitmap.IsOk())) {
            throw std::invalid_argument("image not successfully loaded");
        } else {
            SetScrollbars(1, 1, bitmap.GetWidth(), bitmap.GetHeight(), 0, 0);
            imPath = path;
        }
    } else {
        imPath = path;
    }
}

bool ImageWindow::hasImage() const {
    return imPath != "";
}

std::string ImageWindow::getImPath() const {
    return imPath;
}

bool ImageWindow::isSelected() const {
    return selected;
}
