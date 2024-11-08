#ifndef REGFRAME_H
#define REGFRAME_H

#include <wx/wx.h>
#include "components/Dialog.h"
#include "components/myCtrl.h"

class RegisterFrame : public wxFrame {
    public:
    RegisterFrame();
    ~RegisterFrame() {
        delete panel;
        delete vbox;
        delete textTitle;
        delete subTitle;
        delete regTitle;
        delete usernameSizer;
        delete passwordSizer;
        delete confpasswordSizer;
        delete userCtrl;
        delete passCtrl;
        delete confCtrl;
        delete ptr_dialog;
    }
    // members:
        wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800,600));
        wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
        wxStaticText* textTitle = new wxStaticText(panel, wxID_ANY, "Chatterchums");
        wxStaticText* subTitle = new wxStaticText (panel, wxID_ANY, "A Place for Chats!");
        wxStaticText* regTitle = new wxStaticText (panel, wxID_ANY, "Register User");


         wxBoxSizer* usernameSizer = new wxBoxSizer(wxHORIZONTAL);
         wxBoxSizer* passwordSizer = new wxBoxSizer(wxHORIZONTAL);
         wxBoxSizer* confpasswordSizer = new wxBoxSizer(wxHORIZONTAL);

         myCtrl* userCtrl =  new myCtrl(panel, wxID_ANY);
         myCtrl* passCtrl = new myCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
         myCtrl* confCtrl = new myCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    
        RegBackDialog *ptr_dialog;
    
    void OnButtonClick(wxCommandEvent &event);
    void OnBackButtonClick(wxCommandEvent &event);
};


#endif