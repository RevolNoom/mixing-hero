#ifndef UNIT_H
#define UNIT_H

#include <array>
#include <memory>
#include <deque>

#include <Label.hpp>
#include <Godot.hpp>

using namespace godot;

class Unit : public Node {
    GODOT_CLASS(Unit, Node)

public:

    // UNIT METHODS
    Unit();
    ~Unit();

    // GODOT METHODS
    static void _register_methods();
    virtual void _init(); // our initializer called by Godot
    virtual void _ready();

    //virtual void AffectedBy(Effect::Effect e);

};


#endif