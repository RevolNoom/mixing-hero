#include "unit.hpp"
#include "attribute.hpp"
#include "effect.hpp"
#include "attr_modify.hpp"
#include "survival_bars.hpp"
#include "arena.hpp"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<Unit>();
    godot::register_class<SurvivalBars>();
    godot::register_class<Attribute>();
    godot::register_class<AttributeDynamic>();

    godot::register_class<Arena>();

    godot::register_class<BaseEffect>();
    godot::register_class<EffectOvertime>();

    godot::register_class<Damage>();
    godot::register_class<Heal>();

}