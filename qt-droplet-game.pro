QT+=widgets

QT+=multimedia


SOURCES += \
    backgroundscene.cpp \
    basket.cpp \
    canvaswidget.cpp \
    cherryblossom.cpp \
    constants.cpp \
    gamestatemachine.cpp \
    main.cpp \
    soundeffectmanager.cpp \
    user.cpp \
    usertest.cpp

RESOURCES += \
    resources.qrc

HEADERS += \
    backgroundscene.h \
    basket.h \
    canvaswidget.h \
    cherryblossom.h \
    constants.h \
    gamestatemachine.h \
    soundeffectmanager.h \
    user.h \
    usertest.h

DISTFILES += \
    data/users/test_user.json \
    data/users/user_test.json \
    gamemodel.qmodel
