QT += widgets
QT += charts
QT += core gui network serialport
requires(qtConfig(listwidget))
requires(qtConfig(combobox))
qtHaveModule(printsupport): QT += printsupport


INCLUDEPATH  +=  ../
HEADERS         = mainwindow.h \
    ../device/mgcdevice.h \
    ../device/mgcdeviceserial.h \
    ../device/mgcdeviceudp.h \
    ../gui/biosigscope.h \
    ../gui/themewidget.h
SOURCES         = main.cpp \
    ../device/mgcdeviceserial.cpp \
    ../device/mgcdeviceudp.cpp \
    ../device/mgcdevice.cpp \
    ../gui/biosigscope.cpp \
    ../gui/themewidget.cpp \
    mainwindow.cpp
RESOURCES       = biosignalscope.qrc

# install
# target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/dockwidgets
# INSTALLS += target

FORMS += \
    ../gui/themewidget.ui
