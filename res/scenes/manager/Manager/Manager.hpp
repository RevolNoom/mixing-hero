/*
    MANAGER CLASS

    Has the responsibility to set up:
    + Player (Controller)
    + PickSurvivalBarsLeft & GUI

    Manager
    |_ GUI
    |_ InteractionManager
    |_ Units?
*/
#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <Godot.hpp>
#include <Node.hpp>
#include <Control.hpp>

using namespace godot;

class GUI;
class Unit;

class Manager: public Node
{
    GODOT_CLASS(Manager, Node)
public:
    static void _register_methods()
    {
        register_method("_ready", &Manager::_ready);
    }
    virtual void _init(){}
    virtual void _ready();


    // Set this unit as controlled by the player
    // who sits before the computer screen
    // (or phone screen, if I ever export this game to android)
    void SetController(Unit* const u);


private:
    // Currently I don't know what I'm going to do with this
    // Unit* _controller;

    GUI* _GUI;
};
#endif