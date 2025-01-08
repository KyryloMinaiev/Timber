// Timber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML\Graphics.hpp>
#include <memory>

using namespace sf;

const float TREE_HORIZONTAL_POSITION = 810;
const float TREE_VERTICAL_POSITION = 0;

const float START_BEE_HORIZONTAL_POSITION = 0;
const float START_BEE_VERTICAL_POSITION = 800;

class GameEntity {
private:
    void UpdateSpritePosition() {
        m_entitySprite->setPosition(m_position);
    }

    std::unique_ptr<Texture> m_spriteTexture;
    std::unique_ptr<Sprite> m_entitySprite;
    Vector2f m_position;
public:
    GameEntity(const std::filesystem::path& spriteName) : m_position(0, 0){
        m_spriteTexture = std::make_unique<Texture>(spriteName);
        m_entitySprite = std::make_unique<Sprite>(*m_spriteTexture.get());
        UpdateSpritePosition();
    }

    ~GameEntity() = default;

    void SetPosition(Vector2f position) {
        m_position = position;
        UpdateSpritePosition();
    }

    void Draw(RenderWindow& window) {
        window.draw(*m_entitySprite.get());
    }

    void Move(Vector2f translate) {
        SetPosition(m_position + translate);
    }
};


int main()
{
    VideoMode videoMode(Vector2u(1920, 1080));
    RenderWindow window(videoMode, "Timber", State::Fullscreen);

    GameEntity background("res/graphics/background.png");
    GameEntity tree("res/graphics/tree.png");
    tree.SetPosition(Vector2f(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION));

    GameEntity bee("res/graphics/bee.png");
    bee.SetPosition(Vector2f(START_BEE_HORIZONTAL_POSITION, START_BEE_VERTICAL_POSITION));

    bool beeActive = false;
    float beeSpeed = 0.0f;

    GameEntity cloud1("res/graphics/cloud.png");
    GameEntity cloud2("res/graphics/cloud.png");
    GameEntity cloud3("res/graphics/cloud.png");

    cloud1.SetPosition(Vector2f(0, 0));
    cloud2.SetPosition(Vector2f(0, 250));
    cloud3.SetPosition(Vector2f(0, 500));

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            window.close();
        }

        window.clear();
        background.Draw(window);

        cloud1.Draw(window);
        cloud2.Draw(window);
        cloud3.Draw(window);

        tree.Draw(window);
        bee.Draw(window);
        window.display();
    }

    return 0;
}
