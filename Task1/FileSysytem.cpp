#ifndef FILE_SYSTEM_HEADER
#define FILE_SYSTEM_HEADER
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class FileSystemNode {
    protected:
        std::string m_name;
        int m_size;
    public:
        FileSystemNode(int size, std::string name) : m_size(size), m_name(name) {}
        virtual int getSize() const = 0;
        virtual void display() const = 0;
};

class File : public FileSystemNode {
    public:
        File(int fileSize, std::string name) : FileSystemNode(fileSize, name) {}
        virtual int getSize() const override {return m_size;}
        virtual void display() const override {std::cout << m_name << std::endl;}
};

class Directory : public FileSystemNode {
        std::vector<std::shared_ptr<FileSystemNode>> m_elements;
    public:
        Directory(std::string name, std::vector<std::shared_ptr<FileSystemNode>> elements)
          : FileSystemNode(0, name), m_elements(elements) {
            for (auto p : elements) {
                m_size += p->getSize();
            }
        }
        virtual int getSize() const override {
            return m_size;
        }
        virtual void display() const override {std::cout << m_name << std::endl;}
};
#endif