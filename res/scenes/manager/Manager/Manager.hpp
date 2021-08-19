/*
    MANAGER CLASS

    That boss who tells the newbies what to do. 

    Manager
    |_ GUI
    |_ ManagerInteraction
    |_ ManagerUnit(?)
*/
#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <Control.hpp>
#include <Godot.hpp>
#include <Node.hpp>

using namespace godot;

class ManagerInteraction;
class Unit;
class GUI;

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
    ManagerInteraction* _ManagerInteraction;
};
#endif