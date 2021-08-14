/*
    PROFILE CLASS

    This is a messenger class. 

    When objects need to communicate with each other (Insiders),
    the sender will create a Profile and send it to the receiver.
    The Insiders will both agree on what and how the Profile 
    stores their communication.

    A Profile holds many nodes. Of which type is of no concern
    to Outsiders and Profile itself.

    A Profile also keeps a Variant. Let's call it EasterEgg. 
    No one knows what it actually is except the Insiders.

    HOW TO USE A PROFILE:
    + Modify it freely if you are the creator (who needs
        to send something)
    + Readonly if you are a receiver
    + Profile is an upgraded-to-node Variant. 
        Basically, you may think of adding a Profile 
        to a scene as appending a Variant.
    + Profile is NOT responsible for deleting Variant object.
        If you somehow make a _new() node and add it to Variant, don't!
        _new() and then Profile.Steal() instead

    Profile 
    |_ Node
    |_ Node
    |_ ...
*/

#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <Variant.hpp>
#include <Godot.hpp>
#include <Node.hpp>

using namespace godot;

class Profile: public Node
{
    GODOT_CLASS(Profile, Node)
public:

    static void _register_methods();
    void _init();

    // Duplicate info to this Profile
    void Add(const Node* info);

    // Remove info node from parent (if any)  
    // and then add this node to Profile
    // (Move semantic)
    void Steal(Node* const info);

    // Remove an info from this Profile
    void Remove(const NodePath infoName);

    // Remove all infos on this Profile
    void Wipe();

    // Ask for info, and I'll tell you what I know
    template <class T = Node>
    const T* Get(const String nodepath) const
    {
        return cast_to<T>(get_node_or_null((String) nodepath));
    }


    // Store a Variant to Profile
    void Store(Variant v) {_EasterEgg = v;}
    // Get the Variant this Profile holds
    Variant Get() const {return _EasterEgg;}

    // Store a Pointer to Profile
    // Be VERY CAREFUL when use Profile to store pointers!
    template <typename T>
    void Store(T* aRandomPointerFellFromTheSky)
    {
        Store(reinterpret_cast<size_t>(aRandomPointerFellFromTheSky));
    }

    /*
        <!> E X T R E M E L Y  D A N G E R O U S <!>
    
        Explicit cast Profile to a random pointer type
        CONSULT your Sender for the EXACT object type

        I'm not responsible for the following, but not
        limited to your game breaking down, vomitting,
        hallucinating, tripping all over, gut spilling
        everywhere, destroying operating system,...
    */
    template <typename ExactType>
    ExactType* GetPtr() const {return reinterpret_cast<ExactType*>((size_t)(_EasterEgg));}
    
protected:
    Variant _EasterEgg;
};

#endif