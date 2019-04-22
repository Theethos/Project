#ifndef _STATE_H_
#define _STATE_H_

class State
{
public:
	// Constructor
	State(sf::RenderWindow *window, std::stack<State*>* states, WhichState state);
	// Destructor
	virtual ~State();

	// Virtual functions
	virtual void HandleInput(int input, const float &dt) = 0;
	virtual void Update(const float &dt) = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;
	virtual void InitControllerKeys();
	virtual void InitControllerActions();
	virtual void InitKeyboardKeys();
	virtual void InitKeyboardActions();

	// Getters
	virtual const bool& getQuit() const;
	virtual const WhichState& getState() const;

protected:
	// Actual state
	WhichState state;
	// Main window
	sf::RenderWindow *window;
	// If the state wants to quit
	bool quit;
	// Supported keys
	std::map < std::string, int> keys;
	// Actions associated to those keys
	std::map < std::string, int> actions;
	// Mouse positions
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	// Pointer to the stack of States
	std::stack<State*>* states;

	// Private functions
	virtual void UpdateMousePositions();
};

#endif // !_STATE_H_

