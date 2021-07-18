#include "arena.hpp"
#include "unit.hpp"
#include "attr_modify.hpp"

void Arena::_register_methods()
{
    register_method("_ready", &Arena::_ready);
}

void Arena::_init()
{
}

void Arena::_ready()
{
    Unit* u = get_node<Unit>("Unit");
    Damage* d = get_node<Damage>("Damage");
    Heal* h = get_node<Heal>("Heal");

    u->AffectedBy(d);
    u->AffectedBy(h);
}