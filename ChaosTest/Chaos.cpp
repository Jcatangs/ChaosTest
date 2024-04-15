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
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;
    Font font;

    while (window.isOpen())
    {
        font.loadFromFile("GamersDemoRegular.ttf");

        if (!font.loadFromFile("GamersDemoRegular.ttf"))
        {
            cout << "Can't load the font file." << endl;
        }

        Text text1("\n                                                                         Click anywhere to make three points for a triangle \n                                                                                         The fourth point starts the chaos \n", font);
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

                    if (vertices.size() < 3)
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

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            
            ///generate more point(s)
            ///select random vertex
            int random_index = rand() % vertices.size();
            ///calculate midpoint between random vertex and the last point in the vector
            Vector2f mid_point = (vertices[random_index] + points.back()) / (float)2;

            ///push back the newly generated coord.
            points.push_back(mid_point);
        }


        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        window.draw(text1);

        int n = vertices.size();

        //Draw initial points
        for (int i = 0; i < n; i++)
        {
            RectangleShape rect(Vector2f(3, 3));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Color(0,255,255,195));
            window.draw(rect);
        }

        //Start Chaos points
        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(3, 3));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Color(0,255,255,195));
            window.draw(rect);

        }
        window.display();
    }
}

