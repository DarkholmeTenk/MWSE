#pragma once

#include "TES3MobileObjectLua.h"

#include "TES3ActorAnimationData.h"
#include "TES3Cell.h"

namespace mwse {
	namespace lua {
		template <typename T>
		void setUserdataForMobileActor(sol::simple_usertype<T>& usertypeDefinition) {
			setUserdataForMobileObject(usertypeDefinition);

			// Basic property binding.
			usertypeDefinition.set("actionBeforeCombat", sol::readonly_property(&TES3::MobileActor::actionBeforeCombat));
			usertypeDefinition.set("actionData", sol::readonly_property(&TES3::MobileActor::actionData));
			usertypeDefinition.set("activeMagicEffectCount", sol::readonly_property(&TES3::MobileActor::activeMagicEffectCount));
			//usertypeDefinition.set("activeMagicEffects", sol::readonly_property(&TES3::MobileActor::activeMagicEffects));
			usertypeDefinition.set("actorType", sol::readonly_property(&TES3::MobileActor::actorType));
			usertypeDefinition.set("alarm", &TES3::MobileActor::alarm);
			usertypeDefinition.set("barterGold", &TES3::MobileActor::barterGold);
			usertypeDefinition.set("collidingReference", sol::readonly_property(&TES3::MobileActor::collidingReference));
			usertypeDefinition.set("corpseHourstamp", &TES3::MobileActor::corpseHourstamp);
			usertypeDefinition.set("currentEnchantedItem", sol::readonly_property(&TES3::MobileActor::currentEnchantedItem));
			usertypeDefinition.set("currentSpell", &TES3::MobileActor::currentSpell);
			usertypeDefinition.set("encumbrance", sol::readonly_property(&TES3::MobileActor::encumbrance));
			usertypeDefinition.set("fatigue", sol::readonly_property(&TES3::MobileActor::fatigue));
			usertypeDefinition.set("fight", &TES3::MobileActor::fight);
			usertypeDefinition.set("flee", &TES3::MobileActor::flee);
			usertypeDefinition.set("friendlyActors", sol::readonly_property(&TES3::MobileActor::listFriendlyActors));
			usertypeDefinition.set("greetDuration", &TES3::MobileActor::greetDuration);
			usertypeDefinition.set("greetTimer", sol::readonly_property(&TES3::MobileActor::greetTimer));
			usertypeDefinition.set("health", sol::readonly_property(&TES3::MobileActor::health));
			usertypeDefinition.set("hello", &TES3::MobileActor::hello);
			usertypeDefinition.set("holdBreathTime", &TES3::MobileActor::holdBreathTime);
			usertypeDefinition.set("hostileActors", sol::readonly_property(&TES3::MobileActor::listTargetActors));
			usertypeDefinition.set("lastGroundZ", &TES3::MobileActor::lastGroundZ);
			usertypeDefinition.set("magicka", sol::readonly_property(&TES3::MobileActor::magicka));
			usertypeDefinition.set("magickaMultiplier", sol::readonly_property(&TES3::MobileActor::magickaMultiplier));
			usertypeDefinition.set("nextActionWeight", sol::readonly_property(&TES3::MobileActor::nextActionWeight));
			//usertypeDefinition.set("powers", sol::readonly_property(&TES3::MobileActor::powers));
			usertypeDefinition.set("readiedAmmo", &TES3::MobileActor::readiedAmmo);
			usertypeDefinition.set("readiedAmmoCount", sol::readonly_property(&TES3::MobileActor::readiedAmmoCount));
			usertypeDefinition.set("readiedShield", &TES3::MobileActor::readiedShield);
			usertypeDefinition.set("readiedWeapon", &TES3::MobileActor::readiedWeapon);
			usertypeDefinition.set("scanInterval", sol::readonly_property(&TES3::MobileActor::scanInterval));
			usertypeDefinition.set("scanTimer", sol::readonly_property(&TES3::MobileActor::scanTimer));
			usertypeDefinition.set("torchSlot", &TES3::MobileActor::torchSlot);
			usertypeDefinition.set("width", sol::readonly_property(&TES3::MobileActor::widthInUnits));

			// Indirect bindings to unions and arrays.
			usertypeDefinition.set("animationData", sol::readonly_property([](TES3::MobileActor& self) { return self.animationData.asActor; }));
			usertypeDefinition.set("attributes", sol::readonly_property([](TES3::MobileActor& self) { return std::ref(self.attributes); }));
			usertypeDefinition.set("effectAttributes", sol::readonly_property([](TES3::MobileActor& self) { return std::ref(self.effectAttributes); }));

			// Friendly access to actor flags.
			usertypeDefinition.set("activeAI", sol::property(
				[](TES3::MobileActor& self) { return self.getMobileActorFlag(TES3::MobileActorFlag::ActiveAI); },
				[](TES3::MobileActor& self, bool set) { self.setMobileActorFlag(TES3::MobileActorFlag::ActiveAI, set); }
			));
			usertypeDefinition.set("attacked", sol::property([](TES3::MobileActor& self) { return self.getMobileActorFlag(TES3::MobileActorFlag::Attacked); }));
			usertypeDefinition.set("idleAnim", sol::property([](TES3::MobileActor& self) { return self.getMobileActorFlag(TES3::MobileActorFlag::IdleAnim); }));
			usertypeDefinition.set("inCombat", sol::property([](TES3::MobileActor& self) { return self.getMobileActorFlag(TES3::MobileActorFlag::InCombat); }));
			usertypeDefinition.set("isCrittable", sol::property([](TES3::MobileActor& self) { return self.getMobileActorFlag(TES3::MobileActorFlag::IsCrittable); }));
			usertypeDefinition.set("spellReadied", sol::property([](TES3::MobileActor& self) { return self.getMobileActorFlag(TES3::MobileActorFlag::SpellReadied); }));
			usertypeDefinition.set("underwater", sol::property([](TES3::MobileActor& self) { return self.getMobileActorFlag(TES3::MobileActorFlag::Underwater); }));
			usertypeDefinition.set("weaponDrawn", sol::property([](TES3::MobileActor& self) { return self.getMobileActorFlag(TES3::MobileActorFlag::WeaponDrawn); }));
			usertypeDefinition.set("werewolf", sol::property([](TES3::MobileActor& self) { return self.getMobileActorFlag(TES3::MobileActorFlag::Werewolf); }));

			// Provide some friendly exposure to attributes by name.
			usertypeDefinition.set("agility", sol::readonly_property([](TES3::MobileActor& self) { return &self.attributes[TES3::Attribute::Agility]; }));
			usertypeDefinition.set("endurance", sol::readonly_property([](TES3::MobileActor& self) { return &self.attributes[TES3::Attribute::Endurance]; }));
			usertypeDefinition.set("intelligence", sol::readonly_property([](TES3::MobileActor& self) { return &self.attributes[TES3::Attribute::Intelligence]; }));
			usertypeDefinition.set("luck", sol::readonly_property([](TES3::MobileActor& self) { return &self.attributes[TES3::Attribute::Luck]; }));
			usertypeDefinition.set("personality", sol::readonly_property([](TES3::MobileActor& self) { return &self.attributes[TES3::Attribute::Personality]; }));
			usertypeDefinition.set("speed", sol::readonly_property([](TES3::MobileActor& self) { return &self.attributes[TES3::Attribute::Speed]; }));
			usertypeDefinition.set("strength", sol::readonly_property([](TES3::MobileActor& self) { return &self.attributes[TES3::Attribute::Strength]; }));
			usertypeDefinition.set("willpower", sol::readonly_property([](TES3::MobileActor& self) { return &self.attributes[TES3::Attribute::Willpower]; }));

			// Provide some friendly exposure to effect attributes.
			usertypeDefinition.set("attackBonus", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::AttackBonus]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::AttackBonus] = value; }
			));
			usertypeDefinition.set("blind", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Blind]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Blind] = value; }
			));
			usertypeDefinition.set("chameleon", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Chameleon]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Chameleon] = value; }
			));
			usertypeDefinition.set("invisibility", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Invisibility]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Invisibility] = value; }
			));
			usertypeDefinition.set("jump", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Jump]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Jump] = value; }
			));
			usertypeDefinition.set("levitate", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Levitate]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Levitate] = value; }
			));
			usertypeDefinition.set("paralyze", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Paralyze]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Paralyze] = value; }
			));
			usertypeDefinition.set("resistBlightDisease", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistBlightDisease]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistBlightDisease] = value; }
			));
			usertypeDefinition.set("resistCommonDisease", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistCommonDisease]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistCommonDisease] = value; }
			));
			usertypeDefinition.set("resistCorprus", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistCorprus]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistCorprus] = value; }
			));
			usertypeDefinition.set("resistFire", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistFire]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistFire] = value; }
			));
			usertypeDefinition.set("resistFrost", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistFrost]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistFrost] = value; }
			));
			usertypeDefinition.set("resistMagicka", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistMagicka]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistMagicka] = value; }
			));
			usertypeDefinition.set("resistNormalWeapons", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistNormalWeapons]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistNormalWeapons] = value; }
			));
			usertypeDefinition.set("resistParalysis", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistParalysis]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistParalysis] = value; }
			));
			usertypeDefinition.set("resistPoison", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistPoison]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistPoison] = value; }
			));
			usertypeDefinition.set("resistShock", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::ResistShock]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::ResistShock] = value; }
			));
			usertypeDefinition.set("sanctuary", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Sanctuary]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Sanctuary] = value; }
			));
			usertypeDefinition.set("shield", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Shield]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Shield] = value; }
			));
			usertypeDefinition.set("silence", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Silence]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Silence] = value; }
			));
			usertypeDefinition.set("sound", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::Sound]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::Sound] = value; }
			));
			usertypeDefinition.set("swiftSwim", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::SwiftSwim]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::SwiftSwim] = value; }
			));
			usertypeDefinition.set("waterBreathing", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::WaterBreathing]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::WaterBreathing] = value; }
			));
			usertypeDefinition.set("waterWalking", sol::property(
				[](TES3::MobileActor& self) { return self.effectAttributes[TES3::EffectAttribute::WaterWalking]; },
				[](TES3::MobileActor& self, int value) { self.effectAttributes[TES3::EffectAttribute::WaterWalking] = value; }
			));

			// Provide some friendly exposure for movement flags.
			usertypeDefinition.set("isFlying", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Flying) != 0; }));
			usertypeDefinition.set("isJumping", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Jumping) != 0; }));
			usertypeDefinition.set("isMovingBack", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Back) != 0; }));
			usertypeDefinition.set("isMovingForward", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Forward) != 0; }));
			usertypeDefinition.set("isMovingLeft", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Left) != 0; }));
			usertypeDefinition.set("isMovingRight", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Right) != 0; }));
			usertypeDefinition.set("isRunning", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Running) != 0; }));
			usertypeDefinition.set("isSneaking", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Sneaking) != 0; }));
			usertypeDefinition.set("isStartingJump", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Jumped) != 0; }));
			usertypeDefinition.set("isSwimming", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Swimming) != 0; }));
			usertypeDefinition.set("isTurningLeft", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::TurnLeft) != 0; }));
			usertypeDefinition.set("isTurningRight", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::TurnRight) != 0; }));
			usertypeDefinition.set("isWalking", sol::readonly_property([](TES3::MobileActor& self) { return (self.movementFlags & TES3::ActorMovement::Walking) != 0; }));

			// Basic function binding.
			usertypeDefinition.set("applyHealthDamage", &TES3::MobileActor::applyHealthDamage);
			usertypeDefinition.set("getSkillStatistic", &TES3::MobileActor::getSkillStatistic);
			usertypeDefinition.set("getSkillValue", &TES3::MobileActor::getSkillValue);
			usertypeDefinition.set("startCombat", &TES3::MobileActor::startCombat);
			usertypeDefinition.set("stopCombat", &TES3::MobileActor::stopCombat);

			// Functions exposed as properties.
			usertypeDefinition.set("cell", sol::property(&TES3::MobileActor::getCell));
			usertypeDefinition.set("hasFreeAction", sol::property(&TES3::MobileActor::hasFreeAction));
		}
	}
}
