#include "MindReadStrategy.hpp"
#include "MindRead.hpp"
#include "Profile.hpp"
#include "Unit.hpp"

using namespace Effect;

void MindRead::_register_methods()
{
    register_method("Read", &MindRead::Read);
    register_method("GetProfile", &MindRead::GetProfile);

    // I'm thinking about removing this line. 
    // BaseEffect class already register this
    register_method("AffectOnUnit", &MindRead::AffectOnUnit);
    register_method("_ready", &MindRead::_ready);
}
void MindRead::_init()
{
    _Strategy = DefaultRead::_new();
    _Strategy->set_name("Strategy");
    this->add_child(_Strategy);
}

void MindRead::Read(const Unit* const u) const
{
    _Strategy->Read(_reader, u); 
}

void MindRead::AffectOnUnit(Unit* const u) const                  
{
    Read(u);
}

void MindRead::SetReader(const Unit* const source_reader)         
{
    _reader = source_reader;
}

const Profile* MindRead::GetProfile() const                       
{
    return _Strategy->GetProfile();
} 

void MindRead::Decorate(const MindReadStrategy* const mrs)
{
    MindReadStrategy* duplicate = cast_to<MindReadStrategy>(mrs->duplicate());
    duplicate->Decorate(_Strategy);
    duplicate->set_name(String("Strategy"));
    this->remove_child(_Strategy);
    _Strategy = duplicate;
    this->add_child(_Strategy);
}

void MindRead::_ready()
{
}
