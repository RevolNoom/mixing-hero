#include <Node.hpp>
#include "AttrModify.hpp"
#include "Attribute.hpp"
#include "Unit.hpp"

using namespace Effect;

/*
    D A M A G E   E F F E C T
*/
void Damage::_register_methods()
{
}

void Damage::_init()
{
}

void Damage::AffectOnUnit(Unit* const u) const
{
    auto u_attr = u->get_node("Attribute");
    auto dmg_attr = get_children();

    for (int iii=0; iii<dmg_attr.size(); ++iii)
    {
        String attr_name = cast_to<Node>(dmg_attr[iii])->get_name();
        NodePath np(attr_name);
        auto affected_attr = u_attr->get_node<AttributeDynamic>(np);
        if (affected_attr)
        {
            affected_attr->AddValue(-GetIntensity());
            godot::Godot::print(String("Ouch, that's hurt. Dealt ") + String::num_int64(GetIntensity()) + String(" damage."));
        }
        else 
        {
            godot::Godot::print_error(String("AttributeDynamic ") + attr_name + String(" not found"), "Damage::AffectOnUnit", "attr_modify.cpp", 0);
        }
    }
}


/*
    H E A L   E F F E C T
*/

void Heal::_register_methods()
{
}

void Heal::_init()
{
}

void Heal::AffectOnUnit(Unit* const u) const
{
    Node* u_attr = u->get_node("Attribute");
    auto dmg_attr = get_children();

    for (int iii=0; iii<dmg_attr.size(); ++iii)
    {
        String attr_name = cast_to<Node>(dmg_attr[iii])->get_name();
        NodePath np(attr_name);
        auto affected_attr = u_attr->get_node<AttributeDynamic>(np);
        if (affected_attr)
        {
            affected_attr->AddValue(GetIntensity());
        }
        else 
        {
            godot::Godot::print_error(String("AttributeDynamic ") + attr_name + String(" not found"), "Damage::AffectOnUnit", "attr_modify.cpp", 0);
        }
    }
}