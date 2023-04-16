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
    btn = new wxButton *[N_BOARD_SIZE * N_BOARD_SIZE];

    // create a grid sizer to distribute the buttons
    wxGridSizer *grid = new wxGridSizer(
        N_BOARD_SIZE,
        N_BOARD_SIZE,
        5, // this is padding
        5);

    // create a font
    wxFont font(36,
                wxFONTFAMILY_DEFAULT,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD,
                false);

    for (uint i = 0; i < N_BOARD_SIZE * N_BOARD_SIZE; i++)
    {
        btn[i] = new wxButton(
            this,
            10000 + i);
        // set the font
        btn[i]->SetFont(font);
        // add each button to the grid sizer
        grid->Add(
            btn[i],
            1,
            wxEXPAND | wxALL);

        // dynamically link button clicked event to the handling function
        btn[i]->Bind(
            wxEVT_COMMAND_BUTTON_CLICKED,
            &cMain::OnButtonClicked,
            this);
    }

    this->SetSizer(grid);
    grid->Layout();
}

cMain::cMain()
{
}

cMain::~cMain()
{
    // I do need to delete the array of pointers to buttons to prevent a memory leak
    delete[] btn;
}

// callback function from button
void cMain::OnButtonClicked(wxCommandEvent &event)
{
    // Identify the button that was clicked by ID
    // and get its x,y coordinates
    uint player_move = (event.GetId() - 10000);

    // tell the system that this event has been handled
    event.Skip();

    // check if the player move is valid and make it
    if (game.MakeMove(player_move, TicTacToe::O))
    {
        // set color to GRAY
        btn[player_move]->SetForegroundColour(*wxBLACK);
        // disable the button to prevent it being clicked again
        btn[player_move]->Enable(false);

        // display player move
        btn[player_move]->SetLabel(std::string(1, TicTacToe::O));

        // calculate computer move
        uint computer_move = game.FindBestMove();

        // check if computer move is valid, make it and display it
        if (computer_move < N_BOARD_SIZE * N_BOARD_SIZE)
        {
            game.MakeMove(computer_move, TicTacToe::X);
            // set color to RED
            btn[computer_move]->SetForegroundColour(*wxRED);
            // disable the button to prevent it being clicked again
            btn[computer_move]->Enable(false);
            // display computer move
            btn[computer_move]->SetLabel(std::string(1, TicTacToe::X));
        }

        if (game.IsGameOver() || game.Evaluate()) // if board already full or someone already won
        {
            // show Message box
            std::string msg = "Game Over";
            if (game.Evaluate() > 0)
                msg += ". I Win!!";
            else if (game.Evaluate() > 0)
                msg += ". You Win!!";
            else
                msg += ". It's a Tie!!";

            wxMessageBox(msg);

            // reset the game
            for (int i = 0; i < N_BOARD_SIZE * N_BOARD_SIZE; i++)
            {
                btn[i]->Enable(true); // reactivate buttons
                btn[i]->SetLabel(""); // clear labels
            }
            char c = TicTacToe::EMPTY;
            game.set_board({c, c, c,
                            c, c, c,
                            c, c, c}); // clear board
        }
    }
}