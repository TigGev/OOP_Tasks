#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <typeinfo>

class UIComponent {
    public:
        virtual ~UIComponent() = default;
        virtual void draw() const = 0;
        virtual  void onClick() = 0;
        virtual std::unique_ptr<UIComponent> clone() const = 0;
};

class Button : public UIComponent {
        std::string name;
    public:
        Button(const std::string& button_name) : name(button_name) {}
        void draw() const override {
            std::cout << "| "  << name << " |" << std::endl;
        }
        void onClick() override {
            //any logic;
            std::cout << "pressing the button -> | " << name << " |" << std::endl;
        }
        std::unique_ptr<UIComponent> clone() const override {
            return std::make_unique<Button>(*this);
        }
        
};

class Checkbox : public UIComponent {
        char symb;
        bool flag;
    public:
        Checkbox(const char ch) : symb(ch), flag(false) {}
        void draw() const override {
            std::cout << "-|" << (flag ? symb : ' ') << "|-" << std::endl;
        }
        void onClick() override {
            flag ^= 1;
            std::cout << "Changeing checkbox -> -|" << (flag ? symb : ' ') << "|-" << std::endl;
        }
        std::unique_ptr<UIComponent> clone() const override {
            return std::make_unique<Checkbox>(*this);
        }

};
class TextField : public UIComponent {
        std::string text;
    public:
        TextField() : text("") {}
        void draw() const override {
            std::cout << "[ " << text << " ]" << std::endl;
        }
        void onClick() override {
            std::cout << "Please etnter the text: ";
            std::getline(std::cin, text);
        }
        std::unique_ptr<UIComponent> clone() const override {
            return std::make_unique<TextField>(*this);
        }
};

class GUImanager {
        std::vector<std::unique_ptr<UIComponent>> components;
    public:
        void addComponent(const UIComponent& newComponent) {
            components.push_back(newComponent.clone());
        }
        void drawLayout() const {
            std::cout << "Buttons: " << std::endl;
            for (const auto& c : components) {
                if(dynamic_cast<Button*>(c.get())) c->draw();
            }
            std::cout << "Checkboxes: " << std::endl;
            for (const auto& c : components) {
                if(dynamic_cast<Checkbox*>(c.get())) c->draw();
            }
            std::cout << "Text Fields: " << std::endl;
            for (const auto& c : components) {
                if(dynamic_cast<TextField*>(c.get())) c->draw();
            }
        }

};

int main() {
    Button bt1("OK");
    Button bt2("Cancle");
    // bt.draw();
    // bt.onClick();
    Checkbox chb1('X');
    Checkbox chb2('+');
    // chb.draw();
    chb2.onClick();
    // chb.draw();
    TextField tx1;
    tx1.onClick();
    TextField tx2;
    tx2.onClick();
    // tx.draw();
    // tx.draw();

    GUImanager gm;
    gm.addComponent(bt1);
    gm.addComponent(bt2);
    gm.addComponent(chb1);
    gm.addComponent(chb2);
    gm.addComponent(tx1);
    gm.addComponent(tx2);
    gm.drawLayout();
}