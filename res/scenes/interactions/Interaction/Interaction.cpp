#include "Interaction.hpp"
#include "Profile.hpp"
#include "BaseEffect.hpp"
#include "Unit.hpp"

void Interaction::_register_methods()
{
    register_method("Perform", &Interaction::Perform);
    register_method("SourceCanPerform", &Interaction::SourceCanPerform);
    register_method("CanApplyOnTarget", &Interaction::CanApplyOnTarget);
    register_method("GetInfo", &Interaction::GetInfo);
    register_method("_ready", &Interaction::_ready);
}

void Interaction::_ready()
{
    _effectToSource = get_node("EffectsToSource");
    _effectToTarget = get_node("EffectsToTarget");

    _button = get_node<TextureButton>("Button");
}

void Interaction::_init()
{}

void Interaction::Perform(Unit* const source, Unit* const target)
{
    // Affects all kind of effects to target first
    auto ett = _effectToTarget->get_children();
    for (int iii=0; iii<ett.size(); ++iii)
    {
        target->AffectedBy(ett[iii]);
    }

    // And then move on to source's turn
    auto ets = _effectToSource->get_children();
    for (int iii=0; iii<ets.size(); ++iii)
    {
        source->AffectedBy(ets[iii]);
    }
}

bool Interaction::SourceCanPerform(Unit* const source, Unit* const target) const
{
    return true;
}

bool Interaction::CanApplyOnTarget(Unit* const source, Unit* const target) const
{
    return true;
}

const Profile* Interaction::GetInfo(const Unit* const source, const Unit* const target) const
{
    return get_node<Profile>("Profile");
}
