/*
    InteractionWheel Class

    Provide a beautiful (*cough, cough) interface to display,
    as well as handling insertion, deletion, arrangement 
    of interactions, interaction icons

    Structure:

    Path2D InteractionWheel
    |_ PathFollow2D 0           (Yes, pure Natural number)
        |_ Interaction
    |_ PathFollow2D 1           (Each PathFollow is a slot on the wheel)
        |_ Interaction
    |_ ... 
    |_ PathFollow2D 9           
        |_ Interaction 
    |_ ClickUnit ClickUnit
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

    // ===========
    // A N I M E Z
    // ===========

    // Smoothly pull the interactions out like a chain 
    void Show();

    // Smoothly push the interactions back in like a chain 
    void Hide();

    // Tween's signal handler
    // Called to invisiblize the interaction wheel when it's done hiding
    void _on_Tween_Tween_completed();

    // ===========================================================
    // I N T E R A C T I O N S  M A N A G I N G  F U N C T I O N S
    // ===========================================================

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

    //
    // SIGNAL HANDLERS
    //

    // Emit signal on which interaction was picked
    void _on_Interaction_picked(Interaction* const pickedInteraction);

    // ===============================================
    // W H E E L  A R R A N G I N G  F U N C T I O N S
    // ===============================================

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