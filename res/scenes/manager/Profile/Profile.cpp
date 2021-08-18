#include "Profile.hpp"

void Profile::_init()
{
}

void Profile::_register_methods()
{
    register_method("Add", &Profile::Add);
    register_method("Get", &Profile::Get<Node>);
    register_method("Store", &Profile::Store);
    register_method("Remove", &Profile::Remove);
}


void Profile::Add(const Node* info)
{
    this->add_child(info->duplicate());
}

void Profile::Steal(Node* const info)
{
    auto unfortunateParent = info->get_parent();
    if (unfortunateParent)
    {
        unfortunateParent->remove_child(info);
    }

    add_child(info);
}

void Profile::Remove(const NodePath nodepath)
{
    // Phelp, Luckily I read the docs
    // Removing child does not delete the child.
    // We must manually delete it with queue_free
    auto deletedNode = this->get_node(nodepath);
    this->remove_child(deletedNode);
    deletedNode->queue_free();
}

void Profile::Wipe()
{
    auto children = this->get_children();

    for (int iii = 0; iii<children.size(); ++iii)
    {
        auto info = cast_to<Node>(children[iii]);
        remove_child(info);
        info->queue_free();
    }

    _EasterEgg = Variant();
}