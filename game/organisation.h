#pragma once

#include "game/rules/organisationdef.h"

namespace OpenApoc
{

class Organisation
{
  public:
	const OrganisationDef &def;
	int balance;

	Organisation(const OrganisationDef &def);
	bool isHostileTo(const Organisation &other) const;
};

}; // namespace OpenApoc
