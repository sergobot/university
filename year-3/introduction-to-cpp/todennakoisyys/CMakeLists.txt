cmake_minimum_required(VERSION 3.5)

project(todennakoisyys LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 COMPONENTS Widgets Charts LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Charts LinguistTools REQUIRED)

set(TS_FILES todennakoisyys_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp

        distribution.h
        groupeddiscretedistribution.cpp
        groupeddiscretedistribution.h
        discretedistribution.cpp
        discretedistribution.h

        point.cpp
        point.h
        groupedpoint.cpp
        groupedpoint.h

        sample.cpp
        sample.h
        groupedsample.h
        groupedsample.cpp

        samplegenerator.h
        chensamplegenerator.cpp
        chensamplegenerator.h
        tablesamplegenerator.cpp
        tablesamplegenerator.h

        chisquarecriterion.h
        chisquarecriterion.cpp

        random_generator_provider.cpp
        random_generator_provider.h

        mainwindow.h
        mainwindow.cpp
        mainwindow.ui

        settingsdialog.h
        settingsdialog.cpp
        settingsdialog.ui

        defaults.h
        resources.qrc
        ${TS_FILES}

        3rdparty/probdist.h
        3rdparty/probdist.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(todennakoisyys
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(todennakoisyys SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(todennakoisyys
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(todennakoisyys PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)
