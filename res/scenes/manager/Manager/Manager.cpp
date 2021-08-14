#include "Manager.hpp"
#include "Unit.hpp"
#include "GUI.hpp"


void Manager::SetController(Unit* const u)
{
    _GUI->SetController(u);
}

void Manager::_ready()
{
    Unit* u = get_node<Unit>("Unit");

    _GUI = get_node<GUI>("CanvasLayer/GUI");
    //SetController(u);

    //_InteractionManager = get_node<InteractionManager>("InteractionManager");
    //auto pickSurvivalBarsLeft = _InteractionManager->get_node<PickSurvivalBarsLeft>("PickSurvivalBarsLeft");
    // Bind unit-mouse-clicks to _GUI
    //pickSurvivalBarsLeft->BindGUI(_GUI);

}

