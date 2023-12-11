#ifndef ANALYSIS_H
#define ANALYSIS_H

struct Match {
    char tactic[8];
    int finalScore;
    int finalScorethem;
    int scorerShirtNumber;
    int assistantShirtNumber;
};

struct Player {
    int shirtNumber;
    int goals;
    int assists;
};

int calculateOverallScore(int wins, int draws, int losses);
int comparePlayers(const void* a, const void* b);

#endif 
