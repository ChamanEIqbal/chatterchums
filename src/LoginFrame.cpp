#include "frames/LoginFrame.h"
#include "frames/NextFrame.h" // not using
#include "frames/Dashboard.h"
#include "database/userDao.h"
#include "components/Dialog.h"
using namespace std;

LoginFrame::LoginFrame() 
: wxFrame(nullptr, wxID_ANY, "Login", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE && ~wxCAPTION) {
   wxPanel* panel = new wxPanel(this);
   panel->SetBackgroundColour(wxColour(0,0,0));
   wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

   wxStaticText* textTitle = new wxStaticText(panel, wxID_ANY, "Chatterchums");
   wxStaticText* subTitle = new wxStaticText (panel, wxID_ANY, "A place for chats");
   textTitle->SetFont(wxFont(72, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
   textTitle->SetForegroundColour(wxColour(255,255,255));
   subTitle->SetFont(wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
   subTitle->SetForegroundColour(wxColour(69,69,69));
   vbox->Add(textTitle, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxTOP, 5);
   vbox->Add(subTitle, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 25);


    wxPanel* tempPanel = new wxPanel(panel);
    vbox->Add(tempPanel, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 125);

    wxBoxSizer* usernameSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* passwordSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* userLabel = new wxStaticText(panel, wxID_ANY, "Username: ");
    userLabel->SetFont(wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    userLabel->SetForegroundColour(wxColour(69,69,69));
    usernameSizer->Add(userLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    userCtrl =  new myCtrl(panel, wxID_ANY);
    usernameSizer->Add(userCtrl, 1, wxEXPAND);
    vbox->Add(usernameSizer, 0, wxEXPAND | wxRIGHT | wxLEFT | wxTOP, 10);

    wxStaticText* passLabel = new wxStaticText(panel, wxID_ANY, "Password: ");
    passLabel->SetFont(wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    passLabel->SetForegroundColour(wxColour(69,69,69));
    passwordSizer->Add(passLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    passCtrl = new myCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    passwordSizer->Add(passCtrl, 1, wxEXPAND);
    vbox->Add(passwordSizer, 0, wxEXPAND | wxRIGHT | wxLEFT | wxTOP, 10);

    wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login");
    vbox->Add(loginButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    loginButton->Bind(wxEVT_BUTTON, LoginFrame::OnButtonClick, this);

    panel->SetSizer(vbox);
      
}

void LoginFrame::OnButtonClick(wxCommandEvent &event) {
    std::string username = userCtrl->GetValue().ToStdString();
    std::string userpass = passCtrl->GetValue().ToStdString();
    UserDAO login_dao;
    int i = 0;
    vector<User> users = login_dao.selectAllFromTable();
    User user;
    for(vector<User>::iterator it = users.begin(); it != users.end(); ++it) {
        user = *it;
        if((user.name == username) && (user.m_password == userpass)) {
            ++i;
            break;
        }
    }

    cout << i << endl;

    if(i == 1) {
        cout << "found!" << endl;
        this->Close(true);
        Dashboard *frame = new Dashboard("Dashboard", wxPoint(50,50), wxSize(800,600), user);
        frame->Maximize();
        frame->Show(true);
    } else if (i == 0) {
        Dialog dialog("Login failed.", "incorrect username or password.");
        dialog.ShowModal();
    }
}