/*
    MANAGER CLASS

    Has the responsibility to set up:
    + Player (Controller)
    + PickSurvivalBars & GUI

    Manager
    |_ GUI
    |_ InteractionManager
    |_ Units?
*/
#ifndef MANAGER_H
#define MANAGER_H

#include <Godot.hpp>
#include <Node.hpp>
#include <Control.hpp>

using namespace godot;

class GUI;
class Unit;
class InteractionManager;

class Manager: public Node
{
    GODOT_CLASS(Manager, Node)
public:
    static void _register_methods();
    void _init();
    void _ready();

    void _unhandled_input(InputEvent* const event);

    // Set this unit as controlled by the player
    // who sits before the computer screen
    // (or phone screen, if I ever export this game to android)
    void SetController(Unit* const u);

    // Do some work dirty work you probably 
    // don't want to know about
    // Just don't forget to call this when you make a new unit
    void RegisterUnit(Unit* const u);

private:
    // Currently I don't know what I'm going to do with this
    // Unit* _controller;

    GUI* _GUI;
    InteractionManager* _InteractionManager;


};
#endif