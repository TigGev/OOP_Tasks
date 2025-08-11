#ifndef FILE_SYSTEM_HEADER
#define FILE_SYSTEM_HEADER
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <stdexcept>

class Directory;

class FileSystemNode {
    protected:
        std::weak_ptr<Directory> parent;
        std::string m_name;
    public:
        FileSystemNode(const std::string& name, std::weak_ptr<Directory> p) : parent(p), m_name(name) {}
        virtual int getSize() const = 0;
        virtual void display(std::ostream& os, int indent = 0) const = 0;
        std::string name() const;
        void setParent(std::weak_ptr<Directory>& p);
        virtual ~FileSystemNode() = default;
};

class File : public FileSystemNode {
        std::string content;
    public:
        File(const std::string& name, std::weak_ptr<Directory> p, std::string fileContent = "")
            : FileSystemNode(name, p), content(fileContent) {}
        int getSize() const override;
        void display(std::ostream& os, int indent = 0) const override;
};

class Directory : public FileSystemNode, public std::enable_shared_from_this<Directory> {
        std::vector<std::shared_ptr<FileSystemNode>> children;
    public:
        Directory(const std::string& name, std::weak_ptr<Directory> p = std::weak_ptr<Directory>())
            : FileSystemNode(name, p) {}
        int getSize() const override;
        void display(std::ostream& os, int indent = 0) const override;
        void addChild(const std::shared_ptr<FileSystemNode>& child);
        void removeChildByName(std::string chName);
};
#endif