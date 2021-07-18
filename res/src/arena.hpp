#ifndef ARENA_H
#define ARENA_H

#include <Godot.hpp>
#include <Node.hpp>

using namespace godot;

class Arena: public Node
{
    GODOT_CLASS(Arena, Node)
    public:
    static void _register_methods();
    virtual void _init();
    virtual void _ready();
};
#endif