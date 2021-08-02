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

    + Usage can be summed up in this diagram:

            User -> GUI -> Interaction -> Units

    + Structure:

        Node Interaction
        |_ TextureButton Button
        |_ TextureRect Icon
        |_ Profile "Profile"
        |   |_ Node Info1
        |   |_ Node Info2
        |   |_ ...
        |
        |_ Node EffectsToSource
        |   |_ Effect 1
        |   |_ Effect 2
        |   |_ ...
        |
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
            DivineRead is created solely with Interaction in mind 
*/

#ifndef INTERACTION_H
#define INTERACTION_H

#include <Godot.hpp>
#include <Node.hpp>

using namespace godot;
class Unit;
class Profile;

class Interaction: public Node
{
    GODOT_CLASS(Interaction, Node)

public:
    static void _register_methods();
    virtual void _ready();
    void _init();

    // TODO: There must be a way for SourceCanPerform() 
    // and CanApplyOnTarget() to communicate with a Server
    // so that they can fetch needed information.

    // True if source can perform this interaction.
    // The condition may or may not be related to target
    virtual bool SourceCanPerform(Unit* const source, Unit* const target) const;

    // True if source can apply this interaction on target
    virtual bool CanApplyOnTarget(Unit* const source, Unit* const target) const;

    // Get a Profile that holds information about Interaction:
    // - Cost
    // - Description
    // - ... and something else I have not thought of 
    // As noted in Profile header, the GUI must shakes hand 
    // with Profile on what to be expected of each other
    // (Probably, just a few Label notes with lots of text)
    virtual const Profile* GetInfo(const Unit* const source, const Unit* const target) const;

    // Apply effects on target, and then on source. 
    // Also tell source and target to play corresponding animations
    virtual void Perform(Unit* const source, Unit* const target);

private:
    Node* _effectToSource;
    Node* _effectToTarget;
    
};

#endif