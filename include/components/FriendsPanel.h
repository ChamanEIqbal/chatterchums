#ifndef FRIENDSPANEL_H
#define FRIENDSPANEL_H

#include <wx/wx.h>
#include <wx/scrolwin.h>
#include "database/friendsDao.h"
#include "database/userDao.h"
#include "classes/User.h"
#include "classes/Graph.h"
#include "main.h"

class FriendsPanel : public wxPanel {
public:
    FriendsPanel(wxWindow* parent, User user, Graph& Graph) : wxPanel(parent), user_(user) {

        FriendsDAO dao_friends;
        UserDAO dao_user;
        vector<string> usernames = dao_friends.getFriends(user.id);


        wxBoxSizer* mainBoxSizer = new wxBoxSizer(wxVERTICAL);

        // First Title
        wxStaticText* titleLabel1 = new wxStaticText(this, wxID_ANY, "Chatterchums - Your Friends");
        titleLabel1->SetFont(wxFont(30, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        titleLabel1->SetForegroundColour(wxColour(255, 255, 255));
        mainBoxSizer->Add(titleLabel1, 0, wxTOP | wxLEFT, 10); 
        
        // First Scrolled Window
        wxBoxSizer* boxSizer1 = new wxBoxSizer(wxHORIZONTAL);
        wxScrolledWindow* scrolledWindow1 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL);
        wxBoxSizer* scrolledBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);

        for (int i = 0; i < usernames.size(); ++i) {  
            wxPanel* squarePanel = CreateSquarePanel(scrolledWindow1, usernames[i]);
            scrolledBoxSizer1->Add(squarePanel, 0, wxALL, 10);
        }

        scrolledWindow1->SetSizer(scrolledBoxSizer1);
        scrolledWindow1->SetMinSize(wxSize(400, -1));  
        scrolledWindow1->SetScrollRate(10, 0);
        scrolledWindow1->SetBackgroundColour(wxColour(0, 0, 0));

        boxSizer1->Add(scrolledWindow1, 1, wxEXPAND);
        mainBoxSizer->Add(boxSizer1, 1, wxEXPAND);

        // Second Title
        wxStaticText* titleLabel2 = new wxStaticText(this, wxID_ANY, "Chatterchums - Your Recommended Friends");
        titleLabel2->SetFont(wxFont(30, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        titleLabel2->SetForegroundColour(wxColour(255, 255, 255));
        mainBoxSizer->Add(titleLabel2, 0, wxTOP | wxLEFT, 10); 

        // Second Scrolled Window
        wxBoxSizer* boxSizer2 = new wxBoxSizer(wxHORIZONTAL);
        wxScrolledWindow* scrolledWindow2 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL);
        wxBoxSizer* scrolledBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);


         
            vector<string> recommended = dao_user.getUsernamesFromIds(Graph.dfsRecommendation(user_.id, 15));

        for (int i = 0; i < recommended.size(); ++i) {  
            wxPanel* squarePanel = CreateSquarePanel(scrolledWindow2, recommended[i]);
            scrolledBoxSizer2->Add(squarePanel, 0, wxALL, 10);
        }

        scrolledWindow2->SetSizer(scrolledBoxSizer2);
        scrolledWindow2->SetMinSize(wxSize(400, -1));  
        scrolledWindow2->SetScrollRate(10, 0);
        scrolledWindow2->SetBackgroundColour(wxColour(0, 0, 0));

        boxSizer2->Add(scrolledWindow2, 1, wxEXPAND);
        mainBoxSizer->Add(boxSizer2, 1, wxEXPAND);

        // Set the main box sizer as the sizer for the panel
        SetSizerAndFit(mainBoxSizer);

        // Set the background color for the main panel
        SetBackgroundColour(wxColour(0, 0, 0));
    }

private:
    wxPanel* CreateSquarePanel(wxWindow* parent, const wxString& name) {
        // Create a square panel
        wxPanel* panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
        panel->SetBackgroundColour(wxColour(25, 25, 25));  // Square panel background color

        // Add a text control to display the name
        wxStaticText* nameLabel = new wxStaticText(panel, wxID_ANY, name, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        nameLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        nameLabel->SetForegroundColour(wxColour(100, 209, 10));  // Text color

        // Create a box sizer for the square panel with margins
        wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
        panelSizer->Add(nameLabel, 1, wxEXPAND | wxALL, 5);  // Margins

        // Set the box sizer as the sizer for the panel
        panel->SetSizer(panelSizer);

        return panel;
    }

    User user_;
};

#endif
