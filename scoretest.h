#ifndef SCORETEST_H
#define SCORETEST_H

#include "score.h"


class ScoreTest
{
private:
    QString username1, username2;
public:
    ScoreTest();
    void testAddScoreAndGlobalBestScore();
    void testGetScoreHistory();
    void testAll();
    Score generateScore(QString username);
};

#endif // SCORETEST_H
