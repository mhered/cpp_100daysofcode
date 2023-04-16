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
        wxT("Tic Tac Toe"),
        600,
        600);

    m_frame1->Show(); // show it
    return true;
}