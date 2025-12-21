#pragma once
#include <list>
#include "budzet.h"

void zapiszBaze(const std::list<Budzet>& lista, const std::list<std::string>& konta);
void wczytajBaze(std::list<Budzet>& lista, std::list<std::string>& konta);
