#include "InteractionManager.hpp"
#include "InteractionWheel.hpp"
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
    _InteractionWheel = get_node<InteractionWheel>("InteractionWheel");
}

void InteractionManager::SetController(Unit* const newController)
{
    _controller = newController;
}