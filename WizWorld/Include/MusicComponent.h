#ifndef MUSIC_COMPONENT_H
#define MUSIC_COMPONENT_H

class MusicComponent
{
public:
	MusicComponent(std::string path);
	virtual ~MusicComponent();

	void initMusics(std::string path);

	void play(const float &dt, std::string music_key);
	void pause(std::string music_key);
	void stop(std::string music_key);

	//Getters
	const std::pair<sf::Music*, float >* getPlay() const;

private:
	std::map<std::string, std::pair<sf::Music*, float>> musics;
	std::pair<sf::Music*, float >* isPlaying;
	// Time between two music
	float waitingBeforePlay;
};

#endif // !MUSIC_COMPONENT_H

