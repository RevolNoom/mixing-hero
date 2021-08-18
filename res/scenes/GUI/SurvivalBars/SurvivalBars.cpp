#include "SurvivalBars.hpp"
#include "Attribute.hpp"
#include "MindRead.hpp"
#include "Label.hpp"
#include "Unit.hpp"

using namespace Effect;

void SurvivalBarsLeft::Update(const Profile* const p)
{
    for (int iii=0; iii < _attributes.size(); ++iii)
    {
        // Get each info from Profile
        AttributeDynamic* attr = cast_to<AttributeDynamic>(p->Get((NodePath) _attributes[iii]));

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

void SurvivalBarsRight::_on_Pick_done(const InputHogger* const object)
{
    godot::Godot::print("RightBars");
    auto clickedUnit = cast_to<Unit>(object->GetProfile()->GetPtr<Object>());
    
    if (clickedUnit)
    {
        godot::Godot::print("It's an unit");
        MindRead* mr = MindRead::_new();

        mr->SetReader(_subject);
        clickedUnit->AffectedBy(mr);
        Update(mr->GetProfile());
    }
}