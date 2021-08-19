#include "ManagerInteraction.hpp"

#include "Unit.hpp"
#include "Pick.hpp"
#include "Profile.hpp"
#include "Interaction.hpp"
#include "InputHogger.hpp"
#include "InteractionWheel.hpp"

void ManagerInteraction::_register_methods()
{
    register_method("_ready", &ManagerInteraction::_ready);
    register_method("_on_Pick_done", &ManagerInteraction::_on_Pick_done);
    register_method("_handle_exec_ready", &ManagerInteraction::_handle_exec_ready);
    register_method("_handle_change_state", &ManagerInteraction::_handle_change_state);
    register_method("_handle_request_input", &ManagerInteraction::_handle_request_input);
    register_method("_handle_request_choice", &ManagerInteraction::_handle_request_choice);
    register_method("_on_InteractionWheel_interaction_picked", &ManagerInteraction::_on_InteractionWheel_interaction_picked);
    /*
    register_method("_on_ManagerInteraction_Abort", &ManagerInteraction::_on_ManagerInteraction_Abort);
    */
}

void ManagerInteraction::_ready()
{
    _ExecQueue = get_node("ExecQueue");
    _InteractionWheel = get_node<InteractionWheel>("InteractionWheel");
    _InteractionWheel->connect("interaction_picked", this, "_on_InteractionWheel_interaction_picked");

    _Pick = get_node<Pick>("Pick");
    _Pick->connect("done", this, "_on_Pick_done");

    _Top = get_node("Top");
    _InteractionWheel->LoadInteractionProfile(_Top->get_node<Profile>("Choices"));
}

// Controls InteractionWheel appearance
void ManagerInteraction::_on_Pick_done(const InputHogger* const object)
{
    auto pickedUnit = cast_to<Unit>(object->GetProfile()->GetPtr<Object>());

    if (pickedUnit)
    {
        _pickedUnit = pickedUnit;
        //_InteractionWheel->LoadInteractionProfile()
        _InteractionWheel->Show(pickedUnit);
    }
    else
    {
        _pickedUnit = nullptr;
        _InteractionWheel->Hide();
        Abort();
    }
}

// Drop the currently in active Interaction
// And all extra layer of interaction sets
void ManagerInteraction::Abort()
{
    // Drop Interaction in active
    auto IIA = get_node_or_null("InteractionInActive");
    if (IIA)
    {
        remove_child(IIA);
        IIA->queue_free();
    }

    // Drop all Interaction sets
    PopTopSetAll();
    _InteractionWheel->LoadInteractionProfile(_Top->get_node<Profile>("Choices"));

    // Go back to Interaction-picking state
    _Pick->Enable(true);
    _InteractionWheel->Hide();
}


// ===============================
// U N I Q U E   F U N C T I O N S
// ===============================


void ManagerInteraction::_on_InteractionWheel_interaction_picked(const Interaction* const interaction)
{
    // Shoo the Wheel away
    _InteractionWheel->Hide();

    // Set up proxy node InteractionInActive
    auto IIA = Node::_new();
    IIA->set_name("InteractionInActive");
    add_child(IIA);

    // Set up operation for this interaction
    auto newInteraction = cast_to<Interaction>(interaction->duplicate());
    newInteraction->connect("exec_ready", this, "_handle_exec_ready");
    newInteraction->connect("change_state", this, "_handle_change_state");
    newInteraction->connect("request_input", this, "_handle_request_input");
    newInteraction->connect("request_choice", this, "_handle_request_choice");
    IIA->add_child(newInteraction);

    // Let that interaction throws at us with everything it has
    newInteraction->Start(_controller, _pickedUnit);
}

// This Interaction the player pick has some sub-Interaction branch
// that must be taken. We put it on the Interaction sets stack
void ManagerInteraction::_handle_request_choice(Interaction* const interaction)
{
    auto newInteractionSet = interaction->GetChoices();
    if (_InteractionWheel->LoadInteractionProfile(newInteractionSet))
    {
        PushInteractionSet(newInteractionSet);
    }
    else
    {
        godot::Godot::print("handle_request_choice failed. Can't load InteractionProfile for" + interaction->get_name());
    }

    // Show the wheel with new choices
    _InteractionWheel->Show(_pickedUnit);
    _Pick->Enable(true);
}

void ManagerInteraction::_handle_request_input(Interaction* const interaction)
{
    // Disable Wheel's InputHogger
    // And that's it. We enter Interaction input phase
    // Wake up only by Abort() or exec_ready
    Godot::print("ManagerI Pick disabled");
    _Pick->Enable(false);
}

void ManagerInteraction::_handle_change_state(Interaction* const oldState, Interaction* const newState)
{
    // TODO
}

void ManagerInteraction::_handle_exec_ready(Interaction* const interaction)
{
    // I'm pretty sure that this interaction is from InteractionInActive
    // Knock my head if I'm wrong

    /*  Commented for short test
    // Detach from IIA
    interaction->get_parent()->remove_child(interaction);
    // Append it to the queue
    get_node("ExecQueue")->add_child(interaction);

    */

    Godot::print("Slap is ready");
    interaction->Execute();

    // Get rid of IIA
    auto IIA = get_node("InteractionInActive");
    remove_child(IIA);
    IIA->queue_free();
    
   
    // Go back to Interaction Picking State
    _Pick->Enable(true);
}

// =======================================================
// I N T E R A C T I O N   S T A C K   O P E R A T I O N S 
// =======================================================

void ManagerInteraction::PushInteractionSet(const Profile* const set)
{
    // Create a new Top
    Node *newTop = Node::_new();
    newTop->set_name("Top");
    newTop->add_child(_Top);

    // Duplicate and add the Interaction set to new top
    auto nIS = set->duplicate();
    nIS->set_name("Choices");
    newTop->add_child(nIS);

    // Now, if we already have a top
    if (_Top)
    {
        // Temporarily detach top to reserve spot for a new one
        remove_child(_Top);

        // Append old top to new top
        // Then finally, plug new top back
        // We have successfully add a new choice Profile to the stack
        newTop->add_child(_Top);
        _Top = newTop;
    }
    // Else if we have empty stack, make _Top points to a new one
    else 
    {
        _Top = newTop;
    }

    _InteractionWheel->LoadInteractionProfile(_Top->get_node<Profile>("Choices"));
}

// TODO: Make PopTopSet/All() has independent implementation
// PopTopSet one layer of interaction set
// Can't PopTopSet the base set
// True if it PopTopSet one layer, false otherwise
bool ManagerInteraction::PopTopSet()
{
    auto secondToTop = _Top->get_node_or_null("Top");
    
    // Return if we're already at the base Interaction set
    if (!secondToTop)
        return false;


    // Peel off the top layer of the stack 
    remove_child(_Top);
    _Top->remove_child(secondToTop);    // Keep the inner layer intact
    _Top->queue_free();

    // Redirect _Top to the new top
    add_child(secondToTop);
    _Top = secondToTop;
    return true;
}

// PopTopSet all layer of interaction set
// until the base set is the only one left
void ManagerInteraction::PopTopSetAll()
{
    // PopTopSet until we can't Pop any layer more
    while (PopTopSet());
}

void ManagerInteraction::SetController(Unit* const u)
{
    _controller = u;
    _InteractionWheel->SetController(u);
    Godot::print(get_name());
    
}