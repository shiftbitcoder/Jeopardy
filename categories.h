#ifndef CATEGORIES_H
#define CATEGORIES_H

#include "questions.h"
#include <QString>
#include <QList>

struct Category{
    int cat_id;
    QString name;
    QList<Questions> questions;
};

#endif // CATEGORIES_H
