/*
    SURVIVAL WHEEL

    Show core stats of an unit.
    "Tween" controls showing animation

    SURVIVAL WHEEL
    |_ TextureProgress Health
    |_ TextureProgress Spirit
    |_ TextureProgress Stamina
    |_ InputHogger InputHogger
    |_ Tween Tween
*/

#ifndef SURVIVAL_WHEEL_HPP
#define SURVIVAL_WHEEL_HPP

#include <TextureProgress.hpp>
#include <PoolArrays.hpp>
#include <Control.hpp>
#include <Godot.hpp>
#include <Tween.hpp>

#include "Profile.hpp"
#include "HoverUnit.hpp"

using namespace godot;
class Unit;

// TODO: SurvivalWheel's glitchy when we move mouse in and out too quickly
class SurvivalWheel: public Control 
{
    GODOT_CLASS(SurvivalWheel, Control)
public:
    static void _register_methods();
    void _init();
    void _ready();
    void _process(float delta);

    // The Wheel will show info based on point of view of this Unit
    void SetViewer(Unit* const viewer) { _viewer = viewer;}

protected:
    // Show the wheel when you hover on the unit
    void _on_HoverUnit_done(const InputHogger* const hogger);

    void FadeAway();

    // If the wheel is transparent when tweening complete
    // Set visibility to false
    void _on_Tween_tween_completed();

    // Update the wheel values with this profile
    void Update(const Profile* const mindReadInfo);

private:

    Tween* _Tween;

    PoolStringArray _attributeNames;

    HoverUnit* _HoverUnit;

    // The Unit who is trying to see info of others
    Unit* _viewer;

    // The Wheel will try to follow this Unit 
    Unit* _hoveredUnit;

    // Test Variable to make sure I'm not starting
    // and stopping tween too many time
    // True if tween is fading or already hidden, false otherwise
    bool _isFading;
};

#endif