#include "survival_wheel.hpp"
#include "unit.hpp"

void SurvivalWheel::_register_methods()
{
    register_method("Show", &SurvivalWheel::Show);
    register_method("FadeAway", &SurvivalWheel::FadeAway);
    register_method("_ready", &SurvivalWheel::_ready);
    register_method("Update", &SurvivalWheel::Update);
    register_method("CompletedTweening", &SurvivalWheel::CompletedTweening); }

void SurvivalWheel::_init()
{
    _unitWithStatsChanged = nullptr;
}

void SurvivalWheel::_ready()
{
    // Completely hide the bars when created
    set_visible(false);

    _health = get_node<TextureProgress>("Health");
    _spirit = get_node<TextureProgress>("Spirit");
    _stamina = get_node<TextureProgress>("Stamina");

    // Setup signals and handlers
    _tween = get_node<Tween>("Tween");
    _tween->connect("tween_completed", this, "CompletedTweening");
}

void SurvivalWheel::Update(const Unit* const u)
{
    if (u == nullptr)
    {
        return;
    }
    // There's no way to defer this update if
    // the player is seeing the bars
    if (is_visible())
    {
        _unitWithStatsChanged = nullptr;
        _RealUpdate(u);
    }
    // Defer updating the bars if possible
    else
    {
        _unitWithStatsChanged = u;
    }
}

void SurvivalWheel::_RealUpdate(const Unit* const u)
{
    // Look at these code lines make me think about creating an array for attributes
    AttributeDynamic *health = u->get_node<AttributeDynamic>("Attribute/Health");
    AttributeDynamic *spirit = u->get_node<AttributeDynamic>("Attribute/Spirit");
    AttributeDynamic *stamina= u->get_node<AttributeDynamic>("Attribute/Stamina");

    _health->set_max(health->GetTotal());
    _health->set_value(health->GetCurrent());

    _spirit->set_max(spirit->GetTotal());
    _spirit->set_value(spirit->GetCurrent());

    _stamina->set_max(stamina->GetTotal());
    _stamina->set_value(stamina->GetCurrent());
}

void SurvivalWheel::Show()
{
    
    // We update the bars before visualizing
    // DO NOT swap the order of set_visible() and then Update()
    set_visible(true);
    Update(_unitWithStatsChanged);

    // Be sure to interrupt tween if it's fading
    _tween->stop_all();
    // Set Transparency from Fully Transparent to Fully Opaque
    _tween->interpolate_property(this, "modulate", get_modulate(), Color(1, 1, 1, 1), 0.4, Tween::TRANS_LINEAR, Tween::EASE_OUT_IN);
    _tween->start();
}

void SurvivalWheel::FadeAway()
{
    // Be sure to interrupt tween if it's in process of showing
    _tween->stop_all();
    // Set Transparency from Fully Opaque to Fully Transparent
    _tween->interpolate_property(this, "modulate", get_modulate(), Color(1, 1, 1, 0), 0.4, Tween::TRANS_LINEAR, Tween::EASE_IN_OUT);
    _tween->start();
}

void SurvivalWheel::CompletedTweening()
{
    // Hide the bars if it's transparent
    // I think hiding will stop it from being rendered
    if (get_modulate() == Color(1,1,1,0))
    {
        set_visible(false);
    }
}