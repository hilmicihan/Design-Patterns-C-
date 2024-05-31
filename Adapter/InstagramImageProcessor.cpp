/* 
Situation:
Instagram has been using a legacy image processing library to apply basic filters to photos.
The company wants to integrate a new, advanced image processing library that supports more complex filters and effects.
Existing features rely heavily on the legacy library, and a complete overhaul is not feasible immediately.
The Adapter Design Pattern can help bridge the gap between the legacy system and the new library, enabling a seamless transition and new feature integration.
*/
#include <iostream>
#include <string>
#include <memory>
using namespace std;
class LegacyImageProcessor {
public:
    virtual void applyFilter(const string& imagePath, const string& filter) {
        cout << "Applying " << filter << " filter using the legacy processor to " << imagePath << endl;
    }
};

class NewImageProcessor {
public:
    void applyAdvancedFilter(const string& imagePath, const string& filter, int intensity) {
        cout << "Applying " << filter << " with intensity " << intensity << " using the new processor to " << imagePath << endl;
    }

    void applyEffect(const string& imagePath, const string& effect) {
        cout << "Applying " << effect << " effect using the new processor to " << imagePath << endl;
    }
};

class ImageProcessorAdapter : public LegacyImageProcessor {
    shared_ptr<NewImageProcessor> newProcessor;
public:
    ImageProcessorAdapter(shared_ptr<NewImageProcessor> processor) : newProcessor(processor) {}

    void applyFilter(const string& imagePath, const string& filter) override {
        // Basic filters use a default intensity of 5
        newProcessor->applyAdvancedFilter(imagePath, filter, 5);
    }

    void applyAdvancedFilter(const string& imagePath, const string& filter, int intensity) {
        newProcessor->applyAdvancedFilter(imagePath, filter, intensity);
    }

    void applyEffect(const string& imagePath, const string& effect) {
        newProcessor->applyEffect(imagePath, effect);
    }
};
int main() {
    shared_ptr<LegacyImageProcessor> legacyProcessor = make_shared<LegacyImageProcessor>();
    legacyProcessor->applyFilter("photo.jpg", "sepia");

    shared_ptr<NewImageProcessor> newProcessor = make_shared<NewImageProcessor>();
    ImageProcessorAdapter adapter(newProcessor);

    // Using the adapter to apply a filter using the new system
    adapter.applyFilter("photo.jpg", "vintage");

    // Using the adapter to apply advanced filters and effects
    adapter.applyAdvancedFilter("photo.jpg", "vintage", 10);
    adapter.applyEffect("photo.jpg", "blur");

    return 0;
}
/*
Benefits:
Backward Compatibility: Existing code that relies on the legacy image processor can continue to function without modification.
Enhanced Functionality: The adapter allows the new system's advanced features to be used, providing additional benefits while maintaining compatibility with the old system.
Incremental Transition: The system can gradually transition from the legacy image processor to the new image processor, minimizing risks and disruptions.
Maintainability: The adapter encapsulates the logic for choosing between the legacy and new systems, making the codebase cleaner and easier to maintain.
Flexibility: The system can be easily extended to handle additional conditions or new features without significant changes to the existing code.

*/