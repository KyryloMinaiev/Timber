// Timber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML\Graphics.hpp>
#include <memory>
#include <sstream>

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

    Vector2f GetPosition() const {
        return m_position;
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

    int score = 0;
    
    Font font("res/fonts/KOMIKAP_.ttf");
    Text messageText(font, "Press Enter to start!", 75);
    Text scoreText(font, "Score = 0", 100);

    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(Vector2f(textRect.position.x +
        textRect.size.x / 2.0f,
        textRect.position.y +
        textRect.size.y / 2.0f));
    messageText.setPosition(Vector2f(1920 / 2.0f, 1080 / 2.0f));
    scoreText.setPosition(Vector2f(20, 20));

    Clock clock;
    bool paused = true;

    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    RectangleShape timeBar(Vector2f(400, 80));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(Vector2f((1920 / 2) - timeBarStartWidth / 2, 980));

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
            paused = false;
            timeRemaining = 6.0f;
        }

        if (!paused) {
            Time dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
            if (timeRemaining <= 0.0f) {
                paused = true;
                messageText.setString("Out of time!");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(Vector2f(textRect.position.x +
                    textRect.size.x / 2.0f,
                    textRect.position.y +
                    textRect.size.y / 2.0f));
                messageText.setPosition(Vector2f(1920 / 2.0f, 1080 / 2.0f));
            }

            if (!beeActive) {
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 500;
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                bee.SetPosition(Vector2f(2000, height));
                beeActive = true;
            }
            else {
                bee.Move(Vector2f(-beeSpeed * dt.asSeconds(), 0));

                if (bee.GetPosition().x < -100) {
                    beeActive = false;
                }
            }

            if (!cloud1Active) {
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                cloud1.SetPosition(Vector2f(-200, height));
                cloud1Active = true;
            }
            else {
                cloud1.Move(Vector2f(cloud1Speed * dt.asSeconds(), 0));

                if (cloud1.GetPosition().x > 1920) {
                    cloud1Active = false;
                }
            }

            if (!cloud2Active) {
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                cloud2.SetPosition(Vector2f(-200, height));
                cloud2Active = true;
            }
            else {
                cloud2.Move(Vector2f(cloud2Speed * dt.asSeconds(), 0));

                if (cloud2.GetPosition().x > 1920) {
                    cloud2Active = false;
                }
            }

            if (!cloud3Active) {
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);
                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                cloud3.SetPosition(Vector2f(-200, height));
                cloud3Active = true;
            }
            else {
                cloud3.Move(Vector2f(cloud3Speed * dt.asSeconds(), 0));

                if (cloud3.GetPosition().x > 1920) {
                    cloud3Active = false;
                }
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        window.clear();
        background.Draw(window);

        cloud1.Draw(window);
        cloud2.Draw(window);
        cloud3.Draw(window);

        tree.Draw(window);
        bee.Draw(window);

        window.draw(scoreText);
        window.draw(timeBar);

        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}
