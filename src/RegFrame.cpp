#include "frames/RegFrame.h"
#include "components/Dialog.h"
#include "frames/StartupFrame.h" // to go back to main from ptr_dialog (regback)
#include "database/userDao.h"


RegisterFrame::RegisterFrame() 
: wxFrame(NULL, wxID_ANY, "Register User", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE && ~wxCAPTION) {
    
    panel->SetBackgroundColour(wxColour(0,0,0));
    ptr_dialog = new RegBackDialog(this, "Back / Exit", "Back to Menu, or Exit the Program");

    textTitle->SetFont(wxFont(72, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
    textTitle->SetForegroundColour(wxColour(255,255,255));
    subTitle->SetFont(wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    subTitle->SetForegroundColour(wxColour(69,69,69));
    regTitle->SetFont(wxFont(9, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    regTitle->SetForegroundColour(wxColour(69,69,69));
    vbox->Add(textTitle, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxTOP, 5);
    vbox->Add(subTitle, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 25);
    vbox->Add(regTitle, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER_HORIZONTAL, 3);


    wxPanel* tempPanel = new wxPanel(panel);
    vbox->Add(tempPanel, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 100);

   
    wxStaticText* userLabel = new wxStaticText(panel, wxID_ANY, "Username: ");
    userLabel->SetFont(wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    userLabel->SetForegroundColour(wxColour(69,69,69));
    usernameSizer->Add(userLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    usernameSizer->Add(userCtrl, 1, wxEXPAND);
    vbox->Add(usernameSizer, 0, wxEXPAND | wxRIGHT | wxLEFT | wxTOP, 10);

    wxStaticText* passLabel = new wxStaticText(panel, wxID_ANY, "Password: ");
    passLabel->SetFont(wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    passLabel->SetForegroundColour(wxColour(69,69,69));
    passwordSizer->Add(passLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    passwordSizer->Add(passCtrl, 1, wxEXPAND);
    vbox->Add(passwordSizer, 0, wxEXPAND | wxRIGHT | wxLEFT | wxTOP, 10);

    wxStaticText* confPassLabel = new wxStaticText(panel, wxID_ANY, "Confirm:  ");
    confPassLabel->SetFont(wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    confPassLabel->SetForegroundColour(wxColour(69,69,69));
    confpasswordSizer->Add(confPassLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    confpasswordSizer->Add(confCtrl, 1, wxEXPAND);
    vbox->Add(confpasswordSizer, 0, wxEXPAND | wxRIGHT | wxLEFT | wxTOP, 10);

    wxButton* registerButton = new wxButton(panel, wxID_ANY, "Register");
    vbox->Add(registerButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");
    vbox->Add(backButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    registerButton->Bind(wxEVT_BUTTON, RegisterFrame::OnButtonClick, this);
    backButton->Bind(wxEVT_BUTTON, RegisterFrame::OnBackButtonClick, this);


    panel->SetSizer(vbox);
 }

 void RegisterFrame::OnButtonClick(wxCommandEvent &event) {
        std::string username = userCtrl->GetValue().ToStdString();
        std::string password = passCtrl->GetValue().ToStdString();
        std::string confpassword = confCtrl->GetValue().ToStdString();

       if (username.empty() && password.empty() && confpassword.empty()) {
              Dialog dialog("ERROR:", "Field is missing!");
              dialog.ShowModal();
       } else {

       UserDAO dao_user;
       bool unique = dao_user.is_unique(username);
       if(unique) {
        if(password == confpassword) {
              dao_user.insert(username, password);
              Dialog dialog("Success!", "User inserted successfully");
              dialog.ShowModal();

              this->Hide();

              StartupFrame *frame = new StartupFrame();
              frame->SetSize(wxSize(800,600));
              frame->Center();
              frame->Maximize();
              frame->Show(true);
        } else {
              Dialog dialog("Passwords don't match!", "Please confirm the password correctly.");
              dialog.ShowModal();
        }
       } else {
              Dialog dialog("Username given is already taken!", "Please enter an unused username.");
              dialog.ShowModal();
              }
       }
 }

 void RegisterFrame::OnBackButtonClick(wxCommandEvent &event) {
      
       this->Hide();

      StartupFrame *frame = new StartupFrame();
      frame->SetSize(wxSize(800,600));
      frame->Center();
      frame->Maximize();
      frame->Show(true);
 }