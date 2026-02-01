
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(kaucja_lib
  

    dodajsaldo.cpp
    dodajsaldo.h
    dodajsaldo.ui

    wyplacsaldo.cpp
    wyplacsaldo.h
    wyplacsaldo.ui

    wrzucbutelki.cpp
    wrzucbutelki.h
    wrzucbutelki.ui
)

target_link_libraries(kaucja_lib PUBLIC Qt6::Widgets)
