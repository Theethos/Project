#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/EditorState.h"

using namespace sf;
// Construtor
EditorState::EditorState(RenderWindow& window, std::stack<State*>& states_stack, WhichState state, bool &running) :
State(window, states_stack, state, running),
m_GUI(window),
m_MaxWidthTiles(0),
m_TileIndex(-1)
{
	InitTilesSheets();
	int witdh = (int)(m_Window.getSize().x - m_MaxWidthTiles) / m_TilesSize;
	int height = (int)(m_Window.getSize().y) / m_TilesSize;
	std::cout << witdh << " " << height << std::endl;
	m_DrawingArea.setSize(Vector2f((witdh - 1) * m_TilesSize, (height - 1) * m_TilesSize));
	m_DrawingArea.setPosition(Vector2f(m_MaxWidthTiles, 0) + Vector2f(m_Window.getSize().x * 0.01, m_Window.getSize().y * 0.01));
	m_DrawingArea.setFillColor(Color(255, 255, 255, 20));
	m_DrawingArea.setOutlineColor(Color::Red);
	m_DrawingArea.setOutlineThickness(2);	
}
// Destructor
EditorState::~EditorState()
{
	for (auto &it : m_TilesTextureSheets)
		delete it.first;
}

// Functions
void EditorState::Update(const float & dt)
{
	m_GUI.Update(dt);
	auto mouse_position = m_Window.mapPixelToCoords(Mouse::getPosition(m_Window));
	for (auto &it : m_TilesTextureSheets[m_GUI.GetSelectedShape()].second)
	{
		if (m_Tiles[it].getGlobalBounds().contains(mouse_position))
		{
			m_TileIndex = it;
			m_TileCursor.setPosition(m_Tiles[it].getPosition());
			if (Mouse::isButtonPressed(Mouse::Button::Left))
				m_SelectedTile = m_Tiles[it];
		}
	}
	if (m_DrawingArea.getGlobalBounds().contains(mouse_position))
	{
		m_Window.setMouseCursorVisible(false);
		m_SelectedTile.setPosition(m_DrawingArea.getPosition() +
			Vector2f((static_cast<int>((mouse_position.x - m_DrawingArea.getPosition().x)) / m_TilesSize) * m_TilesSize,
					 (static_cast<int>((mouse_position.y - m_DrawingArea.getPosition().y)) / m_TilesSize) * m_TilesSize));
	}
	else
	{
		m_Window.setMouseCursorVisible(true);
		m_SelectedTile.setPosition(- m_TilesSize, - m_TilesSize);
	}
}

void EditorState::Render(RenderTarget & target)
{
	m_GUI.Render(target);
	if (m_GUI.GetSelectedShape() >= 0)
	{
		for (auto &it : m_TilesTextureSheets[m_GUI.GetSelectedShape()].second)
			target.draw(m_Tiles[it]);
	}
	target.draw(m_DrawingArea);
	if (m_TileIndex >= 0)
		m_TileCursor.setOutlineColor(Color::Red);
	else 
		m_TileCursor.setOutlineColor(Color::Transparent);
	target.draw(m_TileCursor);
	target.draw(m_SelectedTile);
}

