#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <Godot.hpp>
#include <Node.hpp>
#include <Math.hpp>

using namespace godot;

class Attribute: public Node
{
    GODOT_CLASS(Attribute, Node)

    public:
        static void _register_methods();

        void _init();
        virtual void _ready();

        // Add an amount to base attribute
        // Clamped to be non-negative 
        virtual void AddBase(int add);
        // Add an amount to bonus attribute
        virtual void AddBonus(int add);

        int GetBase() const;
        int GetBonus() const;
        // Return the total sum of base and bonus
        // Clamped to be non-negative
        int GetTotal() const;

    protected:
        int _base;
        int _bonus;
};

class AttributeDynamic: public Attribute
{
    GODOT_CLASS(AttributeDynamic, Attribute)
    public:
        void _init();
        void _ready();

        static void _register_methods();

        // Add an amount to base attribute
        // Clamped to be non-negative 
        // Also clamp Attribute's Value to between 0 and max
        void AddBase(int add) override;

        // Add an amount to bonus attribute
        // Also clamp Attribute's Value to between 0 and max
        void AddBonus(int add) override;

        // Add an amount to current value
        // Clamped between 0 and max() 
        void AddValue(int add);

        int GetValue() const;
        int GetMax() const;

    protected:
        int _value;
};
#endif