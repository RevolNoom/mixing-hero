#include "BaseEffect.hpp"
#include "Unit.hpp"

using namespace Effect;

void BaseEffect::_register_methods()
{
    register_property("Intensity", &BaseEffect::_intensity, 0);
    register_method("GetIntensity", &BaseEffect::GetIntensity);
    register_method("AddIntensity", &BaseEffect::AddIntensity);

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

int BaseEffect::GetIntensity() const
{
    return _intensity < 0? 0 : _intensity;
}

void BaseEffect::SetIntensity(const int intensity)
{
    _intensity = intensity < 0? 0 : intensity;
}

// Add to the intensity of current effect overtime
// Can never drops below zero
void BaseEffect::AddIntensity(const int intensity)
{
    _intensity += GetIntensity() + intensity;
    if (_intensity < 0)
        _intensity = 0;
}

// Not yet implemented
//void AffectOnItem(Item *e);
//void AffectOnAction(Action *e);
//void AffectOnEnvironment(Environment *e);
