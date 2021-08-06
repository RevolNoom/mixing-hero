/*
    InteractionWheel Class

    Provide a beautiful (*cough, cough) interface to display as GUI,
    as well as handling insertion, deletion, arrangement 
    of interactions, interaction icons

    Structure:

    Path2D InteractionWheel
    |_ PathFollow2D 0           (Yes, pure Natural number)
    |   |_ Interaction [Slap]
    |_ PathFollow2D 1           (Each PathFollow is a slot on the wheel)
    |   |_ Interaction [Cuddle]
    |_ ... 
    |_ PathFollow2D 9           
        |_ Interaction [Cuddle]
*/
#ifndef INTERACTION_WHEEL_HPP
#define INTERACTION_WHEEL_HPP

#include <Godot.hpp>
#include <Path2D.hpp>

using namespace godot;
class Interaction;
class Profile;


class InteractionWheel: public Path2D
{
    GODOT_CLASS(InteractionWheel, Path2D)

    public:
    // There can be at most 10 interactions on the wheel
    // Numbered from 0 to 9
    static constexpr int MAX_SIZE = 10;

    static void _register_methods();
    void _init();

    // Whatever chaos you arranged in the editor, don't bother
    // I'm going to rearrange it to my liking
    void _ready();

    // Return true if the interaction is added successfully
    bool AddInteraction(const Interaction* const interaction);

    // Try to add all the Interactions in the Profile into the wheel
    // Abort if doing so would:
    // 1. Exceed the maximum size
    // 2. Insert junk into the wheel (non-Interaction classes)
    // Else, the wheel will happily accept all these Interactions
    bool AddInteractionProfile(const Profile* const profileWithOnlyInteractionInfos);

    // Return true if an interaction with that name
    // is removed successfully
    bool RemoveInteraction(const String interactionName);

    // Remove all interactions in each slot
    void CleanWheel();


    // WHEEL ARRANGING FUNCTIONS

    // Remove unused holes on the wheel
    // For example: [x] means slot x has an interaction
    //
    // [0] - 1 - [2] - 3 - 4 - [5] - ... 
    // Will become:
    // [0] - [1] - [2] - [3] - 4 - 5 - ... 
    // 
    void Squeeze() const;

    // Rearrange Squeeze()ed interactions on the wheel
    // so that each interaction icon are spaced evenly
    void SocialDistancing() const;

    // Disable PathFollows' Rotate property
    // so that Interactions don't tumble on the wheel
    void Untumble() const;

private:
    // The current number of interactions on the wheel
    int _size;

};

#endif