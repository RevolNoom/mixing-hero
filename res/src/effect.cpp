#include "effect.hpp"
#include "unit.hpp"

using namespace Effect;

void BaseEffect::_register_methods()
{
    register_property("Intensity", &BaseEffect::_intensity, 0);
    register_method("AffectOnEffect", &BaseEffect::AffectOnEffect);
    register_method("AffectOnUnit", &BaseEffect::AffectOnUnit);
    register_method("AffectedBy", &BaseEffect::AffectedBy);
}

// virtual bool IsType(Type type) const;

void BaseEffect::_init()
{}

void BaseEffect::AffectOnUnit(Unit* const u) const
{
    godot::Godot::print("A Strange Effect made the Unit feels dizzzzzzy. (This is a test message)");
}

void BaseEffect::AffectOnEffect(BaseEffect* const e) const
{
}

void BaseEffect::AffectedBy(const BaseEffect* const e)
{
    e->AffectOnEffect(this);
}

// Not yet implemented
//void AffectOnItem(Item *e);
//void AffectOnAction(Action *e);
//void AffectOnEnvironment(Environment *e);


/*
template <Unit::ATTRIBUTE ATTR_TYPE>
void Effect::Empower<ATTR_TYPE>::AffectOnUnit(Unit &u) const
{
    u.GetAttribute(ATTR_TYPE)->AddBonus(_intensity);
}

template <Unit::ATTRIBUTE ATTR_TYPE>
void Effect::Weaken<ATTR_TYPE>::AffectOnUnit(Unit &u) const
{
    u.GetAttribute(ATTR_TYPE)->AddBonus(-_intensity);
}

template <Unit::ATTRIBUTE_DYNAMIC ATTR_TYPE>
void Effect::Heal<ATTR_TYPE>::AffectOnUnit(Unit &u) const
{
    u.GetAttribute(ATTR_TYPE)->AddCurrent(_intensity);
}

template <Unit::ATTRIBUTE_DYNAMIC ATTR_TYPE>
void Effect::Damage<ATTR_TYPE>::AffectOnUnit(Unit &u) const 
{
    u.GetAttribute(ATTR_TYPE)->AddCurrent(-_intensity);
}

*/