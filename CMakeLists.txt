# cmake_minimum_required(VERSION <specify CMake version here>)
project(hueApp)

set(CMAKE_CXX_STANDARD 11)

add_executable(hueApp
        api.cpp
        api.h
        connect.h
        e27_off_waca.svg
        e27_on_waca.svg
        formsinglelight.cpp
        formsinglelight.h
        formsinglelight.ui
        group.cpp
        group.h
        grouplistmodel.cpp
        grouplistmodel.h
        hueApp.pro
        huestate.cpp
        huestate.h
        icons.qrc
        light.cpp
        light.h
        lightlistmodel.cpp
        lightlistmodel.h
        lightsform.cpp
        lightsform.h
        lightsform.ui
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        mygrouplistmodel.cpp
        mygrouplistmodel.h
        mygroupsform.cpp
        mygroupsform.h
        mygroupsform.ui
        setting.cpp
        setting.h
        settings.cpp
        settings.h
        settings.ui)
