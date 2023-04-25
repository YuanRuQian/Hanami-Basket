#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

enum error_t {
    success,
    duplicate_username,
    invalid_password,
    wrong_password,
    open_file_failure
};


class User
{
public:
    static QString USER_PATH;
    static QString AVATAR_PATH;
    static QString SCORE_PATH;
    static QString GUEST_AVATAR_PATH;
    QString username;
    QString password;
    QString firstName;
    QString lastName;
    QString gender;
    QString avatar; // the path of the profile picture
    QDate birthday;
    User(QString uname, QString pwd, QString firstN, QString lastN, QString gender, QString avatar, QDate bDay);
    static bool checkUsername(QString username);
    static bool checkPassword(QString password);
    static bool checkUser(QString username, QString password);
    static error_t addUser(User user);
    static bool isBirthday(QString username);
    static QString getUserFilePath(QString username);
    static QJsonObject getUserData(QString username);
    static QString getAvatarPath(QString username, bool isGuest);
    static QString createAvatarFileName(QString username, QString filePath);
    static QString createAvatarPath(QString username, QString filePath);
};

#endif // USER_H
