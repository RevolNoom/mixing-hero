/*
    - Effects are the ONLY way to communicate with an Entity

    - Want your Entity to do something? Make a new Effect. 

    - Cause different behaviors on different object type (Visitor)

    ALL EFFECTS <<NEVER>> DO OPPOSITE AS THEY SAY
    i.e. Heal(-100) does not deal 100 damage instead of Healing
    Heal(-100) will heal 0 health. 
*/

#ifndef EFFECT_H
#define EFFECT_H

#include <algorithm>
#include <Godot.hpp>
#include <Node.hpp>

using namespace godot;
class Unit;

namespace Effect
{
    /*
        ABSTRACT CLASS, THE FATHER OF ALL EFFECTS

        Instead of doing Flyweight (let Effect holds no extrinsic state)
        I decided that letting each effect holds "_intensity"
        will be useful when it comes to EffectOvertime

        (When a stat-modifying EffectOvertime takes effect, it remembers
        how much _intensity it has taken/granted, so that it may returns it
        when the effect ends.)
    */
    class BaseEffect: public Node
    {
        GODOT_CLASS(BaseEffect, Node)
        friend class Unit;
    public:
        static void _register_methods();
        virtual void _init();

        // POINTERS TROUBLE! :>
        // const T* ptr: You can't modify the value through ptr (*ptr=someT raises error)
        // T* const ptr: You can't point ptr to other address (ptr = otherTAddress raises error)         

        // Visitor function. Perform effect e on "this" current effect
        virtual void AffectedBy(const BaseEffect* const e);

        // Every effect has do-nothing for default behaviour
        // when affecting other objects
        // virtual bool IsType(Type type) const;
        virtual void AffectOnUnit(Unit* const u) const;
        virtual void AffectOnEffect(BaseEffect* const e) const; 


        // Not yet implemented
        //void AffectOnItem(Item *e);
        //void AffectOnAction(Action *e);
        //void AffectOnEnvironment(Environment *e);
    
    protected:
        // Returns the intensity of current effect
        // Is never less than zero
        virtual int GetIntensity() const;

        // Add to the intensity of current effect
        // Can never drops below zero
        virtual void AddIntensity(const int intensity);

    private:
        int _intensity;
    };

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
}
#endif