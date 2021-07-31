#ifndef UNIT_H
#define UNIT_H

#include <Godot.hpp>
#include <Node.hpp>
#include <Node2D.hpp>
#include <Control.hpp>
#include <AnimationPlayer.hpp>
#include <InputEventMouse.hpp>


namespace Effect
{
    class BaseEffect;
}
class SurvivalWheels;

using namespace godot;
using namespace Effect;

class Unit : public Node2D {
    GODOT_CLASS(Unit, Node2D)

public:

    // GODOT METHODS
    void _init(); 
    static void _register_methods();
    virtual void _ready();
    virtual void AffectedBy(BaseEffect* const e);


    // Signal handlers
    // This Unit does not deal with signals.
    // It delegates the works to its parents

    void MouseEvent(InputEventMouse* const ev);
    void MouseExited();
private:
    // The character we see and interact
    Node2D* _doll;
};

#endif