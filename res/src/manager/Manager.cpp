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

void Manager::RegisterUnit(Unit* const u)
{
    u->connect("unit_mouse_event", _GUI, "UnitMouseEvent");
    u->connect("unit_mouse_exited", _GUI, "HideWheel");

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
    /*
    auto mouse_button = cast_to<InputEventMouseButton>(event);
    if (mouse_button && 
        mouse_button->get_button_index() == GlobalConstants::BUTTON_LEFT &&
        mouse_button->is_pressed())
    {
    }
    */
}
