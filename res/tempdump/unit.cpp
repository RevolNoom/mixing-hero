#include "unit.hpp"

using namespace godot;

void Unit::_register_methods() {
    register_method("_ready", &Unit::_ready);
}

Unit::Unit() {
}

Unit::~Unit() {
    // add your cleanup here
}
/*
void Unit::AffectedBy(Effect::Effect e) 
{
    e.AffectOnUnit(*this);
}
*/

void Unit::_ready()
{
    //AffectedBy(Effect::Damage<Unit::ATTRIBUTE_DYNAMIC::HEALTH>(50));
    //AffectedBy(Effect::Effect(50));
    Label *lb = get_node<Label>("TestMessage");
    Node *health = get_node("Attribute/Health");
    String hp = health->get("Base");
    lb->set_text(hp);
}

void Unit::_init() {

    // DO NOT ACCESS CHILD NODES
    // THEY ARE NOT CREATED AT THIS MOMENT YET
    //Label *lb = cast_to<Label>(get_node("TestMessage"));
    //lb->set_text(GetAttribute(Unit::ATTRIBUTE::HEALTH)->GetTotal());

}
