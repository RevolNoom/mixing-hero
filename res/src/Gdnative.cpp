#include "Attribute.hpp"
#include "Profile.hpp"
// Unit related
#include "Unit.hpp"

// GUI related
#include "Arena.hpp"
#include "gui.hpp"
#include "SurvivalWheel.hpp"
#include "SurvivalBars.hpp"

// Effects related
#include "Effect.hpp"
#include "AttrModify.hpp"
#include "MindRead.hpp"
#include "MindReadStrategy.hpp"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    // Base classes that are important but no one cares
    godot::register_class<Profile>();
    godot::register_class<Attribute>();
    godot::register_class<AttributeDynamic>();

    // Unit related
    godot::register_class<Unit>();

    // GUI related
    godot::register_class<GUI>();
    godot::register_class<SurvivalBars>();
    godot::register_class<SurvivalWheel>();

    godot::register_class<Arena>();

    // Effect related
    godot::register_class<BaseEffect>();
    godot::register_class<EffectOvertime>();

        // Mind Readings
        godot::register_class<MindRead>();
        godot::register_class<DefaultRead>();

        // Attributes modifying
        godot::register_class<Damage>();
        godot::register_class<Heal>();

}