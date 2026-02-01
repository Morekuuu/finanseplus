find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(archiwum_lib
    backend_budzet.cpp
    budzet_main_backend.cpp
    struktury.h
)

target_link_libraries(archiwum_lib PUBLIC Qt6::Widgets budzet_lib)

target_include_directories(archiwum_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/budzet
)