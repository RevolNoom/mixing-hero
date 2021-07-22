#include "interaction.hpp"
#include "unit.hpp"

void Interaction::_register_methods()
{
    register_method("CanBePerformedBy", &Interaction::CanBePerformedBy);
    register_method("CanPerformOn", &Interaction::CanPerformOn);
    register_method("CalculateCost", &Interaction::CalculateCost);
    register_method("Perform", &Interaction::Perform);
}

void Interaction::_init()
{}

bool Interaction::CanBePerformedBy(const Unit* const u) const
{
    return false;
}

bool Interaction::CanPerformOn(const Unit* const u) const
{
    return false;
}

bool Interaction::CalculateCost(const Unit* const u) const
{
    return false;
}

bool Interaction::Perform(Unit* const source, Unit* const target)
{
    return false;
}