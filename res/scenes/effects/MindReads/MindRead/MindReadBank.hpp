/*
    MIND READ BANK CLASS

    USER READS USING BANKS, NOT MINDREAD OBJECTS

    The Bank is an interface for the user to quickly retrieve
    reading informations from an object of choice without needing
    to hassle themselves with objects management.

    The Bank is a singleton (or pool?), meaning that all Bank 
    instances share reading results to each other. All instances
    are a handle of the Singleton: instance.Read() will delegate
    the work to _singleton.Read()

    As said, The Bank is only an interface. The actual reading job
    is done by MindRead objects. The Bank manages MindRead objects 
    and their reading results, so that users don't have to worry 
    about freeing MindRead objects, and speed up reading process 
    by remembering past readings that are still valid.

    Since each type of MindRead returns different result,
    IT IS MANDATORY to couple a MindRead class with a corresponding
    MindReadBank class.

    If you want to (what I wanted to say here, I forgot)

    MindReadBank inst   (an instance. Is a handle to access _bank)
    |_ [Absolutely NO child]
    |_ [If there is, it's your responsibility to manage them, not me]


    When the bank encounters a new Unit it has never seen, it connects
    that Unit to hotlineService. The Unit notifies hotline that it has
    outdated informations, and any read that includes it must be redo.

    MindReadBank _hotlineService   (does not live in SceneTree)
    |_ [Also Absolutely NO child]

    All information is kept statically by the Class. 
    _
*/
#ifndef MIND_READ_BANK_HPP
#define MIND_READ_BANK_HPP

#include "MindRead.hpp"

// For mapping timestamp
#include "Unit.hpp"
#include <OS.hpp>
#include <map>

using namespace godot;
using namespace Effect;

class MindReadBank: public Node
{
    GODOT_CLASS(MindReadBank, Node);
public:
    static void _register_methods()
    {
        register_method("Read", &MindReadBank::Read);
        register_method("Invalidate", &MindReadBank::Invalidate);
        // TODO: register_method
    }

    void _init()
    {
        _prototype = MindRead::_new();
    }

    // Delete and free all accounts, account conditions
    void GoBankrupt()
    {
        // Remove all modify times
        _modifiedTimeOf.clear();

        // Now, remove each profile we allocated
        for (auto it = _account.begin(); it!=_account.end(); ++it)
        {
            // uhmmmmmmmmmmmmm... 
            // Don't look at me. I'm also out of words.
            it->second.second->free();
        }
        _account.clear();
    }

    // Withdraw a reading Profile 
    const Profile* Read(Unit* source, Unit* target)
    { 
        std::pair couple{source, target};
        auto profile = _account[couple];


        // This profile is not valid
        // And thus must be re-read
        if (_modifiedTimeOf[source] >= profile.first || 
            _modifiedTimeOf[target] >= profile.first)
            {
                // Getting time may take time (?), so I get it once and for all
                size_t currentTime = OS::get_singleton()->OS::get_ticks_msec();

                // This couple has not been read before
                if (profile.second == nullptr)
                {
                    if (!source)
                        Godot::print("Source null!");
                    if (!target)
                        Godot::print("Target null!");
                        
                    // I don't want this "if", but I don't want error messages either
                    if (!(source->is_connected("attributes_modified", this, "Invalidate")))
                    {
                        source->connect("attributes_modified", this, "Invalidate");
                        _modifiedTimeOf[source] = currentTime;
                    }

                    if (!(target->is_connected("attributes_modified", this, "Invalidate")))
                    {
                        target->connect("attributes_modified", this, "Invalidate");
                        _modifiedTimeOf[target] = currentTime;
                    }
                }
                // There's an old profile associated with this account
                // because it has been read before
                // Delete it before restarting anew 
                else  
                    profile.second->queue_free();

                auto newProt = Prototype();
                _account[couple] = std::pair{currentTime+1, newProt->Read(source, target)};
                newProt->queue_free();
            }

        return _account[couple].second;
    }

    // Prototype resetting is only allowed on an empty bank
    // Because changing type of Prototype will invalidate All
    // reading results
    bool SetPrototype(const MindRead* const m) 
    {
        if (_account.size() != 0)
            return false;
        return _prototype = cast_to<MindRead>(m->duplicate());
    }

    // Return a new instance of MindRead Prototype
    MindRead* Prototype() 
    {
        return cast_to<MindRead>(_prototype->duplicate());
    }

    // Signal handler
    // Invalidate this unit because some of its infos has changed
    // The signals should be connected automatically to _pool in DoRead()
    void Invalidate(Unit* target)
    { 
        _modifiedTimeOf[target] = OS::get_singleton()->get_ticks_msec();
    }

    // TODO: Create "die" signal handler:
    // Remove all informations relevant to an Unit
    // void Forget(Unit* deadUnit);
protected:

    using Participant=Unit*;
    using SourceUnit=Unit*;
    using TargetUnit=Unit*;
    // In milisecond (0.001)
    using CreatedTime=size_t;
    // In milisecond (0.001)
    using ModifiedTime=size_t;

    // Helps determine whether a Profile is still valid or not
    // A Profile is only valid when it has CreatedTime >= ModifiedTime of both participants
    std::map<Participant, ModifiedTime>  _modifiedTimeOf;

    // Caches the reading result from source to target
    std::map<
            std::pair<SourceUnit, TargetUnit>, 
            std::pair<CreatedTime, Profile*>
            > _account;

    // The reading results are done by this MindRead
    MindRead* _prototype;
};

#endif