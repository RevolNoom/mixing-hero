#include "MindReadStrategy.hpp"
#include "Profile.hpp"
#include "Unit.hpp"

void MindReadStrategy::_init()
{}
void MindReadStrategy::_ready()
{}

const Profile* MindReadStrategy::GetProfile() const
{
    return _Profile;
}

void MindReadStrategy::_register_methods()
{
    register_method("Read", &MindReadStrategy::Read);
    register_method("_ready", &MindReadStrategy::_ready);
}

void MindReadStrategy::SnatchProfileFromChild()
{
    Profile* p=_Strategy->get_node<Profile>("Profile");
    _Strategy->remove_child(p);
    _Strategy->_Profile = nullptr;

    this->add_child(p);
    _Profile = p;
}

void MindReadStrategy::Read(const Unit* const reader, const Unit* const target)
{
    // Remove the old profile before doing a new read
    if (_Profile != nullptr)
    {
        this->remove_child(_Profile);
        _Profile->queue_free();
    }

    // We have a child Strategy. Tell it to read first
    if (_Strategy != nullptr)
    {
        _Strategy->Read(reader, target);
        // Then, we steal the work of our child
        SnatchProfileFromChild();
    }
    // This is the end of decorator chain
    // Create a new profile, because we are at the end
    else
    {
        _Profile = Profile::_new();
        _Profile->set_name("Profile");
        this->add_child(_Profile);
    }

    // The hook function
    // We tweak the profile we stole from our child
    // Or tweak the profile we created for ourselves
    Tweak(reader, target);
}

void MindReadStrategy::Decorate(const MindReadStrategy* const mrs)
{
    if (_Strategy && mrs != _Strategy)
    {
        this->remove_child(_Strategy);
        _Strategy->queue_free();
    }

    auto duplicate = mrs->duplicate();
    duplicate->set_name("Strategy");
    _Strategy->add_child(duplicate);
}

void MindReadStrategy::Tweak(const Unit* const reader, const Unit* const target)
{}

// =======================
// D E F A U L T   R E A D 
// =======================

void DefaultRead::_register_methods()
{
}

void DefaultRead::_init()
{
    _attributes.append("Attribute/Health");
    _attributes.append("Attribute/Spirit");
    _attributes.append("Attribute/Stamina");
    _attributes.append("Attribute/Endurance");
    _attributes.append("Attribute/Physique");
    _attributes.append("Attribute/Mentality");
    _attributes.append("Attribute/Speed");
}

void DefaultRead::Tweak(const Unit* const reader, const Unit* const target)
{
    // Do nothing because we have no right to stalk other people
    // TODO: Read not just ourselves, but also our team
    //if (target != reader)
    //    return;


    for (int iii=0; iii<_attributes.size(); ++iii)
    {
        // We already have the info of this attribute, skip
        if (_Profile->get_node_or_null((NodePath) _attributes[iii]))
            continue;

        // Copy the attribute we need to read
        // Add it to the Profile
        auto attr = target->get_node_or_null((NodePath)( _attributes[iii]));
        if (attr)
            _Profile->AddInfo(attr);
    }

    // TODO: Add Effects to Profile
}