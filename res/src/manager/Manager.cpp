#include <InputEvent.hpp>
#include "InteractionManager.hpp"
#include "Interaction.hpp"
//#include "AttrModify.hpp"
#include <Control.hpp>
#include "Manager.hpp"
#include "Unit.hpp"
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
    _GUI = get_node<GUI>("CanvasLayer/GUI");
    _InteractionManager = get_node<InteractionManager>("InteractionManager");
    SetController(u);

    RegisterUnit(u);

    Unit* u2 = get_node<Unit>("Unit2");
    RegisterUnit(u2);
}

void Manager::_unhandled_input(InputEvent* const event)
{
    _InteractionManager->FeedInput(event);
}
