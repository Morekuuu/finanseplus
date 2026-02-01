cmake_minimum_required(VERSION 3.16)
project(finanseplus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory(logowanie)
add_subdirectory(budzet)
add_subdirectory(archiwum)
add_subdirectory(kaucja)


add_executable(finanseplus_app
    app/main.cpp
    logo.rc
)

target_link_libraries(finanseplus_app
    Qt6::Widgets
    logowanie_lib
    budzet_lib
    archiwum_lib
    kaucja_lib
)
target_include_directories(finanseplus_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/logowanie
    ${CMAKE_CURRENT_SOURCE_DIR}/budzet
    ${CMAKE_CURRENT_SOURCE_DIR}/archiwum
    ${CMAKE_CURRENT_SOURCE_DIR}/kaucja
)
