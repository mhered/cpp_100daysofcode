#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(10001, cMain::OnButtonClicked) // link callback function my button by ID
    wxEND_EVENT_TABLE()

    // no parent, any ID, title, topleft corner, size
    cMain::cMain(const wxString &title, // wxString interchangeable with std::string
                 int width,
                 int height) : wxFrame(nullptr,
                                       wxID_ANY,
                                       title,
                                       wxPoint(30, 30),
                                       wxSize(width, height))

{
    Centre();
    m_btn1 = new wxButton(this,
                          10001, // we need to ID the button to associate the callback
                          "Click me!",
                          wxPoint(10, 10),
                          wxSize(150, 50));
    m_txt1 = new wxTextCtrl(this,
                            wxID_ANY,
                            "",
                            wxPoint(10, 70),
                            wxSize(300, 30));
    m_list1 = new wxListBox(this,
                            wxID_ANY,
                            wxPoint(10, 110),
                            wxSize(300, 300));
                            // note to corresponding `delete` matching the `new`. 
                            // wxWidgets automatically handles tear down 
}

cMain::cMain()
{
}

cMain::~cMain()
{
}

// callback function from button
void cMain::OnButtonClicked(wxCommandEvent &event)
{
    // when button clicked append content of text box to the list

    m_list1->AppendString(m_txt1->GetValue());
    event.Skip(); // tell the system that this event has been handled
}