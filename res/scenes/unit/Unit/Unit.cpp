#include "Unit.hpp"
#include "BaseEffect.hpp"
#include "AttributeModify.hpp"
#include "Attribute.hpp"
#include "SurvivalWheel.hpp"

using namespace godot;
using namespace Effect;

void Unit::_init()
{
} 

void Unit::_register_methods() {
    register_method("_ready", &Unit::_ready);

    register_signal<Unit>("die", "Unit", GODOT_VARIANT_TYPE_OBJECT);
    register_signal<Unit>("attributes_modified", "Unit", GODOT_VARIANT_TYPE_OBJECT);
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
    //_doll->connect("mouse_event", this, "MouseEvent");
    //_doll->connect("mouse_exited", this, "MouseExited");

    // TODO: Let _doll delegates play() to its animation player
    AnimationPlayer *anim = _doll->get_node<AnimationPlayer>("AnimationPlayer");
    anim->play("Idle");
}