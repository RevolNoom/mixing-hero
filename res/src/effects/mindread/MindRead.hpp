/*
    Mind Read classes

    Provide a way for players to see attributes of other characters or themselves

    Mind Read constructs a profile of the affected character, and then send that 
    profile to GUI components

    Mind Read effectiveness can be confused, blocked by other effects
*/
#ifndef MIND_READ_H
#define MIND_READ_H

#include <Godot.hpp>
#include <Node.hpp>

using namespace std;

#include "Effect.hpp"

class Profile;
class Unit;

namespace Effect
{
    // Abstract Class for all kind of ways you can do Mind Reading
    class MindReadStrategy; 

    /*  The simplest Mind Reading method: Can read mind of self and teammates
        This is not supposed to be an Interaction.
        It's intended for private use in implementation
        
        How MindRead implementation works:
        + This process is done when you click on an unit or hover your mouse on
        + A MindRead is created by your controlled character.
        + That character will pass Mindread to the target Unit.
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

        // This is where we perform reading target
        void Read(const Unit* const u) const;

        // Other words for Read(). 
        // Don't worry about it. It's harmless
        void AffectOnUnit(Unit* const u) const override;

        // Return the reading result
        const Profile* GetProfile() const;

        void SetReader(const Unit* const source_reader);

    protected:
        // Wrap the current strategy with a new Mrs
        // In other words, the Profile we get from our strategy
        // is now tweaked by Mrs, then returned to us
        void Decorate(const MindReadStrategy* const mrs);

    private:
        // Who's doing reading?
        const Unit* _reader;
        
        // The State. How MindRead performs on Units. 
        MindReadStrategy* _Strategy;
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