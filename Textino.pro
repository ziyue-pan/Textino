CONFIG      += qscintilla2

HEADERS      = \
    src/core/Textino.h \
    src/config/ConfigManager.h \
    src/ui/LineEdit.h \
    src/dialog/FindDialog.h\
    src/dialog/ReplaceDialog.h


SOURCES      = src/main.cpp \
    src/core/Slots.cpp \
    src/core/Textino.cpp \
    src/config/ConfigManager.cpp \
    src/ui/LineEdit.cpp \
    src/dialog/FindDialog.cpp \
    src/dialog/ReplaceDialog.cpp

RESOURCES    = application.qrc
