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
#include <PoolArrays.hpp>


using namespace godot;
class Unit;
class Profile;

class SurvivalWheel: public Control 
{
    GODOT_CLASS(SurvivalWheel, Control)
public:
    static void _register_methods();
    void _init();
    void _ready();

    // Show the wheel to the screen
    // Should connect to unit's mouse entered signal
    void Show(const Profile* const p);


    // Fade the wheel from screen
    // Should connect to unit's mouse exited signal
    void FadeAway();

    // Things to do when tween finishes
    // If the wheel is transparent when tweening complete
    // Set visibility to false
    void CompletedTweening();

protected:
    // Update the wheel values with this profile
    // Should connect to unit's attributes_modified signal
    void Update(const Profile* const p);

private:
    Tween* _tween;
    PoolStringArray _attributeNames;

    // Test Variable to make sure I'm not starting
    // and stopping tween too many time
    // True if tween is fading or already hidden, false otherwise
    bool _isFading;
};

#endif