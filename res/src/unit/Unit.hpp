#ifndef UNIT_H
#define UNIT_H

#include <KinematicBody2D.hpp>
#include <AnimationPlayer.hpp>
#include <InputEventMouse.hpp>
#include <Control.hpp>
#include <Godot.hpp>
#include <Node.hpp>


namespace Effect
{
    class BaseEffect;
}

using namespace godot;
using namespace Effect;

class Unit : public KinematicBody2D {
    GODOT_CLASS(Unit, KinematicBody2D)

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