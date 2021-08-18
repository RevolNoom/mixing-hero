/*
    Survival Bars on top corner of the screen

    Display more detailed information of an unit

    SurvivalBarsLeft
    |_ TextureProgress Health
        |_ Label Label
    |_ TextureProgress Spirit
        |_ Label Label
    |_ TextureProgress Stamina 
        |_ Label Label
    |_ TextureRect TextureRect
*/

#ifndef SURVIVAL_BARS_HPP
#define SURVIVAL_BARS_HPP

#include <TextureProgress.hpp>
#include <Control.hpp>
#include <Godot.hpp>
// TODO: Make animation smooth with Tweeeeeenie
//#include <Tween.hpp>

#include "Profile.hpp"
#include "Pick.hpp"
using namespace godot;
class Unit;

// TODO: Implement this when you figure out the MindRead cache
class SurvivalBarsLeft: public Control
{
    GODOT_CLASS(SurvivalBarsLeft, Control)
public:
    static void _register_methods()
    {
        register_method("_ready", &SurvivalBarsLeft::_ready);
    }
    virtual void _ready(){}
    virtual void _init()
    {
        // The order of attributes ARE IMPORTANT
        // (not at the moment, but in the future (i think?))
        // Don't mess them up
        _attributes.append("Health");
        _attributes.append("Spirit");
        _attributes.append("Stamina");
    }

    // Get a Profile holding info of an Unit
    // Update the bars to reflect the info 
    virtual void Update(const Profile* const unitProfile);

protected:

    // Consider adding a tween here. They're smooooooth
    // Tween* _Tween;

    // The Bars are bound to this unit
    Unit* _subject;

    // The attributes this objects requires from a Profile
    PoolStringArray _attributes;
};


/*
    SURVIVAL BARS RIGHT

    These bars show info of the unit you PickMany on

    SurvivalBarsRight
    |_ (all the nodes of SurvivalBarsLeft)
    ...
    |_ PickObject PickObject
*/
class SurvivalBarsRight: public SurvivalBarsLeft
{
    GODOT_CLASS(SurvivalBarsRight, SurvivalBarsLeft)

public:

    static void _register_methods()
    {
        register_method("_on_Pick_done", &SurvivalBarsRight::_on_Pick_done);
    }

    virtual void _ready()
    {
        _Pick = get_node<Pick>("Pick");
        _Pick->connect("done", this, "_on_Pick_done");
    }


    void _on_Pick_done(const InputHogger* const unitPath);

protected:
    
    Pick* _Pick;
};
#endif