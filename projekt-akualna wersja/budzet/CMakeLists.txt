find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(budzet_lib
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

target_link_libraries(budzet_lib PUBLIC Qt6::Widgets kaucja_lib)
target_include_directories(budzet_lib PUBLIC ${CMAKE_SOURCE_DIR}/kaucja)
