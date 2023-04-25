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
QString User::DEFAULT_AVATAR_PATH = "../../../../Hanami-Basket/images/default_avatar.jpeg";


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
 * @brief Add a new user to the database and store its avatar in the destination folder.
 * @return an error message.
 */
error_t User::addUser(QString username, QString password, QString firstName, QString lastName, QString gender, QString avatarSrcPath, QDate birthday) {
    if (User::checkUsername(username)) {
        qDebug() << username << "already exists!";
        return duplicate_username;
    }
    if (!User::checkPassword(password)) {
        qDebug() << password << "is invalid!";
        return invalid_password;
    }
    QString avatarDestPath = createAvatarPath(username, avatarSrcPath);
    User user(username, password, firstName, lastName, gender, avatarDestPath, birthday);
    copyFile(avatarSrcPath, avatarDestPath);
    return JsonFileUtils::writeObject(User::getUserFilePath(user.username), User::userToJsonObject(user));
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

/**
 * @brief Get a user's profile picture path.
 * @param username -- the username of the specified user
 * @param isGuest -- if this is a guest
 * @return If this is a guest, return the guest avatar path,
 * otherwise the user's avatar path.
 */
QString User::getAvatarPath(QString username, bool isGuest) {
    if (isGuest) {
        return DEFAULT_AVATAR_PATH;
    }
    QJsonObject obj = User::getUserData(username);
    return obj["avatar"].toString();
}

/**
 * @brief Generate a file name for a user's profile picture. The file
 * is named as "<username>.<file extension>"
 * @param username -- the username of the specified user
 * @param filePath -- the file's original path
 * @return the generated file path
 */
QString User::createAvatarFileName(QString username, QString filePath) {
    std::string path = filePath.toStdString();
    size_t index = path.find_last_of(".");
    if (index != std::string::npos) {
        std::string extension = path.substr(index + 1);
        return username.toLower() + "." + QString::fromStdString(extension);
    }
    return username;
}

/**
 * @brief Generate a file path for a user's profile picture. The file
 * is named as "<username>.<file extension>" and stored under AVATAR_PATH
 * @param username -- the username of the specified user
 * @param filePath -- the file's original path
 * @return the generated file path
 */
QString User::createAvatarPath(QString username, QString filePath) {
    if (filePath == "") {
        return User::DEFAULT_AVATAR_PATH;
    }
    return AVATAR_PATH + createAvatarFileName(username, filePath);
}

bool User::copyFile(const QString &srcFilePath, const QString &destFilePath)
{
    QFile srcFile(srcFilePath);
    QFileInfo srcFileInfo(srcFile);
    QFile destFile(destFilePath);

    qDebug() << "srcFilePath: " << srcFilePath;
    qDebug() << "destFilePath: " << destFilePath;

    if (!srcFile.exists() || !srcFile.open(QIODevice::ReadOnly) || !destFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to open files";
        return false;
    }

    QByteArray buffer;
    while (!srcFile.atEnd())
    {
        buffer = srcFile.read(1048576);
        destFile.write(buffer);
    }

    srcFile.close();
    destFile.close();

    qDebug() << "File copied successfully";
    return true;
}

QJsonObject User::userToJsonObject(User user) {
    QJsonObject jsonObj;
    jsonObj["username"] = user.username;
    jsonObj["password"] = user.password;
    jsonObj["firstName"] = user.firstName;
    jsonObj["lastName"] = user.lastName;
    jsonObj["gender"] = user.gender;
    jsonObj["avatar"] = user.avatar;
    jsonObj["birthday"] = user.birthday.toString("yyyy-MM-dd");
    return jsonObj;
}
