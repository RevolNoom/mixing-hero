#include "MindReadStrategy.hpp"
#include "MindRead.hpp"
#include "Profile.hpp"
#include "Unit.hpp"

using namespace Effect;

void MindRead::_register_methods()
{
    register_method("Read", &MindRead::Read);
    register_method("GetProfile", &MindRead::GetProfile);
    register_method("AffectOnUnit", &MindRead::AffectOnUnit);
    register_method("_ready", &MindRead::_ready);
}
void MindRead::_init()
{
    _Strategy = DefaultRead::_new();
    _Strategy->set_name("Strategy");
    this->add_child(_Strategy);
}

// Read the target, and construct a profile about it
void MindRead::Read(const Unit* const u) const                    { _Strategy->Read(_reader, u); }
// Same as Read(). It's actually Read() in disguise.
void MindRead::AffectOnUnit(Unit* const u) const                  { Read(u); }
// Set the perspective of this mind read. 
// Different unit gets different mindread result from the target
void MindRead::SetReader(const Unit* const source_reader)         {_reader = source_reader;}
// Return the profile you got from reading your last target.
// Nullptr if you didn't perform a read beforehand
// (Don't come running to me asking why your game crashes :> )
const Profile* MindRead::GetProfile() const                       {return _Strategy->GetProfile();} 

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
