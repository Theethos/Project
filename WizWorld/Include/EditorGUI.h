#ifndef EDITOR_GUI_H
#define EDITOR_GUI_H

#include "GUI.h"

class EditorGUI : public GUI
{
public:
	// Constructor
	EditorGUI(sf::RenderWindow &window);
	// Destructor
	~EditorGUI();

	// Functions
	void Update(const float &dt);
	void Render(sf::RenderTarget &target);
	void Divide(float number_of_textures);
	inline const int &GetSelectedTileset() const { return m_SelectedShape; }
	inline const void SetSelectedShape(int value) { m_SelectedShape = value; }
	inline const sf::Vector2f &GetSize() const { return m_GlobalShape.getSize(); }

private:
	sf::RectangleShape m_GlobalShape;
	std::vector < std::pair<sf::RectangleShape, sf::ConvexShape>> m_Division;
	int m_SelectedShape;

	// Private function
	void UpdatePosition(const sf::Vector2f &mouse_position);
};

#endif // !EDITOR_GUI_H

