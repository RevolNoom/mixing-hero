/*
    Interaction Manager class

    Defines an interface for interactions to query into the world
    for information

    Receive the input from the world and react accordingly for 
    the interaction

*/
#ifndef INTERACTION_MANAGER_HPP
#define INTERACTION_MANAGER_HPP

#include <Godot.hpp>
#include <Node.hpp>

using namespace godot;
class Unit;
class InteractionWheel;

class InteractionManager: public Node
{
    GODOT_CLASS(InteractionManager, Node)

public:
    static void _register_methods();
    void _init();
    void _ready();

    // Set newController to be the one who initiate interactions
    void SetController(Unit* const newController);

    // Class InputSequence defines the sequence of inputs needed
    // to perform the interaction
    // void AcceptInputSequence(const InputSequence* const input);

    // Feed input to the InputSequence
    // void FeedInput(const InputEvent* const event);

private:
    Unit* _controller;
    InteractionWheel* _InteractionWheel;
    // InputSequence* _InputSequence;
};

#endif