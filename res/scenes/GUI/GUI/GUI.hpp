/*
    GUI class

    That SOAB who keeps prying into other units' private life,
    and then reports back to the player

    MindRead are performed here. 
    Though you probably don't need to know that

    TODO: Nah, MindRead should not be performed here
*/

#ifndef GUI_H
#define GUI_H

#include <Godot.hpp>
#include <Control.hpp>
#include <InputEventMouse.hpp>

using namespace godot;
class SurvivalWheel;
class SurvivalBarsLeft;
class SurvivalBarsRight;
class Unit;

class GUI: public Control
{
    GODOT_CLASS(GUI, Control)
public:

    static void _register_methods();
    void _init();
    void _ready();

    // Connect this player to the GUI
    // The info shown on the GUI is what this unit is permitted to see
    void SetController(Unit* const player);

private:
    // The character which the user is controlling
    // The left survival bars are bound to this unit
    Unit* _controller;

    // TODO: Setup a MindRead cache to prevent creating too many MindRead
    // Also, create a signal to flush the cache when needed
    // (Another) Also, create a lookup table to determine which unit
    // needs to redo MindRead (when they are "attribute_modified", maybe?)

    // Child Nodes
    SurvivalWheel*     _SurvivalWheel;
    // The left survival bars are designed to be bound to _controller
    SurvivalBarsLeft*  _SurvivalBarsLeft;
    SurvivalBarsRight*  _SurvivalBarsRight;
};
#endif