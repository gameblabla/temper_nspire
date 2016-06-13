#include "common.h"

s32 receive_packet(control_buffer_entry_struct *remote_controls);

#ifdef WIN32_BUILD
  //typedef struct sockaddr sockaddr_type;
  typedef struct sockaddr_in sockaddr_type;
#else
  typedef struct sockaddr_in sockaddr_type;
#endif

static void print_netplay_error(char *str)
{
}

netplay_struct netplay;

void flush_receive(void)
{
}

void reset_control_buffer(control_buffer_struct *control_buffer)
{

}

void queue_controls(control_buffer_struct *control_buffer,
 u32 frame_number, u32 controls)
{
}


// TODO: This can be done better, you can find out sooner if you definitely
// won't find the frame.

control_buffer_entry_struct
 *find_controls_at_frame_number(control_buffer_struct *control_buffer,
 u32 frame_number)
{
  return NULL;
}


void netplay_disconnect(void)
{
}

void invalidate_send_buffer(void)
{
}

void netplay_queue_latency_filler(void)
{
}

void netplay_reset_buffers(void)
{
}


s32 netplay_connect_server(void)
{
  return -1;
}

s32 netplay_connect_client(void)
{
  return -1;
}

void disable_blocking(void)
{
}

s32 server_wait_for_connection(void)
{
  return 0;
}

u32 netplay_ip_string_value(const char *ip_string)
{
  return 0;
}

void flush_send_buffer(void)
{
}

void send_packet(u8 *send_buffer, u32 length)
{
}

void send_controls(u32 controls, u32 frame_number)
{  
}

void send_talk_message(char *message)
{
}

void send_latency_report(u32 latency_value, u32 stalls)
{
}

void send_set_latency(u32 set_frame, u32 set_value)
{
}

void send_netplay_pause(void)
{
}

void send_netplay_unpause(void)
{
}

void send_savestate_start(u32 savestate_length)
{
}

void send_savestate_block(u8 *block_buffer,u32 block_length, u32 block_number)
{
}

void send_savestate_block_confirm(u32 block_number)
{
}

#ifdef WIN32_BUILD

#define receive_packet_data_unavailable(_receive_bytes)                        \
 ((_receive_bytes == 0) || (WSAGetLastError() == WSAEWOULDBLOCK))              \

#else

#define receive_packet_data_unavailable(_receive_bytes)                        \
 ((_receive_bytes == 0) || (errno == EAGAIN))                                  \

#endif

#define receive_packet_ensure_available(size)                                  \
  while(receive_bytes < size)                                                  \
  {                                                                            \
  }                                                                            \

s32 receive_packet(control_buffer_entry_struct *remote_controls)
{
  return 0;
}


s32 queue_controls_remote(void)
{
  return 0;
}

#ifndef SOL_TCP
#define SOL_TCP IPPROTO_TCP
#endif

void disable_nagle(void)
{
}

void tcp_quick_ack(void)
{
}

void netplay_connect(void)
{
}

void netplay_frame_update(u32 new_local_controls, u32 *_use_local_controls,
 u32 *_use_remote_controls)
{
 
}

s32 netplay_send_savestate(char *file_name)
{

  return 0;
}

