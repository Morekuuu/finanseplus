cmake_minimum_required(VERSION 3.16)

project(Informatyka)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Informatyka
    main.cpp
    mainwindow.cpp
    mainwindow.h
    baza_danych.h
    baza_danych.cpp
    budzet.h
    budzet.cpp
    konto.h
    konto.cpp
    dlugi.h
    dlugi.cpp
)

target_link_libraries(Informatyka PRIVATE Qt6::Widgets)
