/*
    PICK OBJECT 

    Report back what you clicked on the screen

    Profile holds an Object*
    Use GetPtr<Object>() to get that pointer
*/
#ifndef PICK_HPP
#define PICK_HPP

#include <InputEventMouseButton.hpp>
#include <InputEventMouseMotion.hpp>
#include <GlobalConstants.hpp>
#include <RayCast2D.hpp>

#include "InputHogger.hpp"

using namespace godot;

class Pick: public InputHogger
{
    GODOT_CLASS(Pick, InputHogger)
public:
    static void _register_methods()
    {
        register_method("Reset", &Pick::Reset);
    }

    virtual void _ready()
    {
        _Profile= get_node<Profile>("Profile");
        _RayCast2D = get_node<RayCast2D>("RayCast2D");
        _RayCast2D->set_enabled(false);
    }

    // Discards everything and accept input again
    virtual void Reset() 
    {
        _Profile->Wipe();
    }

    void _unhandled_input(const InputEvent* const ev)
    {
        auto mouseClick = cast_to<InputEventMouseButton>(ev);

        if (mouseClick &&
            mouseClick->is_pressed() &&
            mouseClick->get_button_index() == GlobalConstants::BUTTON_LEFT)
            {
                _RayCast2D->set_position(mouseClick->get_position());
                _RayCast2D->force_raycast_update();

                if (_RayCast2D->is_colliding())
                {
                    _Profile->StorePtr(_RayCast2D->get_collider());
                }
                else 
                    // Let's pray I don't mess this up
                    _Profile->StorePtr((Object*) nullptr);

                emit_signal("done", this);
            }
    }


protected:
    // The RayCast used to pick object
    RayCast2D *_RayCast2D;
};

#endif