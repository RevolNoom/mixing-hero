#include "InteractionWheel.hpp"
#include "Interaction.hpp"
#include "Unit.hpp"
#include "Node.hpp"

#include "Slap.hpp"

void InteractionWheel::_register_methods()
{
    register_method("_ready", &InteractionWheel::_ready);


    register_method("Show", &InteractionWheel::Show);
    register_method("Hide", &InteractionWheel::Hide);
    register_method("_process", &InteractionWheel::_process);
    register_method("_on_Interaction_picked", &InteractionWheel::_on_Interaction_picked);
    register_method("_on_Tween_tween_completed", &InteractionWheel::_on_Tween_tween_completed);


    register_method("CleanWheel", &InteractionWheel::CleanWheel);
    register_method("AddInteraction", &InteractionWheel::AddInteraction);
    register_method("RemoveInteraction", &InteractionWheel::RemoveInteraction);
    register_method("LoadInteractionProfile", &InteractionWheel::LoadInteractionProfile);


    register_method("Untumble", &InteractionWheel::Untumble);
    register_method("SocialDistancing", &InteractionWheel::SocialDistancing);
    register_signal<InteractionWheel>("interaction_picked", "interaction", GODOT_VARIANT_TYPE_OBJECT);

}

void InteractionWheel::_init()
{
    _carrier = nullptr;
}

void InteractionWheel::SetController(Unit* const u)
{
    _controller = u;
}


void InteractionWheel::_ready()
{
    Hide();
}

void InteractionWheel::_process(float delta)
{
    // Check for valid carrier. I don't want to
    // fling my Wheel around to a dead soul
    if(_carrier && _carrier->is_inside_tree())
    {
        // Setting position might be costly?
        // So I test for their position first before 
        // doing anything rampaging
        if (_carrier->get_position() != get_position())
            set_position(_carrier->get_position());
    }
    else
    {
        Hide();
    }

}


// TODO: Come on! Give me some grand animation here!
// Where's my tween? I waaaaaaaaant my Tween.
// ===========
// A N I M E Z
// ===========


void InteractionWheel::Show(Unit* const u)
{
    set_visible(true);
    _carrier = u;
    set_process(true);
}

// TODO: Create something like a bool in SurvivalWheel + Tween
void InteractionWheel::Hide()
{
    _on_Tween_tween_completed();
}

void InteractionWheel::_on_Tween_tween_completed()
{
    _carrier = nullptr;
    set_visible(false);
    set_process(false);
}


// ===========================================================
// I N T E R A C T I O N S  M A N A G I N G  F U N C T I O N S
// ===========================================================

bool InteractionWheel::AddInteraction(const Interaction* const interaction)
{
    if (interaction == nullptr)
    {
        godot::Godot::print_error("InteractionWheel encountered junk! This is not an Interaction",
                                    "InteractionWheel::AddInteraction", "InteractionWheel.cpp", 0);
        return false;
    }

    if (get_child_count() >= MAX_SIZE)
    {
        godot::Godot::print_error("InteractionWheel can't add " + 
                                 interaction->get_name() + " because it's full",
                                "InteractionWheel::AddInteraction", "InteractionWheel.cpp", 0);
        return false;
    }

    // Set up signals
    auto newInteraction = interaction->duplicate();
    newInteraction->connect("picked", this, "_on_Interaction_picked");

    // Set up new home in node hierachy
    PathFollow2D *newSlot = PathFollow2D::_new();
    newSlot->set_name(interaction->get_name());
    add_child(newSlot);
    newSlot->add_child(newInteraction);
    return true;
}




// ===========================================================
// I N T E R A C T I O N S  M A N A G I N G  F U N C T I O N S
// ===========================================================

bool InteractionWheel::LoadInteractionProfile(const Profile* const profileWithOnlyInteractionInfos)
{
    if (profileWithOnlyInteractionInfos->get_child_count() > MAX_SIZE)
    {
        godot::Godot::print("InteractionWheel Can't load Profile: Interaction amount exceeded max size");
        return false;
    }

    // Test for junks (non-Interaction)
    auto ominousInteractions = profileWithOnlyInteractionInfos->get_children();
    for (int iii=0; iii<ominousInteractions.size(); ++iii)
    {
        if (!cast_to<Interaction>(ominousInteractions[iii]))
        {
            String error_message = "InteractionWheel Can't load Profile: Junk encountered: ";
            error_message += cast_to<Interaction>(ominousInteractions[iii])->get_class();
            godot::Godot::print(error_message);
            return false;
        }
    }

    // Everything seems ok. Time to add them.
    for (int iii=0; iii<ominousInteractions.size(); ++iii)
    {
        AddInteraction(cast_to<Interaction>(ominousInteractions[iii]));
    }

    return true;
}

bool InteractionWheel::RemoveInteraction(const String interactionName)
{
    auto deleteNode = get_node((NodePath)interactionName);
    if (deleteNode)
    {
        remove_child(deleteNode);
        deleteNode->queue_free();
        return true;
    }
    return false;
}

// Remove all Interactions on the Wheel
void InteractionWheel::CleanWheel()
{
    auto children = get_children();
    for (int iii=0; iii<children.size(); ++iii)
    {
        auto pthfllw = cast_to<PathFollow2D>(children[iii]);
        remove_child(pthfllw);
        pthfllw->queue_free();
    }
}



// ============================
// S I G N A L  H A N D L E R S
// ============================

void InteractionWheel::_on_Interaction_picked(Interaction* const pickedInteraction)
{
    godot::Godot::print("An Interaction was picked!");
    emit_signal("interaction_picked", pickedInteraction);
}

// ===============================================
// W H E E L  A R R A N G I N G  F U N C T I O N S
// ===============================================


void InteractionWheel::SocialDistancing() const
{
    auto children = get_children();

    for (int iii=0; iii<children.size(); ++iii)
    {
        auto pthfllw = cast_to<PathFollow2D>(children[iii]);

        // Start from twelve O'clock. 
        // Which way it goes, I don't know. F.
        // Not even sure that it starts from 12
        pthfllw->set_unit_offset(iii/children.size());
    }
}

void InteractionWheel::Untumble() const
{
    auto children = get_children();

    for (int iii=0; iii<children.size(); ++iii)
    {
        auto slot = cast_to<PathFollow2D>(children[iii]);
        slot->set_rotate(false);
        slot->set_rotation(0);
    }
}