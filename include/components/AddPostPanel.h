#ifndef ADDPOST_H
#define ADDPOST_H


#include <wx/wx.h>
#include <classes/Post.h>
#include "database/postDao.h"
#include "AllPostsPane.h"
#include "classes/User.h"
#include "myCtrl.h"

    class AddPostPanel : public wxPanel {
    public:
        AddPostPanel(wxWindow* parent, AllPostsPane* view, User user) : wxPanel(parent), m_view(view), user_(user) {
            wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
            SetBackgroundColour(wxColor(25, 25, 25));

            wxStaticText* addpostTitle = new wxStaticText(this, wxID_ANY, "Add New Post");
            wxStaticText* subtitle = new wxStaticText(this, wxID_ANY, "add a new post to the main feed.");
            addpostTitle->SetFont(wxFont(31, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            subtitle->SetFont(wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            addpostTitle->SetForegroundColour(wxColor(255, 255, 255));
            subtitle->SetForegroundColour(wxColor(60, 60, 60));

            boxSizer->Add(addpostTitle, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 50);
            boxSizer->Add(subtitle, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 5);

            textCtrl = new myCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, 100), wxTE_MULTILINE);
            boxSizer->Add(textCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 20);

            wxButton* addButton = new wxButton(this, wxID_ANY, "Add Post");
            addButton->SetBackgroundColour(wxColor(0, 0, 0));
            addButton->SetForegroundColour(wxColor(100, 209, 10));
            boxSizer->Add(addButton, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
            addButton->Bind(wxEVT_BUTTON, AddPostPanel::OnButtonClick, this);

            SetSizerAndFit(boxSizer);
        }

        void OnButtonClick(wxCommandEvent &event) {
            std::string text = textCtrl->GetValue().ToStdString();
            std::string username = user_.name;
            Post post(text, 29, username);

            PostDAO dao_post;
            dao_post.insert(post);

            m_view->AddPanelToPane(post);

            wxSize panelSize = m_view->GetLastPanelSize();

            wxSize contentSize = m_view->GetVirtualSize();
            contentSize.y += panelSize.y + 100;  // Adjust for panel size and spacing
            m_view->SetVirtualSize(contentSize);

            m_view->Layout();
            m_view->GetSizer()->Layout();
            m_view->Refresh();
        }

    private:
        AllPostsPane* m_view;
        myCtrl* textCtrl;
        User user_;
    };
#endif


