/*
    Pick declares some InputSequences that rely on
    mouse (or finger) to get something on the screen

    (Currently, only using mouse, though)
*/

#ifndef PICK_HPP
#define PICK_HPP

#include "InputSequence.hpp"
#include <RayCast2D.hpp>
#include <InputEventMouseButton.hpp>
#include <InputEventMouseMotion.hpp>
#include <InputEventMouse.hpp>
#include <GlobalConstants.hpp>

class InteractionWheel;
class SurvivalWheel;
class Unit;
class GUI;

// This class serves as an Abstract Class
// It's not intended to be instantiated
class Pick: public InputSequence
{
    GODOT_CLASS(Pick, InputSequence)

public:
    static void _register_methods();
    void _init();
    void _ready();

    // Discards everything I have picked and try again
    void ResetPicking();

    // OVERRIDE me!
    // Feed me with Events and I'll hog them up
    // I will only digests Events that interests me
    // You'll get "sequence_done" signal when I'm done
    virtual void Accept(const InputEvent* const event, Unit* const performer) override;

protected:

    // The RayCast used to pick object
    RayCast2D* _Picker;

    // The amount of objects needed picking
    int _PickAmount;

    // Do I have to spell it out for you?
    bool _DontFeedMeEventsAnymore;
};

// An InputSequence specialized in picking clicked positions
class PickPosition: public Pick
{
    GODOT_CLASS(PickPosition, Pick)

public:
    static void _register_methods();
    void _init();
    void _ready();
    virtual void Accept(const InputEvent* const event, Unit* const performer) override;
};


// An InputSequence specialized in picking clicked Units
class PickUnit: public PickPosition
{
    GODOT_CLASS(PickUnit, PickPosition)

public:
    static void _register_methods();
    void _init();
    void _ready();
    virtual void Accept(const InputEvent* const event, Unit* const performer) override;
};


// Show a survival wheel on a mouse-hovered unit
class PickSurvivalWheel: public Pick 
{
    GODOT_CLASS(PickSurvivalWheel, Pick)

public:
    static void _register_methods();
    void _init();
    void _ready();
    void _process(float delta);

    // Set this unit to be the source of reading
    // other units' attributes
    void SetPerformer(Unit* const performer);

    // Move RayCast along with the mouse pointer
    void Accept(const InputEvent* const ev, Unit* const performer);

protected:
    SurvivalWheel* _SurvivalWheel;
    Unit*          _Performer;
};

// Exclusively made to work with GUI
// Bind and unbind an unit to right Survival Bars
// Click on an Unit to bind, click on any non-Unit to unbind
class PickSurvivalBars: public Pick 
{
    GODOT_CLASS(PickSurvivalBars, Pick)

public:
    static void _register_methods();
    void _init();
    void _ready();

    // Set this unit to be the source of reading
    // other units' attributes
    void SetPerformer(Unit* const performer);

    void BindGUI(GUI* const gui);
    virtual void Accept(const InputEvent* const event, Unit* const performer) override;

protected:
    // The _GUI that this Pick is bound to
    GUI*    _GUI;

    // Who performs MindReading on the clicked Unit? 
    // (probably the Player)
    Unit*   _Performer;

};
/*
    // The Wheel which this Pick is responsible to.
    InteractionWheel* _InteractionWheel;

    // _InteractionWheel is bound to this unit
    // Wherever it goes, the wheel follows
    Unit*   _BoundUnit;
    */
#endif