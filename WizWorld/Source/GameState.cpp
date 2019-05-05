#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/GameState.h"
#include "../Include/MenuState.h"

using namespace sf;

// Function to tranform std::string in AnimationSide::side \see CheckSpriteCollision()
AnimationSide StringToSide(const std::string side)
{
	if (side == "LEFT")
	{
		return AnimationSide::LEFT;
	}
	else if (side == "RIGHT")
	{
		return AnimationSide::RIGHT;
	}
	else if (side == "DOWN")
	{
		return AnimationSide::DOWN;
	}
	else if (side == "UP")
	{
		return AnimationSide::UP;
	}
}

// Construtor
GameState::GameState(RenderWindow& window, std::stack<State*>& states_stack, WhichState state, bool &running, const std::string path,
					 const int sprite_scale, const std::string player_name, Font& player_name_font) :
State(window, states_stack, state, running),
m_Player(1.f, 0.0, 0.0, path, player_name, player_name_font, sprite_scale),
m_CantMove(false),
m_Transition(m_Window.getSize())
{
	InitMaps(sprite_scale);
	InitGUI(player_name);


	m_PlayerView.setSize(m_Window.getSize().x, m_Window.getSize().y);
	m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetSize().x * sprite_scale / 2, m_Maps[m_CurrentMap]->GetSize().y * sprite_scale / 2);

	InitView();

	// Display the area where the camera can move (Render it to see)
	m_ViewArea.setFillColor(Color::Transparent);
	m_ViewArea.setOutlineColor(Color::Red);
	m_ViewArea.setOutlineThickness(1);
	m_ViewArea.setPosition(m_LockView["LEFT"], m_LockView["UP"]);
	m_ViewArea.setSize(Vector2f(m_LockView["RIGHT"] - (m_Window.getSize().y / 2), m_LockView["DOWN"] - (m_Window.getSize().y / 2)));
}
// Destructor
GameState::~GameState()
{
	for (auto &it : m_Maps)
		delete it.second;

	for (auto &it : m_CollisionsMaps)
		delete it.second;

	for (auto &it : m_GUI)
		delete it.second;
}

