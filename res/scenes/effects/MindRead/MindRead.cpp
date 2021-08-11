#include "MindRead.hpp"
#include "Profile.hpp"
#include "Unit.hpp"

using namespace Effect;

void MindRead::_register_methods()
{
    register_method("Read", &MindRead::Read);
    register_method("GetProfile", &MindRead::GetProfile);
    register_method("SetReader", &MindRead::SetReader);
    
    register_method("_ready", &MindRead::_ready);
}

void MindRead::_init()
{
    // Create a new, blank profile
    _Profile = Profile::_new();
    add_child(_Profile);
    _Profile->set_name("Profile");

    _peekedNodes.append("Attribute/Health");
    _peekedNodes.append("Attribute/Spirit");
    _peekedNodes.append("Attribute/Stamina");
    _peekedNodes.append("Attribute/Endurance");
    _peekedNodes.append("Attribute/Physique");
    _peekedNodes.append("Attribute/Mentality");
    _peekedNodes.append("Attribute/Speed");
    //_peekedNodes.append("EffectOvertime");
}

void MindRead::_ready()
{
}

void MindRead::Read(const Unit* const target) const
{
    _Profile->WipeClean(); 
    // And here comes the real reading part
    DoRead(_reader, target, _Profile);
}

void MindRead::AffectOnUnit(Unit* const u) const                 
{
    // a bit silly, eh?
    Read(u);
}

void MindRead::SetReader(const Unit* const source_reader)         
{
    _reader = source_reader;
}

const Profile* MindRead::GetProfile() const                       
{
    return _Profile; 
} 

void MindRead::AppendChain(const MindRead* const mr)
{
    // Base case, when we're at the end of the chain
    if (_nextMindRead == nullptr)
    {
        _nextMindRead = cast_to<MindRead>(mr->duplicate());
        _nextMindRead->set_name("MindRead");
        add_child(_nextMindRead);
        return;
    }

    _nextMindRead->AppendChain(mr);
}

void MindRead::DoRead(const Unit* const source, const Unit* const target, Profile* const dirtyProfile) const
{
    // Do nothing because we have no right to stalk other people
    // TODO: Read not just ourselves, but also our team
    if (target != source)
        return;

    // First time I see Read and Write child classes. Pretty neat
    auto peekedNodes = _peekedNodes.read();

    for (int iii=0; iii<_peekedNodes.size(); ++iii)
    {
        // We already have the info of this attribute, skip
        if (dirtyProfile->get_node_or_null((NodePath) peekedNodes[iii]))
            continue;

        // Copy the attribute we need to read
        // Add it to the Profile
        auto attr = target->get_node_or_null((NodePath) peekedNodes[iii]);
        if (attr)
            dirtyProfile->AddInfo(attr);
    }

    // TODO: Add Effect infos to Profile
}



// ======================================
// D I V I N E  I N T E R R O G A T I O N
// ======================================

void DivineInterrogation::_register_methods()
{
}

void DivineInterrogation::_init()
{
    _peekedNodes.append("Attribute/Health");
    _peekedNodes.append("Attribute/Spirit");
    _peekedNodes.append("Attribute/Stamina");
    _peekedNodes.append("Attribute/Endurance");
    _peekedNodes.append("Attribute/Physique");
    _peekedNodes.append("Attribute/Mentality");
    _peekedNodes.append("Attribute/Speed");
}

void DivineInterrogation::_ready()
{
}

void DivineInterrogation::AppendChain(const MindRead* const mr)
{
    // Do not append anything because this is already the highest
    // most noble, awesome, overwhelming read
    // Appending anything after this will only contaminate the informations
}

void DivineInterrogation::DoRead(const Unit* const source, const Unit* const target, Profile* const dirtyProfile) const
{
    // All information we get from parents MindRead is trash
    _Profile->WipeClean();

    auto peekedNodes = _peekedNodes.read();
    for (int iii=0; iii<_peekedNodes.size(); ++iii)
    {
        // Copy the attribute we need to read
        // Add it to the Profile
        auto attr = target->get_node_or_null((NodePath) peekedNodes[iii]);
        if (attr)
            dirtyProfile->AddInfo(attr);
    }
}
