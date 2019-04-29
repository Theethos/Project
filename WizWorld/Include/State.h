#ifndef _STATE_H_
#define _STATE_H_

class State
{
public:
	// Constructor
	State(sf::RenderWindow& window, std::stack<State*>& states_stack, WhichState state);
	// Destructor
	virtual ~State();

	// Virtual functions
	virtual void HandleInput(int input, const float &dt) = 0;
	virtual void Update(const float &dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	virtual void InitControllerKeys();
	virtual void InitControllerActions();
	virtual void InitKeyboardKeys();
	virtual void InitKeyboardActions();

	// Getters
	virtual const bool& GetQuit() const;
	virtual const WhichState& GetState() const;

protected:
	sf::RenderWindow& m_Window;
	std::map < std::string, int> m_Keys;	// Supported keys
	std::map < std::string, int> m_Actions; // Actions associated to those keys
	
	WhichState m_State;						// Actual state
	bool m_Quit;							// If the state wants to m_Quit
	
	sf::Vector2f m_MousePosition;

	std::stack<State*>& m_StatesStack;		// Reference to the stack of States
};

#endif // !_STATE_H_

