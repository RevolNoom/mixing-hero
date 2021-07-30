#ifndef ARENA_H
#define ARENA_H

#include <Godot.hpp>
#include <Node.hpp>
#include <Control.hpp>
#include <InputEventMouse.hpp>
#include <InputEventMouseButton.hpp>
#include <InputEventMouseMotion.hpp>

using namespace godot;

class GUI;
class Unit;

class Arena: public Node
{
    GODOT_CLASS(Arena, Node)
public:
    static void _register_methods();
    void _init();
    virtual void _ready();

    // Why don't I connect units directly to GUI, you ask?
    // Because, Arena supplies the unit who has been touched
    // with the information of the player's unit 
    // (implementation details: MouseEntered/Clicked accepts u as non-const
    // because unit u is affected by a mind read
    //  (yeah, i think i need to put this to GUI))

    // I don't want GUI to have any idea on 
    // why tf it needs to know any particular unit

    void UnitMouseEvent(Unit* const u, InputEventMouse* const event);
    void UnitMouseExited(const Unit* const u);

private:
    Unit* _controlledUnit;
    GUI* _GUI;
};
#endif