TARGET = sclai

QT = core

CONFIG += c++17 cmdline

SOURCES += \
        main.cpp \
        src/commands/dataset.cpp \
        src/commands/model.cpp \
        src/commands/profile.cpp \
        src/commands/project.cpp \
        src/commands/frameworks.cpp\
        src/core/parser.cpp \       
        src/utils/tools.cpp \
        src/utils/errors.cpp

HEADERS += \
        src/commands/dataset.h \
        src/commands/model.h \
        src/commands/profile.h \
        src/commands/project.h \
        src/commands/frameworks.h \
        src/core/parser.h \
        src/utils/tools.h \
        src/utils/errors.h \
        src/config/config.h

# Following two blocks are for 'make install'.
# Those will not be needed for (deb) packages as only 'make' is used.
# The copying to the destination in deb packages is done by the
# package manager. However, it still needs to be copied MANUALLY
# in a representation of the folders on package creation.
CONFIG(release, debug|release): INSTALLS += target config_install
config_install.path = /etc/$${TARGET}/scripts
config_install.files += config/*

CONFIG(release, debug|release): INSTALLS += target script_install
script_install.path = /etc/$${TARGET}/scripts
script_install.files += scripts/*

# adjust your python libs!!
#LIBS += -lpython3.11
#INCLUDEPATH += /usr/include/python3.11

target.path = /usr/bin
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target
