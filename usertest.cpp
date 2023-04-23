#include "usertest.h"
#include "user.h"

#include <cassert>

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
    User user1("Gloria_test", "Password1", "Gloria", "Wells", "Woman", "avatar1.jpg", QDate(1998, 12, 9));
    assert(User::addUser(user1));
    User user2("Gloria_test", "Password1", "Gloria", "Wells", "Woman", "avatar1.jpg", QDate(1998, 12, 9));
    assert(!User::addUser(user2)); // the username already exists
    User user3("Gloria2", "password1", "Gloria", "Wells", "Woman", "avatar1.jpg", QDate(1998, 12, 9));
    assert(!User::addUser(user3)); // invalid password
    User user4("Lauryn_test", "12345678Ab", "Lauryn", "Hanson", "Woman", "avatar2.jpg", QDate::currentDate());
    assert(User::addUser(user4));
}

void UserTest::testCheckUsername() {
    assert(User::checkUsername("Gloria_test"));
    assert(User::checkUsername("Lauryn_test"));
    assert(!User::checkUsername("Amy"));
}

void UserTest::testCheckUser() {
    assert(User::checkUser("Gloria_test", "Password1"));
    assert(!User::checkUser("Gloria_test", "Password2"));
    assert(User::checkUser("Lauryn_test", "12345678Ab"));
}

void UserTest::testIsBirthday() {
    assert(!User::isBirthday("Gloria_test"));
    assert(User::isBirthday("Lauryn_test"));
}

void UserTest::testAll() {
    UserTest::testCheckPassword();
    UserTest::testAddUser();
    UserTest::testCheckUsername();
    UserTest::testCheckUser();
    UserTest::testIsBirthday();
}
