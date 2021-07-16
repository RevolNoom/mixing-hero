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
        void _ready();
        void _init();
        void AddBase(int add);
        void AddBonus(int add);
        int GetBase() const;
        int GetBonus() const;
        int GetTotal() const;

    protected:
        int _base;
        int _bonus;
};

class AttributeDynamic: public Attribute
{
    GODOT_CLASS(Attribute, Node)
    public:

        static void _register_methods()
        {
            /*
            register_property("Base", AttributeDynamic::_base, 10);
            register_property("Bonus", AttributeDynamic::_bonus, 10);
            register_property("Current", AttributeDynamic::_current, 10);

            register_method("AddBase", AttributeDynamic::AddBase);
            register_method("AddBonus", AttributeDynamic::AddBonus);
            register_method("GetBase", AttributeDynamic::GetBase);
            register_method("GetBonus", AttributeDynamic::GetBonus);
            */
            register_method("AddCurrent", &AttributeDynamic::AddBase);
            register_method("GetCurrent", &AttributeDynamic::AddBonus);
        }
        void _init()
        {
            _base = 10;
            _bonus = 0;
            _current = 10;
        }

        void AddCurrent(int add)
        {
            _current += add;
            if (_current < 0) _current = 0;
            int max = GetTotal();
            if (_current > max) _current = max;
        }

        int GetCurrent() const
        {
            return _current < 0 ? 0 : _current;
        }

    protected:
        int _current;

};

#endif