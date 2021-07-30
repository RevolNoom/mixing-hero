#include "SurvivalWheel.hpp"
#include "Attribute.hpp"
#include "Profile.hpp"
#include "Unit.hpp"

void SurvivalWheel::_register_methods()
{
    register_method("Show", &SurvivalWheel::Show);
    register_method("FadeAway", &SurvivalWheel::FadeAway);
    register_method("_ready", &SurvivalWheel::_ready);
    register_method("Update", &SurvivalWheel::Update);
    register_method("CompletedTweening", &SurvivalWheel::CompletedTweening); 
}

void SurvivalWheel::_init()
{
    _attributeNames.append("Health");
    _attributeNames.append("Spirit");
    _attributeNames.append("Stamina");

}

void SurvivalWheel::_ready()
{
    // Completely hide the bars when created
    set_visible(false);
    set_modulate(Color(1,1,1,0));

    // Setup signals and handlers
    _tween = get_node<Tween>("Tween");
    _tween->connect("tween_completed", this, "CompletedTweening");
}

void SurvivalWheel::Update(const Profile* const p)
{
    // Only update when the Wheel is shown
    // Who's going to know if the wheel is hidden, anyway?
    if (!is_visible())
        return;
    
    // Sequentially grabs each needed attribute and update the wheels
    for (int iii=0; iii<_attributeNames.size(); ++iii)
    {
        const AttributeDynamic *attr = cast_to<AttributeDynamic>(p->get_node_or_null((String)_attributeNames[iii]));
        TextureProgress *prog  = cast_to<TextureProgress>(get_node_or_null((String)_attributeNames[iii]));

        if (attr)
        {
            prog->set_max(attr->GetTotal());
            prog->set_value(attr->GetValue());
        }
        else 
        {
            // We see nothing, so default into all bars are full
            prog->set_max(1);
            prog->set_value(1);
            godot::Godot::print("You can't look into the mind of this unit");
        }
    }
}

void SurvivalWheel::Show(const Profile* const p)
{
    // We update the bars before visualizing
    // DO NOT swap the order of set_visible() and then Update()
    set_visible(true);
    Update(p);

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