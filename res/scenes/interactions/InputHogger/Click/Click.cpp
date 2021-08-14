#include "Click.hpp"
#include "Unit.hpp"

// ==========================
// C L I C K  P O S I T I O N 
// ==========================
void ClickPosition::_unhandled_input(const InputEvent* const ev)
{
    if (IsFull())
        return;

    auto mouseClick = cast_to<InputEventMouseButton>(ev);

    if (mouseClick &&
        mouseClick->is_pressed() &&
        mouseClick->get_button_index() == GlobalConstants::BUTTON_LEFT)
        {
            // Create a position2D with the currently clicked position
            Node2D* clickPos = Position2D::_new();
            clickPos->set_position(mouseClick->get_position());
            clickPos->set_name(String::num_int64(_Profile->get_child_count()));
            _Profile->Steal(clickPos);

            if (IsFull()) 
            {
                emit_signal("hogged_full", _Profile);
            }
        }
}

// ==================
// C L I C K  U N I T
// ==================

void ClickUnit::_unhandled_input(const InputEvent* const ev)
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
                    // Create a Label, and write the absolute path
                    // of this unit on it
                    // I'm a genius, I know
                    Label* unitPath = Label::_new();
                    unitPath->set_name(String::num_int64(_Profile->get_child_count()));
                    unitPath->set_visible(false);
                    unitPath->set_text(unit->get_path());
                    _Profile->Steal(unitPath);

                    if (IsFull()) 
                    {
                        emit_signal("hogged_full", _Profile);
                    }
                }
            }
        }
}



// ==================
// H O V E R  U N I T  
// ==================

void HoverUnit::_process(float delta)
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
                godot::Godot::print("On");
                _unit = unit;
                _Profile->Store(unit);

                emit_signal("hover_new_unit", _Profile);

                // For compatibility with InputHogger
                emit_signal("hogged_full", _Profile);
            }
        }
    }
    else if (_unit != nullptr)
    {
        _unit = nullptr;
        emit_signal("off_unit");
        godot::Godot::print("Off");
    }
}

void HoverUnit::_ready()
{
    _RayCast2D = get_node<RayCast2D>("RayCast2D");
    _RayCast2D->set_enabled(true);

    // Set up the signaling Profile
    _Profile = get_node<Profile>("Profile");
}


void HoverUnit::_unhandled_input(const InputEvent* const ev)
{
    auto mouseMotion = cast_to<InputEventMouseMotion>(ev);
    if (mouseMotion)
        _RayCast2D->set_position(mouseMotion->get_position());
}