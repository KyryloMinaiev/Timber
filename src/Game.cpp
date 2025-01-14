#include "Game.h"

void Game::Run(RenderWindow& window)
{
    GameEntity background("res/graphics/background.png");
    GameEntity tree("res/graphics/tree.png");
    tree.setPosition(Vector2f(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION));

    GameEntity bee("res/graphics/bee.png");
    bee.setPosition(Vector2f(START_BEE_HORIZONTAL_POSITION, START_BEE_VERTICAL_POSITION));

    GameEntity player("res/graphics/player.png");
    player.setPosition(Vector2f(580, 720));

    side playerSide = side::LEFT;

    GameEntity deadPlayer("res/graphics/rip.png");
    deadPlayer.setPosition(Vector2f(600, 860));

    GameEntity axe("res/graphics/axe.png");
    axe.setPosition(Vector2f(700, 830));

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    GameEntity log("res/graphics/log.png");
    log.setPosition(Vector2f(810, 720));

    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    bool beeActive = false;
    float beeSpeed = 0.0f;

    GameEntity cloud1("res/graphics/cloud.png");
    GameEntity cloud2("res/graphics/cloud.png");
    GameEntity cloud3("res/graphics/cloud.png");

    cloud1.setPosition(Vector2f(0, 0));
    cloud2.setPosition(Vector2f(0, 250));
    cloud3.setPosition(Vector2f(0, 500));

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

    Texture textureBranch("res/graphics/branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches.push_back(Sprite(textureBranch));
        branches[i].setPosition(Vector2f(-2000, -2000));
        branches[i].setOrigin(Vector2f(220, 20));
        branchPositions.push_back(side::NONE);
    }

    bool acceptInput = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::KeyPressed>() && !paused)
            {
                acceptInput = true;

                axe.setPosition(Vector2f(2000, axe.getPosition().y));
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
        {
            paused = false;
            timeRemaining = 6.0f;
            score = 0;

            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                branchPositions[i] = side::NONE;
            }

            deadPlayer.setPosition(Vector2f(675, 2000));
            player.setPosition(Vector2f(580, 720));

            acceptInput = true;
        }

        if (acceptInput)
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::Right))
            {
                playerSide = side::RIGHT;
                score++;

                timeRemaining += (2 / score) + 0.15f;
                axe.setPosition(Vector2f(AXE_POSITION_RIGHT, axe.getPosition().y));
                player.setPosition(Vector2f(1200, 720));

                updateBranches(score);

                log.setPosition(Vector2f(810, 720));
                logSpeedX = -5000;
                logActive = true;

                acceptInput = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Left))
            {
                playerSide = side::LEFT;
                score++;

                timeRemaining += (2 / score) + 0.15f;
                axe.setPosition(Vector2f(AXE_POSITION_LEFT, axe.getPosition().y));
                player.setPosition(Vector2f(580, 720));

                updateBranches(score);

                log.setPosition(Vector2f(810, 720));
                logSpeedX = 5000;
                logActive = true;

                acceptInput = false;
            }
        }

        if (!paused)
        {
            Time dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
            if (timeRemaining <= 0.0f)
            {
                paused = true;
                messageText.setString("Out of time!");

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(Vector2f(textRect.position.x +
                                               textRect.size.x / 2.0f,
                                               textRect.position.y +
                                               textRect.size.y / 2.0f));
                messageText.setPosition(Vector2f(1920 / 2.0f, 1080 / 2.0f));
            }

            if (!beeActive)
            {
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 500;
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                bee.setPosition(Vector2f(2000, height));
                beeActive = true;
            }
            else
            {
                bee.move(Vector2f(-beeSpeed * dt.asSeconds(), 0));

                if (bee.getPosition().x < -100)
                {
                    beeActive = false;
                }
            }

            if (!cloud1Active)
            {
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                cloud1.setPosition(Vector2f(-200, height));
                cloud1Active = true;
            }
            else
            {
                cloud1.move(Vector2f(cloud1Speed * dt.asSeconds(), 0));

                if (cloud1.getPosition().x > 1920)
                {
                    cloud1Active = false;
                }
            }

            if (!cloud2Active)
            {
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                cloud2.setPosition(Vector2f(-200, height));
                cloud2Active = true;
            }
            else
            {
                cloud2.move(Vector2f(cloud2Speed * dt.asSeconds(), 0));

                if (cloud2.getPosition().x > 1920)
                {
                    cloud2Active = false;
                }
            }

            if (!cloud3Active)
            {
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);
                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                cloud3.setPosition(Vector2f(-200, height));
                cloud3Active = true;
            }
            else
            {
                cloud3.move(Vector2f(cloud3Speed * dt.asSeconds(), 0));

                if (cloud3.getPosition().x > 1920)
                {
                    cloud3Active = false;
                }
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT)
                {
                    branches[i].setPosition(Vector2f(610, height));
                    branches[i].setRotation(degrees(180));
                }
                else if (branchPositions[i] == side::RIGHT)
                {
                    branches[i].setPosition(Vector2f(1330, height));
                    branches[i].setRotation(Angle::Zero);
                }
                else
                {
                    branches[i].setPosition(Vector2f(3000, height));
                }
            }

            if (logActive)
            {
                log.setPosition(
                    Vector2f(log.getPosition().x +
                             (logSpeedX * dt.asSeconds()),

                             log.getPosition().y +
                             (logSpeedY * dt.asSeconds())));

                // Has the log reached the right hand edge?
                if (log.getPosition().x < -100 ||
                    log.getPosition().x > 2000)
                {
                    // Set it up ready to be a whole new log next frame
                    logActive = false;
                    log.setPosition(Vector2f(810, 720));
                }
            }
        }

        window.clear();
        background.draw(window);

        cloud1.draw(window);
        cloud2.draw(window);
        cloud3.draw(window);

        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }

        tree.draw(window);
        player.draw(window);
        axe.draw(window);
        log.draw(window);
        deadPlayer.draw(window);

        bee.draw(window);

        window.draw(scoreText);
        window.draw(timeBar);

        if (paused)
        {
            window.draw(messageText);
        }

        window.display();
    }
}

void Game::updateBranches(int seed)
{
    for (int i = NUM_BRANCHES - 1; i > 0; i--)
    {
        branchPositions[i] = branchPositions[i - 1];
    }

    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r)
    {
    case 0:
        branchPositions[0] = side::LEFT;
        break;
    case 1:
        branchPositions[0] = side::RIGHT;
        break;
    default:
        branchPositions[0] = side::NONE;
        break;
    }
}
