#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

// Queue implementation using structures
struct QueueNode {
    int row;
    int col;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

void enqueue(struct Queue* q, int row, int col) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    struct QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}

void displayQueue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    struct QueueNode* current = q->front;
    while (current != NULL) {
        printf("(%d, %d) ", current->row, current->col);
        current = current->next;
    }
    printf("\n");
}

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '-';
        }
    }
}

void displayBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int checkWin(char board[SIZE][SIZE], char player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1; // Win
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return 1; // Win
        }
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1; // Win
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return 1; // Win
    }

    return 0; // No win
}

int main() {
    char board[SIZE][SIZE];
    initializeBoard(board);

    struct Queue* movesQueue = createQueue();
    int currentPlayer = 1; // Player 1 starts
    int totalMoves = 0;
    int gameOver = 0;

    printf("Welcome to Tic Tac Toe!\n");

    while (!gameOver && totalMoves < SIZE * SIZE) {
        printf("Current board:\n");
        displayBoard(board);

        int row, col;
        printf("Player %d, enter your move (row column): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != '-') {
            printf("Invalid move. Try again.\n");
            continue;
        }

        enqueue(movesQueue, row, col);
        board[row][col] = (currentPlayer == 1) ? 'X' : 'O';
        totalMoves++;

        if (checkWin(board, board[row][col])) {
            printf("Player %d wins!\n", currentPlayer);
            gameOver = 1;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Switch players
    }

    if (!gameOver) {
        printf("It's a draw!\n");
    }

    free(movesQueue); // Free memory allocated for the queue
    return 0;
}