#ifndef PROFILEPANEL_H
#define PROFILEPANEL_H

#include <wx/wx.h>
#include "classes/User.h"
#include "frames/StartupFrame.h"

class ProfilePanel : public wxPanel {
private:
    User m_user;
    wxFrame* frame_;

public:
    ProfilePanel(wxWindow* parent, User user, wxFrame* parent_frame) : wxPanel(parent), m_user(user), frame_(parent_frame) {
        this->SetBackgroundColour(wxColor(25, 25, 25));
        wxBoxSizer* profile_sizer = new wxBoxSizer(wxVERTICAL);

        // Title and subtitle
        wxStaticText* chattertitle = new wxStaticText(this, wxID_ANY, "Chatterchums");
        chattertitle->SetFont(wxFont(72, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD, false));
        wxStaticText* chattersubtitle = new wxStaticText(this, wxID_ANY, "A place for chats!");
        chattersubtitle->SetFont(wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        chattertitle->SetForegroundColour(wxColor(255, 255, 255));
        chattersubtitle->SetForegroundColour(wxColor(69, 69, 69));

        profile_sizer->Add(chattertitle, 0, wxTOP | wxLEFT, 10);
        profile_sizer->Add(chattersubtitle, 0, wxTOP | wxLEFT, 20);

        // User info
        wxStaticText* chatterusername = new wxStaticText(this, wxID_ANY, "Welcome back, " + m_user.name + "!");
        chatterusername->SetFont(wxFont(24, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        chatterusername->SetForegroundColour(wxColor(255, 255, 255));

        profile_sizer->Add(chatterusername, 0, wxTOP, 25);

        // Logout button (moved to the bottom)
        wxButton* chatterlogout = new wxButton(this, wxID_ANY, "Logout");
        chatterlogout->SetBackgroundColour(wxColor(0, 0, 0));
        chatterlogout->SetForegroundColour(wxColor(100, 209, 10));

        profile_sizer->AddStretchSpacer(); // Add a stretchable spacer
        profile_sizer->Add(chatterlogout, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 20);

        chatterlogout->Bind(wxEVT_BUTTON, onClickButton, this);

        this->SetSizer(profile_sizer);
    }
    void onClickButton(wxCommandEvent &event) {
        frame_->Close(true);
    }
};

#endif
