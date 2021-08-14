/*
    Click'S FAMILY

    A Click deals with mouse action, whether it be mouse click
    or mouse motion.

    When the mouse moved/clicked something of interest, the Click
    builds its profile. It signals "hogged_full"
*/

#ifndef PICK_HPP
#define PICK_HPP

#include <InputEventMouseButton.hpp>
#include <InputEventMouseMotion.hpp>
#include <GlobalConstants.hpp>
#include <Position2D.hpp>
#include <RayCast2D.hpp>
#include <Label.hpp>

#include "InputHogger.hpp"
class Unit;

// THIS CLASS SERVES AS AN ABSTRACT cLASS
// IT'S NOT INTENDED TO BE INSTANTIATED
class Click: public InputHogger
{
    GODOT_CLASS(Click, InputHogger)

public:
    static void _register_methods()
    {
        register_method("SetPickAmount", &Click::SetPickAmount);
        register_property("PickAmount", &Click::_PickAmount, 0);
    }

    void _init(){}

    virtual void _ready()
    {
        _Profile= get_node<Profile>("Profile");
        _RayCast2D = get_node<RayCast2D>("RayCast2D");
        _RayCast2D->set_enabled(false);
    }

    // Reset() and set PickAmount
    // Note: PickAmount value will not be less than 0
    // Set PickAmount = 0 equals to disabling this Click 
    void SetPickAmount(int PickAmount)    
    {
        Reset();
        _PickAmount = PickAmount < 0? 0 : PickAmount;
    }

    virtual bool IsFull() const { return _Profile->get_child_count() == _PickAmount; }

protected:

    // The RayCast used to pick object
    RayCast2D* _RayCast2D;

    // The amount of objects needed picking
    int _PickAmount;
};


/*
    An InputHogger specialized in picking clicked positions

    When you click somewhere on the screen, the position you click
    is stored in a Node2D, and then appended to a Profile

	Profile
    |_ Node2D 0 
    |_ Node2D 1 
    |_ Node2D 2 
    |_ ...
*/
class ClickPosition: public Click
{
    GODOT_CLASS(ClickPosition, Click)

public:
    static void _register_methods(){}
    void _init(){}
    void _unhandled_input(const InputEvent* const ev);
};

/*
    An InputHogger specialized in picking clicked Units

    When you click an Unit, the Unit you clicked has its 
    absolute path stored in a label, and then appended to 
    the InputHogger Profile

	Profile
    |_ Label 0 
    |_ Label 1 
    |_ Label 2 
    |_ ...
*/
class ClickUnit: public Click
{
    GODOT_CLASS(ClickUnit, Click)

public:
    static void _register_methods(){}
    void _init(){}
    void _unhandled_input(const InputEvent* const ev);
};

/*
    An InputHogger specialized in picking Unit
    when the mouse is hovered over them

    PROFILE:
    Profile stores a pointer to an Unit. 
    Get it by Profile.GetPtr<Unit>()
*/
class HoverUnit: public InputHogger
{
    GODOT_CLASS(HoverUnit, InputHogger)

public:
    static void _register_methods()
    {
        register_method("_process", &HoverUnit::_process);

        register_signal<HoverUnit>("hover_new_unit", "Profile", GODOT_VARIANT_TYPE_OBJECT);
        register_signal<HoverUnit>("off_unit");
    }

    virtual void _ready();
    void _init(){}

    void _process(float delta);

    // Disable resetting because...
    // What do you intend Reset() to do, anyway?
    virtual void Reset(){}

    // Let _RayCast follows the mouse pointer
    void _unhandled_input(const InputEvent* const ev);

protected:
    RayCast2D* _RayCast2D;

    // Cached Unit. I don't want to rewrite Profile too much
    Unit*   _unit;
};
#endif