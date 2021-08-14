#ifndef SLAP_HPP
#define SLAP_HPP

#include "Interaction.hpp"
#include "Node.hpp"

class Slap: public Interaction
{
    GODOT_CLASS(Slap, Interaction)
public:
    static void _register_methods()
    {}

    virtual void _ready()
    {
        /*
        _effectToSource = get_node("EffectsToSource");
        _effectToTarget = get_node("EffectsToTarget");
        _InputHogger = get_node<InputHogger>("ClickUnit");

        _InputHogger->connect("hogged_full", this, "ReadyToExecute");
        */
    }

    virtual void Execute(Unit* const source)
    {
        /*
        auto profile = _InputHogger->GetProfile();
        
        auto effectsToTarget = get_node("EffectsToTarget")->get_children();

        for (int iii=0; iii<effectsToTarget.size(); ++iii)
        {
        }

        auto effectsToSource = get_node("EffectsToSource")->get_children();

        for (int iii=0; iii<effectsToSource.size(); ++iii)
        {
            source->AffectedBy(cast_to<BaseEffect>(effectsToSource[iii]));
        }
        */
    }
};

#endif