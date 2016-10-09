#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char sudoku_number;
    int column;
} QueenPosition; // determines a position of a queen in the board

// checks if the positions of the queens is valid for the last added queen
char valid_position(QueenPosition *positions, int current) {
    int i;
    for (i = 0; i < current; i++) {
        // check if the sudoku_number is repeated
        if (positions[i].sudoku_number == positions[current].sudoku_number) {
            return 0;
        }

        // check if there's another queen in the same column
        if (positions[i].column == positions[current].column) {
            return 0;
        }

        // check if there's a queen on the diagonal
        if (abs(positions[i].column - positions[current].column) == abs(current - i)) {
            return 0;
        }

    }
    return 1;
}

// auxiliar recursive function for exists_position
char do_exists_solution(char **board, QueenPosition *positions, int currentLine, int dimension) {
    int i;
    // if has ended going through the lines
    if (currentLine == dimension) {
        return 1;
    } else {
        // position the queen on each column of the line, looking for a valid position
        for (i = 0; i < dimension; i++) {
            QueenPosition positionOption;
            positionOption.column = i;
            positionOption.sudoku_number = board[currentLine][i]; // set the corresponding sudoku number from the board
            positions[currentLine] = positionOption; // fix the queen of the line
            if (valid_position(positions, currentLine)) { // if the position for the queen is valid for the other queens already positioned
                if (do_exists_solution(board, positions, currentLine+1, dimension)) { // if there's a solution with the queen in the current column
                    return 1;
                }
            }

        }
    }

    return 0;
}

// check if there's a solution for a certain board
char exists_solution(char **board, int dimension) {
    QueenPosition *positions = malloc(sizeof(QueenPosition) * dimension); // stores the possible queen positions determined so far
    char exists =  do_exists_solution(board, positions, 0, dimension);

    free(positions);

    return exists;
}

int main(void) {
    int dimension;
    char **board;
    int i, j;

    scanf("%d", &dimension);

    board = malloc(sizeof(char*) * dimension);
    for (i = 0; i < dimension; i++) {
        board[i] = malloc(sizeof(char) * dimension);
        for (j = 0; j < dimension; j++) {
            scanf(" %c", &board[i][j]);
        }
    }

    if (exists_solution(board, dimension)) {
        printf("Tem solucao.");
    } else {
        printf("Sem solucao.");
    }
    for (i = 0; i < dimension; i++) {
        free(board[i]);
    }

    free(board);
}