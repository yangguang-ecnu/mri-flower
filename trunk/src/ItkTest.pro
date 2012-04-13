#-------------------------------------------------
#
# Project created by QtCreator 2012-01-12T15:03:10
#
#-------------------------------------------------

INCLUDEPATH +=  /usr/local/include/ITK-4.0/ \
                /usr/local/include/vtk-5.8 \
                /usr/include/gdcm-2.0 \

LIBS += -L/usr/local/lib \
        -L/usr/lib \
        -L/usr/local/lib/vtk-5.8  \
        -L/home/kuba/External/ItkSandbox/bin/lib \
        -litkgdcmMSFF \
        -litkgdcmDICT \
        -litkgdcmIOD \
        -litkgdcmDSED \
        -litkgdcmCommon \
        -lITKIOVTK \
        -lITKVtkGlue \
        -lITKIOGDCM \
        -lITKSpatialObjects \
        -lITKCommon \
        -lm \
        -lpthread \
        -lITKMetaIO \
        -ldl  \
        -lITKDICOMParser  \
        -lz  \
        -lm  \
        -Wl

QT       += core

QT       -= gui

TARGET = ItkTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    seriesmanager.cpp \
    series.cpp \
    vtkKWImageIO.cxx \
    vtkKWImage.cxx \
    imagereader.cpp \
    vtkimagewriter.cpp \
    utils.cpp \
    otsusegmentation.cpp \
    imagemasker.cpp \
    itkimagewriter.cpp \
    imagecutter.cpp

HEADERS += \
    seriesmanager.h \
    series.h \
    vtkKWImageIO.h \
    vtkKWImage.h \
    imagereader.h \
    vtkimagewriter.h \
    utils.h \
    otsusegmentation.h \
    defines.h \
    imagemasker.h \
    itkimagewriter.h \
    imagecutter.h
