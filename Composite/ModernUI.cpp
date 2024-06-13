// 🚀 Modern Software Example: User Interface Components with Composite Design Pattern 🌐
// 
// In this scenario, we represent a hierarchical structure of a user interface (UI) with various UI components. 
// We have components such as buttons, text fields, and containers. Containers can contain other UI components, 
// allowing us to build complex, nested UIs. The Composite Design Pattern helps us manage this structure uniformly.
//
// Benefits:
// - Uniformity: Treat individual and composite components the same way. 🔄
// - Flexibility: Easily add new components without changing existing code. ➕
// - Simplicity: Provide a consistent interface for client code, regardless of complexity. 💡
//
// Components:
// - Leaf Components: Button, TextField
// - Composite Component: Container (can contain other UI components)

#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// Abstract base class representing a UI component
class UIComponent {
public:
    virtual void render() const = 0;  // Pure virtual method to render the component
    virtual void add(shared_ptr<UIComponent> component) {
        throw runtime_error("Cannot add to a leaf component");
    }
    virtual ~UIComponent() = default;  // Virtual destructor for proper cleanup
};

// Leaf component: Button
class Button : public UIComponent {
private:
    string label;
public:
    Button(const string& label) : label(label) {}

    void render() const override {
        cout << "Button: " << label << endl;
    }
};

// Leaf component: TextField
class TextField : public UIComponent {
private:
    string placeholder;
public:
    TextField(const string& placeholder) : placeholder(placeholder) {}

    void render() const override {
        cout << "TextField: " << placeholder << endl;
    }
};

// Composite component: Container
class Container : public UIComponent {
private:
    string name;
    vector<shared_ptr<UIComponent>> components;
public:
    Container(const string& name) : name(name) {}

    void add(shared_ptr<UIComponent> component) override {
        components.push_back(component);
    }

    void render() const override {
        cout << "Container: " << name << endl;
        for (const auto& component : components) {
            component->render();
        }
    }
};

// Main function to demonstrate the Composite Pattern
int main() {
    // Creating leaf components
    shared_ptr<UIComponent> button1 = make_shared<Button>("Submit");
    shared_ptr<UIComponent> button2 = make_shared<Button>("Cancel");
    shared_ptr<UIComponent> textField = make_shared<TextField>("Enter your name");

    // Creating composite component: Form
    shared_ptr<Container> form = make_shared<Container>("Form");
    form->add(button1);
    form->add(button2);
    form->add(textField);

    // Creating another composite component: Window
    shared_ptr<Container> window = make_shared<Container>("Main Window");
    window->add(form);

    // Displaying the structure of the UI
    window->render();

    return 0;
}
