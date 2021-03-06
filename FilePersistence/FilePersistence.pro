ENVISION_ROOT_DIR = $$PWD/..
CONFIG(release, debug|release):BUILD_DIR = $${ENVISION_ROOT_DIR}/ReleaseBuild
CONFIG(debug, debug|release):BUILD_DIR = $${ENVISION_ROOT_DIR}/DebugBuild
PLUGINS_DIR = $${BUILD_DIR}/plugins
CONFIG(debug, debug|release):DEFINES += DEBUG
QMAKE_CXXFLAGS += -Werror -std=c++0x
INCLUDEPATH += ./headers \
    ./src \
    ./test \
    $${ENVISION_ROOT_DIR}
TARGET = filepersistence
DEFINES += FILEPERSISTENCE_LIBRARY
win32:LIBS += -L$${PLUGINS_DIR} \
    -llogger \
    -lselftest \
    -lmodelbase
QT = core gui xml
TEMPLATE = lib
CONFIG += plugin \
    warn_on \
    thread \
    precompile_header
target.path = $$PLUGINS_DIR
pluginmeta.path = $$PLUGINS_DIR
pluginmeta.files = $${TARGET}.plugin
INSTALLS += target \
    pluginmeta
PRECOMPILED_HEADER = headers/precompiled.h
HEADERS += headers/precompiled.h \
    headers/XMLModel.h \
    headers/SystemClipboard.h \
    headers/FilePersistenceException.h \
    headers/FileStore.h \
    headers/filepersistence_api.h \
    src/filepersistence.h
SOURCES += test/TypedListTests.cpp \
    test/ClipboardTests.cpp \
    src/XMLModel.cpp \
    src/SystemClipboard.cpp \
    test/LoadNodeDataTests.cpp \
    test/PartialNodeTests.cpp \
    src/FilePersistenceException.cpp \
    test/LoadTests.cpp \
    test/SaveTests.cpp \
    src/FileStore.cpp \
    src/filepersistence.cpp
RESOURCES = FilePersistence.qrc
