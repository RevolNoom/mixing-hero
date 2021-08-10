#include "SurvivalWheel.hpp"
#include "MindReading.hpp"
#include "Profile.hpp"
#include "Pick.hpp"
#include "Unit.hpp"

// ================================= 
// B A S E  S E Q U E N C E  P I C K
// ================================= 

void Pick::_register_methods()
{
    register_property("PickAmount", &Pick::_PickAmount, 0);
    register_method("ResetPicking", &Pick::ResetPicking);
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
    auto event = cast_to<InputEventMouse>(ev);

    if (event)
    {
        // RayCast at mouse position to search for adorable thingies
        _Picker->set_position(event->get_position());
        _Picker->force_raycast_update();

        // and then...
        DoYourJob(ev, performer);
    }
}


void Pick::DoYourJob(const InputEvent* const ev, Unit* const performer)
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

void PickPosition::DoYourJob(const InputEvent* const ev, Unit* const performer)
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

void PickUnit::DoYourJob(const InputEvent* const ev, Unit* const performer)
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

// =============================== 
// =============================== 

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

// TODO: Use the cache to stop creating so many MindReading
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
                MindReading* mindread = MindReading::_new();
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