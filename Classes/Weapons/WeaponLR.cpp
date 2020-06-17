#include "WeaponLR.h"

WeaponLR::WeaponLR(int ap, int as, int md, int cd, std::string path, int id, int bs, std::string bpath) :
	Weapon(ap, as, md, cd, path, id, bpath),
	bulletSpeed(bs)
{}

WeaponLR::~WeaponLR()
{}

int WeaponLR::getARBS()
{
	return bulletSpeed;
}