#ifndef STARTUPFRAME_H
#define STARTUPFRAME_H


#include <wx/wx.h>

enum startbuttons {
    LOGINID = 11002,
    REGISTERID = 11003,
    EXITID = 11004
};

class StartupFrame : public wxFrame {
private:
    wxButton *loginBtn;
    wxButton *regBtn;
public:
    StartupFrame();
    void OnLoginButtonClick(wxCommandEvent &event);
    void OnRegButtonClick(wxCommandEvent &event);
};

#endif