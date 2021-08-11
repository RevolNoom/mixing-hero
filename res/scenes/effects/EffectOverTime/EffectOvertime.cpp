#include "EffectOvertime.hpp"

using namespace Effect;

void EffectOvertime::_register_methods()
{
    register_property("Potency", &EffectOvertime::_potency, 0);
    register_method("GetPotency", &EffectOvertime::GetPotency);
    register_method("AddPotency", &EffectOvertime::AddPotency);
}
void EffectOvertime::_init()
{
    if (_potency < 0)
        _potency = 0;
}

void EffectOvertime::AffectedBy(const BaseEffect* const e){}

// bool IsType(Type type) const;
void EffectOvertime::AffectOnUnit(Unit* const u) const
{}
void EffectOvertime::AffectOnEffect(BaseEffect* const e) const
{}

// Not yet implemented
//void AffectOnItem(Item *e);
//void AffectOnAction(Action *e);
//void AffectOnEnvironment(Environment *e);

// Returns the potency of current effect overtime
// Is never less than zero
int EffectOvertime::GetPotency() const
{
    return _potency < 0? 0 : _potency;
}

// Add to the potency of current effect overtime
// Can never drops below zero
void EffectOvertime::AddPotency(const int potency)
{
    _potency += GetPotency() + potency;
    if (_potency < 0)
        _potency = 0;
}