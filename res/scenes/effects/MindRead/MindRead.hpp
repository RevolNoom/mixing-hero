/*
    MindRead classes

    Provide a way for players to see attributes of other characters or themselves

    Mind Read constructs a profile of the affected character, and then send that 
    profile to GUI components

    Mind Read effectiveness can be confused, blocked by other effects

    This is Decorator pattern 
    (or Composite pattern? I think it's Decorator)

    BaseEffect MindRead                                 |
    |_ Profile Profile  (shared along the chain)        |
    |_ MindRead MindRead                                | Read
        |_ MindRead MindRead                            | Sequence
            |_ MindRead MindRead                        |
                |_ ...                                  v
    
    It's also worth note-taking that Profile is going to be 
    shared by the chain.
    Meaning that only the root (top) MindRead owns it
    But, Profile can be modified by any link in the chain.
*/
#ifndef MIND_READ_H
#define MIND_READ_H

#include <Godot.hpp>
#include <Node.hpp>

using namespace std;

#include "BaseEffect.hpp"

class Profile;
class Unit;

namespace Effect
{
    /*  The simplest Mind Reading method: Can read mind of self and teammates
        This is not supposed to be an Interaction.
        It's intended for private use in implementation
        
        How MindRead implementation works:
        + This process is done when you click on an unit or hover your mouse on
        + A MindRead is created by your controlled character.
        + That character will pass MindRead to the target Unit.
        + MindRead then constructs a Profile of target Unit.
        + Finally, based on how you invoke this process (Hover mouse/Click),
            then pass it to GUI
        
        Default _strategy is a DefaultRead. See MindReadStrategy.hpp for more details
    */ 
    class MindRead: public BaseEffect 
    {
        GODOT_CLASS(MindRead, BaseEffect)
    public:

        static void _register_methods();
        void _init();
        void _ready();

        // Construct a profile and add infos of this unit into it
        void Read(const Unit* const target) const;

        // Same as Read(). It's actually Read() in disguise.
        // (*Implementation detail: This is why I must add _Profile as a private member,
        // that is to conform to Effect interface) 
        void AffectOnUnit(Unit* const u) const override;

        // Return the profile you got from reading your latest target.
        // Nullptr if you didn't perform a read beforehand
        // (Don't come running to me asking why your game crashes :> )
        const Profile* GetProfile() const;

        // Set the perspective of this mind read. 
        // Different source unit gets different MindRead result from the target
        void SetReader(const Unit* const source_reader);

        // Pass Mr. along the MindRead chain. Hopefully
        // that Mr. will reach the chain ending and be appended there
        // NOT GUARANTEED, though.
        // Some effects could stop Mr. from joining the family
        // *aggressively glare DivineRead (>_>)
        virtual void AppendChain(const MindRead* const mr);

    protected:
        // Here's where you:
        // + Perform reading unit
        // + Modify already known informations
        // + Pass the work along the chain. DON'T FORGET THIS! PUT THIS AT THE FINAL LINES
        virtual void DoRead(const Unit* const source, const Unit* const target, Profile* const dirtyProfile) const;

        // List of NodePath for all the nodes 
        // this MindRead is going to peek at an Unit
        PoolStringArray _peekedNodes;

        // Who's doing reading?
        const Unit* _reader;

        // Our Profile constructed so far
        // This Profile is shared for modification to the whole chain
        // But there's only one owner: The root MindRead
        Profile* _Profile;

        // The next Profile processing phase
        MindRead* _nextMindRead;
    };

    /*
        The strongest MindRead type.
        This type is intended for Interaction & Effects
        to correctly acquire informations from unit.
    */
    class DivineInterrogation: public MindRead 
    {
        GODOT_CLASS(DivineInterrogation, MindRead)
    public:

        static void _register_methods();
        void _init();
        void _ready();

        void AppendChain(const MindRead* const actuallyNotAppendedButIsHereJustForFun) override;
    
    protected:
        void DoRead(const Unit* const source, const Unit* const target, Profile* const dirtyProfile) const override;
    };


    /*  
        More advanced Mind Reading
        When it catches a MindRead, it will allow that MindRead 
        to read the attributes of any unit

        DeepGaze intensity will reveal how much information is disclosed.
        The amount of information is increased when intensity is increased, in this order:
        + Health Value
        + Spirit Value
        + Stamina Value
        + Max Health
        + Max Spirit
        + Max Stamina 
        + Static Attributes, from lowest to highest. 
            If there's a tie, then they're revealed in this order:
            * Endurance
            * Physique
            * Spirit
            * Speed
    */
   /*
    class DeepGaze: public EffectOvertime 
    {
        GODOT_CLASS(DeepGaze, Effect)
    };
    */

    /*  The strongest Mind Reading method.

        In addition to the (ordered) info revealed by DeepGaze
        Soul Stare can read currently affected Effects

        The amount of information is increased when intensity is increased
        Effect revelations are ordered by their intensity, and then potency 
        (lower intensity/potency effects are revealed first)
        If there's a tie, then they're chosen in this order:
        + Passive Effects
        + Random (depends on the sorting algorithm. But no one knows what sorting algorithm it is. Thus, random)

        Note that the amount of intensity needed to reveal attributes is not necessary identical to DeepGaze
        Soul Stare may reveal info interchangingly (i.e. an attribute, then an effect, then an attribute,...)

        If SoulStare does not have enough intensity to fully reveal the effect, then the reader will see
        the effect info partially, in this order:
        + Effect type
        + Intensity
        + Potency
    */
    /*class SoulStare: public DeepGaze 
    {
        GODOT_CLASS(SoulStare, DeepGaze)
    };*/

}

#endif