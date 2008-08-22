#Configure
TEMPLATE = lib
CONFIG += warn_on
TARGET = gui
DESTDIR = ./build

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
QT -= xml sql svg

#Temporary Directory
MOC_DIR =	./tmp
UI_DIR =	./tmp
OBJECTS_DIR =	./tmp
RCC_DIR	=	./tmp

INCLUDEPATH +=	./tmp \
		./src/dialogs \

CONFIG(designer) {
DEFINES += DESIGNER
CONFIG += plugin
} else {
INCLUDEPATH +=  ${TOOLCHAIN}/Qt/include/*
LIBS += -L${TOOLCHAIN}/Qt/lib
}


#Library
LIBS+=

#Source Files
SOURCES +=	./dialogs/nmessagedialog.cpp \
		./dialogs/nhelpdialog.cpp \
		./dialogs/nbusywidget.cpp

#Header Files
HEADERS +=	./dialogs/nmessagedialog.h \
		./dialogs/nhelpdialog.h \
		./dialogs/nbusywidget.h

#Form Files
FORMS +=	./dialogs/forms/nmessagedialog.ui \
		./dialogs/forms/nhelpdialog.ui

#Translation Files
TRANSLATIONS +=

#Resource files
RESOURCES += ./resources/lib-gui.qrc

#Install
CONFIG(designer) {
designer_plugin.path = $$[QT_INSTALL_PLUGINS]/designer
designer_plugin.files = ./build/*
designer_plugin.extra = cp -a ./build/* $$[QT_INSTALL_PLUGINS]/designer

designer_include.path = $$[QT_INSTALL_HEADERS]/neux
designer_include.files = $$HEADERS
designer_include.extra = cp ./tmp/*.h $$[QT_INSTALL_HEADERS]/neux

INSTALLS += designer_plugin designer_include
} else {
rootfs.path = /${ROOTFS}/fs/lib
rootfs.files = ./build/*.so.1.0.0
rootfs.extra = cp -a ./build/* /${ROOTFS}/fs/lib

toolchain_include.path = /${TOOLCHAIN_USR_INSTALL}/include/neux
toolchain_include.files = 	./tmp/*.h
				./dialog/*.h \

toolchain_lib.path = /${TOOLCHAIN_USR_INSTALL}/lib
toolchain_lib.files = ./build/*.so.1.0.0
toolchain_lib.extra = cp -a ./build/* /${TOOLCHAIN_USR_INSTALL}/lib

INSTALLS += rootfs toolchain_include toolchain_lib
}


QMAKE_CLEAN = ./build/* ./Makefile ./tmp/* ./*~