// Functions
void GameState::HandleInput(int input, const float & dt)
{
	bool chating = static_cast<ChatBoxGUI*>(m_GUI["CHAT_BOX"])->IsActive();
	if (chating) // Consume the input if the m_Player is in the chat box
		input = -1;
	// Open pause menu when "Options" or "Escape" is pressed
	else if (input == (Joystick::isConnected(0) ? m_Actions["PAUSE"] : Keyboard::Key(m_Actions["PAUSE"])))
		m_StatesStack.push(new MenuState(m_Window, m_StatesStack, WhichState::MENU_STATE, m_Running, "../External/Config/Buttons/Pause_menu.cfg", Menu::PAUSE_MENU));
	else if (input == (Joystick::isConnected(0) ? m_Actions["ENTER_CHAT"] : Keyboard::Key(m_Actions["ENTER_CHAT"])))
		static_cast<ChatBoxGUI*>(m_GUI["CHAT_BOX"])->Activate();
	// Only-Joystick inputs
	else if (Joystick::isConnected(0))
	{
		if (input == m_Actions["TOGGLE_GUI"])
		{
			for (auto &it : m_GUI)
				it.second->Toggle();
		}
		else if (input == m_Keys["Square"])
			m_Player.GetStatistics().AddExp(100);
		else if (input == m_Keys["Triangle"])
			m_Player.GetStatistics().RemoveExp(100);
		else if (input == m_Keys["Cross"])
			m_Player.GetStatistics().AddHp(100);
		else if (input == m_Keys["Circle"])
			m_Player.GetStatistics().RemoveHp(100);
	}
	// Only-Keyboard inputs
	else
	{
		if (input == Keyboard::Key(m_Actions["TOGGLE_PLAYER_GUI"]))
			m_GUI["PLAYER"]->Toggle();
		else if (input == Keyboard::Key(m_Actions["TOGGLE_MINIMAP_GUI"]))
			m_GUI["MINI_MAP"]->Toggle();
	}
	// Makes the m_Player run
	bool running = false;
	if (Joystick::isButtonPressed(0, m_Actions["RUN"]) || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["RUN"])))
	{
		m_Player.GetMovement().SetMaxVelocity(2.f);
		running = true;
	}
	else
		m_Player.GetMovement().SetMaxVelocity(1.f);

	Vector2f controller_position(Joystick::getAxisPosition(0, Joystick::Axis::X), Joystick::getAxisPosition(0, Joystick::Axis::Y));

	if (!m_CantMove && !chating)
	{
		if (controller_position.y < -80 || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["UP"])))
		{
			if (!CheckSpriteCollision(dt, "UP"))
			{
				m_Player.GetMovement().SetVelocityX(0);
				m_Player.Move(dt, 0.f, (running ? -2.f : -1.f));
			}
			else
				m_Player.GetAnimation().PlayAnimation(0, dt, "UP");
		}
		else if (controller_position.y > 80 || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["DOWN"])))
		{
			if (!CheckSpriteCollision(dt, "DOWN"))
			{
				m_Player.GetMovement().SetVelocityX(0);
				m_Player.Move(dt, 0.f, (running ? 2.f : 1.f));
			}
			else
				m_Player.GetAnimation().PlayAnimation(0, dt, "DOWN");
		}
		else if (controller_position.x < -80 || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["LEFT"])))
		{
			if (!CheckSpriteCollision(dt, "LEFT"))
			{
				m_Player.GetMovement().SetVelocityY(0);
				m_Player.Move(dt, (running ? -2.f : -1.f), 0.f);
			}
			else
				m_Player.GetAnimation().PlayAnimation(0, dt, "LEFT");
		}
		else if (controller_position.x > 80 || Keyboard::isKeyPressed(Keyboard::Key(m_Actions["RIGHT"])))
		{
			if (!CheckSpriteCollision(dt, "RIGHT"))
			{
				m_Player.GetMovement().SetVelocityY(0);
				m_Player.Move(dt, (running ? 2.f : 1.f), 0.f);
			}
			else
				m_Player.GetAnimation().PlayAnimation(0, dt, "RIGHT");
		}
	}
}

void GameState::ChangeMap(const Color& color)
{
	if (m_CurrentMap == "Courtyard")
	{
		if (color == Color::Blue)
		{
			m_CurrentMap = "Hogwarts_Hallways";
			m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
		else if (color == Color::Green)
		{
			m_CurrentMap = "Library";
			m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
		else if (color == Color::Yellow)
		{
			m_CurrentMap = "Potions_Room";
			m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
		else if (color == Color::Magenta)
		{
			m_CurrentMap = "The_Great_Hall";
			m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
	}
	else if (m_CurrentMap == "Hogwarts_Hallways")
	{
		if (color == Color::Red)
		{

		}
		else if (color == Color::Red)
		{

		}
		else if (color == Color::Red)
		{
		}
	}
	else if (m_CurrentMap == "Library")
	{
		if (color == Color::Red)
		{

		}
		else if (color == Color::Red)
		{

		}
		else if (color == Color::Red)
		{

		}
	}
	else if (m_CurrentMap == "Potions_Room")
	{
		if (color == Color::Blue)
		{
			m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("FROM_BLUE"));
			ResetView();
		}
		else if (color == Color::Magenta)
		{
			m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("FROM_MAGENTA"));
			ResetView();
		}
		else if (color == Color::Green)
		{
			m_CurrentMap = "Library";
			m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("START"));
			ResetView(true);
		}
	}
	else if (m_CurrentMap == "The_Great_Hall")
	{
		if (color == Color::Magenta)
		{
			m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("FROM_BLUE"));
			ResetView();
		}
		else if (color == Color::Blue)
		{
			m_Player.GetSprite().setPosition(m_Maps[m_CurrentMap]->GetStartingPosition("FROM_MAGENTA"));
			ResetView();
		}
		else if (color == Color::Red)
		{

		}
	}
}

