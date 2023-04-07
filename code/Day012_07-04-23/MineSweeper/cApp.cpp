#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
    // create an instance of cMain
    cMain *m_frame1 = new cMain(
        wxT("A 9x9 grid of buttons"),
        600,
        600);

    m_frame1->Show(); // show it
    return true;
}