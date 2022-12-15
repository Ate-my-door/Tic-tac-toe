// Tic Tac Toe

#include <iostream>
#include <string>
#include <random>

void drawBoard(const std::string&);
std::string whoGoesFirst();
void inputPlayerLetter(char&, char&);
unsigned getPlayerMove(const std::string& board);
unsigned getComputerMove(const std::string&, const char);
bool isDigits(const std::string&);
bool isSpaceFree(const std::string&, const unsigned);
void makeMove(std::string& b, const char, const unsigned);
bool isWinner(const std::string&, const char);
bool isBoardFull(const std::string&);
unsigned chooseRandomMoveFromString(const std::string&, const std::string&);
bool playAgain();

char playerLetter;
char computerLetter;

int main()
{
	std::cout << "Welcome to Tic Tac Toe!\n";
	
	while (true)
	{
		// Reset the board
		std::string theBoard{"          "};	
		inputPlayerLetter(playerLetter, computerLetter);
		std::string turn{whoGoesFirst()};
		std::cout << "The " << turn << " will go first.\n";
		bool gameIsPlaying{true};
		
		while (gameIsPlaying)
		{
			if (turn == "player")
			{
				// Player's turn.
				drawBoard(theBoard);
				unsigned move{getPlayerMove(theBoard)};
				makeMove(theBoard, playerLetter, move);
				
				if (isWinner(theBoard, playerLetter))
				{
					drawBoard(theBoard);
					std::cout << "Hooray! You have won the game!\n";
					gameIsPlaying = false;
				}
				else
				{
					if (isBoardFull(theBoard))
					{
						drawBoard(theBoard);
						std::cout << "The game is a tie!\n";
						break;
					}
					else
					{
						turn = "computer";
					}
				}
				
			}
			else
			{		
				// Computer's turn.	
				unsigned move{getComputerMove(theBoard, computerLetter)};
				makeMove(theBoard, computerLetter, move);
				
				if (isWinner(theBoard, computerLetter))
				{
					drawBoard(theBoard);
					std::cout << "The computer has beaten you! You lose.\n";
					gameIsPlaying = false;
				}
				else
				{
					if (isBoardFull(theBoard))
					{
						drawBoard(theBoard);
						std::cout << "The game is a tie!\n";
						break;
					}
					else
					{
						turn = "player";
					}
				}
			}
		}
		
		if (!playAgain())
		{
			break;
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////

void drawBoard(const std::string& b)
{
	// This function prints out the board that it was passed.
	std::cout << "   |   |\n";
	std::cout << ' ' << b[1] << " | " << b[2] << " | " << b[3] << '\n';
	std::cout << "   |   |\n";
	std::cout << "-----------\n";
	std::cout << "   |   |\n";
	std::cout << ' ' << b[4] << " | " << b[5] << " | " << b[6] << '\n';
	std::cout << "   |   |\n";
	std::cout << "-----------\n";
	std::cout << "   |   |\n";
	std::cout << ' ' << b[7] << " | " << b[8] << " | " << b[9] << '\n';
	std::cout << "   |   |\n";
}

void inputPlayerLetter(char& pl, char& cl)
{
	// Let's the player type which letter they want to be.
	std::string s;
	
	do
	{
		std::cout << "Do you want to be X or O?\n";
		getline(std::cin, s);
		
		if ((s[0] = toupper(s[0])) == 'X')
		{
			pl = 'X';
			cl = 'O';
		}
		else
		{
			pl = 'O';
			cl = 'X';
		}
			
	} while ((s[0] != 'X') && (s[0] != 'O'));
}

bool playAgain()
{
	// This function returns True if the player wants to play again, otherwise it returns False.
	std::string s;
	
	do
	{
		std::cout << "Do you want to play again? (yes or no)\n";
		getline(std::cin, s);
		
	} while ((tolower(s[0]) != 'y') && (tolower(s[0]) != 'n'));
	
	return ((s[0] = tolower(s[0])) == 'y');
}

std::string whoGoesFirst()
{
	// Randomly choose the player who goes first.
	std::random_device rd;
	std::uniform_int_distribution<unsigned> dist(0, 1);
	
	if (dist(rd) == 0)
	{
		return "computer";
	}
	else
	{
		return "player";
	}
}

unsigned getPlayerMove(const std::string& board)
{
	// Let the player type in his move.
	std::string inp;
	unsigned move{0};
	
	do
	{
		do
		{
			do
			{
				std::cout << "What is your next move? (1-9)\n";
				getline(std::cin, inp);
				inp = inp.substr(0, 3);
			
			} while ((!isDigits(inp)) || (inp == ""));
		
			move = stoi(inp); 

		} while ((move < 1) || (move > 9));
		
	} while (!isSpaceFree(board, move));
	
	return move;
}

bool isDigits(const std::string& s)
{
	// This function returns True if the player's input consist of a digits only, otherwise it returns False.
	return (s.find_first_not_of("0123456789") == std::string::npos);
}

bool isSpaceFree(const std::string& b, const unsigned m)
{
	// Return true if the passed move is free on the passed board.
	return (b[m] == ' ');
}

void makeMove(std::string& b, const char l, const unsigned m)
{
    b[m] = l;
}

bool isWinner(const std::string& b, const char l)
{
	// Given a board and a player's letter, this function returns True if that player has won.
	// We use bo instead of board and le instead of letter so we don't have to type as much.
	return (((b[1] == l) && (b[2] == l) && (b[3] == l)) || // across the top
	((b[4] == l) && (b[5] == l) && (b[6] == l)) || // across the middle
	((b[7] == l) && (b[8] == l) && (b[9] == l)) || // across the bottom
	((b[1] == l) && (b[4] == l) && (b[7] == l)) || // down the left side
	((b[2] == l) && (b[5] == l) && (b[8] == l)) || // down the middle
	((b[3] == l) && (b[6] == l) && (b[9] == l)) || // down the right side
	((b[1] == l) && (b[5] == l) && (b[9] == l)) || // diagonal
	((b[3] == l) && (b[5] == l) && (b[7] == l))); // diagoal
}

bool isBoardFull(const std::string& board)
{
	// Return True if every space on the board has been taken. Otherwise return False.
	for (int i = 1; i <= 10; i++)
	{
		if (isSpaceFree(board, i))
		{
			return false;
		}
	}
	return true;
}

unsigned getComputerMove(const std::string& b, const char l)
{	
	// Given a board and the computer's letter, determine where to move and return that move.		
	// Here is our algorithm for our Tic Tac Toe AI:
    // First, check if we can win in the next move.
    std::string copy;
    
    for (unsigned i = 1; i <= 9; i++)
    {
		copy = b;
		
		if (isSpaceFree(copy, i))
		{
			makeMove(copy, computerLetter, i);
			
			if (isWinner(copy, computerLetter))
			{
				return i;
			}
		}
	}
	
	// Check if the player could win on his next move, and block them.
	for (unsigned i = 1; i <= 9; i++)
	{
		copy = b;
		
		if (isSpaceFree(copy, i))
		{
			makeMove(copy, playerLetter, i);
			
			if (isWinner(copy, playerLetter))
			{
				return i;
			}
		}
		
	}
	
	// Try to take one of the corners, if they are free.
	unsigned m = chooseRandomMoveFromString(b, "1379");
	
	if (m != 255)
	{
		return m;
	}
	
	// Try to take the center, if it is free.
	if (isSpaceFree(b, 5))
	{
		return 5;
	}
	
	// Move on one of the sides.
	return (chooseRandomMoveFromString(b, "2468"));
}

unsigned chooseRandomMoveFromString(const std::string& b, const std::string& moves)
{
	// Returns a valid move from the passed string on the passed board.
	// Returns 0 if there is no valid move.
	std::string possibleMoves{""};
	unsigned pos;
	
	for (int i = 0; i < moves.size(); i++)
	{
		pos = moves[i] - '0';
		
		if (isSpaceFree(b, pos))
		{
			possibleMoves.push_back(moves[i]);
		}
	}
	
	if (possibleMoves.size() != 0)
	{
		std::random_device rd;
		std::uniform_int_distribution<unsigned> dist(0, (static_cast<unsigned>(possibleMoves.size()) - 1));
		return (possibleMoves[dist(rd)] - '0');
	}
	else
	{
		return 255;
	}
}
