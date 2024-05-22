#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Represents a YouTube video, holding all relevant information
// that would be needed to define and display a video's metadata on YouTube.
class YouTubeVideo {
public:
    // Member variables to store video properties.
    std::string title;
    std::string description;
    std::vector<std::string> tags;
    std::string privacyStatus;
    std::string thumbnailUrl;
    bool monetizationEnabled;

    // Function to display all current video details to the console.
    void displayDetails() const {
        std::cout << "Video Title: " << title << "\n"
                  << "Description: " << description << "\n"
                  << "Tags: ";
        for (const auto& tag : tags) {
            std::cout << tag << ", ";
        }
        std::cout << "\nPrivacy Status: " << privacyStatus << "\n"
                  << "Thumbnail URL: " << thumbnailUrl << "\n"
                  << "Monetization: " << (monetizationEnabled ? "Enabled" : "Disabled") << std::endl;
    }
};

// Interface for building YouTube video objects step-by-step.
class YouTubeVideoBuilder {
public:
    virtual ~YouTubeVideoBuilder() {}

    // Method declarations for setting various parts of the video.
    virtual YouTubeVideoBuilder& setTitle(const std::string& title) = 0;
    virtual YouTubeVideoBuilder& setDescription(const std::string& description) = 0;
    virtual YouTubeVideoBuilder& addTag(const std::string& tag) = 0;
    virtual YouTubeVideoBuilder& setPrivacyStatus(const std::string& status) = 0;
    virtual YouTubeVideoBuilder& setThumbnailUrl(const std::string& url) = 0;
    virtual YouTubeVideoBuilder& enableMonetization(bool enabled) = 0;
    virtual std::unique_ptr<YouTubeVideo> build() = 0;
};

// Concrete builder class that implements the builder interface.
// This class constructs a YouTubeVideo, step-by-step, by implementing
// each method declared in the builder interface.
class ConcreteYouTubeVideoBuilder : public YouTubeVideoBuilder {
private:
    std::unique_ptr<YouTubeVideo> video;  // Unique pointer to hold the video being built

public:
    // Constructor initializes a new YouTubeVideo object.
    ConcreteYouTubeVideoBuilder() : video(new YouTubeVideo()) {}

    // Each method modifies part of the video and returns a reference to the builder,
    // enabling method chaining (also known as fluent interface).
    YouTubeVideoBuilder& setTitle(const std::string& title) override {
        video->title = title;
        return *this;
    }

    YouTubeVideoBuilder& setDescription(const std::string& description) override {
        video->description = description;
        return *this;
    }

    YouTubeVideoBuilder& addTag(const std::string& tag) override {
        video->tags.push_back(tag);
        return *this;
    }

    YouTubeVideoBuilder& setPrivacyStatus(const std::string& status) override {
        video->privacyStatus = status;
        return *this;
    }

    YouTubeVideoBuilder& setThumbnailUrl(const std::string& url) override {
        video->thumbnailUrl = url;
        return *this;
    }

    YouTubeVideoBuilder& enableMonetization(bool enabled) override {
        video->monetizationEnabled = enabled;
        return *this;
    }

    // Builds the final product by returning the unique pointer to the caller,
    // transferring ownership in the process.
    std::unique_ptr<YouTubeVideo> build() override {
        return std::move(video);
    }
};

// Example usage of the builder to create a YouTube video object.
int main() {
    ConcreteYouTubeVideoBuilder builder;
    auto video = builder.setTitle("How to Use the Builder Pattern")
                        .setDescription("A detailed guide on using the Builder Pattern in C++.")
                        .addTag("Programming")
                        .addTag("C++")
                        .addTag("Design Patterns")
                        .setPrivacyStatus("Public")
                        .setThumbnailUrl("http://example.com/thumbnail.jpg")
                        .enableMonetization(true)
                        .build();
    video->displayDetails();  // Output the video details to the console
    return 0;
}
