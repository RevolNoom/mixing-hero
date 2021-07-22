#ifndef INTERACTION_H
#define INTERACTION_H

#include <Godot.hpp>
#include <Node.hpp>

using namespace godot;
class Unit;

class Interaction: public Node
{
    GODOT_CLASS(Interaction, Node)
    public:
    static void _register_methods();
    void _init();

    virtual bool CanBePerformedBy(const Unit* const u) const;
    virtual bool CanPerformOn(const Unit* const o) const;
    virtual bool CalculateCost(const Unit* const u) const;
    virtual bool Perform(Unit* const source, Unit* const target);
};

#endif