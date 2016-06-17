#include "../common.h"


void audio_callback(void *userdata, Uint8 *stream, int length)
{
 
}

void initialize_audio()
{
  audio.playback_buffer_size = 512;
  audio.pause_state = 1;
  audio.playback_buffer_size = 2048;
  audio.output_frequency = 8000;
}

void audio_exit()
{
}

// Do not do either of these two without first locking/unlocking audio
// (see functions below)

void audio_signal_callback()
{
}

void audio_wait_callback()
{
 
}

void audio_lock()
{
}

void audio_unlock()
{
}

u32 audio_pause()
{
  
}

void audio_unpause()
{

}

