#include "scoretest.h"
#include "score.h"
#include "jsonfileutils.h"

#include <QRandomGenerator>
#include <QDateTime>
#include <QVector>
#include <QFile>

ScoreTest::ScoreTest() {
    username1 = "Gloria_test";
    username2 = "Lauryn_test";
}

void ScoreTest::testAddScoreAndGlobalBestScore() {
    Score bestScore("null", QDateTime::currentDateTime(), 0);
    for (int i = 0; i < 10; i++) {
        Score score = generateScore(username1);
        qDebug() << score.username << " " << score.time.toString(Score::TIME_FORMAT) << score.score;
        Score::addScore(score);
        if (score.score > bestScore.score) {
            bestScore = score;
            Score::updateGlobalBestScore(bestScore);
        }
    }
    assert(Score::getGlobalBestScore().score == bestScore.score);
    assert(Score::getGlobalBestScore().username == bestScore.username);

    for (int i = 0; i < 10; i++) {
        Score score = generateScore(username2);
        qDebug() << score.username << " " << score.time.toString(Score::TIME_FORMAT) << score.score;
        Score::addScore(score);
        if (score.score > bestScore.score) {
            bestScore = score;
            Score::updateGlobalBestScore(bestScore);
        }
    }
    assert(Score::getGlobalBestScore().score == bestScore.score);
    assert(Score::getGlobalBestScore().username == bestScore.username);
}

void ScoreTest::testGetScoreHistory() {
    QVector<Score> scores1 = Score::getScoreHistory(username1, false);
    assert(scores1.size() == 10);
    for (Score score : scores1) {
        qDebug() << username1 << " " << score.time.toString(Score::TIME_FORMAT) << score.score;
    }
    QVector<Score> scores2 = Score::getScoreHistory(username2, false);
    assert(scores2.size() == 10);
    for (Score score : scores2) {
        qDebug() << username2 << " " << score.time.toString(Score::TIME_FORMAT) << score.score;
    }
    QVector<Score> scores3 = Score::getScoreHistory("anyone", false); // non-existent user
    assert(scores3.size() == 0);
    assert(Score::getScoreHistory(username1, true).size() == 0);
}

void ScoreTest::testAll() {
    testAddScoreAndGlobalBestScore();
    testGetScoreHistory();
    qDebug() << "Score test passed!";
    JsonFileUtils::removeFile(Score::getScoreFilePath(username1));
    JsonFileUtils::removeFile(Score::getScoreFilePath(username2));
    JsonFileUtils::removeFile(Score::GLOBAL_BEST_SCORE_PATH);
    Score::updateGlobalBestScore(Score("null", QDateTime::currentDateTime(), 0));
}

/**
 * @brief Genearte a Score object with a specified username and random time and score.
 * @param username
 * @return the Score object generated randomly.
 */
Score ScoreTest::generateScore(QString username) {
    qint64 randomSeconds = QRandomGenerator::global()->generate();
    QDateTime randomDateTime = QDateTime::fromMSecsSinceEpoch(randomSeconds);
    int randomScore = rand() % 20 * 5;
    Score score(username, randomDateTime, randomScore);
    return score;
}
