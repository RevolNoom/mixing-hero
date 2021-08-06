#include "GUI.hpp"
#include "Unit.hpp"
#include "Profile.hpp"
#include "MindReading.hpp"
#include "SurvivalBars.hpp"
#include "SurvivalWheel.hpp"
#include "GlobalConstants.hpp"
#include <InputEventMouseButton.hpp>
#include <InputEventMouseMotion.hpp>

void GUI::_init()
{}

void GUI::_register_methods()
{
    register_method("_ready", &GUI::_ready);
    register_method("ShowBars", &GUI::ShowBars);
    register_method("ShowWheel", &GUI::ShowWheel);
    register_method("HideWheel", &GUI::HideWheel);
    register_method("SetController", &GUI::SetController);
    register_method("UnitMouseEvent", &GUI::UnitMouseEvent);
}

void GUI::_ready()
{
    _wheeler = nullptr;
    _wheel = get_node<SurvivalWheel>("SurvivalWheel");
    _controllerBars = get_node<SurvivalBars>("Bars/SurvivalBarsLeft");
    _rightBars = get_node<SurvivalBars>("Bars/SurvivalBarsRight");
}

void GUI::SetController(Unit* const player)
{
    // If we ever want to change the player in the middle of the game,
    // SetController will unbind the current player first 
    if (_controller != nullptr)
        _controller->disconnect("attributes_modified", this, "ShowBars");
    _controller = player;
    _controller->connect("attributes_modified", this, "ShowBars");
    ShowBars(_controller);
}


// TODO: UGHHHH Inefficient, Duplicate code
// You better start working on that cache real fast!

void GUI::ShowBars(Unit* const unit)
{
    if (_controller == nullptr)
    {
        godot::Godot::print("Hey, Who Is Doing Reading? _controller is not initialized");
        return;
    }

    MindReading *MindReading = MindReading::_new();
    MindReading->set_name("MindReading");
    this->add_child(MindReading);

    MindReading->SetReader(_controller);

    // MindReading is an Effect, treated like an Effect
    // And thus it must acts like an Effect
    // (other effects may modify MindReading too)
    unit->AffectedBy(MindReading); 

    if (unit == _controller)
        _controllerBars->Display(MindReading->GetProfile());
    else
        _rightBars->Display(MindReading->GetProfile());
    
    this->remove_child(MindReading);
    MindReading->queue_free();
}

// TODO: Stop creating so many MindReading!
void GUI::ShowWheel(Unit* const unit)
{

    if (_controller == nullptr)
    {
        godot::Godot::print("Hey, Who Is Doing Reading? _controller is not initialized");
        return;
    }

    // Like a mutex, lock the wheel exclusively for this unit
    _wheeler = unit;

    // Move the wheel to the unit's position
    _wheel->set_position(unit->get_position());

    MindReading *MindReading = MindReading::_new();
    MindReading->set_name("MindReading");
    this->add_child(MindReading);

    MindReading->SetReader(_controller);

    // MindReading is an Effect, treated like an Effect
    // And thus it must acts like an Effect
    // (other effects may modify MindReading too)
    unit->AffectedBy(MindReading); 

    // Bink blink magic. Appear!
    _wheel->Show(MindReading->GetProfile());
    
    this->remove_child(MindReading);
    MindReading->queue_free();
}

// Hide the SurvivalWheel 
// Only hide if it's showing info for unit
// Do nothing otherwise
void GUI::HideWheel(const Unit* const unit)
{
    if (unit != _wheeler)
        return;
    
    _wheeler = nullptr;

    _wheel->FadeAway();
}

// I need to come up with a new way to manage MindReading
//
// TODO: Rethink about GUI design. Should it knows which unit the player controls?
// TODO: Can MindReading be reused many times to avoid creation cost?
// TODO: MindReading will also be affected by the caster's effects too. There has to be a way...

void GUI::UnitMouseEvent(Unit* const u, InputEventMouse* const event)
{
    if (cast_to<InputEventMouseMotion>(event))
        ShowWheel(u);
    else
    {
        auto mouse_button = cast_to<InputEventMouseButton>(event);
        if (mouse_button && 
            mouse_button->get_button_index() == GlobalConstants::BUTTON_LEFT &&
            mouse_button->is_pressed())
        {
            ShowBars(u);
        }
    }
}
