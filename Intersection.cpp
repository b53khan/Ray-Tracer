#include "Intersection.hpp"
#include "SceneNode.hpp"
#include "GeometryNode.hpp"

Texture* Intersection::getTexture() {
    if (this->node->m_nodeType == NodeType::GeometryNode) {
        auto node = dynamic_cast<GeometryNode*>(this->node);
        // std::cout << node->m_texture->filename;
        return node->m_texture;
    } else {
        return nullptr;
    }
}