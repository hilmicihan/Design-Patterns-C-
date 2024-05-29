#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Base class for game character prototypes
class GameCharacterPrototype {
public:
    virtual void display() const = 0;
    virtual unique_ptr<GameCharacterPrototype> clone() const = 0;
    virtual ~GameCharacterPrototype() {}
};

// Concrete class for game characters
class GameCharacter : public GameCharacterPrototype {
public:
    string name;
    vector<string> textures;
    vector<string> animations;
    vector<string> equipment; // Additional equipment items
    string skill; // Special skill or ability

    // Constructor for initially creating a character with heavy resources
    GameCharacter(const string& name) : name(name) {
        loadTextures();
        loadAnimations();
    }

    // Simulate loading textures (heavy operation)
    void loadTextures() {
        textures.push_back("texture1.png");
        textures.push_back("texture2.png");
    }

    // Simulate loading animations (heavy operation)
    void loadAnimations() {
        animations.push_back("anim1.anim");
        animations.push_back("anim2.anim");
    }

    // Display character details
    void display() const override {
        cout << "Character: " << name << endl;
        cout << "Textures: ";
        for (const auto& t : textures) cout << t << " ";
        cout << "\nAnimations: ";
        for (const auto& a : animations) cout << a << " ";
        cout << "\nEquipment: ";
        for (const auto& e : equipment) cout << e << " ";
        cout << "\nSkill: " << skill << endl;
    }

    // Cloning method for creating a new character from this instance
    unique_ptr<GameCharacterPrototype> clone() const override {
        auto cloned = make_unique<GameCharacter>(*this);
        return cloned;
    }
};

int main() {
    unique_ptr<GameCharacterPrototype> hero = make_unique<GameCharacter>("Hero");
    hero->display();

    // Clone the hero character and customize it
    auto clonedHero = hero->clone();
    static_cast<GameCharacter*>(clonedHero.get())->equipment.push_back("Shield");
    static_cast<GameCharacter*>(clonedHero.get())->skill = "Fireball";
    clonedHero->display();

    return 0;
}
