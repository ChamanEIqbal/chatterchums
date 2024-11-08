#ifndef MYNOTEBOOK_H
#define MYNOTEBOOK_H
#include <wx/wx.h>
#include "components/AllPostsPane.h"

class MyNotebook : public wxNotebook {
public:
    MyNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxEmptyString)
        : wxNotebook(parent, id, pos, size, style, name) {
            SetSizeHints(wxDefaultSize, wxDefaultSize);
        }

    void OnDrawTab(wxDC& dc, wxRect tab, int selected, wxBitmap& bitmap, const wxString& label, const wxFont& font, int textControl, int alignment, int wxNotebookHitTestResult)
        {
            // Background color
            dc.SetBrush(wxBrush(wxColour(0, 0, 0)));  // black color
            dc.SetBackground(dc.GetBrush());
            dc.Clear();

            // Border
            dc.SetPen(wxPen(wxColour(0, 0, 0), 1, wxPENSTYLE_SOLID));  // Black border, 1 pixel width
            dc.SetBrush(*wxTRANSPARENT_BRUSH);  // Transparent brush
            dc.DrawRectangle(tab);

            // Bitmap
            if (bitmap.IsOk()) {
                dc.DrawBitmap(bitmap, tab.GetLeft(), tab.GetTop(), true);
            }

            // Text color
            dc.SetTextForeground(wxColour(100, 209, 10));  // Red color

            // Draw the label
            dc.DrawText(label, tab.GetLeft() + 5, tab.GetTop() + 5);  // Adjust position as needed
        }
};
#endif