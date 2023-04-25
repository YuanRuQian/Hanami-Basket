#ifndef SCORE_H
#define SCORE_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>

class Score
{
public:
    QString username;
    QDateTime time;
    int score;
    static QString SCORE_PATH;
    static QString GLOBAL_BEST_SCORE_PATH;
    static QString TIME_FORMAT;
    Score(QString username, QDateTime time, int score);

    static QVector<Score> getScoreHistory(QString username, bool isGuest);
    static void addScore(Score score);
    static Score getGlobalBestScore();
    static bool updateGlobalBestScore(Score score);
    static void insertNewRecord(QString username, int score);

    static QString getScoreFilePath(QString username);
    static QJsonArray getScoreData(QString username);
    static Score jsonObjectToScore(QJsonObject obj);
    static QJsonObject scoreToJsonObject(Score score, bool addUsername = false);
};

#endif // SCORE_H
