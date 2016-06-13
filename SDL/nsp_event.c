#include "../common.h"

u32 key_map(u32 keys)
{
	if (isKeyPressed(KEY_NSPIRE_UP))
		return CONFIG_BUTTON_UP;
	else if (isKeyPressed(KEY_NSPIRE_LEFT))
		return CONFIG_BUTTON_LEFT;
	else if (isKeyPressed(KEY_NSPIRE_RIGHT))
		return CONFIG_BUTTON_RIGHT;
	else if (isKeyPressed(KEY_NSPIRE_DOWN))
		return CONFIG_BUTTON_DOWN;
	else if (isKeyPressed(KEY_NSPIRE_CTRL))
		return CONFIG_BUTTON_I;
	else if (isKeyPressed(KEY_NSPIRE_SHIFT))
		return CONFIG_BUTTON_II;
	else if (isKeyPressed(KEY_NSPIRE_VAR))
		return CONFIG_BUTTON_III;
	else if (isKeyPressed(KEY_NSPIRE_DEL))
		return CONFIG_BUTTON_IV;
	else if (isKeyPressed(KEY_NSPIRE_7))
		return CONFIG_BUTTON_V;
	else if (isKeyPressed(KEY_NSPIRE_9))
		return CONFIG_BUTTON_VI;
	else if (isKeyPressed(KEY_NSPIRE_TAB))
		return CONFIG_BUTTON_RUN;
	else if (isKeyPressed(KEY_NSPIRE_DOC))
		return CONFIG_BUTTON_SELECT;
	else
		return CONFIG_BUTTON_NONE;
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
	event_input->config_button_action = CONFIG_BUTTON_NONE;
	event_input->key_action = KEY_ACTION_NONE;
	event_input->key_letter = 0;
	event_input->hat_status = HAT_STATUS_NONE;
  
	if (isKeyPressed(KEY_NSPIRE_MENU))
	{
		event_input->config_button_action = CONFIG_BUTTON_MENU;
	}
	else if (isKeyPressed(KEY_NSPIRE_L))
	{
		event_input->config_button_action = CONFIG_BUTTON_LOAD_STATE;
	}
	else if (isKeyPressed(KEY_NSPIRE_S))
	{
		event_input->config_button_action = CONFIG_BUTTON_SAVE_STATE;
	}
	else if (isKeyPressed(KEY_NSPIRE_ESC))
	{
		 event_input->key_action = KEY_ACTION_QUIT;
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
	if (isKeyPressed(KEY_NSPIRE_UP))
		return CURSOR_UP;
	else if (isKeyPressed(KEY_NSPIRE_LEFT))
		return CURSOR_LEFT;
	else if (isKeyPressed(KEY_NSPIRE_RIGHT))
		return CURSOR_RIGHT;
	else if (isKeyPressed(KEY_NSPIRE_DOWN))
		return CURSOR_DOWN;
	else if (isKeyPressed(KEY_NSPIRE_CTRL) || isKeyPressed(KEY_NSPIRE_ENTER) )
		return CURSOR_SELECT;
	else if (isKeyPressed(KEY_NSPIRE_DEL))
		return CURSOR_PAGE_UP;
	else if (isKeyPressed(KEY_NSPIRE_ESC))
		return CURSOR_EXIT;
	else
		return CURSOR_NONE;
}

u32 joy_axis_map_set_gui_action(u32 axis, s32 value)
{
}

void get_gui_input(gui_input_struct *gui_input)
{
  gui_action_type gui_action = CURSOR_NONE;

  static u64 button_repeat_timestamp;
  static button_repeat_state_type button_repeat_state = BUTTON_NOT_HELD;
  static gui_action_type cursor_repeat = CURSOR_NONE;

  delay_us(10000);

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

