PROJECT                 = qextserialport
TEMPLATE                = lib

CONFIG                 += debug_and_release

#CONFIG                 += qt
#CONFIG                 += warn_on
#CONFIG                 += thread

#CONFIG			+= dll
#CONFIG			+= staticlib

QT                     -= gui

OBJECTS_DIR             = build/obj
MOC_DIR                 = build/moc
DEPENDDIR               = .
INCLUDEDIR              = .
HEADERS                 = qextserialbase.h \
                          qextserialport.h \
                          qextserialenumerator.h \
    com_greenstar_hardware_HWRS232.h
SOURCES                 = qextserialbase.cpp \
                          qextserialport.cpp \
                          qextserialenumerator.cpp \
    JNIMain.cpp

unix:HEADERS           += posix_qextserialport.h
unix:SOURCES           += posix_qextserialport.cpp
unix:DEFINES           += _TTY_POSIX_


win32:HEADERS          += win_qextserialport.h
win32:SOURCES          += win_qextserialport.cpp
win32:DEFINES          += _TTY_WIN_

win32:LIBS             += -lsetupapi


DESTDIR                 = build
#DESTDIR				= examples/enumerator/debug
#DESTDIR				= examples/qespta/debug
#DESTDIR				= examples/event/debug

CONFIG(debug, debug|release) {
        TARGET = JQextSerial
} else {
        TARGET = JQextSerial
}

unix:VERSION            = 1.2.0

OTHER_FILES += \
    Note.Qt5.html

INCLUDEPATH += C:\Java\jdk1.8.0_25\include \
C:\Java\jdk1.8.0_25\include\win32