void EditorState::HandleInput(int input, const float & dt)
{
	Vector2f controller_position(Joystick::getAxisPosition(0, Joystick::Axis::X), Joystick::getAxisPosition(0, Joystick::Axis::Y));
	
	if (input == m_Actions["QUIT"])
		m_Quit = true;
	else if (controller_position.y > 80 || (m_Actions.count("DOWN") && input == m_Actions["DOWN"]))
	{
		if (m_GUI.GetSelectedShape() < m_TilesTextureSheets.size() - 1)
		{
			m_TileIndex -= m_TilesTextureSheets[m_GUI.GetSelectedShape()].second[0];
			m_GUI.SetSelectedShape(m_GUI.GetSelectedShape() + 1);
			m_TileIndex += m_TilesTextureSheets[m_GUI.GetSelectedShape()].second[0];
		}
	}
	else if (controller_position.y < -80 || (m_Actions.count("UP") && input == m_Actions["UP"]))
	{
		if (m_GUI.GetSelectedShape() > 0)
		{
			m_TileIndex -= m_TilesTextureSheets[m_GUI.GetSelectedShape()].second[0];
			m_GUI.SetSelectedShape(m_GUI.GetSelectedShape() - 1);
			m_TileIndex += m_TilesTextureSheets[m_GUI.GetSelectedShape()].second[0];
		}
	}
	else if (controller_position.x > 80 || (m_Actions.count("RIGHT") && input == m_Actions["RIGHT"]))
	{
		if (m_TileIndex < m_TilesTextureSheets[m_GUI.GetSelectedShape()].second[m_TilesTextureSheets[m_GUI.GetSelectedShape()].second.size() - 1])
			++m_TileIndex;
		else if (m_TileIndex < 0)
			m_TileIndex = 0;
		m_TileCursor.setPosition(m_Tiles[m_TileIndex].getPosition());
		m_SelectedTile = m_Tiles[m_TileIndex];
	}
	else if (controller_position.x < -80 || (m_Actions.count("LEFT") && input == m_Actions["LEFT"]))
	{
		if (m_TileIndex > m_TilesTextureSheets[m_GUI.GetSelectedShape()].second[0])
			--m_TileIndex;
		else if (m_TileIndex < 0)
			m_TileIndex = 0;
		m_TileCursor.setPosition(m_Tiles[m_TileIndex].getPosition());
		m_SelectedTile = m_Tiles[m_TileIndex];
	}
}

// Private function
void EditorState::InitTilesSheets()
{
	std::ifstream config_file("../External/Config/Editor/TilesSheets.cfg");

	if (config_file.is_open())
	{
		std::string path = "";
		int id = 0, width = 0, height = 0;
		while (config_file >> width >> height >> m_TilesSize >> path)
		{
			int row = height / m_TilesSize, column = width / m_TilesSize;
			int current_row = 0, current_column = 0;
			
			std::vector<int> tmp_vec;
			Texture* tmp_tex = new Texture;
			tmp_tex->loadFromFile(path);
			for (unsigned i = 0; i < row; ++i) 
			{	
				for (unsigned j = 0; j < column; ++j)
				{
					tmp_vec.push_back(id++); // Each tile as an "id" (number) between 0 and total_number_of_tiles in all the textures combined
					RectangleShape tmp_rect(Vector2f(m_TilesSize * 1.3, m_TilesSize * 1.3));
					m_Tiles.push_back(tmp_rect);
					m_Tiles.back().setTexture(tmp_tex, true);
					m_Tiles.back().setTextureRect(IntRect(j * m_TilesSize, i * m_TilesSize, m_TilesSize, m_TilesSize));
					m_Tiles.back().setPosition(current_column * m_TilesSize * 1.3 + m_Window.getSize().x * 0.01,
											   current_row	  * m_TilesSize * 1.3 + m_Window.getSize().y * 0.01);
					++current_row;
					if ((current_row + 1) * m_TilesSize * 1.3 >= m_Window.getSize().y)
					{
						current_row = 0;
						++current_column;
					}
				}
			}
			m_MaxWidthTiles = std::max(static_cast<float>(m_GUI.GetSize().x + (current_column + 1) * m_TilesSize * 1.3), m_MaxWidthTiles);
			m_TilesTextureSheets.push_back(std::make_pair(tmp_tex, tmp_vec));
		}
		config_file.close();
		m_TileCursor.setSize(Vector2f(m_TilesSize * 1.3, m_TilesSize * 1.3));
		m_TileCursor.setFillColor(Color::Transparent);
		m_TileCursor.setOutlineColor(Color::Transparent);
		m_TileCursor.setOutlineThickness(1);

		m_SelectedTile.setSize(Vector2f(m_TilesSize * 1.3, m_TilesSize * 1.3));
		m_SelectedTile.setFillColor(Color::Transparent);
		m_SelectedTile.setOutlineColor(Color::Red);
		m_SelectedTile.setOutlineThickness(1);

		m_GUI.Divide(m_TilesTextureSheets.size());
		for (auto &it : m_Tiles)
			it.setPosition(it.getPosition() + Vector2f(m_GUI.GetSize().x, 0));
	}

}
