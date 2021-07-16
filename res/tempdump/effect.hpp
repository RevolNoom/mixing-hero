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

#include <memory>
#include <functional>
#include <algorithm>
#include <deque>
#include <Godot.hpp>

#include "unit.hpp"
//#include "entity.hpp"

using namespace godot;

namespace Effect
{
    enum class Type
    {
        BUFF,
        DEBUFF,
        HEAL,
        DAMAGE,
        SHIELD,

        PHYSICAL,
        MENTAL,
        STAMINA
    };

    /*
        ABSTRACT CLASS, THE FATHER OF ALL EFFECTS

        Instead of doing Flyweight (let Effect holds no extrinsic state)
        I decided that letting each effect holds "_intensity"
        will be useful when it comes to EffectOvertime

        (When a stat-modifying EffectOvertime takes effect, it remembers
        how much _intensity it has taken/granted, so that it may returns it
        when the effect ends.)
    class Effect
    {
    friend class Unit;
    public:
        // Every effect has do-nothing for default behaviour
        virtual bool IsType(Type type) const;
        virtual void AffectOnUnit(Unit &u) const {}
        virtual void AffectOnEffect(Effect &e) const {}
        
        virtual void AffectedBy(Effect &e) 
        {
            e.AffectOnEffect(*this);
        }

        // Not yet implemented
        //void AffectOnItem(Item *e);
        //void AffectOnAction(Action *e);
        //void AffectOnEnvironment(Environment *e);
        Effect(){}

        Effect(int intensity): _intensity(intensity)
        {
        }

    private:
        int _intensity;
    };


    template <Unit::ATTRIBUTE ATTR_TYPE>
    class Empower: public Effect
    {
        public:
            // Inherit ALL Effect constructors
            // "It'll be fine!" - I thought
            //using Effect::Effect;

            virtual void AffectOnUnit(Unit &u) const override;
            virtual bool IsType(Type type) const {return type == Type::BUFF;}
    };

    template <Unit::ATTRIBUTE ATTR_TYPE>
    class Weaken: public Effect
    {
        public:
            //using Effect::Effect;

            virtual void AffectOnUnit(Unit &u) const override;
            virtual bool IsType(Type type) const {return type == Type::DEBUFF;}
    };

    template <Unit::ATTRIBUTE_DYNAMIC ATTR_TYPE>
    class Heal: public Effect
    {
        public:
            //using Effect::Effect;

            virtual void AffectOnUnit(Unit &u) const override;
            virtual bool IsType(Type type) const {return type == Type::HEAL;}
    };

    template <Unit::ATTRIBUTE_DYNAMIC ATTR_TYPE>
    class Damage: public Effect
    {
        public:
            //using Effect::Effect;
            Damage(int intensity): Effect(intensity){}

            virtual void AffectOnUnit(Unit &u) const override;
            virtual bool IsType(Type type) const {return type == Type::DAMAGE;}
    };

/*
    namespace Misc
    {
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