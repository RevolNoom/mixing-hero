#include "GUI.hpp"
#include "Unit.hpp"
#include "Profile.hpp"
#include "MindRead.hpp"
#include "SurvivalBars.hpp"
#include "SurvivalWheel.hpp"

void GUI::_init()
{}

void GUI::_register_methods()
{
    register_method("_ready", &GUI::_ready);
    register_method("SetController", &GUI::SetController);
}

void GUI::_ready()
{
    _controllerBars = get_node<SurvivalBarsLeft>("Bars/SurvivalBarsLeft");
    _rightBars = get_node<SurvivalBarsRight>("Bars/SurvivalBarsRight");
}

void GUI::SetController(Unit* const player)
{
    // If we ever want to change the player in the middle of the game,
    // SetController will unbind the current player first 
    //if (_controller != nullptr)
    //    _controller->disconnect("attributes_modified", this, "ShowBars");
    //_controller = player;
    //_controller->connect("attributes_modified", this, "ShowBars");
    //ShowBars(_controller);
}
