#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

using namespace std;

const char com1[16] = { 'G','E', 'N', '_', 'A', 'L', 'L', '_', 'P', 'O', 'S', '_', 'M', 'O', 'V' };
const char com2[33] = { 'G','E', 'N', '_', 'A', 'L', 'L', '_', 'P', 'O', 'S', '_', 'M', 'O', 'V','_','C', 'U', 'T', '_', 'I', 'F', '_', 'G', 'A', 'M', 'E', '_', 'O', 'V', 'E', 'R' };
const char com3[17] = { 'S','O', 'L', 'V', 'E', '_', 'G', 'A', 'M', 'E', '_', 'S', 'T', 'A', 'T','E' };

struct Move
{
    int row, col;
};

int  iswin(int** board, int n, int m, int k, int player) {
    int kol = 0;
    int x, y;
    int whatplayer = 1;
    while (whatplayer <= 2) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == whatplayer) {
                    kol++;
                    if (kol == k) return whatplayer;
                }
                else kol = 0;
            }
            kol = 0;
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[j][i] == whatplayer) {
                    kol++;
                    if (kol == k) return whatplayer;
                }
                else kol = 0;
            }
            kol = 0;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                x = i;
                y = j;
                while (x < n && y < m) {
                    if (board[x][y] == whatplayer) {
                        kol++;
                    }
                    else kol = 0;
                    if (kol == k) return whatplayer;
                    x++;
                    y++;

                }
                kol = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = m - 1; j >= 0; j--) {
                x = i;
                y = j;
                while (x < n && y >= 0) {
                    if (board[x][y] == whatplayer) {
                        kol++;
                    }
                    else kol = 0;
                    if (kol == k) return whatplayer;
                    x++;
                    y--;

                }
                kol = 0;
            }
        }


        whatplayer++;
    }

    return 0;
};

bool isMovesLeft(int** board, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == 0)
                return true;
    return false;
}

int max(int R, int L) {

    if (R > L) {
        return R;
    }
    else {
        return L;
    }
}
int min(int R, int L) {

    if (R < L) {
        return R;
    }
    else {
        return L;
    }
}


void genallposmov(int** board, int n, int m, int k, int player, bool cutifgameover) {

    int kol = 0;
    int stopper = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 0)kol++;
        }
    }

    if (kol != 0) {
        if (cutifgameover == false)  cout << kol << endl;

        int** help_board = new int* [n];
        for (int i = 0; i < n; i++) {
            help_board[i] = new int[m];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                for (int g = 0; g < n; g++) {
                    for (int h = 0; h < m; h++) {
                        help_board[g][h] = board[g][h];
                    }
                }

                if (board[i][j] == 0) {
                    help_board[i][j] = player;
                    if (cutifgameover == true) {
                        if (iswin(help_board, n, m, k, player) != 0) {
                            cout << 1 << endl;
                            for (int k = 0; k < n; k++) {
                                for (int l = 0; l < m; l++) {
                                    printf("%d ", help_board[k][l]);
                                }
                                cout << endl;

                            }
                            return;
                        }
                        else {
                            stopper++;
                        }
                        if (stopper == kol) genallposmov(board, n, m, k, player, false);
                    }
                    else {
                        for (int k = 0; k < n; k++) {
                            for (int l = 0; l < m; l++) {
                                printf("%d ", help_board[k][l]);
                            }
                            cout << endl;

                        }

                    }


                }
            }
        }
        for (int i = 0; i < n; i++) {
            delete[] help_board[i];
        }
        delete[] help_board;
    }
    else {
        cout << kol << endl;
    }
};

int minimax(int** board, int depth, bool isMax, int n, int m, int k, int player, int opponent)
{
    int score = iswin(board, n, m, k, player);

    if (score == player)
        return +10;

    if (score == opponent)
        return -10;

    if (isMovesLeft(board, n, m) == false)
        return 0;


    if (isMax)
    {
        int best = -1000;


        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {

                if (board[i][j] == 0)
                {

                    board[i][j] = player;


                    best = max(best, minimax(board, depth + 1, !isMax, n, m, k, player, opponent));



                    board[i][j] = 0;
                }
            }
        }
        return best;
    }


    else
    {
        int best = 1000;


        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {

                if (board[i][j] == 0)
                {

                    board[i][j] = opponent;


                    best = min(best, minimax(board, depth + 1, !isMax, n, m, k, player, opponent));



                    board[i][j] = 0;
                }
            }
        }
        return best;
    }
}

void change(int& pp, int& oo) {
    int tmp;
    tmp = pp;
    pp = oo;
    oo = tmp;
}

Move findBestMove(int** board, int n, int m, int k, int player, int opponent)
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {

            if (board[i][j] == 0)
            {

                board[i][j] = player;


                int moveVal = minimax(board, 0, false, n, m, k, player, opponent);


                board[i][j] = 0;


                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
                if (moveVal == 10) break;
            }
        }
    }

    return bestMove;
}

int main()
{
    int n, m, k, player, _player, opponent;
    char command[100];


    while (true)
    {
        bool isend = false;

        bool cutifgameover = false;
        scanf("%s", command);
        if (feof(stdin) != 0)
        {
            break;
        }
        scanf("%d%d%d%d", &n, &m, &k, &player);

        _player = player;

        int** board = new int* [n];
        for (int i = 0; i < n; i++) {
            board[i] = new int[m];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++) {

                cin >> board[i][j];
            }
        }

        if (!strcmp(com1, command)) {
            if (iswin(board, n, m, k, player) != 0) cout << 0 << endl;
            else genallposmov(board, n, m, k, player, cutifgameover);

        }
        else if (!strcmp(com2, command)) {
            if (iswin(board, n, m, k, player) != 0) cout << 0 << endl;
            else {
                cutifgameover = true;
                genallposmov(board, n, m, k, player, cutifgameover);
            }

        }
        else {
            if (player == 1) {
                opponent = 2;
            }
            else {
                opponent = 1;
            }

            if (iswin(board, n, m, k, player) == 1) {

                printf("FIRST_PLAYER_WINS");
                printf("\n");
            }
            else if (iswin(board, n, m, k, player) == 2) {

                printf("SECOND_PLAYER_WINS");
                printf("\n");

            }
            else if (!isMovesLeft(board, n, m)) {
                printf("BOTH_PLAYERS_TIE");
                printf("\n");

            }
            else {
                while (isMovesLeft(board, n, m)) {

                    Move bestMove = findBestMove(board, n, m, k, _player, opponent);
                    board[bestMove.row][bestMove.col] = _player;
                    if (iswin(board, n, m, k, player) == 1) {
                        printf("FIRST_PLAYER_WINS");
                        printf("\n");

                        isend = true;
                        break;
                    }
                    else if (iswin(board, n, m, k, player) == 2) {
                        printf("SECOND_PLAYER_WINS");
                        printf("\n");

                        isend = true;
                        break;
                    }

                    change(_player, opponent);
                }

                if (isend == false) {
                    printf("BOTH_PLAYERS_TIE");
                    printf("\n");


                }

            }



        }


    }
    return 0;
}