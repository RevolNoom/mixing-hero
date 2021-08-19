#include "ManagerInteraction.hpp"
#include "Manager.hpp"
#include "Unit.hpp"
#include "GUI.hpp"


void Manager::SetController(Unit* const u)
{
    _GUI->SetController(u);
    _ManagerInteraction->SetController(u);
}

void Manager::_ready()
{
    Unit* u = get_node<Unit>("Unit");

    _GUI = get_node<GUI>("CanvasLayer/GUI");
    _ManagerInteraction = get_node<ManagerInteraction>("ManagerInteraction");

    SetController(u);
}

