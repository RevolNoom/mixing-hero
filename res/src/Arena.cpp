#include "Arena.hpp"
#include "Unit.hpp"
#include "AttrModify.hpp"
#include <Control.hpp>
#include "gui.hpp"
#include "GlobalConstants.hpp"

void Arena::_init(){}

void Arena::_register_methods()
{
    register_method("_ready", &Arena::_ready);
    register_method("UnitMouseEvent", &Arena::UnitMouseEvent);
    register_method("UnitMouseExited", &Arena::UnitMouseExited);

    // I have absolutely no idea what uses I have for them in the future
    // But rest assured that I won't delete 3 lines of code that took me 3 minutes to write
    //register_signal<Unit>("mouse_entered_unit", "Unit", GODOT_VARIANT_TYPE_OBJECT, "Unit", GODOT_VARIANT_TYPE_OBJECT);
    //register_signal<Unit>("mouse_exited_unit", "Unit", GODOT_VARIANT_TYPE_OBJECT);
    //register_signal<Unit>("mouse_clicked_unit", "Unit", GODOT_VARIANT_TYPE_OBJECT);
}


void Arena::_ready()
{
    Unit* u = get_node<Unit>("Unit");
    _GUI = get_node<GUI>("GUI");
    _GUI->BindPlayer(u);

    u->connect("unit_mouse_event", this, "UnitMouseEvent");
    u->connect("unit_mouse_exited", this, "UnitMouseExited");

    Unit* u2 = get_node<Unit>("Unit2");
    u2->connect("unit_mouse_event", this, "UnitMouseEvent");
    u2->connect("unit_mouse_exited", this, "UnitMouseExited");

    Damage* d = get_node<Damage>("Damage");

    u->AffectedBy(d);
}

void Arena::UnitMouseExited(const Unit* const u)
{
    _GUI->HideWheel(u);
}


// I need to come up with a new way to manage mindread
//
// TODO: Rethink about GUI design. Should it knows which unit the player controls?
// TODO: Can MindRead be reused many times to avoid creation cost?
// TODO: MindRead will also be affected by the caster's effects too. There has to be a way...

void Arena::UnitMouseEvent(Unit* const u, InputEventMouse* const event)
{
    if (cast_to<InputEventMouseMotion>(event))
        _GUI->ShowWheel(u);
    else
    {
        auto mouse_button = cast_to<InputEventMouseButton>(event);
        if (mouse_button && 
            mouse_button->get_button_index() == GlobalConstants::BUTTON_LEFT &&
            mouse_button->is_pressed())
        {
            _GUI->ShowBars(u);
        }
    }
}
