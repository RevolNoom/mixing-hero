#ifndef SLAP_HPP
#define SLAP_HPP

#include "Interaction.hpp"
#include "BaseEffect.hpp"
#include "Node.hpp"

class Slap: public Interaction
{
    GODOT_CLASS(Slap, Interaction)
public:
    static void _register_methods()
    {
        register_method("_on_PickManyUnit_done", &Slap::_on_PickManyUnit_done);
    }

    void _ready()
    {
        _effectToSource = get_node("EffectsToSource");
        _effectToTarget = get_node("EffectsToTarget");

        // Disables all InputHoggers
        auto inputhoggers = get_node("InputHoggers")->get_children();
        for (int iii=0; iii < inputhoggers.size(); ++iii)
        {
            cast_to<InputHogger>(inputhoggers[iii])->Enable(false);
        }
        
        // Connect Signals from InputHoggers to this
        get_node<InputHogger>("InputHoggers/PickManyUnit")->connect("done", this, "_on_PickManyUnit_done");
    }


    void Start(Unit* const performer, Unit* const target) override
    {
        _performer = performer;
        _target = target;
        emit_signal("request_input", this);

        get_node<InputHogger>("InputHoggers/PickManyUnit")->Enable(true);
    }


    virtual void Execute() override
    {
        Godot::print("Slap executes");
        auto target = get_node<InputHogger>("InputHoggers/PickManyUnit")->GetProfile()->Get<Profile>("0")->GetPtr<Unit>();
        
        auto _effectsToTarget = get_node("EffectsToTarget")->get_children();

        for (int iii=0; iii<_effectsToTarget.size(); ++iii)
        {
            target->AffectedBy(cast_to<BaseEffect>(_effectsToTarget[iii]));
        }

        auto _effectsToSource = get_node("EffectsToSource")->get_children();

        Godot::print(_performer? "Huh, Slap has performer" : "Slap Performer null");
        for (int iii=0; iii<_effectsToSource.size(); ++iii)
        {
            _performer->AffectedBy(cast_to<BaseEffect>(_effectsToSource[iii]));
        }
    }

// ==================
//  (missing banner) 
// ==================
    void _on_PickManyUnit_done(const InputHogger* const i)
    {
        emit_signal("exec_ready", this);
    }
};

#endif