#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/TransitionComponent.h"

// Constructor
TransitionComponent::TransitionComponent(unsigned int width, unsigned int height) :
status(TransitionStatus::NONE)
{
	this->color.r = 0;
	this->color.g = 0;
	this->color.b = 0;
	this->color.a = 0;

	this->transitionScreen.setSize(sf::Vector2f(width, height));
	this->transitionScreen.setFillColor(this->color);
}
TransitionComponent::TransitionComponent(sf::Vector2u size) :
status(TransitionStatus::NONE)
{
	this->color.r = 0;
	this->color.g = 0;
	this->color.b = 0;
	this->color.a = 0;

	this->transitionScreen.setSize(sf::Vector2f(size.x, size.y));
	this->transitionScreen.setFillColor(this->color);
}
// Destructor
TransitionComponent::~TransitionComponent()
{}

// Functions
void TransitionComponent::Update()
{
	switch (this->status)
	{
	case TransitionStatus::NONE:
		this->color.a += 1;
		if (this->color.a == 255)
			this->status = TransitionStatus::HALF;
		break;
	case TransitionStatus::HALF:
		this->status = TransitionStatus::WAIT_COMPLETE;
		break;
	case TransitionStatus::WAIT_COMPLETE:
		this->color.a -= 1;
		if (this->color.a == 0)
			this->status = TransitionStatus::COMPLETE;
		break;
	case TransitionStatus::COMPLETE:
		this->status = TransitionStatus::NONE;
		break;
	default:
		break;
	}
	this->transitionScreen.setFillColor(this->color);
}

void TransitionComponent::Render(sf::RenderTarget * target)
{
	target->draw(this->transitionScreen);
}

// Getters
const TransitionStatus & TransitionComponent::getStatus() const
{
	return this->status;
}

const sf::Color & TransitionComponent::getColor() const
{
	return this->color;
}
