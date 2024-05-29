#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>

using namespace std;

class GameCharacterPrototype {
public:
    virtual void display() const = 0;
    virtual unique_ptr<GameCharacterPrototype> clone() const = 0;
    virtual ~GameCharacterPrototype() {}
};

class GameCharacter : public GameCharacterPrototype {
public:
    string name;
    vector<string> textures;
    vector<string> animations;

    GameCharacter(const string& name) : name(name) {
        loadTextures();
        loadAnimations();
    }

    void loadTextures() {
        cout << "Loading textures for " << name << "..." << endl;
        this_thread::sleep_for(chrono::seconds(3));
        textures.push_back("texture1.png");
        textures.push_back("texture2.png");
        cout << "Textures loaded." << endl;
    }

    void loadAnimations() {
        cout << "Loading animations for " << name << "..." << endl;
        this_thread::sleep_for(chrono::seconds(3));
        animations.push_back("anim1.anim");
        animations.push_back("anim2.anim");
        cout << "Animations loaded." << endl;
    }

    void display() const override {
        cout << "Character: " << name << " ready with loaded resources." << endl;
    }

    unique_ptr<GameCharacterPrototype> clone() const override {
        cout << "Cloning character: " << name << "..." << endl;
        auto cloned = make_unique<GameCharacter>(*this);
        cout << "Cloning complete." << endl;
        return cloned;
    }
};

int main() {
    auto start = chrono::high_resolution_clock::now();

    cout << "Creating Hero character..." << endl;
    unique_ptr<GameCharacterPrototype> hero = make_unique<GameCharacter>("Hero");
    hero->display();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time taken to create Hero: " << elapsed.count() << " seconds." << endl;

    start = chrono::high_resolution_clock::now();
    cout << "Cloning Hero character..." << endl;
    auto clonedHero = hero->clone();
    clonedHero->display();

    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    cout << "Time taken to clone Hero: " << elapsed.count() << " seconds." << endl;

    return 0;
}
