#include "usertest.h"
#include "user.h"
#include "jsonfileutils.h"

#include <cassert>

UserTest::UserTest() {
    username1 = "Gloria_test";
    username2 = "Lauryn_test";
    password1 = "Password1";
    password2 = "12345678Ab";
}

void UserTest::testCheckPassword() {
    assert(User::checkPassword("Password1"));
    assert(User::checkPassword("12345678Ab"));
    assert(User::checkPassword("SecurePwd123"));
    assert(User::checkPassword("Passw0rd"));
    assert(!User::checkPassword("pa$$word")); // no uupercase letter or number
    assert(!User::checkPassword("password")); // no uppercase letter or number
    assert(!User::checkPassword("PASSWORD" )); // no lowercase letter or number
    assert(!User::checkPassword("Pwd1")); // less than 8 characters
}

void UserTest::testAddUser() {
    User user1(username1, password1, "Gloria", "Wells", "Woman", "avatar1.jpg", QDate(1998, 12, 9));
    assert(User::addUser(user1));
    User user2(username1, "Password1", "Gloria", "Wells", "Woman", "avatar1.jpg", QDate(1998, 12, 9));
    assert(!User::addUser(user2)); // the username already exists
    User user3("Gloria2", "password1", "Gloria", "Wells", "Woman", "avatar1.jpg", QDate(1998, 12, 9));
    assert(!User::addUser(user3)); // invalid password
    User user4(username2, password2, "Lauryn", "Hanson", "Woman", "avatar2.jpg", QDate::currentDate());
    assert(User::addUser(user4));
}

void UserTest::testCheckUsername() {
    assert(User::checkUsername(username1));
    assert(User::checkUsername(username2));
    assert(!User::checkUsername("Amy"));
}

void UserTest::testCheckUser() {
    assert(User::checkUser(username1, password1));
    assert(!User::checkUser(username1, "Password2"));
    assert(User::checkUser(username2, password2));
}

void UserTest::testIsBirthday() {
    assert(!User::isBirthday(username1));
    assert(User::isBirthday(username2));
}

void UserTest::testAll() {
    UserTest::testCheckPassword();
    UserTest::testAddUser();
    UserTest::testCheckUsername();
    UserTest::testCheckUser();
    UserTest::testIsBirthday();
    qDebug() << "User test passed!";
    JsonFileUtils::removeFile(User::getUserFilePath(username1));
    JsonFileUtils::removeFile(User::getUserFilePath(username2));
}
