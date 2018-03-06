////MAIN.cpp
//in game loop
SoundManager.PlayNextMusic();


////SOUND.h
class CSoundManager
{
public:
    //set default member values
    CSoundManager();//constructor
	~CSoundManager();//destructor

	//initialise sound manager
	void SetupSoundManager();
	//release sound manager
	void ReleaseSoundManager();

	//MUSIC
	//load music
	void LoadMusic(const string &sFilename);//filepath
	//unload music
	void UnloadMusic(const string &sFilename);//filepath
	//unload all music
	void ClearMusic();
	//play music
	void PlayMusic(const string &sFilename);//filepath
	//stop music
	void StopMusic(const string &sFilename);//filepath
	//pause music
	void PauseMusic();
	//set music position
	void SetMusicPosition(const float &fPositionPercent);
	//set music volume
	void SetMusicVolume(const float &fMaxVolumePercent);//max volume
	//check if music is playing
	bool IsMusicPlaying(void);
	//add music to queue
	void AddMusicToQueue(const string &sFilename);//filepath
	//sort list of loaded music
	void SortMusic();
	//if the current music is not playing, then play the next music in queue, othewise random music
	void PlayNextMusic();

	//SOUND
	//load sound
	void LoadSound(const string &sFilename);//filepath
	//unload sound
	void UnloadSound(const string &sFilename);//filepath
	//unload all sounds
	void ClearSounds();
	//play sound
	void PlaySound(const string &sFilename,const float &fSoundVolumePercent,const float &fMaxVolumePercent);//filepath, sound volume, max volume
	//stop sound
	void StopSound(const string &sFilename);//filepath
	//stop all sounds
	void StopAllSounds();

//private: //(everything public for testing purposes)
	//MUSIC STRUCT
	struct STREAMMUSIC
    {
		//filepath of music
		string m_sFilename;
		//handle to a stream (music)
		FSOUND_STREAM *m_streMusicHandle;
		//operator to sort music struct
		bool operator<(const STREAMMUSIC &Music) const {return m_sFilename<Music.m_sFilename;}
    };

	//current music playing
	STREAMMUSIC *m_pCurrentStreamMusic;
	//channel that the music is playing on
	int m_nMusicChannel;
	//is the current music stream paused
	bool m_bPaused;

	//list of all loaded music
	static vector <STREAMMUSIC> m_lstLoadedMusicList;

	//list of queued music to play
	static vector <STREAMMUSIC*> m_lstQueuedMusicList;

	//SOUND STRUCT
	struct SAMPLESOUND
    {
		//filepath of sound
		string m_sFilename;
		//handle to a sample (sound)
		FSOUND_SAMPLE *m_sampSoundHandle;
		//channel that the sound is playing on
		int m_nSoundChannel;
    };

	//list of all loaded sounds
	static vector <SAMPLESOUND> m_lstLoadedSoundList;
};


////SOUND.cpp
//check if music is playing
bool CSoundManager::IsMusicPlaying(void)
{
	if(m_pCurrentStreamMusic==NULL)
		return false;

	//get the current position and the duration of the music stream in milliseconds
	int nPosition=FSOUND_Stream_GetTime(m_pCurrentStreamMusic->m_streMusicHandle);
	int nDuration=FSOUND_Stream_GetLengthMs(m_pCurrentStreamMusic->m_streMusicHandle);

	//the music stream is still playing if the current position is less then the duration
	if(nPosition<nDuration)
		return true;//playing
	else
		return false;//finished
}

//if the current music is not playing, then play the next music in queue, othewise random music
void CSoundManager::PlayNextMusic()
{
	bool bResult=IsMusicPlaying();
	if(bResult==false)
	{
		g_Log<<"m_lstQueuedMusicList.empty"<<endl;
		if(m_lstQueuedMusicList.empty()==false)
		{
			//play next music in queue
			vector<STREAMMUSIC*>::iterator itQueuedMusic=m_lstQueuedMusicList.begin();

			//set current music
			m_pCurrentStreamMusic=(*itQueuedMusic);

			int nChannel=-1;
			int nFailCount=0;//when the stream fails to play 10 times, give up
			while(nChannel==-1)
			{
				//play music
				nChannel=m_nMusicChannel=FSOUND_Stream_Play(FSOUND_FREE,m_pCurrentStreamMusic->m_streMusicHandle);

				if(nChannel==-1)
				{
					++nFailCount;
					g_Log<<"SoundManager->PlayNextMusic("<<m_pCurrentStreamMusic->m_sFilename<<"): FAILED"<<endl;
					if(nFailCount>9)//stream failed to play 10 times, don't bother trying to play sound
						return;
				}
			}
		return;
		}
		//else play random music

		//set current music
		m_pCurrentStreamMusic=&m_lstLoadedMusicList[int((m_lstLoadedMusicList.size()+1)*rand()/(RAND_MAX+1.0))];

		int nChannel=-1;
		int nFailCount=0;//when the stream fails to play 10 times, give up
		while(nChannel==-1)
		{
			//play music

			g_Log<<"PlayNextMusic m_pCurrentStreamMusic->m_streMusicHandle="<<m_pCurrentStreamMusic->m_streMusicHandle<<endl;
			g_Log<<"PlayNextMusic index="<<int((m_lstLoadedMusicList.size()+1)*rand()/(RAND_MAX+1.0))<<endl;

			nChannel=FSOUND_Stream_Play(m_nMusicChannel,m_pCurrentStreamMusic->m_streMusicHandle);

			g_Log<<"PlayNextMusic nChannel="<<nChannel<<endl;

			if(nChannel==-1)
			{
				++nFailCount;
				g_Log<<"SoundManager->PlayMusic("<<m_pCurrentStreamMusic->m_sFilename<<"): FAILED"<<endl;
				if(nFailCount>9)//stream failed to play 10 times, don't bother trying to play sound
					return;
			}
		}
		return;
	}
}
