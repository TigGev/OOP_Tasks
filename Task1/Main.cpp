#include "FileSystem.hpp"
#include <memory>
#include <iostream>

int main() {
    auto root = std::make_shared<Directory>("root");

    auto file1 = std::make_shared<File>("file1.txt", root, "Hello, world!");
    root->addChild(file1);

    auto subdir = std::make_shared<Directory>("subdir", root);
    root->addChild(subdir);

    auto file2 = std::make_shared<File>("file2.txt", subdir, "This is a test file.");
    subdir->addChild(file2);

    root->display(std::cout);

    std::cout << "Total size: " << root->getSize() << " bytes" << std::endl;

    try {
        root->removeChildByName("file1.txt");
        std::cout << "file1.txt removed from root" << std::endl;
        root->display(std::cout);
        std::cout << "Total size after removal: " << root->getSize() << " bytes" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Deleting error: " << e.what() << std::endl;
    }

    return 0;
}
