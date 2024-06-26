#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

class GameCharacter {
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
        this_thread::sleep_for(chrono::seconds(3)); // Simulates a 3-second delay for loading textures
        textures.push_back("texture1.png");
        textures.push_back("texture2.png");
        cout << "Textures loaded." << endl;
    }

    void loadAnimations() {
        cout << "Loading animations for " << name << "..." << endl;
        this_thread::sleep_for(chrono::seconds(3)); // Simulates a 3-second delay for loading animations
        animations.push_back("anim1.anim");
        animations.push_back("anim2.anim");
        cout << "Animations loaded." << endl;
    }

    void display() const {
        cout << "Character: " << name << " ready with loaded resources." << endl;
    }
};

int main() {
    auto start = chrono::high_resolution_clock::now();

    cout << "Creating Hero character..." << endl;
    GameCharacter hero("Hero");
    hero.display();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time taken to create Hero: " << elapsed.count() << " seconds." << endl;

    start = chrono::high_resolution_clock::now();
    cout << "Creating another Hero character..." << endl;
    GameCharacter anotherHero("Hero");
    anotherHero.display();

    end = chrono::high_resolution_clock::now();
    elapsed = end - start;
    cout << "Time taken to create another Hero: " << elapsed.count() << " seconds." << endl;

    return 0;
}
