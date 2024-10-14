#define SIZE 3
#define PLAYER 'X'
#define COMPUTER 'O'
#define EMPTY ' '

char board[SIZE][SIZE];

// Initialize the board with empty spaces
void initBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}
void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void playerMove() {
    int row, col;
    while (1) {
        printf("Enter your move (row and column): ");
        scanf("%d %d", &row, &col);

        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == EMPTY) {
            board[row][col] = PLAYER;
            break;
        } else {
            printf("Invalid move! Try again.\n");
        }
    }
}
char checkWinner() {
    // Check rows, columns, and diagonals
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY)
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY)
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
        return board[0][2];

    return EMPTY;
}

int isFull() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == EMPTY)
                return 0;
    return 1;
}
int minimax(int depth, int isMaximizing) {
    char winner = checkWinner();
    if (winner == COMPUTER) return 10 - depth;
    if (winner == PLAYER) return depth - 10;
    if (isFull()) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    int score = minimax(depth + 1, 0);
                    board[i][j] = EMPTY;
                    if (score > bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    int score = minimax(depth + 1, 1);
                    board[i][j] = EMPTY;
                    if (score < bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

void bestMove() {
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int score = minimax(0, 0);
                board[i][j] = EMPTY;
                if (score > bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    board[moveRow][moveCol] = COMPUTER;
}
void playGame() {
    while (1) {
        printBoard();
        if (checkWinner() == PLAYER) {
            printBoard();
            printf("You win!\n");
            break;
        }
        if (isFull()) {
            printBoard();
            printf("It's a tie!\n");
            break;
        }

        // Player's turn
        playerMove();

        if (checkWinner() == PLAYER) {
            printBoard();
            printf("You win!\n");
            break;
        }
        if (isFull()) {
            printBoard();
            printf("It's a tie!\n");
            break;
        }
        // Computer's turn
        bestMove();
        if (checkWinner() == COMPUTER) {
            printBoard();
            printf("Computer wins!\n");
            break;
        }
    }
}
int main() {
    initBoard();
    playGame();
return 0;
}