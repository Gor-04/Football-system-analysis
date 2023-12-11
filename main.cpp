#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analysis.h"


int main() {
    FILE* file;

    // Open the file for writing
    file = fopen("C:\\Users\\user\\Desktop\\data.txt", "w");

    // Check if the file is opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1; // Exit the program with an error code
    }

    struct Player players[100]; // Assuming a maximum of 100 players
    int numPlayers = 0;

    int numMatches;

    // Get the number of matches from the user
    printf("Enter the number of matches: ");
    scanf("%d", &numMatches);

    // Allocate memory for an array of matches
    struct Match* matches = (struct Match*)malloc(numMatches * sizeof(struct Match));

    // Counters for wins, draws, and losses for each tactic
    int wins_433 = 0, draws_433 = 0, losses_433 = 0;
    int wins_422 = 0, draws_422 = 0, losses_422 = 0;
    int wins_4231 = 0, draws_4231 = 0, losses_4231 = 0;

    // Input data for each match
    for (int i = 0; i < numMatches; ++i) {
        printf("\nMatch %d:\n", i + 1);

        // Get tactical formation from the user
        printf("Choose tactical formation:\n");
        printf("1. 4-3-3\n2. 4-4-2\n3. 4-2-3-1\n");
        int choice;
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            sprintf(matches[i].tactic, "4-3-3");
            break;
        case 2:
            sprintf(matches[i].tactic, "4-4-2");
            break;
        case 3:
            sprintf(matches[i].tactic, "4-2-3-1");
            break;
        default:
            printf("Invalid choice. Using default tactic 4-3-3.\n");
            sprintf(matches[i].tactic, "4-4-3");
            break;
        }

        // Get final score from the user
        printf("Enter Your goal number: ");
        scanf("%d", &matches[i].finalScore);
        printf("Enter Their goal number: ");
        scanf("%d", &matches[i].finalScorethem);

        // Input goal scorer's positions
        for (int j = 0; j < matches[i].finalScore; j++) {
            printf("Enter your team goal scorer's position: ");
            scanf("%d", &matches[i].scorerShirtNumber);
            int playerIndex = -1;
            for (int k = 0; k < numPlayers; k++) {
                if (players[k].shirtNumber == matches[i].scorerShirtNumber) {
                    playerIndex = k;
                    break;
                }
            }
            if (playerIndex == -1) {
                players[numPlayers].shirtNumber = matches[i].scorerShirtNumber;
                players[numPlayers].goals = 1;
                players[numPlayers].assists = 0;
                numPlayers++;
            }
            else {
                // If the player is already in the array, increment their goals
                players[playerIndex].goals++;
            }
        }

        // Input assistant's positions
        for (int j = 0; j < matches[i].finalScore; j++) {
            printf("Enter your team assistant's shirt number: ");
            scanf("%d", &matches[i].assistantShirtNumber);

            // Check if the player is already in the players array
            int playerIndex = -1;
            for (int k = 0; k < numPlayers; k++) {
                if (players[k].shirtNumber == matches[i].assistantShirtNumber) {
                    playerIndex = k;
                    break;
                }
            }

            // If the player is not in the array, add them
            if (playerIndex == -1) {
                players[numPlayers].shirtNumber = matches[i].assistantShirtNumber;
                players[numPlayers].goals = 0;
                players[numPlayers].assists = 1;
                numPlayers++;
            }
            else {
                // If the player is already in the array, increment their assists
                players[playerIndex].assists++;
            }
        }


        // Determine the match result and update counters for each tactic
        if (matches[i].finalScore > matches[i].finalScorethem) {
            switch (choice) {
            case 1:
                wins_433++;
                break;
            case 2:
                wins_422++;
                break;
            case 3:
                wins_4231++;
                break;
            }
        }
        else if (matches[i].finalScore == matches[i].finalScorethem) {
            switch (choice) {
            case 1:
                draws_433++;
                break;
            case 2:
                draws_422++;
                break;
            case 3:
                draws_4231++;
                break;
            }
        }
        else {
            switch (choice) {
            case 1:
                losses_433++;
                break;
            case 2:
                losses_422++;
                break;
            case 3:
                losses_4231++;
                break;
            }
        }
    }

    // Display the results for each tactic
   /* printf("\nTactical Performance Summary:\n");
    printf("4-4-3 (Wins: %d, Draws: %d, Losses: %d)\n", wins_433, draws_433, losses_433);
    printf("4-2-2 (Wins: %d, Draws: %d, Losses: %d)\n", wins_422, draws_422, losses_422);
    printf("4-2-3-1 (Wins: %d, Draws: %d, Losses: %d)\n", wins_4231, draws_4231, losses_4231);*/
    fprintf(file, "Tactical Performance Summary:\n");
    fprintf(file, "4-3-3 (Wins: %d, Draws: %d, Losses: %d)\n", wins_433, draws_433, losses_433);
    fprintf(file, "4-4-2 (Wins: %d, Draws: %d, Losses: %d)\n", wins_422, draws_422, losses_422);
    fprintf(file, "4-2-3-1 (Wins: %d, Draws: %d, Losses: %d)\n", wins_4231, draws_4231, losses_4231);


    int overallScore_433 = calculateOverallScore(wins_433, draws_433, losses_433);
    int overallScore_422 = calculateOverallScore(wins_422, draws_422, losses_422);
    int overallScore_4231 = calculateOverallScore(wins_4231, draws_4231, losses_4231);

    char bestTactic[8];
    int bestOverallScore;
    // Determine the best tactic
    if (overallScore_433 > overallScore_422 && overallScore_433 > overallScore_4231) {
       // printf("\nBest Tactical Formation: 4-4-3\n");
        sprintf(bestTactic, "4-3-3");
        bestOverallScore = overallScore_433;
    }
    else if (overallScore_422 > overallScore_433 && overallScore_422 > overallScore_4231) {
        //printf("\nBest Tactical Formation: 4-2-2\n");
        sprintf(bestTactic, "4-4-2");
        bestOverallScore = overallScore_422;
    }
    else {
        //printf("\nBest Tactical Formation: 4-2-3-1\n");
        sprintf(bestTactic, "4-2-3-1");
        bestOverallScore = overallScore_4231;
    }                 
    int bestPlayerShirtNumber = 0;                                                                        
    int maxGoalsAndAssists = 0;

    fprintf(file, "\nThe best structure is (%s):\n", bestTactic);

    //printf("\nThe best structure is (%s):\n", bestTactic);

    for (int i = 0; i < numPlayers; i++) {
       fprintf(file, "Player %d: Goals - %d, Assists - %d\n", players[i].shirtNumber, players[i].goals, players[i].assists);
        //printf("Player %d: Goals - %d, Assists - %d\n", players[i].shirtNumber, players[i].goals, players[i].assists);
    }
    /*int BestPlayer = players[0].shirtNumber;
    int maxga = players[0].goals + players[0].assists;
    for (int i = 1; i < numPlayers; i++) {
        if (maxga < players[i].goals + players[i].assists)
        {
            maxga = players[i].goals + players[i].assists;
            BestPlayer = players[i].shirtNumber;
        }

    }checking besplayer another way
    */
    qsort(players, numPlayers, sizeof(struct Player), comparePlayers);

   // printf("\nPlayers sorted by Goals + Assists:\n");
    fprintf(file, "\nPlayers sorted by Goals + Assists:\n");

    for (int i = 0; i < numPlayers; i++) {
       // printf("Player %d: Goals - %d, Assists - %d\n", players[i].shirtNumber, players[i].goals, players[i].assists);
        fprintf(file, "Player %d: Goals - %d, Assists - %d\n", players[i].shirtNumber, players[i].goals, players[i].assists);
    }
    for (int i = 0; i < numPlayers; i++) {
        if (i == 0)
        {
            fprintf(file, " The best player is  %d, Goals and Assists %d,  \n", players[i].shirtNumber, players[i].goals + players[i].assists);
        }
        else
        {
            if (players[i].goals + players[i].assists == players[0].goals + players[0].assists)
            {
                fprintf(file, " The best player is  %d, Goals and Assists %d,  \n", players[i].shirtNumber, players[i].goals + players[i].assists);
            }
        }
    }
    //printf("The best play is: %d \n", BestPlayer);
    //printf("His goals + assits are %d \n", maxga);
    //fprintf(file, "The best player is: %d \n", BestPlayer);
    //fprintf(file, "His goals + assits are %d \n", maxga);
    fclose(file);
   
    free(matches);

    return 0;
}