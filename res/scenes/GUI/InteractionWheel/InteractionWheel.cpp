#include "InteractionWheel.hpp"
#include "PathFollow2D.hpp"
#include "Interaction.hpp"
#include "Node.hpp"

void InteractionWheel::_register_methods()
{
    register_method("_ready", &InteractionWheel::_ready);

    register_method("Show", &InteractionWheel::Show);
    register_method("Hide", &InteractionWheel::Hide);
    register_method("Invisiblize", &InteractionWheel::Invisiblize);

    register_method("CleanWheel", &InteractionWheel::CleanWheel);
    register_method("AddInteraction", &InteractionWheel::AddInteraction);

    register_method("Squeeze", &InteractionWheel::Squeeze);
    register_method("Untumble", &InteractionWheel::Untumble);
    register_method("SocialDistancing", &InteractionWheel::SocialDistancing);
    register_signal<InteractionWheel>("InteractionCalled", "interaction", GODOT_VARIANT_TYPE_OBJECT);
}

void InteractionWheel::_init()
{
    _size = 0;
}

void InteractionWheel::_ready()
{
    Squeeze();

    // Traverse the nodes "0", "1", "2",... 
    // See how many slots we have used
    for (int iii=0; iii < MAX_SIZE; ++iii)
    {
        NodePath slotPath = String::num_int64(iii);
        Node* slot = get_node(slotPath);
        auto nChildren = slot->get_children();
        if (nChildren.size())
            ++_size; 
        else
            // We squeezed the wheel, so all interactions,
            // if any, should have been counted
            break;  
    }
    
    SocialDistancing();
}



// TODO: Come on! Give me some grand animation here!
// Where's my tween? I want my Tween.
// ===========
// A N I M E Z
// ===========

void InteractionWheel::Show()
{
    set_visible(true);
}

void InteractionWheel::Hide()
{
    set_visible(false);
}

void InteractionWheel::Invisiblize()
{
    set_visible(false);
}


// ===========================================================
// I N T E R A C T I O N S  M A N A G I N G  F U N C T I O N S
// ===========================================================

bool InteractionWheel::AddInteraction(const Interaction* const interaction)
{
    auto i = cast_to<Interaction>(interaction);

    if (i == nullptr)
    {
        godot::Godot::print_error("InteractionWheel encountered junk! This is not an Interaction",
                                    "InteractionWheel::AddInteraction", "InteractionWheel.cpp", 0);
        return false;
    }

    if (_size >= MAX_SIZE)
    {
        godot::Godot::print_error("InteractionWheel can't add " + 
                                 i->get_name() + " because it's full",
                                "InteractionWheel::AddInteraction", "InteractionWheel.cpp", 0);
        return false;
    }

    NodePath slotPath = String::num_int64(_size);
    get_node(slotPath)->add_child(interaction->duplicate());
    ++_size;
    return true;
}




// ===========================================================
// I N T E R A C T I O N S  M A N A G I N G  F U N C T I O N S
// ===========================================================

bool InteractionWheel::AddInteractionProfile(const Profile* const profileWithOnlyInteractionInfos)
{
    // TODO: You know what to do
    return true;
}

bool InteractionWheel::RemoveInteraction(const String interactionName)
{
    // Traverse the nodes "9", "8", "7",... 
    // And find the interaction with that name
    for (int iii=_size-1; iii >= 0; --iii)
    {
        NodePath slotPath = String::num_int64(iii);
        Node* slot = get_node(slotPath);
        // Blindly try and get the interaction 
        Node* luckyLottery = slot->get_node_or_null((NodePath) interactionName);
        if (luckyLottery)
        {
            slot->remove_child(luckyLottery);
            luckyLottery->queue_free();
            return true;
        }
    }
    return false;
}

// Remove all Interactions on the Wheel
void InteractionWheel::CleanWheel()
{
    // Traverse the nodes "0", "1", "2",... 
    for (int iii=0; iii < MAX_SIZE; ++iii)
    {
        NodePath slotPath = String::num_int64(iii);
        Node* slot = get_node(slotPath);
        auto nChildren = slot->get_children();

        // Then delete all of its children
        for (int jjj=0; jjj<nChildren.size(); ++jjj)
        {
            auto aNode = cast_to<Node>(nChildren[jjj]);
            slot->remove_child(aNode);
            aNode->queue_free();
        }
    }
}



// ===============================================
// W H E E L  A R R A N G I N G  F U N C T I O N S
// ===============================================

void InteractionWheel::Squeeze() const
{
    // Double-pointer strategy
    int slot = 0, unused = -1;

    for (; slot<MAX_SIZE; ++slot)
    {
        NodePath slotPath=String::num_int64(slot);
        auto Slot = get_node(slotPath);
        auto childNodes = Slot->get_children();

        if (childNodes.size() > 0)
        {
            ++unused;
            if (unused < slot)
            {
                // Relocate the children to most recently unused slot
                NodePath unusedPath=String::num_int64(unused);
                auto Unused = get_node(unusedPath);

                for (int iii=0; iii<childNodes.size(); ++iii)
                {
                    auto nodeptr = cast_to<Node>(childNodes[iii]);
                    Slot->remove_child(nodeptr);
                    Unused->add_child(nodeptr);
                }
            }
        }
    }
}

void InteractionWheel::SocialDistancing() const
{
    // There's no interaction to distant-iate
    if (_size == 0)
        return;

    for (int iii=0; iii<_size; ++iii)
    {
        auto slot = get_node<PathFollow2D>(String::num_int64(iii));
        // Start from twelve O'clock. 
        // Which way it goes, I don't know. F.
        // Not even sure that it starts from 12
        slot->set_unit_offset(iii/_size);
    }
}

void InteractionWheel::Untumble() const
{
    for (int iii=0; iii<MAX_SIZE; ++iii)
    {
        auto slot = get_node<PathFollow2D>(String::num_int64(iii));
        slot->set_rotate(false);
        slot->set_rotation(0);
    }
}