/*
    SURVIVAL BARS

    Is a child of an Unit

    Show three core stats of an unit: Health, Spirit, Stamina
    
    Three TextureProgress children "Health", "Spirit", "Stamina"

    Tween node "Tween" controls its visibility
*/

#ifndef SURVIVAL_WHEEL_H
#define SURVIVAL_WHEEL_H

#include <Godot.hpp>
#include <Control.hpp>
#include <Tween.hpp>
#include <TextureProgress.hpp>

using namespace godot;

class Unit;

class SurvivalWheel: public Control
{
    GODOT_CLASS(SurvivalWheel, Control)
    public:
    static void _register_methods();
    void _init();
    void _ready();

    // Show the wheel to the screen
    void Show();

    // Fade the wheel from screen
    void FadeAway();

    // Update the wheel when parent Unit's stats change
    // Note that this update will be deferred until
    // the wheel is visible, so don't trust the attributes
    // these survival wheel store 
    void Update(const Unit* const u);

    // Things to do when tween finishes
    // If the wheel is transparent when tweening complete
    // Set visibility to false
    void CompletedTweening();

    private:

    // Here's where the wheel are actually updated
    void _RealUpdate(const Unit* const u);
    const Unit* _unitWithStatsChanged;

    Tween* _tween;
    TextureProgress *_health, *_spirit, *_stamina;

};

#endif