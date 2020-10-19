#include "soundhelper.hpp"

SoundHelper::SoundHelper( MoleApp * const app, const char * const name) : Object(app)
{
    if (SDL_LoadWAV(name, &wav_spec, &wav_buffer, &wav_length) == NULL)
    {
        return ;
    }
	UserData userData {audio_pos, wav_spec.format};
	wav_spec.callback = callback;
	wav_spec.userdata = reinterpret_cast<void *>(&userData);
	audio_pos = wav_buffer;
	audio_len = wav_length;
}

int SoundHelper::play()
{
	int code;
	std::cout<<SDL_GetNumAudioDrivers()<<std::endl;

    //if ( (code = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, 0), 0, &wav_spec, NULL, SDL_AUDIO_ALLOW_FORMAT_CHANGE)) < 0 )
    if ( (code = SDL_OpenAudio(&wav_spec, NULL)) < 0 )
    {
		std::cout<<SDL_GetError()<<std::endl;
      	return code;
	}
	return 0;
}

void callback(void * userdata, Uint8 * stream, int len)
{
	std::cout<<reinterpret_cast<SoundHelper::UserData *>(userdata)->audio_pos<<std::endl;
	SDL_MixAudioFormat(stream, reinterpret_cast<SoundHelper::UserData *>(userdata)->audio_pos, reinterpret_cast<SoundHelper::UserData *>(userdata)->format, len, SDL_MIX_MAXVOLUME);
}