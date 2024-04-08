cmake_minimum_required(VERSION 3.5)

project(mediaPlayer VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_VERSION_MAJOR 6)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

message("My Qt version is: ${QT_VERSION_MAJOR}")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mediaPlayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        playlist.h playlist.cpp
    )
else()
    if(ANDROID)
        add_library(mediaPlayer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(mediaPlayer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(mediaPlayer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)


include(GNUInstallDirs)
install(TARGETS mediaPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mediaPlayer)
endif()
