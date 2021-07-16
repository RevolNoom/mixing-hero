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
}

Attribute::Attribute()
{}
Attribute::~Attribute()
{}

void Attribute::_ready()
{
    Label *lb = get_node<Label>("Label");
    lb->set_text("AAAAAAAAAAAAAAAAAAAAAAAAA");
    godot::Godot::print("AAAAAAAAAAAAAA");
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