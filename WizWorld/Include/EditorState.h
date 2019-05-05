#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.h"
#include "EditorGUI.h"

class EditorState : public State
{
public:
	// Constructor
	EditorState(sf::RenderWindow &window, std::stack<State*> &states_stack, WhichState state, bool &running);
	// Destructor
	~EditorState();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget &target);
	void HandleInput(int input, const float &dt);

private:
	std::vector<std::pair<sf::Texture*, std::vector<int>>> m_TilesTextureSheets;
	std::vector<sf::RectangleShape> m_Tiles;
	sf::RectangleShape m_DrawingArea, m_TileCursor;
	EditorGUI m_GUI;
	float m_MaxWidthTiles;
	int m_SelectedTile;
	
	// Private function
	void InitTilesSheets();
};

#endif // !EDITOR_STATE_H
