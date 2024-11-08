#ifndef DIALOG_H
#define DIALOG_H
#include <wx/wx.h>
#include "frames/StartupFrame.h" // to go back to main from ptr_dialog (regback)

class Dialog : public wxDialog {
public:
    Dialog(const wxString& title, const wxString& message)
        : wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
    {
        SetBackgroundColour(wxColor(0,0,0));
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* text = new wxStaticText(this, wxID_ANY, message, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        text->SetForegroundColour(wxColor(100,209,10));
        sizer->Add(text, 0, wxALL | wxALIGN_CENTER, 10);

        wxButton* okButton = new wxButton(this, wxID_OK, "OK");
        okButton->SetBackgroundColour(wxColor(0,0,0));
        okButton->SetForegroundColour(wxColor(100,209,10));
        sizer->Add(okButton, 0, wxALL | wxALIGN_CENTER, 10);

        SetSizerAndFit(sizer);
        CentreOnScreen();
    }
};

class RegBackDialog : public wxDialog {
    private: 
    wxFrame* parentPointer;
    public:
    
    RegBackDialog(wxFrame* parent, const wxString &title, const wxString &msg) 
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize) {
            parentPointer = parent;
            wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
            wxStaticText *dMsg = new wxStaticText(this, wxID_ANY, msg);
            vbox->Add(dMsg, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

            wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
            wxButton *btnEXIT = new wxButton(this, 69, "Exit");
            wxButton *btnBACK = new wxButton(this, 70, "Back");
            hbox->Add(btnBACK, 0, wxALL, 5);
            hbox->Add(btnEXIT, 0, wxALL, 5);

            vbox->Add(hbox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

            SetSizerAndFit(vbox);
            CenterOnScreen();

            btnEXIT->Bind(wxEVT_BUTTON, RegBackDialog::onRegBackButton, this);
            btnBACK->Bind(wxEVT_BUTTON, RegBackDialog::onRegBackButton, this);

    }    


    void onRegBackButton(wxCommandEvent &evt) {
        int btnID = evt.GetId();
        if(btnID == 69) {
            if(parentPointer) {
                parentPointer->Close();
            }
        } else {
                StartupFrame *frame = new StartupFrame();
                frame->Center();
                frame->SetSize(wxSize(800,600));
                frame->Show(true);
                parentPointer->Close();

        }
    }


};

#endif