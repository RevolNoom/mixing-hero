/*
    An InputHogger specialized in picking Unit
    when the mouse is hovered over them

    PROFILE:
    Profile stores a pointer to an Unit. 
    Get it by Profile.GetPtr<Unit>()
*/

#ifndef HOVER_UNIT_HPP
#define HOVER_UNIT_HPP

#include "InputEventMouseMotion.hpp"
#include "InputHogger.hpp"
#include "RayCast2D.hpp"
#include "Unit.hpp"

using namespace godot;

class HoverUnit: public InputHogger
{
    GODOT_CLASS(HoverUnit, InputHogger)

public:
    static void _register_methods()
    {
        register_method("_process", &HoverUnit::_process);

        register_signal<HoverUnit>("off_unit");
    }

    virtual void _ready()
    {
        _RayCast2D = get_node<RayCast2D>("RayCast2D");
        _RayCast2D->set_enabled(true);

        // Set up the signaling Profile
        _Profile = get_node<Profile>("Profile");
    }

    void _process(float delta)
    {
        if (_RayCast2D->is_colliding())
        {
            auto unit = cast_to<Unit>(_RayCast2D->get_collider());
            if (unit)
            {
                // If we're still hovering on the same unit
                // last frame, then there's nothing to do
                if (unit != _unit)
                {
                    _unit = unit;
                    _Profile->StorePtr<Unit>(unit);

                    emit_signal("done", this);
                }
            }
        }
        else if (_unit != nullptr)
        {
            _unit = nullptr;
            emit_signal("off_unit");
        }
    }


    // Let _RayCast follows the mouse pointer
    void _unhandled_input(const InputEvent* const ev)
    {
        auto mouseMotion = cast_to<InputEventMouseMotion>(ev);
        if (mouseMotion)
            _RayCast2D->set_position(mouseMotion->get_position());
    }

protected:
    RayCast2D* _RayCast2D;

    // Cached Unit. I don't want to rewrite Profile too much
    Unit*   _unit;
};

#endif