QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        ./src/commands/dataset.cpp \
        ./src/commands/model.cpp \
        ./src/commands/profile.cpp \
        ./src/commands/project.cpp \
        ./src/core/parser.cpp \
        ./src/utils/tools.cpp

HEADERS += \
        ./src/commands/dataset.h \
        ./src/commands/model.h \
        ./src/commands/profile.h \
        ./src/commands/project.h \
        ./src/core/parser.h \
        ./src/utils/tools.h

CONFIG += resources
RESOURCES += \
    config \
    scripts

unix {
    LIBS += -lpython3.10
    INCLUDEPATH += /usr/include/python3.10
}

win32 {
    LIBS += -LC:/Python38/libs -lpython38
    INCLUDEPATH += C:/Python38/include
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
