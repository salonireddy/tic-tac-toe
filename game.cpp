#include <iostream>

using namespace std;

char grid[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; // for the grid layout

char current_marker; // to track the marker(changes between x and o according to the player number)
int current_player;  // to track which player is playing

void DrawGrid() // to draw the basic grid design
{
    cout << "  " << grid[0] << "  |  " << grid[1] << "  |  " << grid[2] << endl;
    cout << "-----------------\n";
    cout << "  " << grid[3] << "  |  " << grid[4] << "  |  " << grid[5] << endl;
    cout << "-----------------\n";
    cout << "  " << grid[6] << "  |  " << grid[7] << "  |  " << grid[8] << endl;
}

bool PlaceTheMarker(int slotNumber) // tells us where to place the marker acc to the slot number enetered
{
    slotNumber--;
    if (grid[slotNumber] != 'X' && grid[slotNumber] != 'O')
    {
        grid[slotNumber] = current_marker;
        return true;
    }
    return false;
}

int DetermineTheWinner() // returns the player number after determining who won. returns 0 if tie.
{
    for (int i = 0; i < 3; i++)
    {
        // rows
        if (grid[(3 * i) + 0] == grid[(3 * i) + 1] && grid[(3 * i) + 1] == grid[(3 * i) + 2])
            return current_player;

        // cols
        if (grid[i + 0] == grid[i + 3] && grid[i + 3] == grid[i + 6])
            return current_player;
    }
    // digonals (hard-coded cuz only 2 diagonals of fixed grid size)
    if (grid[0] == grid[4] && grid[4] == grid[8])
        return current_player;
    if (grid[2] == grid[4] && grid[4] == grid[6])
        return current_player;
    return 0;
}

void ChangeTurnOfPlayer() // to change the turn of a player after he has placed his marker
{
    if (current_player == 1)
        current_player = 2;
    else
        current_player = 1;

    if (current_marker == 'X')
        current_marker = 'O';
    else
        current_marker = 'X';
}

void GameInterface()
{
    char marker_player1;
marker_choser:
    cout << "Player 1! Chose your marker (X or O)!!!" << endl;
    cin >> marker_player1;

    if (marker_player1 != 'X' || marker_player1 != 'O' || marker_player1 != 'x' || marker_player1 != 'o')
    {
        cout << "Enter a valid marker, dumbhead!" << endl;
        goto marker_choser;
    }

    current_player = 1;
    current_marker = marker_player1;

    DrawGrid();

    for (int i = 0; i < 9; i++) // there can be utmost 9 moves in the game
    {
        cout << "Player " << current_player << " ENTER YOUR SLOT!  ";
        int chosen_slot;
        cin >> chosen_slot;

        if (chosen_slot < 1 || chosen_slot > 9)
        {
            cout << "Enter a valod slot, dumbhead!";
            i--;      // to provide the current player with another chance
            continue; // to skip the next few lines of the code
        }

        if (!PlaceTheMarker(chosen_slot))
        {
            cout << "Chose an emplty slot, dumbhead!";
            i--;      // to provide the current player with another chance
            continue; // to skip the next few lines of the code
        }

        DrawGrid();
        int player_won = DetermineTheWinner();
        if (player_won == 1)
        {
            cout << "Congratulations Player 1, you managed to beat your opponent and hence it is clear that your dumbness quotient is a little lower than that of your opponent :)" << endl;
            break;
        }
        else if (player_won == 2)
        {
            cout << "Congratulations Player 2, you managed to beat your opponent and hence it is clear that your dumbness quotient is a little lower than that of your opponent :)" << endl;
            break;
        }
        if (i == 8 && player_won == 0)
        {
            cout << "Congratulations Players, you managed to draw the and hence it is clear that you bith are equally dumb :)" << endl;
        }
        ChangeTurnOfPlayer();
    }
}

int main()
{
    GameInterface();
    return 0;
}