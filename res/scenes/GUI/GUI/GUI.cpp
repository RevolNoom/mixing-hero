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
    _controller = player;
    _rightBars->SetController(player);
    _controllerBars->SetController(player);
}
