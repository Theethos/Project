#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/MusicComponent.h"

MusicComponent::MusicComponent(std::string path) : isPlaying(nullptr), waitingBeforePlay(2.5)
{
	this->initMusics(path);
}

MusicComponent::~MusicComponent()
{
	for (auto &it : this->musics)
	{
		delete it.second.first;
	}
}

void MusicComponent::initMusics(std::string path)
{
	std::ifstream config_file(path);

	if (config_file.is_open())
	{
		std::string key = "", music_path = "";
		while (config_file >> key >> music_path)
		{
			this->musics[key].first = new sf::Music();
			this->musics[key].first->openFromFile(music_path);
			this->musics[key].first->setVolume(0);
			this->musics[key].first->setLoop(true);
			this->musics[key].second = 0;
		}
		config_file.close();
	}
}

void MusicComponent::play(const float &dt, std::string music_key)
{ 
	if (this->musics.count(music_key))
	{
		this->musics[music_key].second += dt;
	}
	if (this->musics.count(music_key) && this->musics[music_key].second >= this->waitingBeforePlay)
	{
		if (this->isPlaying != &this->musics[music_key])
		{
			if (this->isPlaying)
			{
				this->isPlaying->first->setVolume(0);
				this->isPlaying->second = 0;
			}
			this->isPlaying = &this->musics[music_key];
			this->isPlaying->first->play();
		}
		else if (this->isPlaying && this->isPlaying->first->getStatus() == sf::Music::Status::Paused)
		{
			this->isPlaying->first->play();
		}
		else
		{
			if (this->isPlaying->first->getVolume() < 100)
			{
				this->isPlaying->first->setVolume(this->isPlaying->first->getVolume() + 5 * dt);
			}
		}
	}
}

void MusicComponent::pause(std::string music_key)
{
	if (this->musics.count(music_key) && this->isPlaying == &this->musics[music_key])
	{
		this->musics[music_key].first->pause();
	}
}

void MusicComponent::stop(std::string music_key)
{
	if (this->musics.count(music_key) && this->isPlaying == &this->musics[music_key])
	{
		this->musics[music_key].first->stop();
	}
}

const std::pair<sf::Music*, float >* MusicComponent::getPlay() const
{
	return this->isPlaying;
}
