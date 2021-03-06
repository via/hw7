# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

symbian:TARGET.UID3 = 0xE32DF7DE

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=

QT += network
CONFIG += debug

SOURCES += main.cpp mainwindow.cpp connectdialog.cpp usersdialog.cpp \
PhoneClient.cpp
HEADERS += mainwindow.h connectdialog.h usersdialog.h PhoneClient.h
FORMS += mainwindow.ui connectdialog.ui usersdialog.ui

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()
