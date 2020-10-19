#pragma once

#include "object.hpp"

#include <SDL.h>

#include <string>

class MoleApp;

void callback(void * userdata, Uint8 * stream, int len);

class SoundHelper : public Object
{

public:
    SoundHelper( MoleApp * const app, const char * const sound=nullptr );

    int play();

private:
    Uint8 * audio_pos;
    Uint32 audio_len;
	Uint8 * wav_buffer;
    Uint32 wav_length;
	SDL_AudioSpec wav_spec;

    struct UserData
    {
        Uint8 * audio_pos;
        SDL_AudioFormat format;
    };

friend void callback(void * userdata, Uint8 * stream, int len);
    
};



#include "main.hpp"