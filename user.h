#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>


class User
{
public:
    static QString USER_PATH;
    static QString AVATAR_PATH;
    static QString SCORE_PATH;
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
    static bool addUser(User user);
    static bool isBirthday(QString username);
    static QString getUserFilePath(QString username);
    static QJsonObject getUserData(QString username);
};

#endif // USER_H
