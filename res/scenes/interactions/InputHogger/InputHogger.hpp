/*
    INPUT HOGGER INTERFACE
    {Builder}

    An InputHogger continuously hogs InputEvent,
    and then decide what to do with that event for themselves.

    InputHogger emits "hogged_full" when it has accumulated 
    enough input. DO NOT MODIFY THE PROFILE IT PASSES TO YOU

    It's important to know the layout of the profile if 
    a class intends to work with an InputHogger. It is InputHogger's
    job to describe the Profile in details.

    _unhandled_input is where an InputHogger decides what to do with 
    given input. OVERRIDE IT!
*/

#ifndef INPUT_SEQUENCE_HPP
#define INPUT_SEQUENCE_HPP

#include <Godot.hpp>
#include <Node.hpp>

#include <InputEvent.hpp>

using namespace godot;

#include "Profile.hpp"

class InputHogger: public Node
{
    GODOT_CLASS(InputHogger, Node)

public:
    static void _register_methods()
    {
        register_method("_ready", &InputHogger::_ready);
        register_method("_unhandled_input", &InputHogger::_unhandled_input);

        register_method("Reset", &InputHogger::Reset);
        register_method("IsFull", &InputHogger::IsFull);
        register_signal<InputHogger>("hogged_full", "Profile", GODOT_VARIANT_TYPE_OBJECT);

    }

    // Discards everything and accept input again
    virtual void Reset() {_Profile->Wipe();}

    void _init(){}

    virtual void _ready()
    {
        _Profile=get_node<Profile>("Profile");
    }

    // Return true when it cannot accept input anymore
    // Default to false
    virtual bool IsFull() const {return false;}

    // OVERRIDE THIS
    // This is where you decide what to do with the input
    virtual void _unhandled_input(const InputEvent* const ev){}

protected:
    // Input Sequence result
    Profile* _Profile;
};
#endif