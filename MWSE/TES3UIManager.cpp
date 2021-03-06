#include "MemoryUtil.h"
#include "TES3UIElement.h"
#include "TES3UIManager.h"
#include "TES3UIMenuController.h"
#include "TES3Util.h"
#include "TES3WorldController.h"

namespace TES3 {
	namespace UI {
		const DWORD TES3_hook_dispatchMousewheelUp = 0x58F19B;
		const DWORD TES3_hook_dispatchMousewheelDown = 0x58F1CA;

		const auto TES3_ui_registerID = reinterpret_cast<UI_ID (__cdecl *)(const char *)>(0x58DF10);
		const auto TES3_ui_createMenu = reinterpret_cast<Element* (__cdecl *)(UI_ID)>(0x595400);
		const auto TES3_ui_findMenu = reinterpret_cast<Element* (__cdecl*)(UI_ID)>(0x595370);
		const auto TES3_ui_getPaletteColour = reinterpret_cast<Vector3& (__cdecl*)(Vector3&, Property)>(0x57F610);
		const auto TES3_ui_onMenuUnfocus = reinterpret_cast<EventCallback>(0x58F790);
		const auto TES3_ui_ScrollbarArrow_onClick = reinterpret_cast<EventCallback>(0x647A60);
		const auto TES3_ui_requestMenuModeOn = reinterpret_cast<Boolean (__cdecl*)(UI_ID)>(0x595230);
		const auto TES3_ui_requestMenuModeOff = reinterpret_cast<Boolean (__cdecl*)(UI_ID)>(0x595270);

		//
		// UI framework functions
		//

		UI_ID registerID(const char *name) {
			return TES3_ui_registerID(name);
		}

		Property registerProperty(const char *name) {
			return static_cast<Property>(TES3_ui_registerID(name));
		}

		Element* createMenu(UI_ID id) {
			return TES3_ui_createMenu(id);
		}

		Element* findMenu(UI_ID id) {
			return TES3_ui_findMenu(id);
		}

		Boolean enterMenuMode(UI_ID id) {
			return TES3_ui_requestMenuModeOn(id);
		}

		Boolean leaveMenuMode() {
			return TES3_ui_requestMenuModeOff(0);
		}

		void acquireTextInput(Element* element) {
			mwse::tes3::getWorldController()->menuController->menuInputController->acquireTextInput(element);
		}

		void preventInventoryMenuToggle(Element* menu) {
			menu->setProperty(Property::event_unfocus, TES3_ui_onMenuUnfocus);
		}

		Vector3 getPaletteColour(Property prop) {
			Vector3 colour;
			return TES3_ui_getPaletteColour(colour, prop);
		}

		//
		// Added functionality
		//

		Boolean __cdecl onScrollPaneMousewheel(Element* owningWidget, Property eventID, int data0, int data1, Element* source) {
			static auto propScrollPane = registerProperty("PartScrollPane");
			static auto propScrollPaneHor = registerProperty("PartScrollPaneHor");
			static auto propScrollPaneVert = registerProperty("PartScrollPaneVert");
			static auto propScrollbarHor = registerID("PartScrollPane_hor_scrollbar");
			static auto propScrollbarVert = registerID("PartScrollPane_vert_scrollbar");
			static auto propScrollLeftArrow = registerID("PartScrollBar_left_arrow");
			static auto propScrollRightArrow = registerID("PartScrollBar_right_arrow");

			Element* scrollbar = nullptr;
			Element* pane;
			for (pane = source; pane; pane = pane->parent) {
				Property part = pane->getProperty(PropertyType::Property, Property::is_part).propertyValue;
				if (part == propScrollPaneVert) {
					scrollbar = pane->findChild(propScrollbarVert);
					break;
				}
				else if (part == propScrollPane || part == propScrollPaneHor) {
					scrollbar = pane->findChild(propScrollbarHor);
					break;
				}
			}

			if (scrollbar) {
				// Forward event to left or right arrow depending on scroll direction in data0
				UI_ID arrowID = (data0 < 0) ? propScrollRightArrow : propScrollLeftArrow;
				Element* arrow = scrollbar->findChild(arrowID);
				return TES3_ui_ScrollbarArrow_onClick(scrollbar, eventID, data0, data1, arrow);
			}
			return 1;
		}

		//
		// UI framework improvement hooks
		//

		__declspec(naked) void patchDispatchMousewheelUp() {
			__asm {
				mov eax, [esi + 4]
				mov edx, [esi + 8]
				push ecx
				push edx
				push eax
				push 0xFFFF8036
				jmp $ + 0x37C
			}
		}
		const size_t patchDispatchMousewheelUp_size = 0x14;

		__declspec(naked) void patchDispatchMousewheelDown() {
			__asm {
				mov eax, [esi + 4]
				mov edx, [esi + 8]
				push ecx
				push edx
				push eax
				push 0xFFFF8037
				jmp $ + 0x34D
			}
		}
		const size_t patchDispatchMousewheelDown_size = 0x14;

		void hook() {
			// Patch mousewheel event dispatch to not redirect to the top-level element,
			// allowing mousewheel to apply to more than the first scrollpane in a menu
			mwse::writePatchCodeUnprotected(TES3_hook_dispatchMousewheelUp, (BYTE*)&patchDispatchMousewheelUp, patchDispatchMousewheelUp_size);
			mwse::writePatchCodeUnprotected(TES3_hook_dispatchMousewheelDown, (BYTE*)&patchDispatchMousewheelDown, patchDispatchMousewheelDown_size);

			// Patch UI layout engine to reflow wrapped text content on size changes
			auto patch = &Element::patchUpdateLayout_propagateFlow;
			mwse::genCallEnforced(0x585E1E, 0x584850, *reinterpret_cast<DWORD*>(&patch));
			mwse::genCallEnforced(0x5863AE, 0x584850, *reinterpret_cast<DWORD*>(&patch));
		}

	}
}
