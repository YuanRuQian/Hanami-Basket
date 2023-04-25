#include "score.h"
#include "jsonfileutils.h"

#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>

QString Score::SCORE_PATH = "../../../../Hanami-Basket/data/scores/";
QString Score::GLOBAL_BEST_SCORE_PATH = "../../../../Hanami-Basket/data/scores/global_best_score/global_best_score.json";
QString Score::TIME_FORMAT = "yyyy-MM-dd HH:mm:ss";

/**
 * @brief Create a new score object.
 * @param username
 * @param time
 * @param score
 */
Score::Score(QString username, QDateTime time, int score) {
    this->username = username;
    this->time = time;
    this->score = score;
}

/**
 * @brief Get a user's score history.
 * @param username -- the specified username
 * @return the user's score history in a QVector<Score>.
 */
QVector<Score> Score::getScoreHistory(QString username, bool isGuest) {
    QVector<Score> scores;
    if (isGuest) return scores;
    QJsonArray arr = Score::getScoreData(username);
    for (int i = 0; i < arr.size(); i++) {
        QJsonObject obj = arr.at(i).toObject();
        scores.append(jsonObjectToScore(obj));
    }
    return scores;
}

/**
 * @brief Add a new score record to a user's score file.
 * (The filename is <username.json>)
 * @param score the score to be added.
 */
void Score::addScore(Score score) {
    QJsonArray arr = getScoreData(score.username);
    QJsonObject obj = scoreToJsonObject(score);
    arr.append(obj);
    JsonFileUtils::writeArray(Score::getScoreFilePath(score.username), arr);
}

/**
 * @brief Get global best scoret.
 * @return the Score object of the gloval best score.
 */
Score Score::getGlobalBestScore() {
    QJsonDocument doc = JsonFileUtils::readFile(Score::GLOBAL_BEST_SCORE_PATH);
    Score score = Score::jsonObjectToScore(doc.object());
    return score;
}

/**
 * @brief Update the global best score.
 * @param score -- the new score
 * @return If the new score is the first score record of it is
 * greater than the global best score, update the global best
 * score and return true. Otherwise the global best score stays
 * the same and return false.
 */
bool Score::updateGlobalBestScore(Score score) {
    if (QFile::exists(Score::GLOBAL_BEST_SCORE_PATH)) {
        Score best = Score::getGlobalBestScore();
        if (score.score > best.score) {
            QJsonObject newBest = scoreToJsonObject(score, true);
            JsonFileUtils::writeObject(Score::GLOBAL_BEST_SCORE_PATH, newBest);
            return true;
        }
        return false;
    }
    JsonFileUtils::writeObject(Score::GLOBAL_BEST_SCORE_PATH, scoreToJsonObject(score, true));
    return true;
}

void Score::insertNewRecord(QString username, int score) {
    Score scoreObj(username, QDateTime::currentDateTime(), score);
    addScore(scoreObj);
    updateGlobalBestScore(scoreObj);
}

/**
 * @brief Get the file path of a user's score data.
 * @param username -- the specified username
 * @return the file path of the user's score data.
 */
QString Score::getScoreFilePath(QString username) {
    return Score::SCORE_PATH + username + QString(".json");
}

/**
 * @brief Read a user's score data and store it in a QJsonArray.
 * @param username -- the specified username
 * @return A QJsonArray of the user's score data.
 */
QJsonArray Score::getScoreData(QString username) {
    QJsonDocument doc = JsonFileUtils::readFile(Score::getScoreFilePath(username));
    return doc.array();
}

/**
 * @brief Turn a QJsonObject into a Score object.
 * @param obj -- the specified QJsonObject
 * @return a score object of the specified QJsonObject.
 */
Score Score::jsonObjectToScore(QJsonObject obj) {
    QDateTime time = QDateTime::fromString(obj["time"].toString(), Score::TIME_FORMAT);
    Score score(obj["username"].toString(), time, obj["score"].toInt());
    return score;
}

/**
 * @brief Turn a score object into a QJsonObject.
 * @param score -- the specified Score object
 * @param addUsername -- if username need to be added to the resulted QJsonObject
 * @return a QJsonObject representing the specified Score object.
 */
QJsonObject Score::scoreToJsonObject(Score score, bool addUsername) {
    QJsonObject obj;
    obj["time"] = score.time.toString(Score::TIME_FORMAT);
    obj["score"] = score.score;
    if (addUsername) {
        obj["username"] = score.username;
    }
    return obj;
}

