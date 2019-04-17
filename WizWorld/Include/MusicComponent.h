#ifndef MUSIC_COMPONENT_H
#define MUSIC_COMPONENT_H

class MusicComponent
{
public:
	// Constructor
	MusicComponent(std::string path);
	// Destructor
	virtual ~MusicComponent();

	// Functions
	void Play(const float &dt, std::string music_key);
	void Pause(std::string music_key);
	void Stop(std::string music_key);

	// Getter 
	const std::pair<sf::Music*, float >* getPlay() const;

private:
	// The float parameter is the timer to launch the music
	std::map<std::string, std::pair<sf::Music*, float>> musics;
	// Pointer to the music currently played
	std::pair<sf::Music*, float >* isPlaying;
	// Time between two music
	float waitingBeforePlay;
	
	// Private functions
	void InitMusics(std::string path);
};

#endif // !MUSIC_COMPONENT_H

