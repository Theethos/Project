#include "Precompiled_Header.h"
#include "../Include/Macros.h"
#include "../Include/MusicComponent.h"

// Constructor
MusicComponent::MusicComponent(std::string path) : isPlaying(nullptr), waitingBeforePlay(2.5)
{
	this->InitMusics(path);
}
// Destructor
MusicComponent::~MusicComponent()
{
	for (auto &it : this->musics)
	{
		delete it.second.first;
	}
}

// Functions
void MusicComponent::InitMusics(std::string path)
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

void MusicComponent::Play(const float &dt, std::string music_key)
{ 
	if (this->musics.count(music_key))
	{
		// Updates the timer
		this->musics[music_key].second += dt;
		// If it is high enough
		if (this->musics[music_key].second >= this->waitingBeforePlay)
		{
			// If this music is not playing
			if (this->isPlaying != &this->musics[music_key])
			{
				// If isPlaying is not nullptr
				if (this->isPlaying)
				{
					// Then it resets it timer and its sound
					this->isPlaying->first->setVolume(0);
					this->isPlaying->second = 0;
				}
				// Change isPlaying pointer
				this->isPlaying = &this->musics[music_key];
				// Play the music
				this->isPlaying->first->play();
			}
			// If this music was playing but was paused
			else if (this->isPlaying && this->isPlaying->first->getStatus() == sf::Music::Status::Paused)
			{
				// Resumes it
				this->isPlaying->first->play();
			}
			// If this music is playing and its volume is not max, then it rises
			else
			{
				if (this->isPlaying->first->getVolume() < 100)
				{
					this->isPlaying->first->setVolume(this->isPlaying->first->getVolume() + 5 * dt);
				}
			}
		}
	}
}

void MusicComponent::Pause(std::string music_key)
{
	if (this->musics.count(music_key) && this->isPlaying == &this->musics[music_key])
	{
		this->musics[music_key].first->pause();
	}
}

void MusicComponent::Stop(std::string music_key)
{
	if (this->musics.count(music_key) && this->isPlaying == &this->musics[music_key])
	{
		this->musics[music_key].first->stop();
	}
}

// Getter
const std::pair<sf::Music*, float >* MusicComponent::getPlay() const
{
	return this->isPlaying;
}
