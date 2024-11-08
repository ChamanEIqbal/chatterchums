#include "frames/StartupFrame.h"
#include "frames/LoginFrame.h"
#include "frames/RegFrame.h"

StartupFrame::StartupFrame()
    : wxFrame(NULL, wxID_ANY, "Chatterchums", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE && ~wxCAPTION)
{
    this->SetBackgroundColour(wxColor(0, 0, 0));

    wxPanel *panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColor(0, 0, 0));
    wxBoxSizer *frameSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *textSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *title = new wxStaticText(panel, wxID_ANY, "Chatterchums");
    title->SetFont(wxFont(72, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD, false));
    wxStaticText *subtitle = new wxStaticText(panel, wxID_ANY, "A place for chats!");
    subtitle->SetFont(wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    title->SetForegroundColour(wxColor(255, 255, 255));
    subtitle->SetForegroundColour(wxColor(69, 69, 69));

    textSizer->Add(title, 0, wxALIGN_CENTER_HORIZONTAL);
    textSizer->Add(subtitle, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    panel->SetSizer(textSizer);

    verticalSizer->Add(panel, 0, wxALIGN_CENTER_HORIZONTAL);

    wxPanel *tempPanel = new wxPanel(this);
    verticalSizer->Add(tempPanel, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER_HORIZONTAL, 60);

    wxBoxSizer *optionsSizer = new wxBoxSizer(wxHORIZONTAL);

    wxPanel *loginPanel = new wxPanel(this);
    wxBoxSizer *loginSizer = new wxBoxSizer(wxVERTICAL);
    loginPanel->SetBackgroundColour(wxColor(0, 0, 0));
    wxPanel *registerPanel = new wxPanel(this);
    wxBoxSizer *registerSizer = new wxBoxSizer(wxVERTICAL);
    registerPanel->SetBackgroundColour(wxColor(0, 0, 0));

    wxStaticText *loginOptionText = new wxStaticText(loginPanel, wxID_ANY, "Login");
    loginOptionText->SetFont(wxFont(36, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    loginOptionText->SetForegroundColour(wxColor(255, 255, 255));

    loginSizer->Add(loginOptionText, 0, wxALIGN_CENTER_HORIZONTAL);

    wxButton *loginBtn = new wxButton(loginPanel, wxID_ANY, ">>");
    loginBtn->SetBackgroundColour(wxColor(15, 15, 15));
    loginBtn->SetForegroundColour(wxColor(100, 209, 10));

    loginSizer->Add(loginBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 5);

    loginPanel->SetSizer(loginSizer);

    wxStaticText *registerOptionText = new wxStaticText(registerPanel, wxID_ANY, "Register");
    registerOptionText->SetFont(wxFont(36, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    registerOptionText->SetForegroundColour(wxColor(255, 255, 255));

    registerSizer->Add(registerOptionText, 0, wxALIGN_CENTER_HORIZONTAL);

    wxButton *regBtn = new wxButton(registerPanel, wxID_ANY, ">>");
    regBtn->SetBackgroundColour(wxColor(15, 15, 15));
    regBtn->SetForegroundColour(wxColor(100, 209, 10));

    registerSizer->Add(regBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 5);

    registerPanel->SetSizer(registerSizer);

    optionsSizer->Add(loginPanel, 2, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    optionsSizer->Add(registerPanel, 2, wxALL | wxALIGN_CENTER_VERTICAL, 10);

    verticalSizer->Add(optionsSizer, 0, wxALIGN_CENTER_HORIZONTAL);

    wxPanel *creditsPanel = new wxPanel(this);
    creditsPanel->SetBackgroundColour(wxColor(0, 0, 0));
    wxBoxSizer *creditsSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *authorsLabel = new wxStaticText(creditsPanel, wxID_ANY, "AUTHORS");
    wxStaticText *mustafaLabel = new wxStaticText(creditsPanel, wxID_ANY, "Mustafa Ahmed Khan");
    wxStaticText *umarLabel = new wxStaticText(creditsPanel, wxID_ANY, "M. Umar Amir");

    authorsLabel->SetForegroundColour(wxColor(255,255,255));
    mustafaLabel->SetForegroundColour(wxColor(69,69,69));
    umarLabel->SetForegroundColour(wxColor(69,69,69));

    authorsLabel->SetFont(wxFont(45, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    wxFont *creditFont = new wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mustafaLabel->SetFont(creditFont->GetBaseFont());
    umarLabel->SetFont(creditFont->GetBaseFont());

    creditsSizer->Add(authorsLabel, 0, wxBOTTOM | wxALIGN_CENTER_HORIZONTAL, 10);
    creditsSizer->Add(mustafaLabel, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 2);
    creditsSizer->Add(umarLabel, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 2);

    creditsPanel->SetSizer(creditsSizer);

    verticalSizer->Add(creditsPanel, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 25);

    SetSizerAndFit(verticalSizer);

     loginBtn->Bind(wxEVT_BUTTON, &StartupFrame::OnLoginButtonClick, this);
    regBtn->Bind(wxEVT_BUTTON, &StartupFrame::OnRegButtonClick, this);
}

void StartupFrame::OnLoginButtonClick(wxCommandEvent& event)
{
    this->Destroy();

    LoginFrame *frame = new LoginFrame();
    frame->SetSize(wxSize(800,600));
    frame->Center();
    frame->Show(true);
}

void StartupFrame::OnRegButtonClick(wxCommandEvent& event)
{
    this->Destroy();

    RegisterFrame *frame = new RegisterFrame();
    frame->SetSize(wxSize(800,600));
    frame->Center();
    frame->Show(true);
}