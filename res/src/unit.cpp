#include "unit.hpp"
#include "effect.hpp"
#include "attr_modify.hpp"

using namespace godot;
using namespace Effect;

void Unit::_register_methods() {
    register_method("_ready", &Unit::_ready);
    register_signal<Unit>("die", "Unit", GODOT_VARIANT_TYPE_OBJECT);
}

void Unit::AffectedBy(BaseEffect* const e) 
{
    // Go through the currently-holding effect (Effect Overtime)
    // To see whether there are damage reduction, healing boost,
    // intensity increase, etcetera... affecting this effect, you know?
    Node *eOT = get_node("EffectOvertime");
    auto childEffect = eOT->get_children();

    for (int iii=0; iii<childEffect.size(); ++iii)
        cast_to<EffectOvertime>(childEffect[iii]);

    e->AffectOnUnit(this);
}

void Unit::_ready()
{
    _doll = get_node<Node2D>("Doll");
    _survivalBars = get_node<SurvivalBars>("SurvivalBars");

    // Show the survival bars when player hover mouse on the doll
    _doll->connect("mouse_entered", _survivalBars, "Show");
    _doll->connect("mouse_exited", _survivalBars, "Hide");

    // TODO: Let _doll delegates play() to its animation player
    AnimationPlayer *anim = _doll->get_node<AnimationPlayer>("AnimationPlayer");
    anim->play("Idle");
}

void Unit::_init() {
}
