/*
    SURVIVAL BARS

    Is a child of an Unit

    Show three core stats of an unit: Health, Spirit, Stamina
    
    Three TextureProgress children "Health", "Spirit", "Stamina"

    Tween node "Tween" controls its visibility
*/

#ifndef SURVIVAL_BARS_H
#define SURVIVAL_BARS_H

#include <Godot.hpp>
#include <Control.hpp>
#include <Tween.hpp>

using namespace godot;

class SurvivalBars: public Control
{
    GODOT_CLASS(SurvivalBars, Control)
    public:
    static void _register_methods();
    void _init();
    void _ready();

    // Show the bars to the screen
    void Show();

    // Fade the bars from screen
    void FadeAway();

    // Set visibility to false
    void Hide();

    private:
    Tween* _tween;
};

#endif