#include "common.h"

//#define LOG_CONTROLS

// Make menu.c match this.

u32 config_to_io_map[] =
{
  IO_BUTTON_UP,
  IO_BUTTON_DOWN,
  IO_BUTTON_LEFT,
  IO_BUTTON_RIGHT,
  IO_BUTTON_I,
  IO_BUTTON_II,
  IO_BUTTON_III,
  IO_BUTTON_IV,
  IO_BUTTON_V,
  IO_BUTTON_VI,
  IO_BUTTON_RUN,
  IO_BUTTON_SELECT
};

void update_events(void)
{
  event_input_struct event_input;
  u32 config_button_action;

  static u32 rapid_fire_state = 0;
  static u32 rapid_fire_mask = 0;
  static u32 button_status = 0xFFFFFFFF;

  while(update_input(&event_input))
  {
    {
      config_button_action = event_input.config_button_action;    
      if(config_button_action <= CONFIG_BUTTON_SELECT)
      {
        u32 io_button = config_to_io_map[config_button_action];
        if(event_input.action_type == INPUT_ACTION_TYPE_RELEASE)
          button_status |= io_button;
        else
          button_status &= ~io_button;
      }
      else
  
      if(config_button_action <= CONFIG_BUTTON_RAPID_VI)
      {
        static u32 config_rapid_to_io_map[] =
        {
          IO_BUTTON_I, IO_BUTTON_II, IO_BUTTON_III,
          IO_BUTTON_IV, IO_BUTTON_V, IO_BUTTON_VI
        };

        u32 rapid_fire_io_button =
         config_rapid_to_io_map[config_button_action - CONFIG_BUTTON_RAPID_I];
  
        if(event_input.action_type == INPUT_ACTION_TYPE_RELEASE)
          rapid_fire_mask &= ~rapid_fire_io_button;
        else
          rapid_fire_mask |= rapid_fire_io_button;
      }
      else

      if(event_input.action_type == INPUT_ACTION_TYPE_PRESS)
      {
        switch(config_button_action)
        {
          case CONFIG_BUTTON_MENU:
            menu(0);
            return;

          case CONFIG_BUTTON_LOAD_STATE:
          {
            char state_name[MAX_PATH];
            sprintf(state_name, "%s_%d.svs.tns", config.rom_filename,
             config.savestate_number);

            load_state(state_name, NULL, 0);
            return;
          }

          case CONFIG_BUTTON_SAVE_STATE:
          {
            char state_name[MAX_PATH];
            sprintf(state_name, "%s_%d.svs.tns", config.rom_filename,
             config.savestate_number);
  
            if((config.snapshot_format) == SS_SNAPSHOT_OFF)
            {
              save_state(state_name, NULL);
            }
            else
            {
              u16 *screen_capture = malloc(320 * 240 * sizeof(u16));
              copy_screen(screen_capture);
              save_state(state_name, screen_capture);
              free(screen_capture);
            }
            break;
          }
  
          case CONFIG_BUTTON_FAST_FORWARD:
            config.fast_forward ^= 1;
            break;
        }
      }

      switch(event_input.key_action)
      {
        case KEY_ACTION_QUIT:
          quit();
          break;

        case KEY_ACTION_BG_OFF:
          config.bg_off ^= 1;
          break;

        case KEY_ACTION_SPR_OFF:
          config.spr_off ^= 1;
          break;

        case KEY_ACTION_DEBUG_BREAK:
          set_debug_mode(DEBUG_STEP);
          break;
      }

      if(event_input.hat_status != HAT_STATUS_NONE)
      {
        u32 hat_buttons_press = 0;
        switch(event_input.hat_status)
        {
          case HAT_STATUS_UP:
            hat_buttons_press = IO_BUTTON_UP;
            break;

          case HAT_STATUS_DOWN:
            hat_buttons_press = IO_BUTTON_DOWN;
            break;

          case HAT_STATUS_LEFT:
            hat_buttons_press = IO_BUTTON_LEFT;
            break;

          case HAT_STATUS_RIGHT:
            hat_buttons_press = IO_BUTTON_RIGHT;
            break;

          case HAT_STATUS_UP_RIGHT:
            hat_buttons_press = IO_BUTTON_UP | IO_BUTTON_RIGHT;
            break;
  
          case HAT_STATUS_DOWN_RIGHT:
            hat_buttons_press = IO_BUTTON_DOWN | IO_BUTTON_RIGHT;
            break;

          case HAT_STATUS_UP_LEFT:
            hat_buttons_press = IO_BUTTON_UP | IO_BUTTON_LEFT;
            break;

          case HAT_STATUS_DOWN_LEFT:
            hat_buttons_press = IO_BUTTON_DOWN | IO_BUTTON_LEFT;
            break;

          default:
            break;
        }
        button_status |=
         (IO_BUTTON_UP | IO_BUTTON_DOWN | IO_BUTTON_LEFT | IO_BUTTON_RIGHT) &
         ~hat_buttons_press;
        button_status &= ~hat_buttons_press;
      }
    }
  }

  if(rapid_fire_state)
    button_status &= ~rapid_fire_mask;
  else
    button_status |= rapid_fire_mask;

  rapid_fire_state ^= 1;

  {
    io.button_status[0] = button_status;
  }

#ifdef LOG_CONTROLS
  static FILE *control_log = NULL;
  static u32 frame_number = 0;

  {
    if(control_log)
      fclose(control_log);    
  }
#endif
}

