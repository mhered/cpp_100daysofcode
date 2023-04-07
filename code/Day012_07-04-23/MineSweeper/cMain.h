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
    // a 9 by 9 array of buttons
    int n_field_width = 9;
    int n_field_height = 9;

    // array of pointers to buttons. This requires tear down!
    wxButton **btn;
    int *n_field = nullptr; // stores the mine field
    // mine field only populated after first click
    // so first play always works. 
    // Hence I need a flag for the first click
    bool b_first_click = true;

    void OnButtonClicked(wxCommandEvent &event);

    // include this macro for the parent window to handle events
    wxDECLARE_EVENT_TABLE();
};

#endif