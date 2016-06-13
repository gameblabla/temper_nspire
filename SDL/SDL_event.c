#include "../common.h"
#include "SDL_event.h"

u32 key_map(u32 keys)
{
  switch(keys)
  {
    case SDLK_UP:
      return CONFIG_BUTTON_UP;

    case SDLK_DOWN:
      return CONFIG_BUTTON_DOWN;

    case SDLK_LEFT:
      return CONFIG_BUTTON_LEFT;

    case SDLK_RIGHT:
      return CONFIG_BUTTON_RIGHT;

    case SDLK_d:
    case SDLK_LCTRL:
      return CONFIG_BUTTON_I;

    case SDLK_s:
    case SDLK_LALT:
      return CONFIG_BUTTON_II;

    case SDLK_a:
    case SDLK_LSHIFT:
      return CONFIG_BUTTON_III;

    case SDLK_c:
    case SDLK_SPACE:
      return CONFIG_BUTTON_IV;

    case SDLK_x:
    case SDLK_TAB:
      return CONFIG_BUTTON_V;

    case SDLK_z:
    case SDLK_BACKSPACE:
      return CONFIG_BUTTON_VI;

    case SDLK_RETURN:
      return CONFIG_BUTTON_RUN;

    case SDLK_RSHIFT:
    case SDLK_ESCAPE:
      return CONFIG_BUTTON_SELECT;

    default:
      return CONFIG_BUTTON_NONE;
  }
}

u32 joy_button_map(u32 button)
{
  return config.pad[button + 4];
}

u32 joy_hat_map(u32 hat_value)
{
}

u32 update_input(event_input_struct *event_input)
{
  Uint8 *keystate = SDL_GetKeyState(NULL);
  SDL_Event event;

  event_input->config_button_action = CONFIG_BUTTON_NONE;
  event_input->key_action = KEY_ACTION_NONE;
  event_input->key_letter = 0;
  event_input->hat_status = HAT_STATUS_NONE;
  
  
  if(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:
        event_input->action_type = INPUT_ACTION_TYPE_PRESS;
        event_input->key_action = KEY_ACTION_QUIT;
        // Deliberate fallthrough

      case SDL_KEYDOWN:
        event_input->action_type = INPUT_ACTION_TYPE_PRESS;
        event_input->key_letter = event.key.keysym.unicode;

        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            event_input->key_action = KEY_ACTION_QUIT;
            break;

          case SDLK_1:
            event_input->key_action = KEY_ACTION_BG_OFF;
            break;

          case SDLK_2:
            event_input->key_action = KEY_ACTION_SPR_OFF;
            break;

          case SDLK_F1:
            event_input->key_action = KEY_ACTION_DEBUG_BREAK;
            break;

          case SDLK_t:
            event_input->key_action = KEY_ACTION_NETPLAY_TALK;
            break;

          case SDLK_BACKQUOTE:
            event_input->config_button_action = CONFIG_BUTTON_FAST_FORWARD;
            break;

          case SDLK_F5:
            event_input->config_button_action = CONFIG_BUTTON_SAVE_STATE;
            break;

          case SDLK_F7:
            event_input->config_button_action = CONFIG_BUTTON_LOAD_STATE;
            break;

          case SDLK_MENU:
          case SDLK_m:
            event_input->config_button_action = CONFIG_BUTTON_MENU;
            break;

          case SDLK_BACKSPACE:
            event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_BACKSPACE;
            break;

          case SDLK_RETURN:
            event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_ENTER;
            event_input->config_button_action = key_map(event.key.keysym.sym);
            break;

          case SDLK_LEFT:
            event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_LEFT;
            event_input->config_button_action = key_map(event.key.keysym.sym);
            break;

          case SDLK_RIGHT:
            event_input->key_action = KEY_ACTION_NETPLAY_TALK_CURSOR_RIGHT;
            event_input->config_button_action = key_map(event.key.keysym.sym);
            break; 
     

          default:
            event_input->config_button_action = key_map(event.key.keysym.sym);
            break;
        }
        break;

      case SDL_KEYUP:
        event_input->action_type = INPUT_ACTION_TYPE_RELEASE;
        event_input->config_button_action = key_map(event.key.keysym.sym);
        break;
    }
  }
  else
  {
    return 0;
  }

  return 1;
}

