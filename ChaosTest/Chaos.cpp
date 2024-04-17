#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1856, 1096);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;
    Font font;
    Vector2f curr;
    Vector2f previous1;
    Vector2f previous2;

    font.loadFromFile("GamersDemoRegular.ttf");

    if (!font.loadFromFile("GamersDemoRegular.ttf"))
    {
       throw runtime_error("Can't load the font file.");
    }

    Texture textureBackground;

    // Load a graphic into the texture
    textureBackground.loadFromFile("CrystalShard.png");
    Sprite spriteBackground;

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);

    while (window.isOpen())
    {
        Text text1("\n                                                               Place three droplets of blood onto three corners to create a portal \n                                                                                          A fourth drop opens the portal \n", font);
        text1.setCharacterSize(30);
        text1.setStyle(Text::Regular);
        text1.setFillColor(Color::White);

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 5)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            points.push_back(vertices[0]);
                        }
                    }
                }
            }
        }
        if (points.size() > 0)
        {
            for (int i = 0; i < 100; i++)
            {
                int random_index = rand() % vertices.size();
                Vector2f mid_point = (vertices[random_index] + points.back()) * 0.5f;

                curr = vertices[random_index];
                if (curr != previous1)
                {
                    ///generate more point(s)
                    ///select random vertex
                    //int random_index = rand() % vertices.size();
                    ///calculate midpoint between random vertex and the last point in the vector
                    //Vector2f mid_point = (vertices[random_index] + points.back()) * 0.5f;
                    ///push back the newly generated coord.
                    points.push_back(mid_point);
                }
                //if (curr == previous1) previous2 = curr;
                previous1 = curr;

            }
         }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        window.draw(spriteBackground);
        window.draw(text1);

        //Draw initial points
        for (size_t i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color(255, 51, 51,195));
            window.draw(rect);
        }

        //Start Chaos points
        for (size_t i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(2, 2));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            if (i % 2 == 0) rect.setFillColor(Color(51, 255, 51, 200));
            else rect.setFillColor(Color(0, 255, 255, 200));
            window.draw(rect);
        }

        window.display();
    }
}

