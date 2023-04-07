#ifndef CMAIN_H
#define CMAIN_H

#pragma once
#include <wx/wx.h>

class cMain : public wxFrame
{
public:
    cMain(const wxString &title, int width, int height);
    cMain();
    ~cMain();

public:
    // add components
    wxButton *m_btn1 = nullptr;
    wxTextCtrl *m_txt1 = nullptr;
    wxListBox *m_list1 = nullptr;

    void OnButtonClicked(wxCommandEvent &event);

    // include this macro for the parent window to handle events
    wxDECLARE_EVENT_TABLE();
};

#endif