#ifndef DASHBOARD_H
#define DASHBOARD_H


#include <wx/wx.h>
#include <wx/notebook.h>
#include "components/MyNotebook.h"
#include "components/ProfilePanel.h"
#include "components/AllPostsPane.h"
#include "components/AddPostPanel.h"
#include "components/FriendsPanel.h"
#include "classes/User.h"
#include "main.h"

Graph MyApp::App_Graph;

class Dashboard : public wxFrame {
public:
    Dashboard(const wxString& title, const wxPoint& pos, const wxSize& size, User user)
        : wxFrame(NULL, wxID_ANY, title, pos, size,  wxDEFAULT_FRAME_STYLE || ~wxCAPTION), m_user(user) {
        
        notebook = new MyNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_LEFT);
        notebook->SetThemeEnabled(false);
        notebook->SetBackgroundColour(wxColor(0,0,0));
        // Add panels to the notebook


        /*PROFILE PANEL*/
        ProfilePanel* profile_panel = new ProfilePanel(notebook, user, this);
        notebook->AddPage(profile_panel, wxString::Format("My Profile"), true);
        /*PROFILE PANEL END */


        /* ALLPOSTS SCROLL WINDOW */
        AllPostsPane* all_posts_pane = new AllPostsPane(notebook, wxID_ANY);
        notebook->AddPage(all_posts_pane, wxString::Format("Mainfeed"));
        /*ALLPOSTS SCROLL WINDOW END */


        /* ADD POST PANEL */
        AddPostPanel *add_post_panel = new AddPostPanel(notebook, all_posts_pane, user);
        notebook->AddPage(add_post_panel, wxString::Format("Add Post"));
         /*ADD POST PANEL END */

        /*ADD FRIENDS PANEL*/
        Graph graph = MyApp::GetGraph();
        FriendsPanel *add_friends_panel = new FriendsPanel(notebook, user, graph);
        notebook->AddPage(add_friends_panel, wxString::Format("Friends"));
        /*Add FRIENDS PANEL END */

        // Create a sizer for the frame
        wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);

        // Add the notebook to the frame sizer
        frameSizer->Add(notebook, 1, wxEXPAND);

        // Set the frame sizer
        SetSizerAndFit(frameSizer);

        // Bind the notebook page changing event
        Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &Dashboard::OnPageChanged, this);
    }

    void OnPageChanged(wxBookCtrlEvent& event) {
        // Get the selected page index
        int pageIndex = event.GetSelection();

        // Hide the previous page
        if (previousPageIndex >= 0) {
            notebook->GetPage(previousPageIndex)->Hide();
        }

        // Show the selected page
        notebook->GetPage(pageIndex)->Show();

        // Update the previous page index
        previousPageIndex = pageIndex;

        Layout();
        Refresh();
    }

private:
    MyNotebook* notebook;
    User m_user;
    int previousPageIndex = -1;
};



#endif

