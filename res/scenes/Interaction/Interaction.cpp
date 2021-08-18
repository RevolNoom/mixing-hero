#include "Interaction.hpp"
#include "Unit.hpp"

void Interaction::_register_methods()
{
    // TODO: fully register all functions
    register_method("_ready", &Interaction::_ready);

    register_method("GetInfo", &Interaction::GetInfo);
    register_method("Execute", &Interaction::Execute);
    register_method("_on_Button_pressed", &Interaction::_on_Button_pressed);

    // Emits when something pressed us
    register_signal<Interaction>("picked", "Interaction", GODOT_VARIANT_TYPE_OBJECT);

    // Emits when an Interaction has gathered all input needed 
    register_signal<Interaction>("exec_ready", "Interaction", GODOT_VARIANT_TYPE_OBJECT);

    // Promote self for input 
    register_signal<Interaction>("request_input", "Interaction", GODOT_VARIANT_TYPE_OBJECT);

    // Request for additional choice. An interaction might have more than 1 options 
    register_signal<Interaction>("request_choice", "ProfileChoices", GODOT_VARIANT_TYPE_OBJECT);

    // Emitted when this signal should be exchanged into another in the InteractionWheel
    register_signal<Interaction>("change_state", "oldInteraction", GODOT_VARIANT_TYPE_OBJECT, "newInteraction", GODOT_VARIANT_TYPE_OBJECT);


}

void Interaction::_ready()
{
    _effectToSource = get_node("EffectsToSource");
    _effectToTarget = get_node("EffectsToTarget");

    // Disables all InputHoggers
    auto inputhoggers = get_node("InputHoggers")->get_children();
    for (int iii=0; iii < inputhoggers.size(); ++iii)
    {
        cast_to<InputHogger>(inputhoggers[iii])->Enable(false);
    }
    
    // Connect Signals from InputHoggers to this
}


const Profile* Interaction::GetChoices() const
{
    return get_node<Profile>("Choices");
}

// =====================================================================
// O V E R R I D E   A L L   O F   T H E   F U N C T I O N S   B E L O W
// =====================================================================


bool Interaction::Performable(Unit* const performer, Unit* const target) const
{
    return true;
}

void Interaction::Start(Unit* const performer, Unit* const target)
{
    emit_signal("exec_ready", this);
}

const Profile* Interaction::GetInfo(Unit* const performer, Unit* const target) const
{
    return get_node<Profile>("Profile");
}


void Interaction::_on_Button_pressed()
{
    emit_signal("picked", this);
}