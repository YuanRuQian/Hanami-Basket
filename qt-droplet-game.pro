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
    score.cpp \
    scoretest.cpp \
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
    score.h \
    scoretest.h \
    soundeffectmanager.h \
    user.h \
    usertest.h

DISTFILES += \
    data/scores/global_best_score/global_best_score.json \
    data/scores/score_test.json \
    data/users/test_user.json \
    data/users/user_test.json \
    gamemodel.qmodel
