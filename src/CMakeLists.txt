cmake_minimum_required(VERSION 3.5)

project(SmartCalc-V2.0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/Applications/Qt/6.2.4/macos/lib/cmake")
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)

set(PROJECT_SOURCES
        model/CalculationModel.cc
        model/CalculationModel.h
        model/CreditModel.cc
        model/CreditModel.h

        controller/CalculationController.cc
        controller/CalculationController.h
        controller/CreditController.cc
        controller/CreditController.h

        view/main.cc
        view/form.cc
        view/loancalc.cc
        view/plot.cc
        view/mainwindow.cc
        view/form.h
        view/mainwindow.h
        view/loancalc.h
        view/plot.h
        view/form.ui
        view/plot.ui
        view/mainwindow.ui

        qcustomplot.cc
        qcustomplot.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc-V2.0
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CmakeSmartCalc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SmartCalc-V2.0 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartCalc-V2.0
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartCalc-V2.0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SmartCalc-V2.0 PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(SmartCalc-V2.0 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc-V2.0)
endif()