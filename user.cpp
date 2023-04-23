#include "user.h"
#include <QDir>
#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

QString User::USER_PATH = "../../../../Hanami-Basket/data/users/";
QString User::AVATAR_PATH = "../../../../Hanami-Basket/data/avatars/";
QString User::SCORE_PATH = "../../../../Hanami-Basket/data/scores/";

User::User(QString uname, QString pwd, QString firstN, QString lastN, QString gender, QString avatar, QDate bDay) {
    username = uname;
    password = pwd;
    firstName = firstN;
    lastName = lastN;
    this->gender = gender;
    this->avatar = avatar;
    birthday = bDay;
}

/**
 * @brief Check if a username already exists.
 * @param username
 * @return true if the username exists. Otherwise return false.
 */
bool User::checkUsername(QString username) {
    QDir dir(User::USER_PATH);
    QStringList user = dir.entryList(QStringList() << (username + QString(".json")));
    return user.size() == 1;
}

/**
 * @brief Check if the password is valid. (The password should
 * consist of at least 8 characters and contain at least one number,
 *  upper and lower case letters.)
 * @param password
 * @return true if the password is valid. Otherwise return false.
 */
bool User::checkPassword(QString password) {
    QRegularExpression pwdRegex("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,}$");
    QRegularExpressionMatch match = pwdRegex.match(password);
    return match.hasMatch();
}

/**
 * @brief When a user logs in, check if the username exists
 *  and the password is correct.
 * @param username
 * @param password
 * @return true if the username exists and the password is correct.
 * Otherwise return false.
 */
bool User::checkUser(QString username, QString password) {
    if (User::checkUsername(username)) {
        QJsonObject obj = User::getUserData(username);
        return password.compare(obj.value("password").toString()) == 0;
    }
    return false;
}

/**
 * @brief add a new user to the databse.
 * @param user
 * @return true if the user is successfully added. Otherwise return false.
 */
bool User::addUser(User user) {
    if (User::checkUsername(user.username)) {
        qDebug() << user.username << "already exists!";
        return false;
    }
    if (!User::checkPassword(user.password)) {
        qDebug() << user.password << "is invalid!";
        return false;
    }
    QJsonObject jsonObj;
    jsonObj["username"] = user.username;
    jsonObj["password"] = user.password;
    jsonObj["firstName"] = user.firstName;
    jsonObj["lastName"] = user.lastName;
    jsonObj["gender"] = user.gender;
    jsonObj["avatar"] = user.avatar;
    jsonObj["birthday"] = user.birthday.toString("yyyy-MM-dd");
    QJsonDocument jsonDoc(jsonObj);
    QFile file(User::getFilePath(user.username));
    if (!file.open(QIODevice::WriteOnly| QIODevice::Truncate)) {
        qDebug() << "can't open the file!";
        return false;
    }
    QTextStream stream(&file);
    stream << jsonDoc.toJson();
    file.close();
    return true;
}

/**
 * @brief Check if today is the user's birthday.
 * @param birthday
 * @return true if today is the user's birthday. Otherwise return false.
 */
bool User::isBirthday(QString username) {
    QDate birthday = QDate::fromString(getUserData(username).value("birthday").toString(), "yyyy-MM-dd");
    QDate today = QDate::currentDate();
    return today.month() == birthday.month() && today.day() == birthday.day();
}

QString User::getFilePath(QString username) {
    return User::USER_PATH + username + QString(".json");
}

QJsonObject User::getUserData(QString username) {
    QFile file(User::getFilePath(username));
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "can't open the file!";
    }
    QTextStream stream(&file);
    QString str = stream.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    return doc.object();
}
