/*
    Justin Lam
    CPSC 351 Spring
    Project 1: Rod Cutting
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_PIECES 100

typedef struct {
    int length;
    int value;
} Piece;

void read_pieces(Piece *pieces, int *piece_count);
int cut_rod(Piece *pieces, int piece_count, int rod_length);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <supplied rod length>\n", argv[0]);
        return 1;
    }

    int rod_length = atoi(argv[1]);
    if (rod_length <= 0) {
        printf("Invalid rod length: %d\n", rod_length);
        return 1;
    }

    Piece pieces[MAX_PIECES];
    int piece_count = 0;

    read_pieces(pieces, &piece_count);
    if (piece_count == 0) {
        printf("No valid pieces provided.\n");
        return 1;
    }

    int total_value = cut_rod(pieces, piece_count, rod_length);
    printf("Value: %d\n", total_value);

    return 0;
}

void read_pieces(Piece *pieces, int *piece_count) {
    printf("Enter piece data (<length>, <value>):\n");
    while (scanf("%d, %d", &pieces[*piece_count].length,
                 &pieces[*piece_count].value) == 2) {
        if (pieces[*piece_count].length > 0 && pieces[*piece_count].value > 0) {
            (*piece_count)++;
        } else {
            printf("Invalid input. Length and value must be positive.\n");
            exit(1);
        }
    }
}

int cut_rod(Piece *pieces, int piece_count, int rod_length) {
    int total_value      = 0;
    int remaining_length = rod_length;

    printf("\nCutting list:\n");

    while (remaining_length > 0) {
        int best_piece_index = -1;

        for (int i = 0; i < piece_count; i++) {
            if (pieces[i].length <= remaining_length) {
                if (best_piece_index == -1 ||
                    pieces[i].value > pieces[best_piece_index].value) {
                    best_piece_index = i;
                }
            }
        }

        if (best_piece_index == -1)
            break;

        int cuts      = remaining_length / pieces[best_piece_index].length;
        int cut_value = cuts * pieces[best_piece_index].value;

        printf("%d @ %d = %d\n", cuts, pieces[best_piece_index].length,
               cut_value);

        total_value += cut_value;
        remaining_length -= cuts * pieces[best_piece_index].length;
    }

    printf("Remainder: %d\n", remaining_length);
    return total_value;
}
