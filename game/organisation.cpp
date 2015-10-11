#include "game/organisation.h"
#include "library/strings.h"

namespace OpenApoc
{

Organisation::Organisation(const OrganisationDef &def) : def(def), balance(0) {}

bool Organisation::isHostileTo(const Organisation &other) const
{
	// FIXME: Everyone is hostile!
	return (this != &other);
}

}; // namespace OpenApoc
