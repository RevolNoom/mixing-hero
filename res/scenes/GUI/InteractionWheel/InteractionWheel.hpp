/*
    InteractionWheel Class

    Provide a beautiful (*cough, cough) interface to display,
    as well as handling insertion, deletion, arrangement 
    of interactions, interaction icons

    Path2D InteractionWheel
    |_ PathFollow2D 
        |_ Interaction
    |_ PathFollow2D            (Each PathFollow is a slot on the wheel)
        |_ Interaction
    |_ ... 
    |_ PathFollow2D            
        |_ Interaction 
*/
#ifndef INTERACTION_WHEEL_HPP
#define INTERACTION_WHEEL_HPP

#include <Godot.hpp>
#include <Path2D.hpp>
#include <PathFollow2D.hpp>

#include "Pick.hpp"

using namespace godot;
class Interaction;
class Profile;
class Unit;


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

    // When the wheel is visible,
    // Move the Wheel to carrier unit
    void _process(float delta);

    // ===========
    // A N I M E Z
    // ===========

    // Smoothly pull the interactions out like a chain 
    // Set the wheel to follow this unit
    void Show(Unit* const u);

    // Smoothly push the interactions back in like a chain 
    void Hide();

    // Tween's signal handler
    // Called to invisiblize the interaction wheel when it's done hiding
    void _on_Tween_tween_completed();

    // ===========================================================
    // I N T E R A C T I O N S  M A N A G I N G  F U N C T I O N S
    // ===========================================================

    void SetController(Unit* const u);

    // Return true if the interaction is added successfully
    bool AddInteraction(const Interaction* const interaction);

    // CleanWheel and try to add all the Interactions from the Profile into the wheel
    // Aborts without modifying the Wheel if loading this Profile would:
    // 1. Exceed the maximum Wheel size
    // 2. Insert non-Interaction classes into the wheel
    bool LoadInteractionProfile(const Profile* const profileWithOnlyInteractionInfos);

    // Return true if an interaction with that name
    // is removed successfully
    bool RemoveInteraction(const String interactionName);

    // Remove all interactions in each slot
    void CleanWheel();

    // ============================
    // S I G N A L  H A N D L E R S
    // ============================

    // Emit signal on which interaction was picked
    void _on_Interaction_picked(Interaction* const pickedInteraction);



    // ===============================================
    // W H E E L  A R R A N G I N G  F U N C T I O N S
    // ===============================================

    // Rearrange Squeeze()ed interactions on the wheel
    // so that each interaction icon are spaced evenly
    void SocialDistancing() const;

    // Disable PathFollows' Rotate property
    // so that Interactions don't tumble on the wheel
    void Untumble() const;

protected:
    // To whom the Wheel follows 
    Unit* _carrier;

    // Who's going to start the interaction?
    Unit* _controller;

    // TODO: That Tween I'm sooooo eager to add
    // Tween* _Tween;
};

#endif