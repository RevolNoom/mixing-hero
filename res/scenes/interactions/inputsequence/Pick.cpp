#include "InteractionWheel.hpp"
#include "SurvivalWheel.hpp"
#include "MindRead.hpp"
#include "Profile.hpp"
#include "Pick.hpp"
#include "Unit.hpp"
#include "GUI.hpp"

// ================================= 
// B A S E  S E Q U E N C E  P I C K
// ================================= 

void Pick::_register_methods()
{
    register_property("PickAmount", &Pick::_PickAmount, 0);
    register_method("ResetPicking", &Pick::ResetPicking);
    register_method("Accept", &Pick::Accept);
}

void Pick::_init()
{
}

void Pick::ResetPicking()
{
    if (_PickAmount == 0)
        _DontFeedMeEventsAnymore = true;
    else
        _DontFeedMeEventsAnymore = false;
    _Profile->WipeClean();
}

void Pick::_ready()
{
    ResetPicking();
    _Picker = get_node<RayCast2D>("RayCast2D");

    // force_raycast_update() does not need "enabled" = true
    // So RayCast will only be called on demand
    _Picker->set_enabled(false);
}

void Pick::Accept(const InputEvent* const ev, Unit* const performer)
{
}

// ========================
// P I C K  P O S I T I O N 
// ========================
void PickPosition::_register_methods()
{
    register_property("PickAmount", &PickPosition::_PickAmount, 0);
}

void PickPosition::_init()
{
    _PickAmount=0;
}

void PickPosition::_ready()
{
    _Picker = get_node<RayCast2D>("RayCast2D");

    // force_raycast_update() does not need "enabled" = true
    // So RayCast will only be called on demand
    _Picker->set_enabled(false);
}

void PickPosition::Accept(const InputEvent* const ev, Unit* const performer)
{
}

// ================
// P I C K  U N I T
// ================

void PickUnit::_register_methods()
{
}

void PickUnit::_init()
{
}

void PickUnit::_ready()
{
    _Picker = get_node<RayCast2D>("RayCast2D");
    _Picker->set_enabled(false);
}

void PickUnit::Accept(const InputEvent* const ev, Unit* const performer)
{
    if (_Picker->is_colliding())
    {
        auto ominousObject = cast_to<Unit>(_Picker->get_collider());
        if (ominousObject)
        {
            // TODO: How to add a reference to Units into Profile?
        }
    }
}

// =================================== 
// P I C K  S U R V I V A L  W H E E L
// =================================== 

void PickSurvivalWheel::_register_methods()
{
    register_method("_ready", &PickSurvivalWheel::_ready);
    register_method("_process", &PickSurvivalWheel::_process);
}

void PickSurvivalWheel::_init()
{
}

void PickSurvivalWheel::_ready()
{
    // With this Picker, we need to enable it to make it update
    // wheel position in runtime
    _Picker = get_node<RayCast2D>("RayCast2D");
    _Picker->set_enabled(true);
    _SurvivalWheel = get_node<SurvivalWheel>("SurvivalWheel");
}

void PickSurvivalWheel::SetPerformer(Unit* const u)
{
    _Performer = u;
}

void PickSurvivalWheel::Accept(const InputEvent* const ev, Unit* const performer)
{
    auto mouseMovement = cast_to<InputEventMouseMotion>(ev);

    if (mouseMovement)
    {
        _Picker->set_position(mouseMovement->get_position());
    }
}

// TODO: Use the cache to stop creating so many MindRead
void PickSurvivalWheel::_process(float delta)
{
    if (_Picker->is_colliding())
    {
        auto ominousObject = cast_to<Unit>(_Picker->get_collider());
        if (ominousObject)
        {
            _SurvivalWheel->set_position(ominousObject->get_position());

            // TODO: What to do when the _Performer is no longer there?
            if (_Performer->is_inside_tree())
            {
                MindRead* mindread = MindRead::_new();
                mindread->SetReader(_Performer);
                ominousObject->AffectedBy(mindread);
                _SurvivalWheel->Show(mindread->GetProfile());
            }
        }
    }
    else
    {
        // Am I Tweening too much?
        _SurvivalWheel->FadeAway();
    }
}

