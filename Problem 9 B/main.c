#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initialize the game board
char board[3][3] = {
    {'-', '-', '-'},
    {'-', '-', '-'},
    {'-', '-', '-'}
};

// Define the function to print the game board
void print_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Define the function to check if a player has won
int check_win(char player) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return 1;
        }
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return 1;
    }

    // No win conditions met
    return 0;
}

// Define the function to play the game
void play_game() {
    // Initialize variables
    char player = 'X';
    char computer = 'O';
    int player_score = 0;
    int computer_score = 0;
    int draw_score = 0;
    int num_games = 3;

    printf("Welcome to the game of dots and crosses!\n");

    // Loop for the number of games
    for (int game = 1; game <= num_games; game++) {
        printf("\nGame %d:\n", game);
        // Initialize the game board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '-';
            }
        }
        int game_over = 0;

        // Loop until game is over
        while (!game_over) {
            // Print the game board
            printf("\n");
            print_board();
            printf("\n");

            // Get the player's move
            int row, col;
            printf("Player's move (row column): ");
            scanf("%d %d", &row, &col);
            while (board[row][col] != '-') {
                printf("Invalid move. Please try again.\n");
                printf("Player's move (row column): ");
                scanf("%d %d", &row, &col);
            }
            board[row][col] = player;

            // Check if player has won
            if (check_win(player)) {
                printf("\n");
                print_board();
                printf("\nPlayer wins!\n");
                player_score += 3;
                game_over = 1;
                break;
            }

            // Check if the game is a draw
            int draw = 1;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == '-') {
                        draw = 0;
                        break;
                    }
                }
                if (!draw) {
                    break;
                }
            }
            if (draw) {
                printf("\n");
                print_board();
                printf("\nDraw!\n");
                draw_score += 1;
                game_over = 1;
                break;
            }

            // Get the computer's move
            int computer_row, computer_col;
            srand(time(NULL));
            do {
                computer_row = rand() % 3;
                computer_col = rand() % 3;
            } while (board[computer_row][computer_col] != '-');
            board[computer_row][computer_col] = computer;

            // Check if computer has won
            if (check_win(computer)) {
                printf("\n");
                print_board();
                printf("\nComputer wins!\n");
                computer_score += 3;
                game_over = 1;
                break;
            }
        }
    }

    // Print the final scores
    printf("\nFinalscore:\n");
    printf("Player: %d points\n", player_score);
    printf("Computer: %d points\n", computer_score);
    printf("Draw: %d points\n", draw_score);
    if (player_score > computer_score) {
        printf("Player wins the game!\n");
    } else if (computer_score > player_score) {
        printf("Computer wins the game!\n");
    } else {
        printf("The game is a draw!\n");
    }
}

// Define the main function
int main() {
    // Play the game
    play_game();

    return 0;
}
