#include "game/rules/rules_private.h"
#include "game/rules/rules_helper.h"

namespace OpenApoc
{

static bool
ParseVehicleWeaponDefinition(WeaponDef &def, tinyxml2::XMLElement *root)
{
	//FIXME: A lot of these could be shared for all weapon types?

	if (!root->Attribute("projectile"))
	{
		LogWarning("No 'projectile' attribute");
		return false;
	}
	UString projectile = root->Attribute("projectile");
	if (projectile == "beam")
	{
		def.projectileType = WeaponDef::ProjectileType::Beam;
	}
	else
	{
		LogWarning("Unknown projectile type \"%s\"", projectile.str().c_str());
		return false;
	}

	/* firingSFX is optional */
	def.firingSFX = root->Attribute("firingSFX");

	/* pointDefence is optional */
	ReadAttribute(root, "pointDefence", def.pointDefence, false);

	/* arc is optional */
	ReadAttribute(root, "arc", def.arc, 0.0f);

	/* accuracy is optional */
	ReadAttribute(root, "accuracy", def.accuracy, 0.0f);

	/* range is required */
	if (!ReadAttribute(root, "range", def.range))
	{
		LogWarning("Failed to read 'range' attribute");
		return false;
	}

	/* firingDelay is required */
	if (!ReadAttribute(root, "firingDelay", def.firingDelay))
	{
		LogWarning("Failed to read 'firingDelay' attribute");
		return false;
	}

	/* projectileDamage is required */
	if (!ReadAttribute(root, "projectileDamage", def.projectileDamage))
	{
		LogWarning("Failed to read 'projectileDamage' attribute");
		return false;
	}

	/* projetileTailLength is optional */
	ReadAttribute(root, "projectileTailLength", def.projectileTailLength, 0.0f);

	/* projectileSpeed is required */
	if (!ReadAttribute(root, "projectileSpeed", def.projectileSpeed))
	{
		LogWarning("Failed to read 'projectileSpeed' attribute");
		return false;
	}

	/* projectileTurnRate is optional */
	ReadAttribute(root, "projectileTurnRate", def.projectileTurnRate, 0.0f);

	/* hitSprite is optional */
	def.hitSprite = root->Attribute("hitSprite");

	/* beamWidth is optional */
	ReadAttribute(root, "beamWidth", def.beamWidth, 1.0f);

	/* beamColour is optional */
	ReadAttribute(root, "beamColour", def.beamColour, {255,255,255,255});

	/* ammoCapacity is required */
	if (!ReadAttribute(root, "ammoCapacity", def.ammoCapacity))
	{
		LogWarning("Failed to read 'ammoCapacity' attribute");
		return false;
	}

	/* ammoPerShot is optional */
	ReadAttribute(root, "ammoPerShot", def.ammoPerShot, 1);

	def.ammoType = root->Attribute("ammoType");

	return true;
}

bool
RulesLoader::ParseWeaponDefinition(Framework &fw, Rules &rules, tinyxml2::XMLElement *root)
{
	std::ignore = fw;
	if (UString(root->Name()) != "weapon")
	{
		LogError("Called on unexpected node \"%s\"", root->Name());
		return false;
	}

	WeaponDef def;

	if (!root->Attribute("name"))
	{
		LogError("No 'name' attribute");
		return false;
	}
	def.name = root->Attribute("name");

	if (!root->Attribute("type"))
	{
		LogError("No 'type' attribute");
		return false;
	}

	UString type = root->Attribute("type");
	if (type == "vehicle")
	{
		def.type = WeaponDef::Type::Vehicle;
		if (!ParseVehicleWeaponDefinition(def, root))
		{
			LogError("Failed to load weapon \"%s\"", def.name.str().c_str());
			return false;
		}
	}
	else
	{
		LogError("Unknown weapon type \"%s\"", type.str().c_str());
		return false;
	}

	LogInfo("Loading weapon \"%s\"", def.name.str().c_str());

	rules.weapons.emplace(def.name, def);

	return true;
}
}; //namespace OpenApoc
