/*
    GUI class

    That SOAB who keeps prying into other units' private life,
    and then reports back to the player

    MindReading are performed here. 
    Though you probably don't need to know that

    TODO: Nah, MindReading should not be performed here
*/

#ifndef GUI_H
#define GUI_H

#include <Godot.hpp>
#include <Control.hpp>
#include <InputEventMouse.hpp>

using namespace godot;
class Unit;
class SurvivalBars;
class SurvivalWheel;

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

    // TODO: Let the bars update automatically when units have attributes changed
    // MindReading unit, then show an unit profile on the right bars
    // If this unit is the player (already bound to left bars),
    // then nothing new needs to be updated
    void ShowBars(Unit* const unit);

private:
    // The character which the user is controlling
    // The left survival bars are bound to this unit
    Unit* _controller;

    // The right survival bars is currently bound to this unit
    Unit* _barrist;

    // TODO: Setup a MindReading cache to prevent creating too many MindReading
    // Also, create a signal to flush the cache when needed
    // (Another) Also, create a lookup table to determine which unit
    // needs to redo MindReading (when they are "attribute_modified", maybe?)

    // Child Nodes
    SurvivalBars*  _rightBars;
    SurvivalBars*  _controllerBars;
};
#endif