/*
    Survival Bars on top corner of the screen

    Display more detailed information of an unit

    There're only 2 instances of survival bars, 
    in contrast to survival wheel, in which each unit
    owns one

    Details of which unit is displayed is handled by GUI,
    this class provides the interface that GUI may need 
    to connect Units with the bars.

    I don't inherit this class from SurvivalWheel because
    their interfaces are mostly different. Their behaviours also.
*/

#ifndef SURVIVAL_BARS_H
#define SURVIVAL_BARS_H

#include <Godot.hpp>
#include <Control.hpp>
// TODO: Make animation smooth with Tweeeeeenie
//#include <Tween.hpp>
#include <TextureProgress.hpp>

class Profile;

using namespace godot;

class SurvivalBars: public Control
{
    GODOT_CLASS(SurvivalBars, Control)
    public:
    static void _register_methods();
    void _init();
    void _ready();

    // Display a profile. Whose profile? I don't care 
    void Display(const Profile* const p);

    private:

    // Consider adding a tween here. They're smooooooth
    // Tween* _tween;

    // The attributes this objects requires from a Profile
    PoolStringArray _attributes;
};

#endif