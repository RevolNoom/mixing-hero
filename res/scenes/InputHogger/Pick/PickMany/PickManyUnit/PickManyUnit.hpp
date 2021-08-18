/* TODO: Profile building
    An InputHogger specialized in picking PickMany Units

    Create a Profile which holds other Profile as node
    Each child Profile node StorePtr() an Unit* pointer
    Use Profile->GetPtr<Unit>() to get that Unit pointer

    If order of picking is important, then you'll be relieved
    to know that each Profile is numbered starting from 0 

	Profile
    |_ Profile 0
    |_ Profile 1 
    |_ Profile 2 
    |_ ...
*/

#ifndef PICK_MANY_UNIT_HPP
#define PICK_MANY_UNIT_HPP

#include "PickMany.hpp"
#include "Unit.hpp"

class PickManyUnit: public PickMany
{
    GODOT_CLASS(PickManyUnit, PickMany)

public:
    static void _register_methods()
    {
    }
    
    void _unhandled_input(const InputEvent* const ev)
    {
        if (IsFull())
            return;

        auto mouseClick = cast_to<InputEventMouseButton>(ev);

        if (mouseClick &&
            mouseClick->is_pressed() &&
            mouseClick->get_button_index() == GlobalConstants::BUTTON_LEFT)
            {
                _RayCast2D->set_position(mouseClick->get_position());
                _RayCast2D->force_raycast_update();
                if (_RayCast2D->is_colliding())
                {
                    auto unit = cast_to<Unit>(_RayCast2D->get_collider());
                    if (unit)
                    {
                        Profile *anotherUnit = Profile::_new();
                        anotherUnit->set_name(String::num_int64(_Profile->get_child_count()));
                        anotherUnit->StorePtr(unit);
                        _Profile->Steal(anotherUnit);

                        if (IsFull()) 
                        {
                            emit_signal("done", this);
                        }
                    }
                }
            }
    }
};

#endif 