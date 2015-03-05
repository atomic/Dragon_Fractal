TEMPLATE = app

SOURCES += main.cpp \
    game.cpp

HEADERS += \
    game.h \

CONFIG += c++11

#------------------------------------------
##Add these lines for SFML:

# LIBS
unix:LIBS += -L"/usr/local/lib" -lsfml-system -lsfml-window -lsfml-graphics
win32:LIBS += -L"C:\SFML\lib" -lsfml-system -lsfml-window -lsfml-graphics

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
# CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
 
 # INCLUDEPATH
unix:INCLUDEPATH += "/usr/local/include"
unix:DEPENDPATH += "/usr/local/include"

# For windows, configure this based on where you install SFML
# Alternatively, merge SFML library with where mingw is
win32:INCLUDEPATH += "C:\SFML"
win32:DEPENDPATH += "C:\SFML"

