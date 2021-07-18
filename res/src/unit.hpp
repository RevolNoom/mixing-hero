#ifndef UNIT_H
#define UNIT_H

#include <Godot.hpp>
#include <Node.hpp>
#include <AnimationPlayer.hpp>

#include <attribute.hpp>

namespace Effect
{
    class BaseEffect;
}

using namespace godot;
using namespace Effect;

class Unit : public Node {
    GODOT_CLASS(Unit, Node)

public:

    // GODOT METHODS
    static void _register_methods();
    virtual void _init(); // our initializer called by Godot
    virtual void _ready();
    virtual void AffectedBy(BaseEffect* const e);
};

#endif