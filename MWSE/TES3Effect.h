#pragma once

namespace TES3 {
	enum EffectType {
		EffectNone = -1,
		EffectWaterBreathing,
		EffectSwiftSwim,
		EffectWaterWalking,
		EffectShield,
		EffectFireShield,
		EffectLightningShield,
		EffectFrostShield,
		EffectBurden,
		EffectFeather,
		EffectJump,
		EffectLevitate,
		EffectSlowFall,
		EffectLock,
		EffectOpen,
		EffectFireDamage,
		EffectShockDamage,
		EffectFrostDamage,
		EffectDrainAttribute,
		EffectDrainHealth,
		EffectDrainMagicka,
		EffectDrainFatigue,
		EffectDrainSkill,
		EffectDamageAttribute,
		EffectDamageHealth,
		EffectDamageMagicka,
		EffectDamageFatigue,
		EffectDamageSkill,
		EffectPoison,
		EffectWeaknesstoFire,
		EffectWeaknesstoFrost,
		EffectWeaknesstoShock,
		EffectWeaknesstoMagicka,
		EffectWeaknesstoCommonDisease,
		EffectWeaknesstoBlightDisease,
		EffectWeaknesstoCorprusDisease,
		EffectWeaknesstoPoison,
		EffectWeaknesstoNormalWeapons,
		EffectDisintegrateWeapon,
		EffectDisintegrateArmor,
		EffectInvisibility,
		EffectChameleon,
		EffectLight,
		EffectSanctuary,
		EffectNightEye,
		EffectCharm,
		EffectParalyze,
		EffectSilence,
		EffectBlind,
		EffectSound,
		EffectCalmHumanoid,
		EffectCalmCreature,
		EffectFrenzyHumanoid,
		EffectFrenzyCreature,
		EffectDemoralizeHumanoid,
		EffectDemoralizeCreature,
		EffectRallyHumanoid,
		EffectRallyCreature,
		EffectDispel,
		EffectSoultrap,
		EffectTelekinesis,
		EffectMark,
		EffectRecall,
		EffectDivineIntervention,
		EffectAlmsiviIntervention,
		EffectDetectAnimal,
		EffectDetectEnchantment,
		EffectDetectKey,
		EffectSpellAbsorption,
		EffectReflect,
		EffectCureCommonDisease,
		EffectCureBlightDisease,
		EffectCureCorprusDisease,
		EffectCurePoison,
		EffectCureParalyzation,
		EffectRestoreAttribute,
		EffectRestoreHealth,
		EffectRestoreMagicka,
		EffectRestoreFatigue,
		EffectRestoreSkill,
		EffectFortifyAttribute,
		EffectFortifyHealth,
		EffectFortifyMagicka,
		EffectFortifyFatigue,
		EffectFortifySkill,
		EffectFortifyMaximumMagicka,
		EffectAbsorbAttribute,
		EffectAbsorbHealth,
		EffectAbsorbMagicka,
		EffectAbsorbFatigue,
		EffectAbsorbSkill,
		EffectResistFire,
		EffectResistFrost,
		EffectResistShock,
		EffectResistMagicka,
		EffectResistCommonDisease,
		EffectResistBlightDisease,
		EffectResistCorprusDisease,
		EffectResistPoison,
		EffectResistNormalWeapons,
		EffectResistParalysis,
		EffectRemoveCurse,
		EffectTurnUndead,
		EffectSummonScamp,
		EffectSummonClannfear,
		EffectSummonDaedroth,
		EffectSummonDremora,
		EffectSummonAncestralGhost,
		EffectSummonSkeletalMinion,
		EffectSummonBonewalker,
		EffectSummonGreaterBonewalker,
		EffectSummonBonelord,
		EffectSummonWingedTwilight,
		EffectSummonHunger,
		EffectSummonGoldenSaint,
		EffectSummonFlameAtronach,
		EffectSummonFrostAtronach,
		EffectSummonStormAtronach,
		EffectFortifyAttack,
		EffectCommandCreature,
		EffectCommandHumanoid,
		EffectBoundDagger,
		EffectBoundLongsword,
		EffectBoundMace,
		EffectBoundBattleAxe,
		EffectBoundSpear,
		EffectBoundLongbow,
		EffectEXTRASPELL,
		EffectBoundCuirass,
		EffectBoundHelm,
		EffectBoundBoots,
		EffectBoundShield,
		EffectBoundGloves,
		EffectCorprus,
		EffectVampirism,
		EffectSummonCenturionSphere,
		EffectSunDamage,
		EffectStuntedMagicka,
		EffectSummonFabricant,
		EffectCallWolf,
		EffectCallBear,
		EffectSummonBonewolf,
		EffectSummonCreature04,
		EffectSummonCreature05,
		EffectFirst = EffectWaterBreathing,
		EffectLast = EffectSummonCreature05
	};

	enum EffectRange {
		EffectRangeSelf,
		EffectRangeTouch,
		EffectRangeTarget
	};

	struct Effect {
		short ID; // 0x00
		char skillID; // 0x02
		char attributeID; // 0x03
		long range; // 0x04
		long area; // 0x08
		long duration; // 0x0C
		long magnitudeMin; // 0x10
		long magnitudeMax; // 0x14
	};
	static_assert(sizeof(Effect) == 0x18, "TES3::Effect failed size validation");
}