#include "cMain.h"
#include <string>

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
    // create array of buttons
    btn = new wxButton *[N_BOARD_WIDTH * N_BOARD_HEIGHT];

    // create a grid sizer to distribute the buttons
    wxGridSizer *grid = new wxGridSizer(
        N_BOARD_WIDTH,
        N_BOARD_HEIGHT,
        5, // this is padding
        5);

    // create the mine field
    n_board = new int[N_BOARD_WIDTH * N_BOARD_HEIGHT];

    // create a font
    wxFont font(24,
                wxFONTFAMILY_DEFAULT,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD,
                false);

    for (int x = 0; x < N_BOARD_WIDTH; x++)
    {
        for (int y = 0; y < N_BOARD_HEIGHT; y++)
        {
            btn[y * N_BOARD_WIDTH + x] = new wxButton(
                this,
                10000 + (y * N_BOARD_WIDTH + x));
            // set the font
            btn[y * N_BOARD_WIDTH + x]->SetFont(font);
            // add each button to the grid sizer
            grid->Add(
                btn[y * N_BOARD_WIDTH + x],
                1,
                wxEXPAND | wxALL);

            // dynamically link button clicked event to the handling function
            btn[y * N_BOARD_WIDTH + x]->Bind(
                wxEVT_COMMAND_BUTTON_CLICKED,
                &cMain::OnButtonClicked,
                this);
            // set default value for mine field
            n_board[y * N_BOARD_WIDTH + x] = 0;
        }
    }

    this->SetSizer(grid);
    grid->Layout();
}

cMain::cMain()
{
}

cMain::~cMain()
{
    // I do need to delete the array of pointers to buttons to prevent memory leak
    delete[] btn;
}

// callback function from button
void cMain::OnButtonClicked(wxCommandEvent &event)
{
    // I can identify the button that was clicked by ID
    // and get its x,y coordinates
    int x = (event.GetId() - 10000) % N_BOARD_WIDTH;
    int y = (event.GetId() - 10000) / N_BOARD_WIDTH;

    // update window title (xwString is equivalent to std::string)
    wxString txt = "Button [ " +
                   std::to_string(x) +
                   ", " +
                   std::to_string(y) +
                   "] was clicked";

    SetTitle(txt);

    if (b_first_click)
    {
        // upon first click populate the field
        int mines = 20;
        while (mines)
        {
            // generate a random position
            int rx = rand() % N_BOARD_WIDTH;
            int ry = rand() % N_BOARD_HEIGHT;
            // and drop a mine there unless
            // there is already one or
            // it is the first pick
            if (n_board[ry * N_BOARD_WIDTH + rx] == 0 &&
                !(rx == x && ry == y))
            {
                n_board[ry * N_BOARD_WIDTH + rx] = -1;
                mines--;
            }
        }
        b_first_click = false;
    }

    // disable the button to prevent it being clicked again
    btn[y * N_BOARD_WIDTH + x]->Enable(false);

    // check if there was a mine
    if (n_board[y * N_BOARD_WIDTH + x] == -1)
    {
        wxMessageBox("Boom!! - Game Over");

        // Reset the game
        b_first_click = true;
        for (int x = 0; x < N_BOARD_WIDTH; x++)
        {
            for (int y = 0; y < N_BOARD_HEIGHT; y++)
            {
                n_board[y * N_BOARD_WIDTH + x] = 0;
                btn[y * N_BOARD_WIDTH + x]->SetLabel("");
                btn[y * N_BOARD_WIDTH + x]->Enable(true);
                btn[y * N_BOARD_WIDTH + x]->SetBackgroundColour(*wxWHITE);
            }
        }
    }
    else
    {
        // count neighbouring mines
        int mine_count = 0;
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (x + i >= 0 &&
                    x + i < N_BOARD_WIDTH &&
                    y + j >= 0 &&
                    y + j < N_BOARD_HEIGHT)
                {
                    if (n_board[(y + j) * N_BOARD_WIDTH + (x + i)] == -1)
                        mine_count++;
                }
            }
        }
        // display number of mines if !=0
        if (mine_count >= 0)
        {
            btn[y * N_BOARD_WIDTH + x]->SetLabel(std::to_string(mine_count));
            switch (mine_count)
            {
            case 0:
                btn[y * N_BOARD_WIDTH + x]->SetBackgroundColour(*wxLIGHT_GREY);
                break;
            case 1:
                btn[y * N_BOARD_WIDTH + x]->SetForegroundColour(*wxLIGHT_GREY);
                break;
            case 2:
                btn[y * N_BOARD_WIDTH + x]->SetForegroundColour(*wxGREEN);
                break;
            case 3:
                btn[y * N_BOARD_WIDTH + x]->SetForegroundColour(*wxBLUE);
                break;
            default:
                btn[y * N_BOARD_WIDTH + x]->SetForegroundColour(*wxRED);
                break;
            }
        }
    }

    event.Skip(); // tell the system that this event has been handled
}