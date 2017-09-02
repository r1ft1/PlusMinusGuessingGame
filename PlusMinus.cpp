#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <sstream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(320, 240),"Plus or Minus");
	
	sf::Font font;
	if (!font.loadFromFile("Bauhaus.ttf"))
		return EXIT_FAILURE;

	sf::Text title("Plus Or Minus", font, 20);
	title.setPosition(10, 10);
	title.setColor(sf::Color::White);

	sf::Text question("Guess number between 0-99", font, 20);
	question.setPosition(5, 30);
	question.setColor(sf::Color::White);

	sf::Text guess("", font, 20);
	guess.setPosition(5, 50);
	guess.setColor(sf::Color::Green);
	sf::String textEntered;
	int numEntered = 0;

	sf::Text status("", font, 16);
	status.setPosition(100, 50);
	status.setColor(sf::Color::Yellow);
	std::stringstream out("");

	sf::Text won("You have discovered\n the secret number \n in less than 10 tries", font, 20);
	won.setPosition(5, 70);
	won.setColor(sf::Color::Green);

	sf::Text lost("You have failed to\n discover the secret\n number in less than \n 10 tries", font, 20);
	lost.setPosition(5, 70);
	lost.setColor(sf::Color::Red);

	srand(static_cast<unsigned int> (time(NULL)));

	int secretNumber = rand() % 100;

	bool isGameOn = true;
	bool playerWon = false;
	int tryNumber = 0;

	while (window.isOpen())
	{
		window.clear();
		window.draw(title);
		if (isGameOn)
		{
			window.draw(question);
			window.draw(guess);
			window.draw(status);
		}
		else
		{
			if (playerWon)
				window.draw(won);
			else
				window.draw(lost);
		}

		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				window.close();

			if (event.type == sf::Event::TextEntered)
			{
				char c = static_cast<char> (event.text.unicode);
				if (c >= '0' && c <= '9')
				{
					textEntered += event.text.unicode;
					guess.setString(textEntered); //update the enter text
				}
				else if (c == '\b')
				{
					textEntered = "";
					guess.setString("");
				}
				/*else if (textEntered.getSize() > 2)
				{
					textEntered = textEntered + "";
					guess.setString(textEntered);
				}*/
				else if (c == '\r') // '\b' to handle backspace
				{
					tryNumber++;

					std::stringstream in(guess.getString());
					in >> numEntered; //just get str as int

					if (numEntered > secretNumber)
					{
						out << tryNumber;
						out << ".  ";
						out << numEntered;
						out << ": Minus" << std::endl;
						status.setString(out.str());
					}
					if (numEntered < secretNumber)
					{
						out << tryNumber;
						out << ".  ";
						out << numEntered;
						out << ": Plus" << std::endl;
						status.setString(out.str());
					}
					if (numEntered == secretNumber)
					{
						playerWon = true;
						status.setString("");
						isGameOn = false;
					}
					if (tryNumber > 10)
					{
						playerWon = false;
						status.setString("");
						isGameOn = false;
					}
					textEntered = ""; //reset textEntered
				}
			}
		}
	}
	return EXIT_SUCCESS;
}
