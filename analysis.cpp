#include "analysis.h"

#include <stdio.h>
#include <stdlib.h>

int calculateOverallScore(int wins, int draws, int losses) {
    return 3 * wins + draws - losses;
}

int comparePlayers(const void* a, const void* b) {
    const struct Player* playerA = (const struct Player*)a;
    const struct Player* playerB = (const struct Player*)b;

    return (playerB->goals + playerB->assists) - (playerA->goals + playerA->assists);
}
