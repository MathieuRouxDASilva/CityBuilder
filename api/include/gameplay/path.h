#ifndef API_GAMEPLAY_PATH_H_
#define API_GAMEPLAY_PATH_H_
#include <queue>
#include <SFML/System/Vector2.hpp>


class Path
{
public:
	//GET ----------
	bool is_ended();
	bool is_available();
	bool is_ready();

	sf::Vector2f GetNextStep();
	void SetSteps(std::vector<sf::Vector2f> steps);
	// steps getter
	const std::queue<sf::Vector2f>& GetSteps();

private:
	std::queue<sf::Vector2f> steps_;
	sf::Vector2f next_step_;

	bool is_available_ = false;
	bool is_ready_ = true;
};





#endif //API_GAMEPLAY_PATH_H_