#include "user.h"
#include "jsonfileutils.h"
#include <QDir>
#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

QString User::USER_PATH = "../../../../Hanami-Basket/data/users/";
QString User::AVATAR_PATH = "../../../../Hanami-Basket/data/avatars/";
QString User::SCORE_PATH = "../../../../Hanami-Basket/data/scores/";

// create a new User Object
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
 * @brief Check if a username already exists. (case insensitive)
 * @param username
 * @return true if the username exists. Otherwise return false.
 */
bool User::checkUsername(QString username) {
    QDir dir(User::USER_PATH);
    QStringList user = dir.entryList(QStringList() << (username.toLower() + QString(".json")));
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
error_t User::addUser(User user) {
    if (User::checkUsername(user.username)) {
        qDebug() << user.username << "already exists!";
        return duplicate_username;
    }
    if (!User::checkPassword(user.password)) {
        qDebug() << user.password << "is invalid!";
        return invalid_password;
    }
    QJsonObject jsonObj;
    jsonObj["username"] = user.username;
    jsonObj["password"] = user.password;
    jsonObj["firstName"] = user.firstName;
    jsonObj["lastName"] = user.lastName;
    jsonObj["gender"] = user.gender;
    jsonObj["avatar"] = user.avatar;
    jsonObj["birthday"] = user.birthday.toString("yyyy-MM-dd");
    return JsonFileUtils::writeObject(User::getUserFilePath(user.username), jsonObj);
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

/**
 * @brief Get the file path of a user's profile.
 * (a user's file name is the lowercase of its
 * username with the extension ".json")
 * @param username -- the specified username
 * @return the file path of the user's profile
 */
QString User::getUserFilePath(QString username) {
    return User::USER_PATH + username.toLower() + QString(".json");
}

/**
 * @brief Read a user's profile and store it in a QJsonObject.
 * @param username -- the specified username
 * @return A QJsonObject of the user's profile
 */
QJsonObject User::getUserData(QString username) {
    QJsonDocument doc = JsonFileUtils::readFile(User::getUserFilePath(username));
    return doc.object();
}

QString User::getAvatarPath(QString username) {
    QJsonObject obj = User::getUserData(username);
    return AVATAR_PATH + obj["avatar"].toString();
}
