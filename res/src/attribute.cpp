#include "attribute.hpp"

void Attribute::_register_methods()
{
    register_property("Base", &Attribute::_base, 10);
    register_property("Bonus", &Attribute::_bonus, 0);

    register_method("_ready", &Attribute::_ready);
    register_method("AddBase", &Attribute::AddBase);
    register_method("AddBonus", &Attribute::AddBonus);
    register_method("GetBase", &Attribute::GetBase);
    register_method("GetBonus", &Attribute::GetBonus);
    register_method("GetTotal", &Attribute::GetTotal);
}

Attribute::Attribute()
{}
Attribute::~Attribute()
{}

void Attribute::_ready()
{
    Label *lb = get_node<Label>("Label");
    lb->set_text("BB");
    godot::Godot::print("BBBBBBBBB");
}

void Attribute::_init()
{
    _base = 10;
    _bonus = 0;
}

void Attribute::AddBase(int add)
{
    _base += add;
}

void Attribute::AddBonus(int add)
{
    _base += add;
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
    int result = _base + _bonus;
    return result < 0 ? 0 : result;
}

void AttributeDynamic::_register_methods()
{
    register_property("Current", &AttributeDynamic::_current, 10);

    register_method("_ready", &AttributeDynamic::_ready);
    register_method("AddCurrent", &AttributeDynamic::AddCurrent);
    register_method("GetCurrent", &AttributeDynamic::GetCurrent);

    // Signal emptied when the _current measure reaches 0
    register_signal<AttributeDynamic>("emptied", "AttributeDynamic", GODOT_VARIANT_TYPE_OBJECT);
}

void AttributeDynamic::_ready()
{
    Label *lb = get_node<Label>("Label");
    lb->set_text("DD");
    godot::Godot::print("DD");
}

void AttributeDynamic::_init()
{
    _base = 10;
    _bonus = 0;
    _current = 10;
}

void AttributeDynamic::AddCurrent(int add)
{
    _current += add;
    if (_current <= 0) 
    {
        _current = 0;
        emit_signal("emptied", this);
    }

    int max = GetTotal();
    if (_current > max) _current = max;
}

int AttributeDynamic::GetCurrent() const
{
    return _current < 0 ? 0 : _current;
}


AttributeDynamic::AttributeDynamic()
{}
AttributeDynamic::~AttributeDynamic()
{}