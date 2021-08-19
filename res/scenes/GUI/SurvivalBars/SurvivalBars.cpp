#include "SurvivalBars.hpp"
#include "Attribute.hpp"
#include "MindRead.hpp"
#include "Label.hpp"
#include "Unit.hpp"

using namespace Effect;

// TODO: There should be some signals here
void SurvivalBarsLeft::SetController(Unit* const u)
{
    _controller = u;
    Update();
}

void SurvivalBarsLeft::Update()
{
    Update(_controller);
}

void SurvivalBarsLeft::Update(Unit* const p)
{
    if (!p)
        return;

    MindRead* mr = MindRead::_new();

    mr->SetReader(_controller);
    p->AffectedBy(mr);
    auto profile = mr->GetProfile();

    for (int iii=0; iii < _attributes.size(); ++iii)
    {
        // Get each info from Profile
        AttributeDynamic* attr = profile->Get<AttributeDynamic>((NodePath) _attributes[iii]);

        // The progress bar of the attribute we're working on
        TextureProgress* tp = cast_to<TextureProgress>(get_node((NodePath) _attributes[iii]));

        // The numbers that appear on the bar
        Label* stat = cast_to<Label>(tp->get_node("Label"));

        if (attr)
        {
            tp->set_max(attr->GetMax());
            tp->set_value(attr->GetValue());

            stat->set_text(String::num_int64(attr->GetValue()) + String(" / ") + String::num_int64(attr->GetMax()));
        }
        else
        {
            // Let the bar shows 100% full 
            tp->set_max(1);
            tp->set_value(1);

            // And let the label shows nothing
            stat->set_text("");
        }
    }

    mr->queue_free();
}

// ===================
// R I G H T   B A R S
// ===================

// TODO: There should be some signals here
void SurvivalBarsRight::SetController(Unit* const u)
{
    _controller = u;
}

// TODO: There should be some signals here
void SurvivalBarsRight::SetConnectedUnit(Unit* const u)
{
    _connectedUnit = u;
    Update();
}

void SurvivalBarsRight::Update()
{
    // why... why must I explicitly refers to the base class?
    SurvivalBarsLeft::Update(_connectedUnit);
}

void SurvivalBarsRight::_on_Pick_done(const InputHogger* const object)
{
    auto clickedUnit = cast_to<Unit>(object->GetProfile()->GetPtr<Object>());
    
    if (clickedUnit && 
        clickedUnit != _controller && 
        clickedUnit != _connectedUnit)
    {
        SetConnectedUnit(clickedUnit);
        Update();
    }
}