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
    User user1(username1, password1, "Gloria", "Wells", "Woman", User::AVATAR_PATH + "avatar1.jpg", QDate(1998, 12, 9));
    assert(User::addUser(user1) == success);
    User user2(username1, "Password1", "Gloria", "Wells", "Woman", User::AVATAR_PATH + "avatar1.jpg", QDate(1998, 12, 9));
    assert(User::addUser(user2) == duplicate_username); // the username already exists
    User user3("Gloria2", "password1", "Gloria", "Wells", "Woman", User::AVATAR_PATH + "avatar1.jpg", QDate(1998, 12, 9));
    assert(User::addUser(user3) == invalid_password); // invalid password
    User user4(username2, password2, "Lauryn", "Hanson", "Woman", User::AVATAR_PATH + "avatar2.jpg", QDate::currentDate());
    assert(User::addUser(user4) == success);
}


void UserTest::testCheckUsername() {
    assert(User::checkUsername("Gloria_test"));
    assert(User::checkUsername("Lauryn_test"));
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

void UserTest::testCreateAvatarPath() {
    // Test case 1: Normal behavior with .png extension
    QString username1 = "john_doe";
    QString filePath1 = "/path/to/avatar.png";
    QString expected1 = "john_doe.png";
    QString result1 = User::createAvatarFileName(username1, filePath1);
    assert(result1 == expected1);

    // Test case 2: Normal behavior with .jpg extension
    QString username2 = "jane_doe";
    QString filePath2 = "/path/to/avatar.jpg";
    QString expected2 = "jane_doe.jpg";
    QString result2 = User::createAvatarFileName(username2, filePath2);
    assert(result2 == expected2);

    // Test case 3: File path with no extension
    QString username3 = "alice";
    QString filePath3 = "/path/to/avatar";
    QString expected3 = "alice";
    QString result3 = User::createAvatarFileName(username3, filePath3);
    qDebug() << result3;
    assert(result3 == expected3);

    // Test case 4: File path with multiple periods
    QString username4 = "bob";
    QString filePath4 = "/path/to/bob's.avatar.png";
    QString expected4 = "bob.png";
    QString result4 = User::createAvatarFileName(username4, filePath4);
    assert(result4 == expected4);

    // Test case 5: File path with no username
    QString username5 = "";
    QString filePath5 = "/path/to/avatar.png";
    QString expected5 = ".png";
    QString result5 = User::createAvatarFileName(username5, filePath5);
    assert(result5 == expected5);
}

void UserTest::testAll() {
    UserTest::testCheckPassword();
    UserTest::testAddUser();
    UserTest::testCheckUsername();
    UserTest::testCheckUser();
    UserTest::testIsBirthday();
    UserTest::testCreateAvatarPath();
    qDebug() << "User test passed!";
    JsonFileUtils::removeFile(User::getUserFilePath(username1));
    JsonFileUtils::removeFile(User::getUserFilePath(username2));
}
