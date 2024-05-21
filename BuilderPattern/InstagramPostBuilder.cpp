#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Abstract base class for post components
class PostComponent {
public:
    virtual void display() const = 0;
    virtual ~PostComponent() {}
};

// Image component
class Image : public PostComponent {
public:
    std::string url;
    Image(const std::string& url) : url(url) {}
    void display() const override {
        std::cout << "Image URL: " << url << std::endl;
    }
};

// Caption component
class Caption : public PostComponent {
public:
    std::string text;
    Caption(const std::string& text) : text(text) {}
    void display() const override {
        std::cout << "Caption: " << text << std::endl;
    }
};

// Location component
class Location : public PostComponent {
public:
    std::string place;
    Location(const std::string& place) : place(place) {}
    void display() const override {
        std::cout << "Location: " << place << std::endl;
    }
};

// Tags component
class Tags : public PostComponent {
public:
    std::vector<std::string> tags;
    Tags(const std::vector<std::string>& tags) : tags(tags) {}
    void display() const override {
        std::cout << "Tags: ";
        for (const auto& tag : tags) {
            std::cout << "#" << tag << " ";
        }
        std::cout << std::endl;
    }
};

// Visibility setting component
class Visibility : public PostComponent {
public:
    std::string visibility;
    Visibility(const std::string& visibility) : visibility(visibility) {}
    void display() const override {
        std::cout << "Visibility: " << visibility << std::endl;
    }
};

// Composite class for an Instagram post
class InstagramPost {
private:
    std::vector<std::unique_ptr<PostComponent>> components;

public:
    void addComponent(std::unique_ptr<PostComponent> component) {
        components.push_back(std::move(component));
    }

    void display() const {
        for (const auto& component : components) {
            component->display();
        }
    }
};

// Builder interface
class InstagramPostBuilder {
public:
    virtual ~InstagramPostBuilder() {}
    virtual InstagramPostBuilder& addImage(const std::string& url) = 0;
    virtual InstagramPostBuilder& addCaption(const std::string& text) = 0;
    virtual InstagramPostBuilder& addLocation(const std::string& place) = 0;
    virtual InstagramPostBuilder& addTags(const std::vector<std::string>& tags) = 0;
    virtual InstagramPostBuilder& setVisibility(const std::string& visibility) = 0;
    virtual std::unique_ptr<InstagramPost> build() = 0;
};

// Concrete builder implementation
class ConcreteInstagramPostBuilder : public InstagramPostBuilder {
private:
    std::unique_ptr<InstagramPost> post;

public:
    ConcreteInstagramPostBuilder() : post(new InstagramPost()) {}

    InstagramPostBuilder& addImage(const std::string& url) override {
        post->addComponent(std::make_unique<Image>(url));
        return *this;
    }

    InstagramPostBuilder& addCaption(const std::string& text) override {
        post->addComponent(std::make_unique<Caption>(text));
        return *this;
    }

    InstagramPostBuilder& addLocation(const std::string& place) override {
        post->addComponent(std::make_unique<Location>(place));
        return *this;
    }

    InstagramPostBuilder& addTags(const std::vector<std::string>& tags) override {
        post->addComponent(std::make_unique<Tags>(tags));
        return *this;
    }

    InstagramPostBuilder& setVisibility(const std::string& visibility) override {
        post->addComponent(std::make_unique<Visibility>(visibility));
        return *this;
    }

    std::unique_ptr<InstagramPost> build() override {
        return std::move(post);
    }
};

// Example usage
int main() {
    ConcreteInstagramPostBuilder builder;
    auto post = builder.addImage("http://example.com/image1.jpg")
                       .addCaption("Enjoying the beautiful views!")
                       .addLocation("New York, USA")
                       .addTags({"travel", "NYC", "sunset"})
                       .setVisibility("Public")
                       .build();
    post->display();
    return 0;
}
