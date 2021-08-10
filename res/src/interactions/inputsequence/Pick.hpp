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

class SurvivalWheel;
class Unit;

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

    // Feed me with Events and I'll hog them up
    // I will only digests Events that interests me
    // You'll get "sequence_done" signal when I'm done
    void Accept(const InputEvent* const event, Unit* const performer) override;

protected:

    // Override this function.
    // This is what you do to your InputSequence's Accept()
    // The Ray has been casted, mouse event tested
    virtual void DoYourJob(const InputEvent* const ev, Unit* const performer);

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

protected:
    virtual void DoYourJob(const InputEvent* const ev, Unit* const performer);
};


// An InputSequence specialized in picking clicked Units
class PickUnit: public PickPosition
{
    GODOT_CLASS(PickUnit, PickPosition)

public:
    static void _register_methods();
    void _init();
    void _ready();

protected:
    virtual void DoYourJob(const InputEvent* const ev, Unit* const performer);
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
    // If no performer is present, PickSurvivalWheel 
    // shows a full-by-default SurvivalWheel
    void SetPerformer(Unit* const performer);

protected:
    SurvivalWheel* _SurvivalWheel;
    Unit*          _Performer;
    
};
#endif