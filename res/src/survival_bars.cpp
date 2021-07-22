#include "survival_bars.hpp"
#include "unit.hpp"

void SurvivalBars::_register_methods()
{
    register_method("Show", &SurvivalBars::Show);
    register_method("FadeAway", &SurvivalBars::FadeAway);
    register_method("_ready", &SurvivalBars::_ready);
    register_method("Hide", &SurvivalBars::Hide);
}

// Completely hide the bars when created
void SurvivalBars::_init()
{
}

void SurvivalBars::_ready()
{
    set_visible(false);
    // Modulate used for tween node (slowly fading)
    //set_modulate(Color(1, 1, 1, 0));
    // Setup signals and handlers
    _tween = get_node<Tween>("Tween");
    _tween->connect("tween_completed", this, "Hide");
}

void SurvivalBars::Show()
{
    set_visible(true);
    // Set Transparency from Fully Transparent to Fully Opaque
    godot::Godot::print("Calling Tween");
    _tween->interpolate_property(this, "modulate", Color(1, 1, 1, 0), Color(1, 1, 1, 1), 3, Tween::TRANS_LINEAR, Tween::EASE_OUT_IN);

    godot::Godot::print("Start Tweening");
}

void SurvivalBars::FadeAway()
{
    godot::Godot::print("Fading");
    // Set Transparency from Fully Opaque to Fully Transparent
    _tween->interpolate_property(this, "modulate", Color(1, 1, 1, 1), Color(1, 1, 1, 0), 3, Tween::TRANS_LINEAR, Tween::EASE_IN_OUT);
}

void SurvivalBars::Hide()
{
    set_visible(false);
    godot::Godot::print("Faded");
}