void GameState::Update(const float& dt)
{
	m_MousePosition = m_Window.mapPixelToCoords(Mouse::getPosition(m_Window));

	m_Player.Update(dt);
	
	HandleInput(-1, dt);

	ResetView();

	for (auto &it : m_GUI)
		it.second->Update(dt);

	if (m_CantMove)
	{
		m_Transition.Update();
		if (m_Transition.GetStatus() == TransitionStatus::HALF)
		{
			ChangeMap(m_TransitionColor);
			MiniMapGUI *tmp = static_cast<MiniMapGUI*>(m_GUI["MINI_MAP"]);
			tmp->SetTexture(*m_Maps[m_CurrentMap]->GetTexture());
		}
		else if (m_Transition.GetStatus() == TransitionStatus::COMPLETE)
		{
			m_CantMove = false;
		}
	}
}

void GameState::Render(RenderTarget& target)
{
	// Change the view
	target.setView(m_PlayerView);
	m_Maps[m_CurrentMap]->Render(target);
	m_Player.Render(target);
	//target.draw(m_ViewArea); // Render the camera area

	// Reset the view
	target.setView(m_Window.getDefaultView());
	
	for (auto &it : m_GUI)
		it.second->Render(target);
	
	if (m_CantMove)
	{
		m_Transition.Render(target);
	}

}

/////////////////////////////////////////////////////////////////////
/// Initializes the map of Maps with the parameters in the files "Maps/Maps.cfg"
/// Format : 
/// Map_name >> map_path >> collision_map_path
/////////////////////////////////////////////////////////////////////
void GameState::InitMaps(int scale)
{
	std::ifstream config_file("../External/Config/Maps/Maps.cfg");
	if (config_file.is_open())
	{
		std::string map_name = "", map_path = "", collision_map_path = "", starting_position = "";
		while (config_file >> map_name >> map_path >> collision_map_path >> starting_position)
		{
			m_Maps[map_name] = new Map(map_path, scale);
			m_Maps[map_name]->InitPositions(starting_position);
			m_CollisionsMaps[map_name] = new Map(collision_map_path, scale, true);
		}
		config_file.close();
	}
	m_CurrentMap = "Courtyard";
}

void GameState::InitView()
{
	int sprite_scale = m_Player.GetSprite().getScale().x;
	// These are the limits for the movement of the camera. If the m_Player goes behond, the camera stops moving
	m_LockView["LEFT"] = m_Maps[m_CurrentMap]->GetPosition().x + m_Window.getSize().x / 2;
	m_LockView["RIGHT"] = m_Maps[m_CurrentMap]->GetPosition().x + (m_Maps[m_CurrentMap]->GetSize().x * sprite_scale) - (m_Window.getSize().x / 2);
	m_LockView["UP"] = m_Maps[m_CurrentMap]->GetPosition().y + m_Window.getSize().y / 2;
	m_LockView["DOWN"] = m_Maps[m_CurrentMap]->GetPosition().y + (m_Maps[m_CurrentMap]->GetSize().y * sprite_scale) - (m_Window.getSize().y / 2);

	Vector2f sprite_size(m_Player.GetSprite().getGlobalBounds().width, m_Player.GetSprite().getGlobalBounds().height);

	m_PlayerView.setCenter(m_Player.GetSprite().getPosition().x + sprite_size.x / 2, m_Player.GetSprite().getPosition().y + sprite_size.y / 2);
}

void GameState::InitGUI(const std::string& player_name)
{
	m_GUI["PLAYER"] = new PlayerGUI(m_Window, &m_Player, player_name);
	m_GUI["MINI_MAP"] = new MiniMapGUI(m_Window, &m_Player, *m_Maps[m_CurrentMap]->GetTexture());
	m_GUI["CHAT_BOX"] = new ChatBoxGUI(m_Window, &m_Player);
	m_GUI["MENU"] = new MenuGUI(m_Window, &m_Player);
}

