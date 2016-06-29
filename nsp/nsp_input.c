#include "../common.h"
#include <nucleus.h>
#include <libndls.h>

u32 sdl_to_config_map[] =
{
	0,1,2,3,4,5,6,7,8,9,10,11,12
};

u32 key_map(u32 keys)
{
	unsigned char i, chosen_key;
	
	chosen_key = 24;

	for (i=0;i<12;i++)
	{
		if (keys == sdl_to_config_map[i])
		{
			chosen_key = config.pad[i];
			break;
		}
	}
	switch(chosen_key)
	{
		case 0:
		  return CONFIG_BUTTON_UP;

		case 1:
		  return CONFIG_BUTTON_DOWN;

		case 2:
		  return CONFIG_BUTTON_LEFT;

		case 3:
		  return CONFIG_BUTTON_RIGHT;

		case 4:
		  return CONFIG_BUTTON_I;

		case 5:
		  return CONFIG_BUTTON_II;

		case 6:
		  return CONFIG_BUTTON_III;

		case 7:
		  return CONFIG_BUTTON_IV;

		case 8:
		  return CONFIG_BUTTON_V;

		case 9:
		  return CONFIG_BUTTON_VI;

		case 10:
		  return CONFIG_BUTTON_RUN;

		case 11:
		  return CONFIG_BUTTON_SELECT;
		  
		case 12:
			return CONFIG_BUTTON_MENU;
		  
		case 18:
			return CONFIG_BUTTON_RAPID_I;

		case 13:
			return CONFIG_BUTTON_RAPID_II;

		case 14:
			return CONFIG_BUTTON_RAPID_III;

		case 15:
			return CONFIG_BUTTON_RAPID_IV;

		case 16:
			return CONFIG_BUTTON_RAPID_V;
			
		case 17:
			return CONFIG_BUTTON_RAPID_VI;

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

struct tt_
{
	unsigned char time;
	unsigned char button;
} touche[16];
u8 gui_actions[16];
u8 t_touche[16];

void clear_gui_actions()
{
  memset(gui_actions, 0, 16);
}

u32 update_input(event_input_struct *event_input)
{
	unsigned char ifevent = 0, i;
	
	if (isKeyPressed(KEY_NSPIRE_UP))
		t_touche[0] = 1;
	else if (isKeyPressed(KEY_NSPIRE_DOWN))
		t_touche[1] = 1;
	else if (isKeyPressed(KEY_NSPIRE_LEFT))
		t_touche[2] = 1;
	else if (isKeyPressed(KEY_NSPIRE_RIGHT))
		t_touche[3] = 1;
	else if (isKeyPressed(KEY_NSPIRE_CTRL))
		t_touche[4] = 1;
	else if (isKeyPressed(KEY_NSPIRE_SHIFT))
		t_touche[5] = 1;
	else if (isKeyPressed(KEY_NSPIRE_VAR))
		t_touche[6] = 1;
	else if (isKeyPressed(KEY_NSPIRE_DEL))
		t_touche[7] = 1;
	else if (isKeyPressed(KEY_NSPIRE_7))
		t_touche[8] = 1;
	else if (isKeyPressed(KEY_NSPIRE_9))
		t_touche[9] = 1;
	else if (isKeyPressed(KEY_NSPIRE_TAB))
		t_touche[10] = 1;
	else if (isKeyPressed(KEY_NSPIRE_DOC))
		t_touche[11] = 1;
	else if (isKeyPressed(KEY_NSPIRE_MENU))
		t_touche[12] = 1;
		
	event_input->config_button_action = CONFIG_BUTTON_NONE;
	event_input->key_action = KEY_ACTION_NONE;
	event_input->key_letter = 0;
	event_input->hat_status = HAT_STATUS_NONE;
  
	for(i=0;i<13;i++)
	{
		switch(touche[i].button)
		{
			case 0:
			if (t_touche[i])
			{
				ifevent = 1;
				event_input->action_type = INPUT_ACTION_TYPE_PRESS;
				event_input->config_button_action = key_map(i);
				touche[i].button = 1;
			}
			break;
			case 1:
			if (!t_touche[i])
			{
				ifevent = 1;
				event_input->action_type = INPUT_ACTION_TYPE_RELEASE;
				event_input->config_button_action = key_map(i);
				touche[i].button = 0;
			}
			break;
		}
		
		t_touche[i] = 0;
	}
	
	if (isKeyPressed(KEY_NSPIRE_MENU))
	{
		ifevent = 1;
		event_input->config_button_action = CONFIG_BUTTON_MENU;
	}

	if(!ifevent)
	{
		return 0;
	}
	
	return 1;
}

gui_action_type joy_hat_map_gui_action(u32 hat_value)
{
  return CURSOR_NONE;
}

gui_action_type key_map_gui_action(u32 key)
{
  switch(key)
  {
    case 0:
      return CURSOR_EXIT;

    case 1:
      return CURSOR_DOWN;

    case 2:
      return CURSOR_UP;

    case 3:
      return CURSOR_LEFT;

    case 4:
      return CURSOR_RIGHT;

    case 5:
      return CURSOR_SELECT;

    case 6:
      return CURSOR_BACK;

    /*case SDLK_PAGEUP:
      return CURSOR_PAGE_UP;

    case SDLK_PAGEDOWN:
      return CURSOR_PAGE_DOWN;*/
  }

  return CURSOR_NONE;
}

u32 joy_axis_map_set_gui_action(u32 axis, s32 value)
{
  /*if(axis & 1)
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
  }*/
}

void get_gui_input(gui_input_struct *gui_input)
{
  gui_action_type gui_action = CURSOR_NONE;

  static u64 button_repeat_timestamp;
  static button_repeat_state_type button_repeat_state = BUTTON_NOT_HELD;
  static gui_action_type cursor_repeat = CURSOR_NONE;

  delay_us(14000);
  
  if (isKeyPressed(KEY_NSPIRE_UP))
	gui_action = key_map_gui_action(2);
  else if (isKeyPressed(KEY_NSPIRE_DOWN))
	gui_action = key_map_gui_action(1);
  else if (isKeyPressed(KEY_NSPIRE_LEFT))
	gui_action = key_map_gui_action(3);
  else if (isKeyPressed(KEY_NSPIRE_RIGHT))
	gui_action = key_map_gui_action(4);
  else if (isKeyPressed(KEY_NSPIRE_CTRL))
	gui_action = key_map_gui_action(5);
  else if (isKeyPressed(KEY_NSPIRE_DEL))
	gui_action = key_map_gui_action(6);
  else if (isKeyPressed(KEY_NSPIRE_ESC))
	gui_action = key_map_gui_action(0);

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

