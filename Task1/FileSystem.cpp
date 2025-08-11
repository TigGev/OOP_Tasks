#include "FileSystem.hpp"

std::string FileSystemNode::name() const {return m_name;}

void FileSystemNode::setParent(std::weak_ptr<Directory>& p) {parent = p;}

int File::getSize() const {return content.length();}

void File::display(std::ostream& os, int indentSize) const {
    os << std::string(indentSize, ' ') << "|-- [file] " << m_name << std::endl;
}

int Directory::getSize() const {
    int m_size = 0;
        for (auto p : children) {
            m_size += p->getSize();
        }
    return m_size;
}

void Directory::display(std::ostream& os, int indentSize) const {
    os << std::string(indentSize, ' ') << "|--" << " [dir] " << m_name << std::endl;
    for (auto ch : children) ch->display(os, indentSize + 3);
}

void Directory::addChild(const std::shared_ptr<FileSystemNode>& child) {
    std::weak_ptr<Directory> p = shared_from_this();
    child->setParent(p);
    children.push_back(child);
}

void Directory::removeChildByName(std::string chName) {
    auto ch = children.begin();
    for (; ch != children.end(); ++ch) {
        if ((*ch)->name() == chName) {
            children.erase(ch);
            break;
        }
    }
    if (ch == children.end()) throw std::runtime_error("Invalid child name");
}

