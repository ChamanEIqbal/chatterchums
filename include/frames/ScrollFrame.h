#include <wx/wx.h>
class ScrollFrame  : public wxFrame
{
public:
wxScrolledWindow *scrolledPanel;
wxBoxSizer *frameSizer;
wxBoxSizer *frameSizer2;
wxPanel *hiddenPanel;
    ScrollFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE)
    {
        SetBackgroundColour(wxColor(0,0,0));
        frameSizer = new wxBoxSizer(wxVERTICAL);
        frameSizer2 = new wxBoxSizer(wxVERTICAL);
        scrolledPanel = new wxScrolledWindow(this, wxID_ANY);
        scrolledPanel->SetBackgroundColour(wxColor(0,0,0));


        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

        for (int w = 1; w <= 120; w++)
        {
            wxPanel* panel = new wxPanel(scrolledPanel, wxID_ANY);

            // Set the background color of the panel to black
            panel->SetBackgroundColour(wxColour(0, 0, 0));  // RGB: (0, 0, 0) is black

            wxStaticText* text = new wxStaticText(panel, wxID_ANY, wxString::Format(wxT("Hi, I am number '%i'"), w));

            // Set the text color to white
            text->SetForegroundColour(wxColour(255, 255, 255));  // RGB: (255, 255, 255) is white

            wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
            panelSizer->Add(text, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 3);
            panel->SetSizer(panelSizer);

            sizer->Add(panel, 0, wxALL, 3);
        }

        scrolledPanel->SetSizer(sizer);
        scrolledPanel->FitInside(); // ask the sizer about the needed size
        scrolledPanel->SetScrollRate(5, 5);

        wxButton *btn = new wxButton(this, wxID_ANY, "POST");

        hiddenPanel = new wxPanel(this);
        hiddenPanel->Hide();
        hiddenPanel->SetBackgroundColour(wxColor(0,0,0));
        wxBoxSizer *hiddenPanelSizer = new wxBoxSizer(wxVERTICAL);
        wxStaticText* hiddenText = new wxStaticText(hiddenPanel, wxID_ANY, "CHAT PLS");
        hiddenText->SetForegroundColour(wxColor(255,255,255));
        hiddenPanelSizer->Add(hiddenText, 0, wxBOTTOM | wxALIGN_CENTER_HORIZONTAL, 100);
        hiddenPanel->SetSizer(hiddenPanelSizer);


        frameSizer->Add(scrolledPanel, 6, wxEXPAND | wxBOTTOM, 20);
        frameSizer->Add(btn, 1, wxTOP | wxEXPAND, 15);

        frameSizer2->Add(hiddenPanel, 6, wxEXPAND | wxBOTTOM, 20);

        btn->Bind(wxEVT_BUTTON, OnButtonClick, this);
        SetSizerAndFit(frameSizer);
    }

    void OnButtonClick(wxCommandEvent &evt) {
        if (scrolledPanel->IsShown()) {
            SetSizerAndFit(nullptr);
            scrolledPanel->Hide();
            SetSizerAndFit(frameSizer2);
            hiddenPanel->Show();
        } else {
            SetSizerAndFit(nullptr);
            hiddenPanel->Hide();
            SetSizerAndFit(frameSizer);
            scrolledPanel->Show();
        }
        Layout();
        Refresh();
        Maximize();
    }
};