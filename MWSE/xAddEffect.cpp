/************************************************************************
	
	xAddEffect.cpp - Copyright (c) 2008 The MWSE Project
	https://github.com/MWSE/MWSE/

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

**************************************************************************/

#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "TES3Util.h"

#include "TES3Alchemy.h"
#include "TES3Enchantment.h"
#include "TES3Spell.h"

using namespace mwse;

namespace mwse
{
	class xAddEffect : mwse::InstructionInterface_t
	{
	public:
		xAddEffect();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static xAddEffect xAddEffectInstance;

	xAddEffect::xAddEffect() : mwse::InstructionInterface_t(OpCode::xAddEffect) {}

	void xAddEffect::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xAddEffect::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		// Get parameters.
		long type = mwse::Stack::getInstance().popLong();
		mwseString& id = virtualMachine.getString(mwse::Stack::getInstance().popLong());
		long effectId = mwse::Stack::getInstance().popLong();
		long skillAttributeId = mwse::Stack::getInstance().popLong();
		long range = mwse::Stack::getInstance().popLong();
		long area = mwse::Stack::getInstance().popLong();
		long duration = mwse::Stack::getInstance().popLong();
		long magMin = mwse::Stack::getInstance().popLong();
		long magMax = mwse::Stack::getInstance().popLong();

		// Get the desired effect.
		TES3::Effect* effects = NULL;
		if (type == TES3::ObjectType::Spell) {
			TES3::Spell* spell = tes3::getSpellById(id.c_str());
			if (spell) {
				effects = spell->effects;
			}
			else {
#if _DEBUG
				mwse::log::getLog() << "xAddEffect: No spell found with id '" << id << "'." << std::endl;
#endif
				mwse::Stack::getInstance().pushLong(false);
				return 0.0f;
			}
		}
		else if (type == TES3::ObjectType::Enchantment) {
			TES3::Enchantment* enchant = tes3::getObjectById<TES3::Enchantment>(id);
			if (enchant) {
				effects = enchant->effects;
			}
			else {
#if _DEBUG
				mwse::log::getLog() << "xAddEffect: No spell found with id '" << id << "'." << std::endl;
#endif
				mwse::Stack::getInstance().pushLong(false);
				return 0.0f;
			}
		}
		else if (type == TES3::ObjectType::Alchemy) {
			TES3::Alchemy* alchemy = tes3::getObjectById<TES3::Alchemy>(id);
			if (alchemy) {
				effects = alchemy->effects;
			}
			else {
#if _DEBUG
				mwse::log::getLog() << "xAddEffect: No alchemy record found with id '" << id << "'." << std::endl;
#endif
				mwse::Stack::getInstance().pushLong(false);
				return 0.0f;
			}
		}
		else {
#if _DEBUG
			mwse::log::getLog() << "xAddEffect: Record type of " << type << " is not supported." << std::endl;
#endif
			mwse::Stack::getInstance().pushLong(false);
			return 0.0f;
		}

		// Get effect count.
		size_t effectCount = tes3::getEffectCount(effects);
		if (effectCount == 8) {
#if _DEBUG
			mwse::log::getLog() << "xAddEffect: Record already contains 8 effects." << std::endl;
#endif
			mwse::Stack::getInstance().pushLong(false);
			return 0.0f;
		}

		// Add effect.
		bool success = tes3::setEffect(effects, effectCount + 1, effectId, skillAttributeId, range, area, duration, magMin, magMax);
		mwse::Stack::getInstance().pushLong(success);

		return 0.0f;
	}
}