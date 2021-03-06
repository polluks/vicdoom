enum ESound
{
	SOUND_CLAW,
	SOUND_DMPAIN,
	SOUND_DOROPN,
	SOUND_DORCLS,
	SOUND_ITEMUP,
	SOUND_OOF,
	SOUND_GURGLE,
	SOUND_PISTOL,
	SOUND_PLPAIN,
	SOUND_POPAIN,
	SOUND_SGCOCK,
	SOUND_SGTDTH,
	SOUND_SHOTGN,
	SOUND_STNMOV,
  SOUND_SAWIDL,
  SOUND_SAWFUL,
  SOUND_SAWHIT,
  SOUND_PUNCH
};

void __fastcall__ playSoundInitialize(void);
void __fastcall__ playSound(char soundIndex);

void __fastcall__ setEffectsVolume(char vol);
char __fastcall__ getEffectsVolume(void);

void __fastcall__ startMusic(void);
void __fastcall__ stopMusic(void);

void __fastcall__ setMusicVolume(char vol);
char __fastcall__ getMusicVolume(void);

char __fastcall__ getTickCount(void);
void __fastcall__ setTickCount(void);

void __fastcall__ resetMapTime(void);
int __fastcall__ getMapTime(void);
void __fastcall__ pauseMapTimer(void);
void __fastcall__ playMapTimer(void);
