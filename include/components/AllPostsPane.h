#ifndef ALLPOSTSPANE_H
#define ALLPOSTSPANE_H

#include "wx/wx.h"
#include <iostream>
#include "classes/Post.h"
#include "components/MyNotebook.h"
#include "database/postDao.h"

class AllPostsPane : public wxScrolledWindow
{
public:
    AllPostsPane(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id)
    {
      boxsizer = new wxBoxSizer(wxVERTICAL);
        
           PostDAO dao_post;
           vector<Post> posts = dao_post.selectAllFromDatabase();

           
            for(int i = 0; i < posts.size(); i++) {
                wxPanel* panel = new wxPanel(this);
                wxBoxSizer* internalsizer = new wxBoxSizer(wxVERTICAL);
                panel->SetBackgroundColour(wxColor(20,20,20));

                wxStaticText* text = new wxStaticText(panel, wxID_ANY, posts[i].m_text);
                wxStaticText* author = new wxStaticText(panel, wxID_ANY, "By: " + posts[i].m_author);
                wxStaticText* date = new wxStaticText(panel, wxID_ANY, "On: " + posts[i].m_date);
                wxFont font = wxFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
                text->SetFont(font);
                author->SetFont(font);
                date->SetFont(font);
                text->SetForegroundColour(wxColor(255,255,255));
                author->SetForegroundColour(wxColor(255,255,255));
                date->SetForegroundColour(wxColor(255,255,255));

                internalsizer->Add(text, 0, wxBOTTOM, 10);
                internalsizer->Add(author,0,wxBOTTOM, 10);
                internalsizer->Add(date, 0, wxBOTTOM, 100);

                panel->SetSizer(internalsizer);
                boxsizer->Add(panel, 1, wxEXPAND | wxTOP, 10);
                }                
                 
            SetSizer(boxsizer);
            SetScrollRate(20,20);  

    }

    void AddPanelToPane(Post post) {
              wxPanel* panel = new wxPanel(this);
                wxBoxSizer* internalsizer = new wxBoxSizer(wxVERTICAL);
                panel->SetBackgroundColour(wxColor(20,20,20));

                wxStaticText* text = new wxStaticText(panel, wxID_ANY, post.m_text);
                wxStaticText* author = new wxStaticText(panel, wxID_ANY, "By: " + post.m_author);
                wxStaticText* date = new wxStaticText(panel, wxID_ANY, "On: " + post.m_date);
                wxFont font = wxFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
                text->SetFont(font);
                author->SetFont(font);
                date->SetFont(font);
                text->SetForegroundColour(wxColor(255,255,255));
                author->SetForegroundColour(wxColor(255,255,255));
                date->SetForegroundColour(wxColor(255,255,255));

                internalsizer->Add(text, 0, wxBOTTOM, 10);
                internalsizer->Add(author,0,wxBOTTOM, 10);
                internalsizer->Add(date, 0, wxBOTTOM, 100);

                panel->SetSizer(internalsizer);
                panels.push_back(panel);
                boxsizer->Add(panel, 1, wxEXPAND | wxTOP, 10);
                        
                UpdateVirtualSize();
    }

    wxSize GetLastPanelSize() const {
    if (!panels.empty()) {
        return panels.back()->GetSize();
    }
    return wxSize(0, 0);  // Return a default size if there are no panels
}

void UpdateVirtualSize() {
    // Update the virtual size of the scrolled window
    wxSize contentSize = GetVirtualSize();
    if (!panels.empty()) {
        contentSize.y += panels.back()->GetSize().y + 100;  // Adjust for panel size and spacing
    }
    SetVirtualSize(contentSize);

    // Refresh the layout
    Layout();
    GetSizer()->Layout();
    Refresh();
}

private:
    wxBoxSizer *boxsizer;
    vector<wxPanel*> panels;
};

#endif