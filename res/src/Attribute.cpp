#include "Attribute.hpp"

void Attribute::_register_methods()
{
    register_property("Base", &Attribute::_base, 0);
    register_property("Bonus", &Attribute::_bonus, 0);

    register_method("_ready", &Attribute::_ready);
    register_method("AddBase", &Attribute::AddBase);
    register_method("AddBonus", &Attribute::AddBonus);
    register_method("GetBase", &Attribute::GetBase);
    register_method("GetBonus", &Attribute::GetBonus);
    register_method("GetTotal", &Attribute::GetTotal);
}

void Attribute::_init()
{
}

void Attribute::_ready()
{
    // Make sure Base is not negative
    AddBase(0);
}

void Attribute::AddBase(int add)
{
    _base += add;
    _base = _base < 0? 0 : _base;
}

void Attribute::AddBonus(int add)
{
    _bonus += add;
}

int Attribute::GetBase() const
{
    return _base;
}

int Attribute::GetBonus() const
{
    return _bonus;
}

int Attribute::GetTotal() const
{
    int total = _base + _bonus;
    return total < 0 ? 0 : total;
}


// ===================
// || D Y N A M I C ||
// ===================

void AttributeDynamic::_register_methods()
{
    register_method("_ready", &AttributeDynamic::_ready);
    register_property("Value", &AttributeDynamic::_value, 0);

    register_method("AddValue", &AttributeDynamic::AddValue);
    register_method("GetValue", &AttributeDynamic::GetValue);

    // Signal emptied when the _value measure reaches 0
    register_signal<AttributeDynamic>("emptied", "AttributeDynamic", GODOT_VARIANT_TYPE_OBJECT);
}

void AttributeDynamic::_init()
{
}

void AttributeDynamic::_ready()
{
    // Make sure Base is not negative
    AddBase(0);

    // Perform clamping between 0 and max
    AddValue(0);
}

void AttributeDynamic::AddValue(int add)
{
    
    _value += add;

    // Don't change the order of these clamps
    // The signal should be put at the bottom, 
    // when the attribute is consistent
    if (_value > GetTotal()) 
        _value = GetTotal();

    if (_value < 0) 
    {
        _value = 0;
        emit_signal("emptied", this);
    }

}

int AttributeDynamic::GetValue() const
{
    return _value;
}

int AttributeDynamic::GetMax() const
{
    return GetTotal();
}
