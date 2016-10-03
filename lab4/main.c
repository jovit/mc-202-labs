#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char sudoku_number;
    int column;
} QueenPositionOption;



char valid_position(QueenPositionOption *positions, int current) {
    int i;
    for (i = 0; i < current; i++) {
        if (positions[i].sudoku_number == positions[current].sudoku_number) {
            return 0;
        }

        if (positions[i].column == positions[current].column) {
            return 0;
        }

        if (abs(positions[i].column - positions[current].column) == abs(current - i)) {
            return 0;
        }

    }
    return 1;
}

char do_exists_solution(char **board, QueenPositionOption *positions, int currentLine, int dimension) {
    int i;

    if (currentLine == dimension) {
        return 1;
    } else {
        for (i = 0; i < dimension; i++) {
            QueenPositionOption positionOption;
            positionOption.column = i;
            positionOption.sudoku_number = board[currentLine][i];
            positions[currentLine] = positionOption;
            if (valid_position(positions, currentLine)) {
                if (do_exists_solution(board, positions, currentLine+1, dimension)) {
                    return 1;
                }
            }

        }
    }

    return 0;
}

char exists_solution(char **board, int dimension) {
    QueenPositionOption *positions = malloc(sizeof(QueenPositionOption) * dimension);
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