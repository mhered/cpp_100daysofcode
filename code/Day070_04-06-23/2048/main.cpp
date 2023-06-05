#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h> // reverse
#include <random>
#include "kbhit.h"

const std::string RED("\033[0;31m");
const std::string GREEN("\033[0;32m");
const std::string BLUE("\033[0;34m");
const std::string YELLOW("\033[0;33m");
const std::string CYAN("\033[0;36m");
const std::string MAGENTA("\033[0;35m");
const std::string RESET("\033[0m");
const char UP = 'q';
const char DOWN = 'a';
const char LEFT = 'o';
const char RIGHT = 'p';

std::string color(int val, bool with_text = true)
{
    const int WIDTH = 6;
    std::string text = "";
    if (with_text && val != 0)
    {
        text = std::to_string(val);
        int addspaces = 1 + (WIDTH - text.size()) / 2;
        text += std::string(addspaces, ' ');
    }
    int code;
    std::stringstream ss;
    switch (val)
    {
    case 0:
        code = 244;
        break;
    case 2:
        code = 255;
        break;
    case 4:
        code = 253;
        break;
    case 8:
        code = 216;
        break;
    case 16:
        code = 210;
        break;
    case 32:
        code = 203;
        break;
    case 64:
        code = 160;
        break;
    case 128:
        code = 220;
        break;
    case 256:
        code = 226;
        break;
    case 512:
        code = 228;
        break;
    case 1024:
        code = 3;
        break;
    case 2048:
        code = 2;
        break;
    }
    ss << "\033[48;5;" << code << "m " << std::setw(WIDTH) << text << RESET;
    return ss.str();
}

void print_vector(std::vector<int> vec)
{
    std::stringstream ss_content, ss_padding;
    for (auto elem : vec)
    {
        ss_content << color(elem, true);
        ss_padding << color(elem, false);
    }
    std::cout << ss_padding.str() << std::endl;
    std::cout << ss_content.str() << std::endl;
    std::cout << ss_padding.str() << std::endl;
}

std::vector<int> swipe_row_left(std::vector<int> row_in, int &score)
{
    std::vector<int> row_tmp, row_out;
    int trail_zeroes = 0;
    // collapse zeroes to left
    for (auto elem : row_in)
    {
        if (elem != 0)
        {
            row_tmp.push_back(elem);
        }
        else
            trail_zeroes++;
    }
    // add pairs
    int first = 0;
    int second = 0;

    for (auto elem : row_tmp)
    {
        if (first == 0)
            first = elem;
        else
            second = elem;

        if (first != 0 && second != 0)
        {
            if (first == second)
            {
                row_out.push_back(first + second);
                score += first + second; // update score
                first = 0;
                second = 0;
                trail_zeroes++;
            }
            else
            {
                row_out.push_back(first);
                first = second;
                second = 0;
            }
        }
    }
    if (first != 0)
        row_out.push_back(first);
    // add trailing zeroes
    for (int i = 0; i < trail_zeroes; i++)
        row_out.push_back(0);

    return row_out;
}

std::vector<int> swipe_row_right(std::vector<int> row_in, int &score)
{
    std::vector<int> row_tmp, row_out;
    row_tmp = row_in;
    std::reverse(row_tmp.begin(), row_tmp.end());
    row_out = swipe_row_left(row_tmp, score);
    std::reverse(row_out.begin(), row_out.end());
    return row_out;
}

void transpose(std::vector<std::vector<int>> &board)
{
    if (board.size() == 0)
        return;

    std::vector<std::vector<int>> trans_vec(board[0].size(), std::vector<int>());

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            trans_vec[j].push_back(board[i][j]);
        }
    }

    board = trans_vec; // <--- reassign here
}

std::vector<std::vector<int>> swipe_board_left(std::vector<std::vector<int>> board, int &score)
{
    std::vector<std::vector<int>> result;
    for (auto row : board)
        result.push_back(swipe_row_left(row, score));
    return result;
}

std::vector<std::vector<int>> swipe_board_right(std::vector<std::vector<int>> board, int &score)
{
    std::vector<std::vector<int>> result;
    for (auto row : board)
        result.push_back(swipe_row_right(row, score));
    return result;
}

std::vector<std::vector<int>> swipe_board_up(std::vector<std::vector<int>> board, int &score)
{
    std::vector<std::vector<int>> tboard, result;
    transpose(board);
    for (auto row : board)
        result.push_back(swipe_row_left(row, score));
    transpose(result);
    return result;
}

std::vector<std::vector<int>> swipe_board_down(std::vector<std::vector<int>> board, int &score)
{
    std::vector<std::vector<int>> tboard, result;
    transpose(board);
    for (auto row : board)
        result.push_back(swipe_row_right(row, score));
    transpose(result);
    return result;
}

int rand_int_in_range(const int range_from, const int range_to)
{
    // from https://stackoverflow.com/a/20136256/15472802
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(range_from, range_to);

    return distr(generator);
}

bool spawn_one(std::vector<std::vector<int>> &board)
{
    // find empty_spaces
    std::vector<std::pair<int, int>> empty_spaces;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == 0)
            {
                empty_spaces.push_back(std::make_pair(i, j));
            }
        }
    }
    if (empty_spaces.empty())
        return false; // return false if full: game over

    //  to spawn a number 2 in a randomly selected empty space
    int idx = rand_int_in_range(0, empty_spaces.size());

    int i = empty_spaces[idx].first;
    int j = empty_spaces[idx].second;

    // 90% of the time adds a 2, 10% of the time a 4, see: https://www.baeldung.com/cs/2048-algorithm
    board[i][j] = rand_int_in_range(0, 9)<1?4:2; 
    return true;
}

int main()
{

    std::vector<std::vector<int>> board = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    spawn_one(board);
    int score = 0;
    int key_nr;
    char key;
    keyboard keyboard;

    while (spawn_one(board))
    {
        // display board
        system("clear");
        std::cout << std::endl
                  << "2048           SCORE: "
                  << std::setfill('0') << std::setw(6) << score << std::endl;
        std::cout << std::endl
                  << " Join the numbers " << std::endl
                  << " and get to the 2048 tile!" << std::endl
                  << std::endl;
        for (auto row : board)
        {
            print_vector(row);
        }

        std::cout << std::endl
                  << "Controls:" << std::endl;
        std::cout << "          | ↑:Q |" << std::endl
                  << "    | ←:O | ↓:A | →:P |" << std::endl;

        // get valid_move
        bool valid_move = false;
        while (!valid_move)
        {
            std::vector<std::vector<int>> new_board;
            // get keypress
            if (keyboard.kbhit())
            {
                key_nr = keyboard.getch(); // return int
                key = key_nr;              // get ascii char

                switch (key)
                {
                case UP:
                    new_board = swipe_board_up(board, score);
                    break;
                case DOWN:
                    new_board = swipe_board_down(board, score);
                    break;
                case LEFT:
                    new_board = swipe_board_left(board, score);
                    break;
                case RIGHT:
                    new_board = swipe_board_right(board, score);
                    break;
                default:
                    valid_move = false;
                    new_board = board;
                }
                if (new_board != board)
                {
                    valid_move = true;
                    board = new_board;
                }
            }
        }
    }
    std::cout << "Game Over!" << std::endl;

    return 0;
}