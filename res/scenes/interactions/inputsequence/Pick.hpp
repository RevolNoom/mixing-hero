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

    // Who performs MindRead on the clicked Unit? 
    // (probably the Player)
    Unit*   _Performer;

};


/*
    PickInteractionWheel

    When you click on an Unit, an InteractionWheel appears,
    and it disappear when you click "thin air".

    And when you click on an interaction, there're three states 
    in which you may go to:
    1. You find yourself looking at a newly created Wheel 
        with more Interactions to choose
    2. The Interaction requires you to pick a target, whether it be 
        a direction, an unit, or a position
    3. The Interaction needs nothing (might be a self-cast or a 
        smart-target Interaction)

    To accomodate with 1., PickInteractionWheel is designed 
    to be stack-like, with each Interaction holds the InputSequence
    it requires. 

    PickInteractionWheel PWheel
    |_InteractionWheel IWheel
        |_ Interaction 1
            |_ Blah Blah
            |_ ...
            |_ InputSequence Required
        |_ Interaction 2
    |_ InputSequence Child  <=

    When the user clicks an Interaction, IWheel signals
    PWheel which Interaction was clicked. PWheel then 
    asks Interaction for Required, duplicating and add it as Child.
    After that, any InputEvent that's sent to PWheel will be 
    redirected to Child. When Child has accumulated enough events, 
    it signals PWheel. PWheel then execute Interaction, finally 
    deleting Child and wait for new Interaction that the Player clicks
*/
class PickInteractionWheel: public Pick 
{
    GODOT_CLASS(PickInteractionWheel, Pick)

public:
    static void _register_methods();
    void _init();
    void _ready();
    void _process(float delta);

    // The InteractionWheel will be filled
    // with Interactions of this Unit 
    void SetOwner(Unit* const Owner);

    virtual void Accept(const InputEvent* const event, Unit* const performer) override;

protected:
    // Whose Interactions is the Wheel showing? 
    // (probably the Player)
    Unit*   _Owner;

    // The Wheel which this Pick is responsible to.
    InteractionWheel* _InteractionWheel;

    // _InteractionWheel is bound to this unit
    // Wherever it goes, the wheel follows
    Unit*   _BoundUnit;

    // Sub-InputSequence that's chosen from our Interactions
    InputSequence* _InputSequence;
};
#endif