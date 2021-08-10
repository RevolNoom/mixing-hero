/*
    INPUT SEQUENCE INTERFACE
    {Builder?}

    This interface encapsulate the routines needed to perform an interaction.

    An InputSequence continuously get input event from InteractionManager,
    and then decide what to do with that event for themselves.

    For example:
        An Input Sequence to pick an Unit 
        will look out for an InputEventMouseButton, 
        and then perform raycast to get the unit clicked by the player

        An Input Sequence that pick a position on the world will
        get position clicked by the player, and return it to the caller.

    When the InputSequence is satisfied with the information it gets,
    it will emit signal "sequence_completed". You will get the infos
    it accumulated in a Profile. This Profile should be passed to 
    the appropriate Interaction. 

    Again, it's important for an InputSequence and Interaction to
    handshakes on what class types and information is kept in the 
    Profile. Each InputSequence must describe precisely what to
    expect in each Profile:
    + What nodes are there in the Profile?
    + What are each node's type?
    + What are each node's name?
*/

#ifndef INPUT_SEQUENCE_HPP
#define INPUT_SEQUENCE_HPP

#include <Godot.hpp>
#include <Node.hpp>

#include <InputEvent.hpp>

using namespace godot;
class Profile;
class Unit;

class InputSequence: public Node
{
    GODOT_CLASS(InputSequence, Node)

public:
    static void _register_methods();
    void _init();
    void _ready();

    // Abstract method. 
    // Override this. Tell your InputSequence 
    // what it must do with this InputEvent
    // Do nothing by default because Godot can't handle 
    // pure virtual functions
    virtual void Accept(const InputEvent* const event, Unit* const performer);

    const Profile* GetProfile() const;

protected:
    // Input Sequence result
    Profile* _Profile;
};
#endif