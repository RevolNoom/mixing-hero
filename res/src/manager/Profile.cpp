#include "Profile.hpp"

void Profile::_init()
{
}

void Profile::_register_methods()
{
    register_method("AddInfo", &Profile::AddInfo);
    register_method("RemoveInfo", &Profile::RemoveInfo);
    register_method("GetInfo", &Profile::GetInfo);
}


void Profile::AddInfo(const Node* info)
{
    this->add_child(info->duplicate());
}

void Profile::RemoveInfo(const NodePath nodepath)
{
    // Phelp, Luckily I read the docs
    // Removing child does not delete the child.
    // We must manually delete it with queue_free
    auto deletedNode = this->get_node(nodepath);
    this->remove_child(deletedNode);
    deletedNode->queue_free();
}

const Node* Profile::GetInfo(const NodePath nodepath) const
{
    return this->get_node_or_null(nodepath);
}

void Profile::WipeClean()
{
    auto children = this->get_children();

    for (int iii = 0; iii<children.size(); ++iii)
    {
        auto info = cast_to<Node>(children[iii]);
        remove_child(info);
        info->queue_free();
    }
    
}