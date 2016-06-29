#include "../common.h"

#include "n2DLib.h"

void get_ticks_us(u64 *ticks_return)
{
}

void delay_us(u32 delay)
{
	sleep(delay/100);
}

config_struct config =
{
  // u32 pad[16];
  {
    CONFIG_BUTTON_UP, CONFIG_BUTTON_DOWN, CONFIG_BUTTON_LEFT,
    CONFIG_BUTTON_RIGHT, CONFIG_BUTTON_I, CONFIG_BUTTON_II,
    CONFIG_BUTTON_III, CONFIG_BUTTON_IV, CONFIG_BUTTON_V,
    CONFIG_BUTTON_VI, CONFIG_BUTTON_SELECT, CONFIG_BUTTON_RUN,
    CONFIG_BUTTON_NONE, CONFIG_BUTTON_NONE, CONFIG_BUTTON_NONE,
    CONFIG_BUTTON_NONE
  },
  0,                 // u32 show_fps;
  1,                 // u32 enable_sound;
  0,                 // u32 fast_forward;
  8000,             // u32 audio_output_frequency;
  1,                 // u32 patch_idle_loops;
  SS_SNAPSHOT_OFF,   // u32 snapshot_format;
  0,                 // u32 force_usa;

  300,               // u32 clock_speed; hurr mr pc is faster
  0,                 // u32 gp2x_ram_timings;
  100,               // u32 gp2x_gamma_percent;
  0,                 // u32 six_button_pad;
  CD_SYSTEM_TYPE_V3, // cd_system_type_enum cd_system_type;
  1,                 // u32 bz2_savestates;
  0,                 // u32 per_game_bram;
  0,                 // u32 sound_double;
  0,          // u32 scale_factor;
  0,                 // u32 fast_cd_access;
  0,                 // u32 fast_cd_load;
  0,                 // u32 scale_width;
  0,                 // u32 unlimit_sprites
  0,                 // u32 compatibility_mode

  "Temper User",     // char netplay_username[16];
  0, // u32 netplay_type;
  12345,             // u32 netplay_port;
  0x7F000001,        // u32 netplay_ip;
  3,                 // u32 netplay_server_frame_latency;
};

void synchronize()
{
}

void platform_initialize()
{
	initBuffering();
	clearBufferB();
	updateScreen();
}

void platform_quit()
{
	deinitBuffering();
}

