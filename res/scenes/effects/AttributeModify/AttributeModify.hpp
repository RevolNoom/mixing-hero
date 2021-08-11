#ifndef ATTRIBUTE_MODIFY_HPP
#define ATTRIBUTE_MODIFY_HPP

#include "BaseEffect.hpp"
class Unit;
class AttributeDynamic;

namespace Effect
{
    
    /*
        Heal
        |_Node AffectedAttributeName1
        |_Node AffectedAttributeName2
        |_...

    */
    class Heal: public BaseEffect 
    {
        GODOT_CLASS(Heal, BaseEffect)
    public:
        static void _register_methods();
        void _init();
        virtual void AffectOnUnit(Unit* const u) const override;
    protected:
        // Since Damage and Heal differ only on increasing/decreasing Attribute value
        // So, AffectOnUnit() calls this hook function to reduce duplicate code
        // This is where Heal/Damage actually does its most important job
        virtual void ModifyAttribute(AttributeDynamic* const affectedAttribute) const;

    };

    /*
        Damage
        |_Node AffectedAttributeName1
        |_Node AffectedAttributeName2
        |_...
    */
    class Damage: public Heal
    {
        GODOT_CLASS(Damage, Heal)
    public:
        static void _register_methods();
        void _init();
    protected:
        // See Effect::Heal for more details
        virtual void ModifyAttribute(AttributeDynamic* const affectedAttribute) const override;
    };

} // namespace Effect

#endif // ATTRIBUTE_MODIFY_HPP