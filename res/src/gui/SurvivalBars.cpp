#include "SurvivalBars.hpp"
#include "Attribute.hpp"
#include "Profile.hpp"
#include "Label.hpp"

void SurvivalBars::_register_methods()
{

}

void SurvivalBars::_init()
{
    // The order of attributes ARE IMPORTANT
    // (not at the moment, but in the future (i think?))
    // Don't mess them up
    _attributes.append("Health");
    _attributes.append("Spirit");
    _attributes.append("Stamina");
}

void SurvivalBars::_ready()
{}

void SurvivalBars::Display(const Profile* const p)
{
    for (int iii=0; iii < _attributes.size(); ++iii)
    {
        // Get each info from Profile
        AttributeDynamic* attr = cast_to<AttributeDynamic>(p->get_node_or_null((NodePath) _attributes[iii]));

        // The progress bar of the attribute we're working on
        TextureProgress* tp = cast_to<TextureProgress>(get_node_or_null((NodePath) _attributes[iii]));

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
