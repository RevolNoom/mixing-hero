/*
    MANAGER INTERACTION CLASS

    ManagerInteraction
    |_ Node InteractionInActive     (a proxy. I don't need to know InteractionName)
        |_  Interaction
    |_ Node Top
        |_ Profile Choices 
        |_ Node Top
            |_ Profile Choices 
            |_ ...
    |_ Pick Pick
    |_ InteractionWheel InteractionWheel
    |_ Node ExecQueue
*/
#ifndef MANAGER_INTERACTION_HPP
#define MANAGER_INTERACTION_HPP

#include <Godot.hpp>
#include <Node.hpp>

class Unit;
class Pick;
class Profile;
class Interaction;
class InputHogger;
class InteractionWheel;
using namespace godot;

class ManagerInteraction: public Node
{
    GODOT_CLASS(ManagerInteraction, Node)

public:

    static void _register_methods();
    void _init(){}

    void _ready();

    // Controls InteractionWheel appearance
    void _on_Pick_done(const InputHogger* const object);

    // Drop the currently in active Interaction
    // And all extra layers of interaction sets
    void Abort();

    // ===============================
    // U N I Q U E   F U N C T I O N S
    // ===============================


    void _on_InteractionWheel_interaction_picked(const Interaction* const interaction);

    // Swap this state-changed interaction with a new one
    void _handle_change_state(Interaction* const oldState, Interaction* const newState);

    // This Interaction the player pick has some sub-Interaction branch
    // that must be taken. We put it on the Interaction sets stack
    void _handle_request_choice(Interaction* const interaction);

    // Direct input request from interaction to GetInput
    void _handle_request_input(Interaction* const interaction);

    // Move this readied interaction to ExecQueue 
    void _handle_exec_ready(Interaction* const interaction);

// =======================================================
// I N T E R A C T I O N   S T A C K   O P E R A T I O N S 
// =======================================================

    // Add a new interaction set on top
    void PushInteractionSet(const Profile* const set);

    // TODO: Make PopTopSet/All() has independent 
    // PopTopSet one layer of interaction set
    // Can't PopTopSet the base set
    // True if it PopTopSet one layer, false otherwise
    bool PopTopSet();

    // PopTopSet all layer of interaction set
    // until the base set is the only one left
    void PopTopSetAll();


    // SETTER
    void SetController(Unit* const u);
// =================
// V A R I A B L E S
// =================
private:

    // Top of the Interactions sets stack
    Node* _Top;
    Node* _ExecQueue;

    InteractionWheel* _InteractionWheel;

    // Handle Unit clicking for InteractionWheel
    Pick* _Pick; 

    Unit* _controller;
    Unit* _pickedUnit;
};

#endif