#include "InputSequence.hpp"
#include "Profile.hpp"
#include "Unit.hpp"

void InputSequence::_register_methods()
{
    register_method("GetProfile", &InputSequence::GetProfile);
    register_method("_ready", &InputSequence::GetProfile);
    register_signal<InputSequence>("sequence_done", "InputSequence", GODOT_VARIANT_TYPE_OBJECT);

    // TODO: Add a signal that would alert the Interaction Wheel
    // to change the interaction set
    //register_signal("", "", GODOT_VARIANT_TYPE_OBJECT);
}

void InputSequence::_init()
{
    _Profile = Profile::_new();
    _Profile->set_name("Profile");
}

void InputSequence::_ready()
{
    _Profile = get_node<Profile>("Profile");
}

const Profile* InputSequence::GetProfile() const
{
    return _Profile;
}

void InputSequence::Accept(const InputEvent* const event, Unit* const performer)
{
}