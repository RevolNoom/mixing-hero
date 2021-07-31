#include "Unit.hpp"
#include "Effect.hpp"
#include "AttrModify.hpp"
#include "Attribute.hpp"
#include "SurvivalWheel.hpp"

using namespace godot;
using namespace Effect;

void Unit::_init()
{
} 

void Unit::_register_methods() {
    register_method("_ready", &Unit::_ready);
    register_method("MouseExited", &Unit::MouseExited);
    register_method("MouseEvent", &Unit::MouseEvent);

    register_signal<Unit>("die", "Unit", GODOT_VARIANT_TYPE_OBJECT);
    register_signal<Unit>("attributes_modified", "Unit", GODOT_VARIANT_TYPE_OBJECT);

    register_signal<Unit>("unit_mouse_event", "Unit", GODOT_VARIANT_TYPE_OBJECT, "Event", GODOT_VARIANT_TYPE_OBJECT);
    register_signal<Unit>("unit_mouse_exited", "Unit", GODOT_VARIANT_TYPE_OBJECT);
}

void Unit::AffectedBy(BaseEffect* const e) 
{
    // Go through the currently-holding effect (Effect Overtime)
    // To see whether there are damage reduction, healing boost,
    // intensity increase, etcetera... affecting this effect, you know?
    /*Node *eOT = get_node("EffectOvertime");
    auto childEffect = eOT->get_children();

    for (int iii=0; iii<childEffect.size(); ++iii)
        cast_to<EffectOvertime>(childEffect[iii]);
    */
    e->AffectOnUnit(this);
}

void Unit::_ready()
{
    _doll = get_node<Node2D>("Doll");

    // It first propagate request for info on who moved the mouse over it
    // The info supplier will then tell it what to do
    // i.e. show wheel, glow wheel, etc...
    _doll->connect("mouse_event", this, "MouseEvent");
    _doll->connect("mouse_exited", this, "MouseExited");

    // TODO: Let _doll delegates play() to its animation player
    AnimationPlayer *anim = _doll->get_node<AnimationPlayer>("AnimationPlayer");
    anim->play("Idle");
}

void Unit::MouseEvent(InputEventMouse* const event)
{
    emit_signal("unit_mouse_event", this, event);
}

void Unit::MouseExited()
{
    emit_signal("unit_mouse_exited", this);
}