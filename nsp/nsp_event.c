// The way this works on PSP is a little different. There are 12
// PSP button config states (see psp_buttons_config_enum in event.h).
// This table converts these to a mask that shows which bit this
// corresponds with in the button status that the PSP system call
// returns. This way we can see if any of these are triggered.

#include "../common.h"
#include <os.h>

u32 update_input(event_input_struct *event_input)
{
  unsigned long psp_buttons;
  unsigned long button_status = 0;
  static unsigned long last_psp_buttons = 0;
  unsigned long i;

	if(iskeyPressed(KEY_NSPIRE_UP))
	{
		button_status |= button_action(0, last_psp_buttons & (1 << 0));
    }
	else if(iskeyPressed(KEY_NSPIRE_DOWN))
	{
		button_status |= button_action(1, last_psp_buttons & (1 << 1));
    }
	else if(iskeyPressed(KEY_NSPIRE_LEFT))
	{
		button_status |= button_action(2, last_psp_buttons & (1 << 2));
    }
	else if(iskeyPressed(KEY_NSPIRE_RIGHT))
	{
		button_status |= button_action(3, last_psp_buttons & (1 << 3));
    }
	else if(iskeyPressed(KEY_NSPIRE_CTRL))
	{
		button_status |= button_action(4, last_psp_buttons & (1 << 4));
    }
	else if(iskeyPressed(KEY_NSPIRE_SHIFT))
	{
		button_status |= button_action(5, last_psp_buttons & (1 << 4));
    }
	else if(iskeyPressed(KEY_NSPIRE_VAR))
	{
		button_status |= button_action(6, last_psp_buttons & (1 << 5));
    }
	else if(iskeyPressed(KEY_NSPIRE_DEL))
	{
		button_status |= button_action(7, last_psp_buttons & (1 << 6));
    }
	else if(iskeyPressed(KEY_NSPIRE_7))
	{
		button_status |= button_action(8, last_psp_buttons & (1 << 6));
    }
	else if(iskeyPressed(KEY_NSPIRE_9))
	{
		button_status |= button_action(9, last_psp_buttons & (1 << 7));
    }
	else if(iskeyPressed(KEY_NSPIRE_TAB))
	{
		button_status |= button_action(10, last_psp_buttons & (1 << 8));
    }
	else if(iskeyPressed(KEY_NSPIRE_DOC))
	{
		button_status |= button_action(11, last_psp_buttons & (1 << 9));
    }
	else if(iskeyPressed(KEY_NSPIRE_MENU))
	{
		event_input->config_button_action = CONFIG_BUTTON_MENU;
    }
    
  last_psp_buttons = psp_buttons;
}

unsigned long platform_specific_button_action_direct(unsigned long button, unsigned long old_action)
{
  return 0;
}

void get_gui_input()
{
  gui_action_type new_button = CURSOR_NONE;
  unsigned long buttons;
  unsigned long new_buttons;

  static unsigned long last_buttons = 0;
  static button_repeat_state_type button_repeat_state = BUTTON_NOT_HELD;

  static unsigned long button_repeat_timestamp;
  static unsigned long button_repeat = 0;
  static gui_action_type cursor_repeat = CURSOR_NONE;

  //buttons = ctrl_data.Buttons;
	if (iskeyPressed(KEY_NSPIRE_UP))
		buttons = 0;
	else if (iskeyPressed(KEY_NSPIRE_LEFT))
		buttons = 1;
	else if (iskeyPressed(KEY_NSPIRE_RIGHT))
		buttons = 3;
	else if (iskeyPressed(KEY_NSPIRE_DOWN))
		buttons = 2;
	else if (iskeyPressed(KEY_NSPIRE_CTRL))
		buttons = 4;
	else if (iskeyPressed(KEY_NSPIRE_SHIFT))
		buttons = 5;
	else if (iskeyPressed(KEY_NSPIRE_VAR))
		buttons = 6;
	else if (iskeyPressed(KEY_NSPIRE_DEL))
		buttons = 7;
	else if (iskeyPressed(KEY_NSPIRE_7))
		buttons = 8;
	else if (iskeyPressed(KEY_NSPIRE_9))
		buttons = 9;
	else if (iskeyPressed(KEY_NSPIRE_TAB))
		buttons = 10;
	else if (iskeyPressed(KEY_NSPIRE_DOC))
		buttons = 11;

  sleep(5);

  new_buttons = (last_buttons ^ buttons) & buttons;
  last_buttons = buttons;

  if(iskeyPressed(KEY_NSPIRE_ENTER))
    new_button = CURSOR_BACK;

  if(iskeyPressed(KEY_NSPIRE_ESC))
    new_button = CURSOR_EXIT;

  if(iskeyPressed(KEY_NSPIRE_VAR))
    new_button = CURSOR_SELECT;

  if(iskeyPressed(KEY_NSPIRE_UP))
    new_button = CURSOR_UP;

  if(iskeyPressed(KEY_NSPIRE_DOWN))
    new_button = CURSOR_DOWN;

  if(iskeyPressed(KEY_NSPIRE_LEFT))
    new_button = CURSOR_LEFT;

  if(iskeyPressed(KEY_NSPIRE_RIGHT))
    new_button = CURSOR_RIGHT;

  if(new_button != CURSOR_NONE)
  {
    get_ticks_us(&button_repeat_timestamp);
    button_repeat_state = BUTTON_HELD_INITIAL;
    button_repeat = new_buttons;
    cursor_repeat = new_button;
  }
  else
  {
    if(buttons & button_repeat)
    {
      unsigned long new_ticks;
      get_ticks_us(&new_ticks);

      if(button_repeat_state == BUTTON_HELD_INITIAL)
      {
        if((new_ticks - button_repeat_timestamp) >
         BUTTON_REPEAT_START)
        {
          new_button = cursor_repeat;
          button_repeat_timestamp = new_ticks;
          button_repeat_state = BUTTON_HELD_REPEAT;
        }
      }

      if(button_repeat_state == BUTTON_HELD_REPEAT)
      {
        if((new_ticks - button_repeat_timestamp) >
         BUTTON_REPEAT_CONTINUE)
        {
          new_button = cursor_repeat;
          button_repeat_timestamp = new_ticks;
        }
      }
    }
  }

  return new_button;
}

void initialize_event()
{
}

