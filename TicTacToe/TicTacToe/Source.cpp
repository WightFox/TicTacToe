#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <random>
#include <algorithm>
#include <iterator>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::max;

static void draw(const vector<string> &board)
{
	for (int n = board.size(), i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << "[" << board[i][j] << "]";

		cout << "\n";
	}

	cout << "\n";
}

static vector<string> empty(int n)
{
	vector<string> board;

	for (int i = 0; i < n; i++)
		board.push_back(string(n, ' '));

	return(board);
}

struct move
{
	int row;
	int column;
	int score;
};

static int pointCheck(const vector<string> &board, int depth)
{

	char player = 'X';
	char computer = 'O';
	//rows
	for (int i = 0; i < 3 ; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
		{
			if (board[i][0] == computer)
				return(10);
			else if (board[i][0] == player)
				return(-10);
		}
	}

	//columns
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
		{
			if (board[0][i] == computer)
				return(10);
			else if (board[0][i] == player)
				return(-10);
		}
	}

	//Diagonal 1
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
	{
		if (board[0][0] == computer)
			return(10);
		else if (board[0][0] == player)
			return(-10);
	}

	//Diagonal 2
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
	{
		if (board[0][2] == computer)
			return(10);
		else if (board[0][2] == player)
			return(-10);
	}

	return 0;
}

static bool horizontalVictory(const vector<string> &board, char which)
{
	int n = board.size();

	for (int i = 0; i < n; i++)
	{
		// for each row

		int count = 0;

		for (int j = 0; j < n; j++)
			if (board[i][j] == which)
				count++;

		if (count == n)
			return(true);
	}

	return(false);
}

static bool verticalVictory(const vector<string> &board, char which)
{
	int n = board.size();

	for (int i = 0; i < n; i++)
	{
		// for each column

		int count = 0;

		for (int j = 0; j < n; j++)
			if (board[j][i] == which)
				count++;

		if (count == n)
			return(true);
	}

	return(false);
}

static bool rightDiagonal(const vector<string> &board, char which)
{
	int n = board.size();

	int count = 0;

	for (int i = 0; i < n; i++)
	{
		// for each column


			if (board[i][i] == which)
				count++;

		if (count == n)
			return(true);
	}

	return(false);
}

static bool leftDiagonal(const vector<string> &board, char which)
{
	int n = board.size();

	int count = 0;

	for (int i = 0, j = n-1; i < n, j >= 0; i++, j--)
	{
		// for each column


		if (board[i][j] == which)
			count++;

		if (count == n)
			return(true);
	}

	return(false);
}

static bool doMove(vector<string> &board, char which, int location)
{
	int n = board.size();

	if (location < 1 || location > n * n)
		return(false);

	int row = (location - 1) / n;
	int column = (location - 1) % n;

	board[row][column] = which;

	return(true);
}


static int  check(vector<string> &board, int input)
{
	int n = board.size();

	int row = (input - 1) / n;
	int column = (input - 1) % n;

	if (input < 0 || input > 9)
	{
		cout << "Invalid, please enter value on chart.\n";
		cin >> input;
		check(board, input);
	}
	else if (!isspace(board[row][column]))
	{
		cout << "Invalid, please enter value on chart.\n";
		cin >> input;
		check(board, input);
	}
	else
	{
		return input;
	}
}


static bool isFull(vector<string> &board)
{
	int n = board.size();

	int total = n * n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			if (board[j][i] == ' ')
				return(false);
	}
	return(true);
}

static bool winnerCheck(const vector<string> &board, char which)
{
	if (verticalVictory(board, which) || horizontalVictory(board, which) || rightDiagonal(board, which) || leftDiagonal(board, which))
	{
		return(true);
	}
	else
		return(false);
}

static int minimax(vector<string> &board, int depth, bool isComputer)
{
	int score = pointCheck(board, depth);

	if (score == 10)
	{
		return score;
	}

	if (score == -10)
	{
		return score;
	}

	if (isFull(board))
	{
		return 0;
	}

	if (isComputer)
	{
		int goal = -1000;

		for (int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
				if (board[i][j] == ' ')
				{
					board[i][j] = 'O';

					goal = std::max(goal, minimax(board, depth+1, !isComputer));

					

					board[i][j] = ' ';
				}

			
		}
		return goal;
	}
	else
	{
		int goal = 1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				if (board[i][j] == ' ')
				{
					board[i][j] = 'X';

					goal = std::min(goal,  minimax(board, depth+1, !isComputer));



					board[i][j] = ' ';
				}
		}
		

		return goal;

	}
}

move nextMove(vector<string> board)
{
	int goal = -1000;
	move nextMove;
	nextMove.row = -1;
	nextMove.column = -1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			if (board[i][j] == ' ')
			{
				board[i][j] = 'O';

				int check = minimax(board, 0, false);

				board[i][j] = ' ';

				if (check > goal)
				{
					nextMove.row = i;
					nextMove.column = j;
					goal = check;
					nextMove.score = check;
				}

				
			}
	}

	printf("The value of the best Move is : %d\n\n",
		goal);
	
	cout << goal << "\n";
	cout << nextMove.row << "\n";
	cout << nextMove.column << "\n";

	return nextMove;

}

int main()
{
	const int x = 3;
	int input;
	int compInput;


	bool winner = false;

	bool pWin = false;
	bool cWin = false;

	vector<string> board = empty(x);

	draw(board);

	const char Player = 'X';
	const char Comp = 'O';

	for (;;)
	{
		cout << "Enter Your location. \n" << "1 2 3\n" << "4 5 6\n" << "7 8 9\n";

		cin >> input;

		input = check(board, input);

		doMove(board, Player, input);

		draw(board);

		if(winnerCheck(board, Player))
		{
			cout << " Player wins\n";
			break;
		}
		if (isFull(board))
		{
			cout << "Tie: No Winner";
			break;
		}

		move counter = nextMove(board);

		board[counter.row][counter.column] = Comp;

		draw(board);

		if(winnerCheck(board, Comp))
		{
			cout << " Computer wins\n"; 
			break;
		}

		if (isFull(board))
		{
			cout << "Tie: No Winner";
			break;
		}

	}

	

	system("pause");

	return(0);
}