// ================================= 
// P I C K  S U R V I V A L  B A R S 
// ================================= 

void PickSurvivalBars::_register_methods()
{
    register_method("_ready", &PickSurvivalBars::_ready);
}

void PickSurvivalBars::_init()
{
}

void PickSurvivalBars::_ready()
{
    // With this Picker, we need to enable it to make it update
    // wheel position in runtime
    _Picker = get_node<RayCast2D>("RayCast2D");
    _Picker->set_enabled(false);
}

void PickSurvivalBars::SetPerformer(Unit* const u)
{
    _Performer = u;
}

void PickSurvivalBars::BindGUI(GUI* const gui)
{
    _GUI = gui;
}

void PickSurvivalBars::Accept(const InputEvent* const ev, Unit* const performer)
{
    auto event = cast_to<InputEventMouseButton>(ev);
    // Only care about left mouse clicks
    if (event &&
        event->is_pressed() &&
        event->get_button_index() == GlobalConstants::BUTTON_LEFT)
    {
        _Picker->set_position(event->get_position());
        _Picker->force_raycast_update();

        if (_Picker->is_colliding())
        {
            // Did the player click on an Unit?  
            auto ominousObject = cast_to<Unit>(_Picker->get_collider());
            if (ominousObject)
            {
                _GUI->ShowBars(ominousObject);
            }
        }
    }
}

// =========================================
// P I C K  I N T E R A C T I O N  W H E E L
// =========================================

void PickInteractionWheel::_register_methods()
{
    register_method("_ready", &PickInteractionWheel::_ready);
    register_method("_process", &PickInteractionWheel::_process);
}

void PickInteractionWheel::_init()
{
}

void PickInteractionWheel::_process(float delta)
{
    // See if the Wheel is bound to any unit
    if (_BoundUnit)
    {
        // If that unit has not died yet, then stick to it
        if (_BoundUnit->is_inside_tree())
            _InteractionWheel->set_position(_BoundUnit->get_position());
        // If suddenly it's dead, pack our bag and dissapear
        else
        {
            _BoundUnit = nullptr;
            _InteractionWheel->Hide();
        }  
    }
}

void PickInteractionWheel::_ready()
{
    // With this Picker, we need to enable it to make it update
    // wheel position in runtime
    _Picker = get_node<RayCast2D>("RayCast2D");
    _Picker->set_enabled(true);

    // Hide the Wheel when the game start
    _InteractionWheel = get_node<InteractionWheel>("InteractionWheel");
    _InteractionWheel->set_visible(false);

    // No one will be able to drag this Wheel around
    _BoundUnit = nullptr;
}

// TODO: Don't forget to Load its Interaction Profile 
void PickInteractionWheel::SetOwner(Unit* const u)
{
    _Owner = u;
}

void PickInteractionWheel::Accept(const InputEvent* const ev, Unit* const performer)
{
    // There's something else demands our attention
    if (_InputSequence != nullptr)
    {
        _InputSequence->Accept(ev, _Owner);
        return;
    }

    // Else, do our job: Showing an InteractionWheel

    auto event = cast_to<InputEventMouseButton>(ev);
    // Only care about left mouse clicks
    if (event &&
        event->is_pressed() &&
        event->get_button_index() == GlobalConstants::BUTTON_LEFT)
    {
        _Picker->set_position(event->get_position());
        _Picker->force_raycast_update();

        if (_Picker->is_colliding())
        {
            // Did the player click on an Unit?  
            auto ominousObject = cast_to<Unit>(_Picker->get_collider());
            if (ominousObject)
            {
                _BoundUnit = ominousObject;
                _InteractionWheel->Show();
            }
        }
        else
        {
            _BoundUnit = nullptr;
            _InteractionWheel->Hide();
        }
    }
}