u8 gui_actions[16];

void clear_gui_actions()
{
  memset(gui_actions, 0, 16);
}

gui_action_type joy_map_gui_action(u32 button)
{
  switch(button)
  {
    case 1:
      return CURSOR_EXIT;

    case 2:
      return CURSOR_SELECT;

    case 0:
      return CURSOR_BACK;

    case 4:
      return CURSOR_PAGE_UP;

    case 5:
      return CURSOR_PAGE_DOWN;
  }

  return CURSOR_NONE;
}

gui_action_type joy_hat_map_gui_action(u32 hat_value)
{
  return CURSOR_NONE;
}

gui_action_type key_map_gui_action(u32 key)
{
  switch(key)
  {
    case SDLK_ESCAPE:
      return CURSOR_EXIT;

    case SDLK_DOWN:
      return CURSOR_DOWN;

    case SDLK_UP:
      return CURSOR_UP;

    case SDLK_LEFT:
      return CURSOR_LEFT;

    case SDLK_RIGHT:
      return CURSOR_RIGHT;

    case SDLK_SPACE:
    case SDLK_RETURN:
      return CURSOR_SELECT;

    case SDLK_BACKSPACE:
      return CURSOR_BACK;

    case SDLK_PAGEUP:
      return CURSOR_PAGE_UP;

    case SDLK_PAGEDOWN:
      return CURSOR_PAGE_DOWN;
  }

  return CURSOR_NONE;
}

u32 joy_axis_map_set_gui_action(u32 axis, s32 value)
{
  if(axis & 1)
  {
    if(value < 0) 
      return CURSOR_UP;
    else
      return CURSOR_DOWN;
  }
  else
  {
    if(value < 0) 
      return CURSOR_LEFT;
    else
      return CURSOR_RIGHT;
  }
}

void get_gui_input(gui_input_struct *gui_input)
{
  SDL_Event event;
  gui_action_type gui_action = CURSOR_NONE;

  static u64 button_repeat_timestamp;
  static button_repeat_state_type button_repeat_state = BUTTON_NOT_HELD;
  static gui_action_type cursor_repeat = CURSOR_NONE;

  delay_us(10000);

  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:
        quit();

      case SDL_KEYDOWN:
        gui_action = key_map_gui_action(event.key.keysym.sym);
        gui_actions[gui_action] = 1;

        if(gui_action == CURSOR_NONE)
        {
          gui_action = CURSOR_LETTER;
          gui_input->key_letter = event.key.keysym.unicode;
        }
        break;

      case SDL_KEYUP:
        gui_actions[key_map_gui_action(event.key.keysym.sym)] = 0;
        break;
    }
  }


  if(gui_action != CURSOR_NONE)
  {
    get_ticks_us(&button_repeat_timestamp);
    button_repeat_state = BUTTON_HELD_INITIAL;
    cursor_repeat = gui_action;
  }
  else
  {
    if(gui_actions[cursor_repeat])
    {
      u64 new_ticks;
      get_ticks_us(&new_ticks);

      if(button_repeat_state == BUTTON_HELD_INITIAL)
      {
        if((new_ticks - button_repeat_timestamp) >
         BUTTON_REPEAT_START)
        {
          gui_action = cursor_repeat;
          button_repeat_timestamp = new_ticks;
          button_repeat_state = BUTTON_HELD_REPEAT;
        }
      }

      if(button_repeat_state == BUTTON_HELD_REPEAT)
      {
        if((new_ticks - button_repeat_timestamp) >
         BUTTON_REPEAT_CONTINUE)
        {
          gui_action = cursor_repeat;
          button_repeat_timestamp = new_ticks;
        }
      }
    }
  }

  gui_input->action_type = gui_action;
}

void initialize_event()
{
}

