#include "InteractionManager.hpp"
#include "InteractionWheel.hpp"
#include "InputSequence.hpp"
#include "Pick.hpp"
#include "Unit.hpp"

void InteractionManager::_register_methods()
{
    register_method("SetController", &InteractionManager::SetController);
    register_method("_ready", &InteractionManager::_ready);
}


void InteractionManager::_init()
{}

void InteractionManager::_ready()
{
    _PickSurvivalWheel = get_node<PickSurvivalWheel>("PickSurvivalWheel");
}

void InteractionManager::SetController(Unit* const newController)
{
    _controller = newController;
    _PickSurvivalWheel->SetPerformer(newController);
}
    
void InteractionManager::FeedInput(const InputEvent* const event)
{
    auto children = get_children();
    for (int iii=0; iii<children.size(); ++iii)
    {
        cast_to<InputSequence>(children[iii])->Accept(event, _controller);
    }
}