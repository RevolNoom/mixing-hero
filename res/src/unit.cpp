#include "unit.hpp"
#include "effect.hpp"

using namespace godot;
using namespace Effect;

void Unit::_register_methods() {
    register_method("_ready", &Unit::_ready);
    register_signal<Unit>("_die", "Unit", GODOT_VARIANT_TYPE_OBJECT);
}

void Unit::AffectedBy(BaseEffect* const e) 
{
    e->AffectOnUnit(this);
}

void Unit::_ready()
{
    AnimationPlayer *anim = get_node<AnimationPlayer>("Doll/AnimationPlayer");
    anim->play("Idle");

    BaseEffect e;
}

void Unit::_init() {

    // DO NOT ACCESS CHILD NODES
    // THEY ARE NOT CREATED AT THIS MOMENT YET
    //Label *lb = cast_to<Label>(get_node("TestMessage"));
    //lb->set_text(GetAttribute(Unit::ATTRIBUTE::HEALTH)->GetTotal());

}
