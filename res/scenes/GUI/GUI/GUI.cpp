#include "GUI.hpp"
#include "Unit.hpp"
#include "Profile.hpp"
#include "MindRead.hpp"
#include "SurvivalBars.hpp"
#include "SurvivalWheel.hpp"
#include <InputEventMouseButton.hpp>
#include <InputEventMouseMotion.hpp>

void GUI::_init()
{}

void GUI::_register_methods()
{
    register_method("_ready", &GUI::_ready);
    register_method("ShowBars", &GUI::ShowBars);
    register_method("SetController", &GUI::SetController);
}

void GUI::_ready()
{
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
    godot::Godot::print("Showing Bars");
    if (_controller == nullptr)
    {
        godot::Godot::print("Hey, Who Is Doing Reading? _controller is not initialized");
        return;
    }

    MindRead *MindRead = MindRead::_new();
    MindRead->set_name("MindRead");
    this->add_child(MindRead);

    MindRead->SetReader(_controller);

    // MindRead is an Effect, treated like an Effect
    // And thus it must acts like an Effect
    // (other effects may modify MindRead too)
    unit->AffectedBy(MindRead); 

    if (unit == _controller)
        _controllerBars->Display(MindRead->GetProfile());
    else
        _rightBars->Display(MindRead->GetProfile());
    
    this->remove_child(MindRead);
    MindRead->queue_free();
} 