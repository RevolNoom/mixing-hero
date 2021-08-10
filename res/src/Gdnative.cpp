// Whatever classes
#include "Profile.hpp"

// Manager classes
#include "Manager.hpp"
#include "InteractionManager.hpp"

// Unit related
#include "Unit.hpp"
#include "Attribute.hpp"

// GUI related
#include "InteractionWheel.hpp"
#include "SurvivalWheel.hpp"
#include "SurvivalBars.hpp"
#include "GUI.hpp"

// Effects related
#include "Effect.hpp"
#include "AttrModify.hpp"
#include "MindReading.hpp"

// Interaction related 
#include "InputSequence.hpp"
#include "Interaction.hpp"
#include "Pick.hpp"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    
    // Managers family
    godot::register_class<Manager>();
    godot::register_class<InteractionManager>();

    // Unit related
    godot::register_class<Unit>();
    godot::register_class<Profile>();
    godot::register_class<Attribute>();
    godot::register_class<AttributeDynamic>();

    // GUI related
    godot::register_class<GUI>();
    godot::register_class<SurvivalBars>();
    godot::register_class<SurvivalWheel>();
    godot::register_class<InteractionWheel>();


    // Effect related
    godot::register_class<BaseEffect>();
    godot::register_class<EffectOvertime>();

        // Mind Readings
        godot::register_class<MindReading>();
        godot::register_class<DivineInterrogation>();

        // Attributes modifying
        godot::register_class<Damage>();
        godot::register_class<Heal>();

    // Interaction related
    godot::register_class<Interaction>();
        // InputSequence family
        godot::register_class<InputSequence>();
        godot::register_class<Pick>();
        godot::register_class<PickUnit>();
        godot::register_class<PickPosition>();
        godot::register_class<PickSurvivalWheel>();
}