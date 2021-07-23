#include "attr_modify.hpp"

using namespace Effect;

/*
    D A M A G E   E F F E C T
*/
void Damage::_register_methods()
{
    register_property("AffectedAttribute", &Damage::_affectedAttrName, String("Health"));
}

void Damage::_init()
{
    _affectedAttrName = "Health";
}

String Damage::GetAffectedAttributeName() const
{
    return _affectedAttrName;
}

void Damage::AffectOnUnit(Unit* const u) const
{
    // There's an internal gcc compiler error 
    // when I shove the whole string into get_node
    // AttributeDynamic *attr = u->get_node<AttributeDynamic>("Attribute/" + GetAffectedAttributeName());
    // Something about "real"? Anyway... here's the workaround
    String str = "Attribute/";
    str += GetAffectedAttributeName();
    NodePath np(str);
    AttributeDynamic *attr = u->get_node<AttributeDynamic>(np);

    if (attr)
    {
        attr->AddCurrent(-GetIntensity());
        godot::Godot::print(String("Ouch, that's hurt. Dealt ") + String::num_int64(GetIntensity()) + String(" damage."));
    }
    else 
    {
        godot::Godot::print_error(String("AttributeDynamic ") + GetAffectedAttributeName() + String(" not found"), "Damage::AffectOnUnit", "attr_modify.cpp", 0);
    }

    u->emit_signal("attributes_modified", u);
}



/*
    H E A L   E F F E C T
*/

void Heal::_register_methods()
{
}

void Heal::AffectOnUnit(Unit* const u) const
{
    String str = "Attribute/";
    str += GetAffectedAttributeName();
    NodePath np(str);
    AttributeDynamic *attr = u->get_node<AttributeDynamic>(np);

    if (attr)
    {
        attr->AddCurrent(GetIntensity());
        godot::Godot::print("It feels pleasant...");
    }
    else 
    {
        godot::Godot::print_error(String("AttributeDynamic ") + GetAffectedAttributeName() + String(" not found"), "Heal::AffectOnUnit", "attr_modify.cpp", 0);
    }

    u->emit_signal("attributes_modified");
}