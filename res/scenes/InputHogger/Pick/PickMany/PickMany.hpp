/*
    PickMany'S FAMILY

    A PickMany deals with mouse action, whether it be mouse PickMany
    or mouse motion.

    When the mouse moved/PickManyed something of interest, the PickMany
    builds its profile. It signals "done"
*/

#ifndef PickMany_HPP
#define PickMany_HPP


#include "Pick.hpp"

// THIS CLASS SERVES AS AN ABSTRACT cLASS
// IT'S NOT INTENDED TO BE INSTANTIATED
class PickMany: public Pick 
{
    GODOT_CLASS(PickMany, Pick)

public:
    static void _register_methods()
    {
        register_property("PickAmount", &PickMany::_PickAmount, 0);

        register_method("IsFull", &PickMany::IsFull);
        register_method("SetPickAmount", &PickMany::SetPickAmount);
    }

    // Return true when it cannot accept input anymore
    virtual bool IsFull() const { return _Profile->get_child_count() == _PickAmount; }


    // Reset() and set PickAmount
    // Note: PickAmount value will not be less than 0
    // Set PickAmount = 0 equals to disabling this PickMany 
    void SetPickAmount(int PickAmount)    
    {
        Reset();
        _PickAmount = PickAmount < 0? 0 : PickAmount;
    }


protected:

    // The amount of objects needed picking
    int _PickAmount;
};



#endif