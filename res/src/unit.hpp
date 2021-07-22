#ifndef UNIT_H
#define UNIT_H

#include <Godot.hpp>
#include <Node.hpp>
#include <Node2D.hpp>
#include <Control.hpp>
#include <AnimationPlayer.hpp>

#include "survival_bars.hpp"

namespace Effect
{
    class BaseEffect;
}

using namespace godot;
using namespace Effect;

class Unit : public Node2D {
    GODOT_CLASS(Unit, Node2D)

public:

    // GODOT METHODS
    static void _register_methods();
    virtual void _init(); // our initializer called by Godot
    virtual void _ready();
    virtual void AffectedBy(BaseEffect* const e);

private:
    // The character we see and interact
    Node2D* _doll;

    // The bars representing survival stats
    SurvivalBars* _survivalBars;
};

#endif