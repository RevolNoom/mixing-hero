/*
    Interaction Manager class

    That awesome class who handles ALL (All? all.) of your input,
    from keyboard to mouse movement to mouse click etc. etc.

    Actually, it's here as a representative. 
    The actual works are delegated to its InputSequence children

    So what do you do with this class? Well, each input sequence does
    different thing based on the input it wants. So, you can create more
    functionalities to your mouse clicks, mouse movement, keyboard
    strokes,... anything, by adding an InputSequence to this InteractionManager.

    Node InteractionManager
    |_ PickSurvivalWheel 
    |_ InputSequence 1
    |_ InputSequence 2
    |_ InputSequence 3
    |_ ...
*/
#ifndef INTERACTION_MANAGER_HPP
#define INTERACTION_MANAGER_HPP

#include <Godot.hpp>
#include <Node.hpp>

using namespace godot;
class Unit;
class InteractionWheel;
class PickSurvivalWheel;

class InteractionManager: public Node
{
    GODOT_CLASS(InteractionManager, Node)

public:
    static void _register_methods();
    void _init();
    void _ready();

    // Set newController to be the one who initiate interactions
    void SetController(Unit* const newController);

    // Duplicate this InputSequence as a child
    // void AcceptInputSequence(const InputSequence* const input);

    // Feed input to all InputSequence, hoping for some miracle to happen 
    void FeedInput(const InputEvent* const event);

private:
    // This unit is the source of all interaction 
    // (probably the Player)
    Unit* _controller;

    // Mouse Event Handler for SurvivalWheel
    // This one needs info on Performer
    PickSurvivalWheel* _PickSurvivalWheel;
};

#endif