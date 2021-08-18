// Whatever classes
#include "Profile.hpp"

// Manager classes
#include "Manager.hpp"
#include "ManagerInteraction.hpp"
#include "MIState.hpp"
#include "StateChooseInteraction.hpp"

// Unit related
#include "Unit.hpp"
#include "Attribute.hpp"

// GUI related
#include "InteractionWheel.hpp"
#include "SurvivalWheel.hpp"
#include "SurvivalBars.hpp"
#include "GUI.hpp"

// Effects related
#include "BaseEffect.hpp"
#include "EffectOvertime.hpp"
#include "AttributeModify.hpp"
#include "MindRead.hpp"

// InputHogger Family
#include "InputHogger.hpp"
#include "Pick.hpp"
#include "PickMany.hpp"
#include "PickManyUnit.hpp"
#include "PickManyPosition.hpp"
#include "HoverUnit.hpp"

// Interaction related 
#include "Interaction.hpp"
#include "PickMany.hpp"
#include "Slap.hpp"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

// TODO: Create Family headers file with RegisterFamily macros

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    
    // Managers family
    godot::register_class<Manager>();
    godot::register_class<ManagerInteraction>();
    godot::register_class<MIState>();
    godot::register_class<StateChooseInteraction>();

    // InputHogger family
    godot::register_class<InputHogger>();
    godot::register_class<Pick>();
    godot::register_class<PickMany>();
    godot::register_class<PickManyUnit>();
    godot::register_class<PickManyPosition>();
    godot::register_class<HoverUnit>();

    // Unit related
    godot::register_class<Unit>();
    godot::register_class<Profile>();
    godot::register_class<Attribute>();
    godot::register_class<AttributeDynamic>();

    // GUI related
    godot::register_class<GUI>();
    godot::register_class<SurvivalWheel>();
    godot::register_class<InteractionWheel>();
    godot::register_class<SurvivalBarsLeft>();
    godot::register_class<SurvivalBarsRight>();

    // Effect related
    godot::register_class<BaseEffect>();
    godot::register_class<EffectOvertime>();

        // Mind Readings
        godot::register_class<MindRead>();
        godot::register_class<DivineInterrogation>();

        // Attributes modifying
        godot::register_class<Heal>();
        godot::register_class<Damage>();

    // Interaction related
    godot::register_class<Interaction>();
    godot::register_class<Slap>();
}