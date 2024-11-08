#include "frames/NextFrame.h"


NextFrame::NextFrame() 
: wxFrame(NULL, wxID_ANY, "Profile", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE && ~wxCAPTION) {
        wxPanel *panel = new wxPanel(this);

        panel->SetBackgroundColour(wxColour(0, 0, 0));
        panel->SetMinSize(wxSize(200,50));
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

        wxPanel *panelInside = new wxPanel(panel);

        panelInside->SetBackgroundColour(wxColour(15,15,15));
        panelInside->SetMinSize(wxSize(100,200));
        wxBoxSizer *sizerInside = new wxBoxSizer(wxHORIZONTAL);  

        wxBoxSizer* s1 = new wxBoxSizer(wxHORIZONTAL);
        wxPanel *left = new wxPanel(panelInside);
        wxPanel *right = new wxPanel(panelInside);

        left->SetBackgroundColour(wxColour(100,100,100));
        wxBoxSizer* leftSizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText *leftText = new wxStaticText(left, wxID_ANY, "LEFT", wxDefaultPosition, wxDefaultSize);
        leftText->SetFont(wxFont(15, wxFONTFAMILY_MODERN,  wxFONTSTYLE_NORMAL, wxFONTWEIGHT_HEAVY));
        leftSizer->AddStretchSpacer(1);
        leftSizer->Add(leftText, 0, wxALIGN_CENTER_VERTICAL);
        leftSizer->AddStretchSpacer(1);
        left->SetSizer(leftSizer);
        
        right->SetBackgroundColour(wxColour(255,255,255));
        wxBoxSizer *rightSizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText *rightText = new wxStaticText(right, wxID_ANY, "RIGHT", wxDefaultPosition, wxDefaultSize);
        rightText->SetFont(wxFont(15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_HEAVY));
        rightSizer->AddStretchSpacer(1);
        rightSizer->Add(rightText, 0, wxALIGN_CENTER_VERTICAL);
        rightSizer->AddStretchSpacer(1);
        right->SetSizer(rightSizer);




        s1->Add(left, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
        s1->Add(right, 1, wxEXPAND | wxALL, 5);


        panelInside->SetSizer(s1);

        sizerInside->Add(panelInside, 1, wxEXPAND | wxALL, 5);
        panel->SetSizerAndFit(sizerInside); 

        sizer->Add(panel, 1, wxEXPAND);


        SetSizerAndFit(sizer);


    }


// NAV BAR FORM, TEMPLATE?

/* 


 // user's object can be passed in the profile frame to have different profiles shown
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxPanel* panel = new wxPanel(this);

    panel->SetMinSize(wxSize(100,50));
    panel->SetBackgroundColour(wxColour(69,69,69));
    SetBackgroundColour(wxColour(0,0,0));

    // creating an hbox for vbox's second element with max taking up space: 6
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL); // will have 2 panels inside

    wxPanel* panel3 = new wxPanel(this);
    panel3->SetMinSize(wxSize(100,50));
    panel3->SetBackgroundColour(wxColour(69,69,69));

    wxPanel* panel2 = new wxPanel(this);
    panel2->SetMinSize(wxSize(100,50));
    panel2->SetBackgroundColour(wxColour(0,0,0));

    hbox->Add(panel3, 2, wxLEFT | wxRIGHT | wxEXPAND, 0);
    hbox->Add(panel2, 4, wxLEFT | wxRIGHT | wxEXPAND, 0);

    vbox->Add(panel, 1, wxBOTTOM | wxEXPAND, 10);
    vbox->Add(hbox, 6, wxLEFT | wxRIGHT | wxEXPAND, 0);
    SetSizer(vbox);



*/



// scrollable and non scrollable in a sizer



/*

  wxPanel* panel = new wxPanel(this);
        wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

        // Scrollable Panel
        wxScrolledWindow* scrolledPanel = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxSize(200, 300), wxVSCROLL);
        wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);

        // Add some content to the scrollable panel
        for (int i = 1; i <= 30; ++i)
        {
            wxString label = wxString::Format("Item %d", i);
            scrolledSizer->Add(new wxStaticText(scrolledPanel, wxID_ANY, label), 0, wxALL, 5);
        }

        scrolledPanel->SetSizer(scrolledSizer);
        scrolledPanel->SetScrollRate(0, 20);  // Set scroll rate if needed

        // Non-Scrollable Panel
        wxPanel* nonScrolledPanel = new wxPanel(panel);
        wxBoxSizer* nonScrolledSizer = new wxBoxSizer(wxVERTICAL);

        // Add some content to the non-scrollable panel
        nonScrolledSizer->Add(new wxStaticText(nonScrolledPanel, wxID_ANY, "Non-Scrollable Content"), 0, wxALL, 5);

        nonScrolledPanel->SetSizer(nonScrolledSizer);

        // Add the panels to the hbox
        hbox->Add(scrolledPanel, 1, wxEXPAND | wxALL, 10);
        hbox->Add(nonScrolledPanel, 0, wxALL, 10);

        panel->SetSizer(hbox);

*/