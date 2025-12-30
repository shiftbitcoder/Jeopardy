#ifndef GAMETYPES_H
#define GAMETYPES_H

enum class Level{
    VeryLow,  //100 points question
    Low,      //200 points question
    Medium,   //300 points question
    High,     //400 points question
    VeryHigh  //500 points question
};

enum class AnswerResult{
    Correct,
    Unclaimed //goes to presenter
};

enum class GameState{
    Setup,
    Playing,
    Scoring,
    Finished
};

#endif // GAMETYPES_H
