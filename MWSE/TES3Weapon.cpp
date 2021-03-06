#include "TES3Weapon.h"

namespace TES3{
	bool Weapon::isOneHanded() {
		switch (weaponType)
		{
		case WeaponType::ShortBlade1H:
		case WeaponType::LongBlade1H:
		case WeaponType::Blunt1H:
		case WeaponType::Axe1H:
			return true;
		}
		return false;
	}

	bool Weapon::isTwoHanded() {
		switch (weaponType)
		{
		case WeaponType::LongBlade2H:
		case WeaponType::Axe2H:
		case WeaponType::Spear2H:
		case WeaponType::Blunt2close:
		case WeaponType::Blunt2wide:
			return true;
		}
		return false;
	}

	bool Weapon::isMelee() {
		switch (weaponType)
		{
		case WeaponType::ShortBlade1H:
		case WeaponType::LongBlade1H:
		case WeaponType::Blunt1H:
		case WeaponType::Axe1H:
		case WeaponType::LongBlade2H:
		case WeaponType::Axe2H:
		case WeaponType::Spear2H:
		case WeaponType::Blunt2close:
		case WeaponType::Blunt2wide:
			return true;
		}

		return false;
	}

	bool Weapon::isRanged() {
		switch (weaponType)
		{
		case WeaponType::Bow:
		case WeaponType::Crossbow:
		case WeaponType::Thrown:
			return true;
		}

		return false;
	}

	bool Weapon::isAmmo() {
		switch (weaponType)
		{
		case WeaponType::Arrow:
		case WeaponType::Bolt:
			return true;
		}

		return false;
	}
}