#pragma once
#include <list>
#include "budzet.h"

void zapiszBaze(const std::list<Budzet>& lista, const std::list<std::string>& konta);
void wczytajBaze(std::list<Budzet>& lista, std::list<std::string>& konta);

void zapisTransackji(int zdarzenie, std::string rodzaj1, std::string rodzaj2);
void odczytTransakcji();

std::string pobierzDate();




//Transakcje
/*
 *typy logów:
 *  <data> Dodano nowy budżet <Budżet>
 *  <data> Usunięto nowy budżet <Budżet>
 *  <data> Dodano nowe <konto> do budżetu <Budżet>
 *  <data> Usunięto <konto> z budżetu <Budżet>
 *  <data> Dodano nowe konto <nazwakonta> do list kont
 *  <data> Usunięto konto <nazwakonta> do list kont
 *  <data> odjęto środki z konta <konto> z budżetu <Budżet>
 *  <data> dodano środki do konta <konto> w Budżecie <budżet>
 *
 *
 *
 */
