/*
    INTERACTION CLASS

    + Provide default behaviours for most interaction usage
    + Provide icons and buttons for GUI.
    + Manages the effects that would apply on 
        target and source units when source performs on target
    + Tell each unit what animation to play
    + Tell InteractionGUI how much this interaction costs (Profile Cost), 
        as well as how effective this interaction is (Profile Effectiveness).
    + Defines some constraints as to when you can apply this interaction, 
        to whom you can apply on,...


    + Structure:

        Node Interaction
        |_ TextureButton Button
        |_ Profile InputHoggers 
            |_ InputHogger
            |_ ...

        |_ Profile Choices
            |_ Interaction
            |_ ...

        |_ Profile Info
            |_ Node Info1
            |_ Node Info2
            |_ ...
         
        |_ Node EffectsToSource
            |_ Effect 1
            |_ Effect 2
            |_ ...
         
        |_ Node EffectsToTarget
            |_ Effect 1
            |_ Effect 2
            |_ ...
    
        The Profile "Info" always exists in scene even if
        its information is inconsistent (e.g. some interactions have 
        cost and effectiveness depends on current units' state)
        In inconsistent cases, it's essential for Interaction to perform
        a MindRead, so that it can show informations correctly

        + If the Interaction wishes to communicate with GUI, then 
            it does a basic MindRead

        + If Interaction needs to know exact information 
        (not contaminated by any MindRead-confusing effect), 
            it should use DivineRead. 
*/

#ifndef INTERACTION_H
#define INTERACTION_H

#include <Godot.hpp>
#include <Node2D.hpp>
#include <TextureButton.hpp>


using namespace godot;
#include "InputHogger.hpp"
#include "Profile.hpp"
class Unit;

class Interaction: public Node2D
{
    GODOT_CLASS(Interaction, Node2D)

public:
    static void _register_methods();
    virtual void _init(){}

    // Return the Subchoices this interaction has
    const Profile* GetChoices() const;

    // =====================================================================
    // O V E R R I D E   A L L   O F   T H E   F U N C T I O N S   B E L O W
    // =====================================================================

    virtual void _ready();

    // True if performer can perform this interaction.
    virtual bool Performable(Unit* const performer, Unit* const target) const;

    // Get a Profile with descriptive infos.
    // This Profile is useful for some Specialized GUI component only 
    virtual const Profile* GetInfo(Unit* const performer, Unit* const target) const;

    // Here's where you start each input hogger, one by one
    // or request choice, whatever
    virtual void Start(Unit* const performer, Unit* const target);

    virtual void Execute(){}

    // Button signal handler
    virtual void _on_Button_pressed();

protected:
    Unit* _performer;
    Unit* _target;

    Node *_effectToSource; 
    Node *_effectToTarget; 
};



#endif