#include "SurvivalWheel.hpp"
#include "MindReadBank.hpp"
#include "Attribute.hpp"
#include "HoverUnit.hpp"
#include "Profile.hpp"
#include "Unit.hpp"

void SurvivalWheel::_register_methods()
{
    register_method("_ready", &SurvivalWheel::_ready);
    register_method("_process", &SurvivalWheel::_process);

    register_method("Update", &SurvivalWheel::Update);
    register_method("FadeAway", &SurvivalWheel::FadeAway);
    register_method("_on_Tween_tween_completed", &SurvivalWheel::_on_Tween_tween_completed); 
    register_method("_on_HoverUnit_done", &SurvivalWheel::_on_HoverUnit_done);
}

void SurvivalWheel::_process(float delta)
{
    set_position(_hoveredUnit->get_position());
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
    _isFading = true;
    set_modulate(Color(1,1,1,0));

    // Stop the Wheel from processing
    // when it's not hovering on any one
    set_process(false);

    // Setup signals and handlers
    _Tween = get_node<Tween>("Tween");
    _Tween->connect("tween_completed", this, "_on_Tween_tween_completed");

    _HoverUnit = get_node<HoverUnit>("HoverUnit");
    _HoverUnit->connect("off_unit", this, "FadeAway");
    _HoverUnit->connect("done", this, "_on_HoverUnit_done");
}

void SurvivalWheel::Update()
{
    // Only update when the Wheel is shown
    // Who's going to know if the wheel is hidden, anyway?
    if (!is_visible())
        return;

    auto profile = get_node<MindReadBank>("/root/MindReadBank")->Read(_controller, _hoveredUnit);

    // Sequentially grabs each needed attribute and update the wheels
    for (int iii=0; iii<_attributeNames.size(); ++iii)
    {
        const AttributeDynamic *attr = profile->Get<AttributeDynamic>(_attributeNames[iii]);

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
        }
    }
}

void SurvivalWheel::SetHoveredUnit(Unit* const hoveredUnit)
{
    if (_hoveredUnit)
    {
        _hoveredUnit->disconnect("attributes_modified", this, "Update");
    }

    _hoveredUnit = hoveredUnit;

    if (hoveredUnit)
    {
        set_visible(true);
        hoveredUnit->connect("attributes_modified", this, "Update");
        set_process(true);
    }
    else 
        set_process(false);
}

void SurvivalWheel::_on_HoverUnit_done(const InputHogger* const hogger)
{
    SetHoveredUnit(hogger->GetProfile()->GetPtr<Unit>());

    // TODO: >>>>>>>>>>
    Update();


    // Only start tweening if it's not fading
    if (_isFading)
    {
        _isFading = false;
        // Do another tweening does not stop Tween from fading the wheel
        // Which will bite us in _on_Tween_tween_completed() set_visible()
        _Tween->stop_all();
        // Set Transparency from Fully Transparent to Fully Opaque
        _Tween->interpolate_property(this, "modulate", get_modulate(), Color(1, 1, 1, 1), 0.4, Tween::TRANS_LINEAR, Tween::EASE_OUT_IN);
        _Tween->start();
    }
}

void SurvivalWheel::FadeAway()
{
    if (!_isFading)
    {
        _isFading = true;

        // Same stopping reason as in _on_HoverUnit_done()
        _Tween->stop_all();

        // Set Transparency from Fully Opaque to Fully Transparent
        _Tween->interpolate_property(this, "modulate", get_modulate(), Color(1, 1, 1, 0), 0.4, Tween::TRANS_LINEAR, Tween::EASE_IN_OUT);
        _Tween->start();
    }
}

void SurvivalWheel::_on_Tween_tween_completed()
{
    // Hide the bars if it's transparent
    // I think hiding will stop it from being rendered
    // Also stop it from following anyone
    if (get_modulate() == Color(1,1,1,0))
    {
        set_visible(false);
        SetHoveredUnit(nullptr);
    }
}