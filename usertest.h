#ifndef USERTEST_H
#define USERTEST_H

#include <QString>


class UserTest
{
private:
    QString username1, username2, password1, password2;
public:
    UserTest();
    void testCheckPassword();
    void testAddUser();
    void testCheckUsername();
    void testCheckUser();
    void testIsBirthday();
    void testCreateAvatarPath();
    void testAll();
};

#endif // USERTEST_H
