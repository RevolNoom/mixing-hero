#include "InteractionManager.hpp"
#include "Interaction.hpp"
#include <InputEvent.hpp>
#include <Control.hpp>
#include "Manager.hpp"
#include "Unit.hpp"
#include "Pick.hpp"
#include "GUI.hpp"

void Manager::_init(){}

void Manager::_register_methods()
{
    register_method("_ready", &Manager::_ready);
    register_method("_unhandled_input", &Manager::_unhandled_input);
}

// TODO: Delete this?
void Manager::RegisterUnit(Unit* const u)
{
}

void Manager::SetController(Unit* const u)
{
    _GUI->SetController(u);
    _InteractionManager->SetController(u);
}

void Manager::_ready()
{
    Unit* u = get_node<Unit>("Unit");
    Unit* u2 = get_node<Unit>("Unit2");

    _GUI = get_node<GUI>("CanvasLayer/GUI");
    _InteractionManager = get_node<InteractionManager>("InteractionManager");
    SetController(u);

    // Bind unit-mouse-clicks to _GUI
    auto pickSurvivalBars = _InteractionManager->get_node<PickSurvivalBars>("PickSurvivalBars");
    pickSurvivalBars->BindGUI(_GUI);


    RegisterUnit(u);
    RegisterUnit(u2);
}

void Manager::_unhandled_input(InputEvent* const event)
{
    _InteractionManager->FeedInput(event);
}
