#ifndef MIND_READ_STRATEGY_H
#define MIND_READ_STRATEGY_H

#include <Godot.hpp>
#include <Node.hpp>


using namespace godot;
class Unit;
class Profile;

namespace Effect
{
    /*
        Abstract class for all kind of ways you can do Mind Reading
        DO NOT CREATE INSTANCE OF THIS TYPE

        Virtual functions without default implementation breaks
        the shared library
    */
    class MindReadStrategy: public Node
    {
        GODOT_CLASS(MindReadStrategy, Node)
    public:
        void _init();
        void _ready();
        static void _register_methods();

        // Return a read-only Profile that's made by reading target unit
        // If you're going to use it, duplicate it 
        virtual const Profile* GetProfile() const; 


        // Return the profile of the target
        // Made by letting the child read Unit first, then furnish the details             
        // This is done this way to make sure Profiles are properly deleted,
        // shared, and duplicated
        void Read(const Unit* const reader, const Unit* const target);

        // Set mrs to be our child strategy
        // Note that this will delete the old child strategy (if any) (but not if mrs is our current child)
        virtual void Decorate(const MindReadStrategy* const mrs);

    protected:

        // Steal child's "Profile" node to us
        // You MUST test if child exists before stealing 
        virtual void SnatchProfileFromChild();

        // This is where we make the difference between 
        // our child's work and our work
        // Override it to achieve your desired result
        // _Profile is snatched from child or created new if no child is there
        virtual void Tweak(const Unit* const reader, const Unit* const target);

        Profile* _Profile;
        // The child strategy
        // Its node name is "Strategy"
        MindReadStrategy* _Strategy;
    };



    // Make a detailed profile of Teammate Unit and nothing for opponent unit
    class DefaultRead: public MindReadStrategy
    {
        GODOT_CLASS(DefaultRead, MindReadStrategy)
        public:

        static void _register_methods();
        void _init();

        // Only read the Unit if it's on the same team (self included)
        // Read all attributes and Effects it sees
        virtual void Tweak(const Unit* const reader, const Unit* const target) override;

        private:
        // All the attributes that are going to be read 
        PoolStringArray _attributes;
    };
}

#endif