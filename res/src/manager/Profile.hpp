/*
    PROFILE CLASS

    Units who wish to display their info on the GUI will pass 
    a Profile object to the GUI component

    The GUI component reads the profile and decide how to display
    the info

    An Unit Constructs a profile by adding nodes to the Profile.
    Units and GUI components must both agree on how the nodes are named,
    what the nodes' types are, so that the GUI components know how to
    read that Profile correctly.
*/

#ifndef PROFILE_H
#define PROFILE_H

#include <Godot.hpp>
#include <Node.hpp>

using namespace godot;

class Profile: public Node
{
    GODOT_CLASS(Profile, Node)
    public:

    static void _register_methods();
    void _init();

    // Add a duplicated node (info) to this Profile
    void AddInfo(const Node* info);

    // Remove node (info) from this Profile
    void RemoveInfo(const NodePath nodepath);

    // Remove all infos on this Profile
    void WipeClean();

    // Ask for info, and I'll tell you what I know
    const Node* GetInfo(const NodePath nodepath) const;
};

#endif