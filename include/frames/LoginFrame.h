
#ifndef LOGINFRAME_H
#define LOGINFRAME_H
#include <wx/wx.h>
#include "components/myCtrl.h"


class LoginFrame : public wxFrame {
    private:
    public:
    LoginFrame(); 
    void OnButtonClick(wxCommandEvent &event);
    myCtrl* passCtrl;
    myCtrl* userCtrl;
};





#endif