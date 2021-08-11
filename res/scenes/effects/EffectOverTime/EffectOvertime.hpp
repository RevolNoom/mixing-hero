#ifndef EFFECT_OVERTIME_HPP
#define EFFECT_OVERTIME_HPP

#include "BaseEffect.hpp"

namespace Effect
{
    /*
        EFFECT OVERTIME:
        Keep children nodes of type Effect. 

        When invoked, EffectOvertime creates and passes some Effect
        with _intensity it manages to the affected entity

    */
    class EffectOvertime: public BaseEffect
    {
        GODOT_CLASS(EffectOvertime, BaseEffect)
    public:
        static void _register_methods();
        virtual void _init() override;

        virtual void AffectedBy(const BaseEffect* const e);

        // virtual bool IsType(Type type) const;
        virtual void AffectOnUnit(Unit* const u) const;
        virtual void AffectOnEffect(BaseEffect* const e) const; 

        // Not yet implemented
        //void AffectOnItem(Item *e);
        //void AffectOnAction(Action *e);
        //void AffectOnEnvironment(Environment *e);

    protected:
        // Returns the potency of current effect overtime
        // Is never less than zero
        virtual int GetPotency() const;

        // Add to the potency of current effect overtime
        // Can never drops below zero
        virtual void AddPotency(const int potency);
        
    private:
            int _potency;
    };
}
/*
    class Empower: public Effect
    {
        GODOT_CLASS(Empower, Effect)
        public:
            static void _register_methods();

            virtual void AffectOnUnit(Unit &u) const override;
            //virtual bool IsType(Type type) const {return type == Type::BUFF;}
        
        private:
            String _affectedAttribute;
    };

/*
    template <Unit::ATTRIBUTE ATTR_TYPE>
    class Weaken: public Effect
    {
        public:
            //using Effect::Effect;

            virtual void AffectOnUnit(Unit &u) const override;
            virtual bool IsType(Type type) const {return type == Type::DEBUFF;}
    };



    namespace Misc
    {
        class Mystify; // Hide the real effect in a bunch of innocent ones
        class ShieldPhysical;
        class ShieldMental;
        class Root;
        class Stun;
        class Blind;
        class Blink;
        class Invisible;
        class Invincible;
    }
*/
#endif