#pragma once

#include "Weapon.h"

class WeaponCC : public Weapon
{
public:

	WeaponCC(int ap, int as, int md, int cd, std::string path, int id, int ar, std::string bpath);

	~WeaponCC();

	int getARBS();

private:

	const int attackRange;

};