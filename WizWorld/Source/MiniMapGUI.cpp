#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/MiniMapGUI.h"


const float MiniMapGUI::_miniMapScale = 0.3;


MiniMapGUI::MiniMapGUI(sf::RenderWindow &window, Player & player) :
GUI(window, player)
{
	_playerPosition.setRadius(2);
	_playerPosition.setFillColor(sf::Color::Red);
}

MiniMapGUI::~MiniMapGUI()
{
}

void MiniMapGUI::Update(const float & dt)
{
	if (!sf::Joystick::isConnected(0) && (!GUI::_token || _move))
		Move();

	if (_mapTexture->getSize().x > _mapShape.getSize().x || _mapTexture->getSize().y > _mapShape.getSize().y)
		setTexture(_mapTexture);
	
	UpdatePlayerPosition();
}

void MiniMapGUI::Render(sf::RenderTarget * target)
{
	if (_visible)
	{
		if (!target)
			target = &_window;

		target->draw(_globalShape);
		target->draw(_mapShape);
		target->draw(_playerPosition);
	}
}

void MiniMapGUI::Init(sf::RenderWindow & window, sf::Texture * mapTexture)
{
	_mapTexture = mapTexture;
	
	_mapShape.setSize(sf::Vector2f(_mapTexture->getSize()));
	_mapShape.setTexture(_mapTexture);
	_mapShape.setScale(_miniMapScale, _miniMapScale);
	
	_globalShape.setSize(sf::Vector2f(_mapShape.getSize().x * _miniMapScale, _mapShape.getSize().y * _miniMapScale) + sf::Vector2f(_window.getSize().x * 0.01, _window.getSize().x * 0.01));
	_globalShape.setFillColor(_globalColor);

	_globalShape.setPosition(sf::Vector2f(_window.getSize().x - _globalShape.getSize().x , _window.getPosition().y));
	_mapShape.setPosition(_globalShape.getPosition() + sf::Vector2f(_globalShape.getSize().x / 2 - _mapShape.getSize().x * _miniMapScale / 2,
																	_globalShape.getSize().y / 2 - _mapShape.getSize().y * _miniMapScale / 2));
	_mapShape.setTextureRect(sf::IntRect(0, 0, _mapShape.getSize().x,_mapShape.getSize().y));

}

void MiniMapGUI::setTexture(sf::Texture * texture)
{
	if (_mapTexture != texture)
	{
		_mapTexture = texture; 
		_mapShape.setTexture(_mapTexture);
	}
	
	_mapShape.setTextureRect(sf::IntRect((_player.getSprite()->getPosition().x / _player.getSprite()->getScale().x - _mapShape.getSize().x / 2),
										 (_player.getSprite()->getPosition().y / _player.getSprite()->getScale().y - _mapShape.getSize().y / 2),
										 _mapShape.getTextureRect().width, _mapShape.getTextureRect().height));

}

void MiniMapGUI::UpdatePosition(const sf::Vector2f & mousPos)
{
	_globalShape.setPosition(mousPos);
	_mapShape.setPosition(_globalShape.getPosition() + sf::Vector2f(_globalShape.getSize().x / 2 - _mapShape.getSize().x * _miniMapScale / 2,
						  _globalShape.getSize().y / 2 - _mapShape.getSize().y * _miniMapScale / 2));
}

void MiniMapGUI::UpdatePlayerPosition()
{
	// If the texture is bigger than the shape, the player is always on center of the minimap, and it is the minimap that moves
	if (_mapTexture->getSize().x > _mapShape.getSize().x || _mapTexture->getSize().y > _mapShape.getSize().y)
		_playerPosition.setPosition(_globalShape.getPosition() + sf::Vector2f(_globalShape.getSize().x / 2, _globalShape.getSize().y / 2));
	// Else, the minimap is fixed and the player moves on it
	else
		_playerPosition.setPosition(_mapShape.getPosition() + sf::Vector2f(
			(_player.getSprite()->getPosition().x / _player.getSprite()->getScale().x) * _miniMapScale,
			(_player.getSprite()->getPosition().y / _player.getSprite()->getScale().y) * _miniMapScale));
}
