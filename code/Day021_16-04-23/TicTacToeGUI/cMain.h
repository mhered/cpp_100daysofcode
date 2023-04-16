#ifndef CMAIN_H
#define CMAIN_H

#pragma once

#include <wx/wx.h>

#include "TicTacToe.h"

class cMain : public wxFrame
{
public:
    cMain(const wxString &title, int width, int height);
    cMain();
    ~cMain();

public:
    // display the board as a 3 by 3 array of buttons
    const int N_BOARD_SIZE = 3;

    // array of pointers to buttons. This requires tear down!
    wxButton **btn;
    TicTacToe game; // stores the board

    void OnButtonClicked(wxCommandEvent &event);

    // include this macro for the parent window to handle events
    wxDECLARE_EVENT_TABLE();
};

#endif