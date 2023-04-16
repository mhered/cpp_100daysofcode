#ifndef CAPP_H
#define CAPP_H

#pragma once
#include <wx/wx.h>
#include "cMain.h"

class cApp : public wxApp // inherited from base class
{
public:
    cApp();
    ~cApp();
    bool OnInit();

private:
    cMain *m_frame1 = nullptr; // pointer to the window in the launcher
};

#endif