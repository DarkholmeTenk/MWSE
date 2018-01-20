/************************************************************************
	
	xSetGSString.cpp - Copyright (c) 2008 The MWSE Project
	http://www.sourceforge.net/projects/mwse

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

using namespace mwse;

namespace mwse
{
	class xSetGSString : mwse::InstructionInterface_t
	{
	public:
		xSetGSString();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xSetGSStringOpcode = 0x394E;
	static xSetGSString xSetGSStringInstance;

	xSetGSString::xSetGSString() : mwse::InstructionInterface_t(xSetGSStringOpcode) {}

	void xSetGSString::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xSetGSString::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		mwLong_t gmstId = Stack::getInstance().popLong();
		mwseString_t& newString = virtualMachine.getString(Stack::getInstance().popLong());

		if (gmstId < 0) {
			mwse::log::getLog() << "xSetGSString: Invalid GMST id." << std::endl;
			mwse::Stack::getInstance().pushLong(false);
			return 0.0f;
		}

		// Get the string we're going to change.
		TES3CellMaster_t* cellMaster = tes3::getCellMaster();
		char *& oldString = cellMaster->recordLists->GMSTs[gmstId]->value.string_value;

		// Reallocate string memory if it is growing in size.
		if (newString.length() > strlen(oldString)) {
			oldString = reinterpret_cast<char*>(realloc(oldString, newString.length() + 1));
		}
		
		// Copy over new value.
		strcpy(oldString, newString.c_str());

		mwse::Stack::getInstance().pushLong(true);
		return 0.0f;
	}
}