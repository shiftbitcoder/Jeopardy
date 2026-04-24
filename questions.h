#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <QString>
#include <gametypes.h>

struct Questions{
    int question_id;
    int qcat_id;
    QString question;
    QString answer;
    Level level;
    int points;

};

#endif // QUESTIONS_H
