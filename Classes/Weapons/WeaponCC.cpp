#include "WeaponCC.h"

WeaponCC::WeaponCC(int ap, int as, int md, int cd, std::string path, int id, int ar, std::string bpath) :
	Weapon(ap, as, md, cd, path, id, bpath),
	attackRange(ar)
{}


WeaponCC::~WeaponCC()
{}

int WeaponCC::getARBS()
{
	return attackRange;
}