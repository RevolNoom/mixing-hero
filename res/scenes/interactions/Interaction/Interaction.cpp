#include "InputHogger.hpp"
#include "Interaction.hpp"
#include "BaseEffect.hpp"
#include "Profile.hpp"
#include "Unit.hpp"

void Interaction::_register_methods()
{
    register_method("_ready", &Interaction::_ready);
    register_method("GetInfo", &Interaction::GetInfo);
    register_method("Execute", &Interaction::Execute);
    register_method("ReadyToExecute", &Interaction::ReadyToExecute);
    register_method("SourceCanPerform", &Interaction::SourceCanPerform);
    register_method("CanApplyOnTarget", &Interaction::CanApplyOnTarget);
    register_method("_on_Button_pressed", &Interaction::_on_Button_pressed);

    register_signal<Interaction>("picked", "Interaction", GODOT_VARIANT_TYPE_OBJECT);
    register_signal<Interaction>("ready_to_execute", "Interaction", GODOT_VARIANT_TYPE_OBJECT);
}

void Interaction::_ready()
{
    _effectToSource = get_node("EffectsToSource");
    _effectToTarget = get_node("EffectsToTarget");
    _InputHogger = get_node<InputHogger>("InputHogger");

    _InputHogger->connect("hogged_full", this, "ReadyToExecute");
    //_button = get_node<TextureButton>("Button");
}

void Interaction::_init()
{}

void Interaction::Execute(Unit* const source)
{
    _InputHogger->Reset();
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


void Interaction::ReadyToExecute(InputHogger* const InputHogger)
{
    emit_signal("ready_to_execute", this);
}

void Interaction::_on_Button_pressed()
{
    godot::Godot::print("Aughhh I can't breeeeeathe");
    emit_signal("picked", this);
}