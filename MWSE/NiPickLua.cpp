#include "NIPickLua.h"

#include "sol.hpp"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "NIUtil.h"
#include "NIDefines.h"
#include "NINode.h"
#include "NIPick.h"
#include "NIRTTI.h"

#include "TES3Defines.h"
#include "TES3Reference.h"

namespace mwse {
	namespace lua {
		void bindNIPick() {
			sol::state& state = LuaManager::getInstance().getState();

			state.new_usertype<TES3::TArray<NI::PickRecord>>("NITArrayPickRecord",
				// Disable construction of this type.
				"new", sol::no_constructor,

				//
				// Meta functions.
				//

				sol::meta_function::index, [](TES3::TArray<NI::AVObject>& self, int index) { return self.storage[index - 1]; },
				sol::meta_function::length, [](TES3::TArray<NI::AVObject>& self) { return self.filledCount; }

			);

			state.new_usertype<NI::Pick>("NIPick",
				// Disable construction of this type.
				"new", sol::no_constructor,

				//
				// Properties.
				//

				"pickType", &NI::Pick::pickType,
				"sortType", &NI::Pick::sortType,
				"intersectType", &NI::Pick::intersectType,
				"coordinateType", &NI::Pick::coordinateType,
				"frontOnly", &NI::Pick::frontOnly,
				"observeAppCullFlag", &NI::Pick::observeAppCullFlag,
				"root", &NI::Pick::pickType,
				"results", sol::readonly_property(&NI::Pick::results),
				"lastAddedRecord", &NI::Pick::lastAddedRecord,
				"returnTexture", &NI::Pick::returnTexture,
				"returnNormal", &NI::Pick::returnNormal,
				"returnSmoothNormal", &NI::Pick::returnSmoothNormal,
				"returnColor", &NI::Pick::returnColor,

				//
				// Methods.
				//

				"pickObjects", &NI::Pick::pickObjects,
				"clearResults", &NI::Pick::clearResults

				);

			state.new_usertype<NI::PickRecord>("NIPickRecord",
				// Disable construction of this type.
				"new", sol::no_constructor,

				//
				// Properties.
				//

				"object", &NI::PickRecord::object,
				"parent", &NI::PickRecord::proxyParent,
				"intersection", &NI::PickRecord::intersection,
				"distance", &NI::PickRecord::distance,
				"triangleIndex", &NI::PickRecord::triangleIndex,
				"vertexIndex", sol::property([](NI::PickRecord& self) { return std::ref(self.vertexIndex); }),
				"texture", &NI::PickRecord::texture,
				"normal", &NI::PickRecord::normal,
				"color", &NI::PickRecord::color,

				// Provide quick reference to the associated object's reference.
				"reference", sol::readonly_property([](NI::PickRecord& self) { return makeLuaObject(NI::getAssociatedReference(self.object)); })

				);
		}
	}
}
