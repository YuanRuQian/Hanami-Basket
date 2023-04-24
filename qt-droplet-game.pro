QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT+=multimedia

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backgroundscene.cpp \
    basket.cpp \
    canvaswidget.cpp \
    cherryblossom.cpp \
    constants.cpp \
    gamestatemachine.cpp \
    jsonfileutils.cpp \
    main.cpp \
    score.cpp \
    scoretest.cpp \
    soundeffectmanager.cpp \
    user.cpp \
    usertest.cpp \
    mainwindow.cpp

RESOURCES += \
    resources.qrc \
    resources.qrc


HEADERS += \
    mainwindow.h \
    backgroundscene.h \
    basket.h \
    canvaswidget.h \
    cherryblossom.h \
    constants.h \
    gamestatemachine.h \
    jsonfileutils.h \
    score.h \
    scoretest.h \
    soundeffectmanager.h \
    user.h \
    usertest.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    data/scores/global_best_score/global_best_score.json \
    data/scores/user_test.json \
    data/users/user_test.json \
    gamemodel.qmodel

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
