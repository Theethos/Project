#ifndef TRANSITION_COMPONENT_H
#define TRANSITION_COMPONENT_H

class TransitionComponent
{
public:
	// Constructors
	TransitionComponent(unsigned int width, unsigned int height);
	TransitionComponent(sf::Vector2u size);
	// Destructor
	virtual ~TransitionComponent();

	// Functions
	void Update();
	void Render(sf::RenderTarget *target);

	// Getters
	const TransitionStatus &getStatus() const;
	const sf::Color &getColor() const;

private:
	sf::RectangleShape transitionScreen;
	sf::Color color;
	TransitionStatus status;
};

#endif // !TRANSITION_COMPONENT_H

