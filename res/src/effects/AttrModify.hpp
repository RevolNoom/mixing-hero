#ifndef ATTR_MODIFY_H
#define ATTR_MODIFY_H

#include "Effect.hpp"
class Unit;

namespace Effect
{
    
    /*
        Damage/Heal
        |_Node AffectedAttributeName1
        |_Node AffectedAttributeName2
        |_...

    */
    class Damage: public BaseEffect
    {
        GODOT_CLASS(Damage, BaseEffect)
        public:
            static void _register_methods();
            void _init();
            virtual void AffectOnUnit(Unit* const u) const override;
    };

    class Heal: public Damage
    {
        GODOT_CLASS(Heal, Damage)
        public:
            static void _register_methods();
            void _init();
            virtual void AffectOnUnit(Unit* const u) const override;
    };
} // namespace Effect

#endif // ATTR_DYN_MODIFY_H