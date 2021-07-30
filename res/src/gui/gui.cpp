#include "gui.hpp"
#include "Unit.hpp"
#include "Profile.hpp"
#include "SurvivalBars.hpp"
#include "SurvivalWheel.hpp"
#include "MindRead.hpp"

void GUI::_init()
{}

void GUI::_register_methods()
{
    register_method("_ready", &GUI::_ready);
    register_method("ShowBars", &GUI::ShowBars);
    register_method("ShowWheel", &GUI::ShowWheel);
    register_method("HideWheel", &GUI::HideWheel);
    register_method("BindPlayer", &GUI::BindPlayer);
}

void GUI::_ready()
{
    _wheeler = nullptr;
    _wheel = get_node<SurvivalWheel>("SurvivalWheel");
    _playerBars = get_node<SurvivalBars>("Bars/SurvivalBarsLeft");
    _rightBars = get_node<SurvivalBars>("Bars/SurvivalBarsRight");
}

void GUI::BindPlayer(Unit* const player)
{
    // If we ever want to change the player in the middle of the game,
    // BindPlayer will unbind the current player first 
    if (_player != nullptr)
        _player->disconnect("attributes_modified", this, "ShowBars");
    _player = player;
    _player->connect("attributes_modified", this, "ShowBars");
    ShowBars(_player);
}


// TODO: UGHHHH Inefficient, Duplicate code
// You better start working on that cache real fast!

void GUI::ShowBars(Unit* const unit)
{
    if (_player == nullptr)
    {
        godot::Godot::print("Hey, Who Is Doing Reading? _player is not initialized");
        return;
    }

    MindRead *mindread = MindRead::_new();
    mindread->set_name("MindRead");
    this->add_child(mindread);

    mindread->SetReader(_player);

    // MindRead is an Effect, treated like an Effect
    // And thus it must acts like an Effect
    // (other effects may modify mindread too)
    unit->AffectedBy(mindread); 

    if (unit == _player)
        _playerBars->Display(mindread->GetProfile());
    else
        _rightBars->Display(mindread->GetProfile());
    
    this->remove_child(mindread);
    mindread->queue_free();
}

// TODO: Stop creating so many MindRead!
void GUI::ShowWheel(Unit* const unit)
{

    if (_player == nullptr)
    {
        godot::Godot::print("Hey, Who Is Doing Reading? _player is not initialized");
        return;
    }

    // Like a mutex, lock the wheel exclusively for this unit
    _wheeler = unit;

    // Move the wheel to the unit's position
    _wheel->set_position(unit->get_position());

    MindRead *mindread = MindRead::_new();
    mindread->set_name("MindRead");
    this->add_child(mindread);

    mindread->SetReader(_player);

    // MindRead is an Effect, treated like an Effect
    // And thus it must acts like an Effect
    // (other effects may modify mindread too)
    unit->AffectedBy(mindread); 

    // Bink blink magic. Appear!
    _wheel->Show(mindread->GetProfile());
    
    this->remove_child(mindread);
    mindread->queue_free();
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