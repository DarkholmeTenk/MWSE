#include "TES3Dialogue.h"

#include "LuaManager.h"

#define TES3_Dialogue_journalAdd 0x4B2F80
#define TES3_Dialogue_journalSetIndex 0x50F8B0

namespace TES3 {
	bool Dialogue::addToJournal(int index, MobileActor * actor) {
		if (type != DialogueType::Journal) {
			return false;
		}

		// Store our old index so we can refer to it later.
		int oldIndex = journalIndex;

		// Call the original function.
		bool added = reinterpret_cast<bool(__thiscall *)(Dialogue*, int, MobileActor *)>(TES3_Dialogue_journalAdd)(this, index, actor);

		// If the journal index changed, raise an event that it was modified.
		if (journalIndex > oldIndex) {
			mwse::lua::LuaManager::getInstance().triggerEvent(new mwse::lua::event::JournalEvent(this, oldIndex, index));
		}

		return added;
	}

	bool Dialogue::setJournalIndex(int index) {
		// Only valid for journal entries.
		if (type != DialogueType::Journal) {
			return false;
		}

		// Only run if the index changes.
		if (journalIndex == index) {
			return false;
		}

		// Store our old index so we can refer to it later.
		int oldIndex = journalIndex;

		// Update the journal index, as the original function would do.
		journalIndex = index;

		// Raise a modified event.
		if (journalIndex > oldIndex) {
			mwse::lua::LuaManager::getInstance().triggerEvent(new mwse::lua::event::JournalEvent(this, oldIndex, index));
		}

		return true;
	}
}

