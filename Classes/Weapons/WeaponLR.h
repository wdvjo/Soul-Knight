#pragma once

#include "Weapon.h"

class WeaponLR : public Weapon
{
public:

	WeaponLR(int ap, int as, int md, int cd, std::string path, int id, int bs, std::string bpath);

	~WeaponLR();

	int getARBS();

private:

	const int bulletSpeed;
};