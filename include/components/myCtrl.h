#ifndef MYCTRL_H
#define MYCTRL_H

#include <wx/wx.h>

class myCtrl : public wxTextCtrl {
    public:
     myCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString,
               const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
               long style = 0, const wxValidator& validator = wxDefaultValidator,
               const wxString& name = wxTextCtrlNameStr)
        : wxTextCtrl(parent, id, value, pos, size, style, validator, name) {
            SetForegroundColour(wxColor(100,209,10));
            SetBackgroundColour(wxColor(0,0,0));
        }
};


#endif