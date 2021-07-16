#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <Godot.hpp>
#include <Label.hpp>
#include <Node.hpp>

using namespace godot;

class Attribute: public Node
{
    GODOT_CLASS(Attribute, Node)

    public:
        static void _register_methods();

        Attribute();
        ~Attribute();
        virtual void _ready();
        virtual void _init();
        virtual void AddBase(int add);
        virtual void AddBonus(int add);
        virtual int GetBase() const;
        virtual int GetBonus() const;
        virtual int GetTotal() const;

    protected:
        int _base;
        int _bonus;
};

class AttributeDynamic: public Attribute
{
    GODOT_CLASS(AttributeDynamic, Attribute)
    public:

        AttributeDynamic();
        ~AttributeDynamic();
        static void _register_methods();
        void AddCurrent(int add);
        int GetCurrent() const;
        void _init();
        void _ready();

    protected:
        int _current;
};
#endif