/*
    An InputHogger specialized in picking clicked positions

    When you click somewhere on the screen, the position you click
    is stored in a Node2D, and then appended to Profile

	Profile
    |_ Node2D 0 
    |_ Node2D 1 
    |_ Node2D 2 
    |_ ...
*/

#ifndef PICK_MANY_POSITION_HPP
#define PICK_MANY_POSITION_HPP

#include "PickMany.hpp"
#include "Node2D.hpp"

class PickManyPosition: public PickMany
{
    GODOT_CLASS(PickManyPosition, PickMany)

public:
    static void _register_methods(){}

    void _init(){}

    void _unhandled_input(const InputEvent* const ev)
    {
        if (IsFull())
            return;

        auto mouseClick = cast_to<InputEventMouseButton>(ev);

        if (mouseClick &&
            mouseClick->is_pressed() &&
            mouseClick->get_button_index() == GlobalConstants::BUTTON_LEFT)
            {
                // Create a position2D with the currently clicked position
                Node2D* clickPos = Node2D::_new();
                clickPos->set_name(String::num_int64(_Profile->get_child_count()));
                clickPos->set_position(mouseClick->get_position());
                _Profile->Steal(clickPos);

                if (IsFull()) 
                {
                    emit_signal("done", this);
                }
            }
    }
};

#endif