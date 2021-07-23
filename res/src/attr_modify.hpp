#ifndef ATTR_MODIFY_H
#define ATTR_MODIFY_H

#include "effect.hpp"
#include "unit.hpp"
#include "attribute.hpp"

namespace Effect
{
    
    class Damage: public BaseEffect
    {
        GODOT_CLASS(Damage, BaseEffect)
        public:
            static void _register_methods();
            virtual void _init() override;
            virtual void AffectOnUnit(Unit* const u) const override;
            virtual String GetAffectedAttributeName() const;

        private:
            String _affectedAttrName;
    };

    class Heal: public Damage
    {
        GODOT_CLASS(Heal, Damage)
        public:
            static void _register_methods();
            virtual void AffectOnUnit(Unit* const u) const override;
    };
} // namespace Effect

#endif // ATTR_DYN_MODIFY_H