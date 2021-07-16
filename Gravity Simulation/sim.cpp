#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

struct Particle
{
    float vx = 0.3325;
    float vy = 0.0f;
    int mass = 40; // mass of the big object
    int r; // radius 
}; Particle p;


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Gravity Simulator");
   
    // Make the big circle 
    sf::CircleShape BigCircle(p.r = 75);
    BigCircle.setFillColor(sf::Color::Green);
    BigCircle.setPosition(1000, 500);
    BigCircle.setOrigin(37.5f, 37.5f);

    // Make the small circle
    sf::CircleShape SmallCircle(p.r = 15);
    SmallCircle.setFillColor(sf::Color::Blue);
    SmallCircle.setPosition(950, 850);
    SmallCircle.setOrigin(7.5f, 7.5f);

    sf::VertexArray line;
    line.setPrimitiveType(sf::PrimitiveType::LinesStrip);
 
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            // "close requested" event: we close the window
            if (evnt.type == sf::Event::Closed)
                window.close();
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            BigCircle.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        }
        
        void physicsCalculations();
        {
            float distanceX = BigCircle.getPosition().x - SmallCircle.getPosition().x;
            float distanceY = BigCircle.getPosition().y - SmallCircle.getPosition().y;

            double acceleration = (p.mass) / (distanceX * distanceX + distanceY * distanceY);
            double accx = (acceleration * distanceX) / (sqrt(distanceX * distanceX + distanceY * distanceY));
            double accy = (acceleration * distanceY) / (sqrt(distanceX * distanceX + distanceY * distanceY));

            p.vx += accx;
            p.vy += accy;
        }

        SmallCircle.move(p.vx, p.vy);
        line.append(sf::Vertex(sf::Vector2f(SmallCircle.getPosition().x, SmallCircle.getPosition().y)));

        // clear the window with black color
        window.clear();

        // Draw circles
        window.draw(BigCircle);
        window.draw(SmallCircle);
        window.draw(line);

        // end the current frame
        window.display();
    }

    return 0;
}