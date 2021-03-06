#include "SurvivalBars.hpp"
#include "MindReadBank.hpp"
#include "Attribute.hpp"
#include "Label.hpp"
#include "Unit.hpp"

using namespace Effect;

// TODO: There should be some signals here
void SurvivalBarsLeft::SetController(Unit* const u)
{
    // Disconnect auto update signal from old controller
    if (_controller != nullptr)
        _controller->disconnect("attributes_modified", this, "Update");

    // Reconnect to new controller
    _controller = u;
    _controller->connect("attributes_modified", this, "Update");

    _connectedUnit = u;

    // Refresh the bars to show the infos of new controller
    Update();
}

void SurvivalBarsLeft::Update()
{
    // TODO: I might have to redo the logic here
    if (! (_connectedUnit && _connectedUnit->is_inside_tree() &&
             _controller && _controller->is_inside_tree()))
        return;

    // Self read
    auto profile = get_node<MindReadBank>("/root/MindReadBank")->Read(_controller, _connectedUnit);

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
}

// ===================
// R I G H T   B A R S
// ===================

void SurvivalBarsRight::SetController(Unit* const u)
{
    _controller = u;
    Update();
}

void SurvivalBarsRight::SetConnectedUnit(Unit* const u)
{
    if (_connectedUnit != nullptr)
        _connectedUnit->disconnect("attributes_modified", this, "Update");

    _connectedUnit = u;
    _connectedUnit->connect("attributes_modified", this, "Update");

    // 
    Update();
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