void GameState::ResetView(bool new_map)
{
	Vector2f sprite_size(m_Player.GetSprite().getGlobalBounds().width, m_Player.GetSprite().getGlobalBounds().height);

	// If the map changes, we have to modify the previous value of m_LockView
	if (new_map)
		InitView();
	else
		m_PlayerView.setCenter(m_Player.GetSprite().getPosition().x + sprite_size.x / 2, m_Player.GetSprite().getPosition().y + sprite_size.y / 2);

	if (m_PlayerView.getCenter().x < m_LockView["LEFT"])
	{
		m_PlayerView.setCenter(m_LockView["LEFT"], m_PlayerView.getCenter().y);
	}
	else if (m_PlayerView.getCenter().x >= m_LockView["RIGHT"])
	{
		m_PlayerView.setCenter(m_LockView["RIGHT"] - 1, m_PlayerView.getCenter().y);
	}
	if (m_PlayerView.getCenter().y < m_LockView["UP"])
	{
		m_PlayerView.setCenter(m_PlayerView.getCenter().x, m_LockView["UP"]);
	}
	else if (m_PlayerView.getCenter().y >= m_LockView["DOWN"])
	{
		m_PlayerView.setCenter(m_PlayerView.getCenter().x, m_LockView["DOWN"] - 1);
	}
}

bool GameState::CheckSpriteCollision(const float & dt,std::string movement)
{
	// Collision are tested on a copy of the map (m_CollisionsMaps). The areas that can't be crossed by the m_Player are in red (255, 0, 0).
	Vector2f sprite_position = Vector2f(m_Player.GetSprite().getPosition().x / m_CollisionsMaps[m_CurrentMap]->GetScale(), m_Player.GetSprite().getPosition().y / m_CollisionsMaps[m_CurrentMap]->GetScale());
	sprite_position = Vector2f(std::roundl(sprite_position.x), std::roundl(sprite_position.y));

	Vector2f sprite_size = Vector2f(m_Player.GetSprite().getGlobalBounds().width / m_CollisionsMaps[m_CurrentMap]->GetScale(), m_Player.GetSprite().getGlobalBounds().height / m_CollisionsMaps[m_CurrentMap]->GetScale());

	Color pixel_toward_color[3];

	if (movement == "UP")
	{
		pixel_toward_color[0] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + 1, sprite_position.y + sprite_size.y - 1);
		pixel_toward_color[1] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + sprite_size.x / 2 , sprite_position.y - 1 + sprite_size.y);
		pixel_toward_color[2] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x - 1 + sprite_size.x, sprite_position.y - 1 + sprite_size.y);
	}
	else if (movement == "DOWN")
	{
		pixel_toward_color[0] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + 1, sprite_position.y + sprite_size.y + 1);
		pixel_toward_color[1] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + sprite_size.x / 2, sprite_position.y + sprite_size.y + 1);
		pixel_toward_color[2] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x - 1 + sprite_size.x, sprite_position.y + sprite_size.y + 1);
	}
	else if (movement == "LEFT")
	{
		pixel_toward_color[0] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x - 1, std::min(sprite_position.y + sprite_size.y, m_Maps[m_CurrentMap]->GetSize().y));
		// Others are not required
		pixel_toward_color[1] = Color::Black;
		pixel_toward_color[2] = Color::Black;
	}
	else if (movement == "RIGHT")
	{
		pixel_toward_color[0] = m_CollisionsMaps[m_CurrentMap]->GetPixelColor(sprite_position.x + sprite_size.x + 1, std::min(sprite_position.y + sprite_size.y, m_Maps[m_CurrentMap]->GetSize().y));
		pixel_toward_color[1] = Color::Black;
		pixel_toward_color[2] = Color::Black;
	}
	for (auto &it : pixel_toward_color)
	{
		if (it == Color::Red)
		{
			m_Player.GetAnimation().SetSide(StringToSide(movement));
			return true;
		}
		else if (it == Color::Magenta || it == Color::Blue || it == Color::Green || it == Color::Yellow)
		{
			m_CantMove = true;
			m_TransitionColor = it;
			return true;
		}
	}
	return false;
}