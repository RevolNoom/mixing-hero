#include <Node.hpp>
#include "AttributeModify.hpp"
#include "Attribute.hpp"
#include "Unit.hpp"

using namespace Effect;

/*
    H E A L   E F F E C T
*/

void Heal::_register_methods()
{
}

void Heal::_init()
{
}

void Heal::ModifyAttribute(AttributeDynamic* const affectedAttribute) const 
{
    affectedAttribute->AddValue(GetIntensity());
}

void Heal::AffectOnUnit(Unit* const u) const
{
    Node* u_attr = u->get_node("Attribute");
    auto dmg_attr = get_children();

    for (int iii=0; iii<dmg_attr.size(); ++iii)
    {
        String attr_name = cast_to<Node>(dmg_attr[iii])->get_name();
        NodePath np(attr_name);
        auto affectedAttribute = u_attr->get_node<AttributeDynamic>(np);
        if (affectedAttribute)
        {
            ModifyAttribute(affectedAttribute);
            u->emit_signal("attributes_modified", u);
        }
        else 
        {
            godot::Godot::print(String("AttributeDynamic ") + attr_name + String(" not found"));
        }
    }
}

/*
    D A M A G E   E F F E C T
*/
void Damage::_register_methods()
{
}

void Damage::_init()
{
}

void Damage::ModifyAttribute(AttributeDynamic* const affectedAttribute) const 
{
    affectedAttribute->AddValue(-GetIntensity());
}