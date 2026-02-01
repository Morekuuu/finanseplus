find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(logowanie_lib
    logowanie.cpp
    logowanie.h
    logowanie.ui

    rejestracja.cpp
    rejestracja.h
    rejestracja.ui







    
)

target_link_libraries(logowanie_lib PUBLIC Qt6::Widgets)
