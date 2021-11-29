//
//pcmstm.h
//
#ifndef __PCMSTM_H__
# define __PCMSTM_H__

#include "pcmsys.h"

///////////////////////////////////////////////////////////////////////////////
// PCM Stream stuff
////////////////////////////
// 
// In case of bugs, increase PCM_BUFFERED_BLANKS by 32.
//
#define PCM_BUFFERED_BLANKS (96)
#define NUM_PCM_BUF (PCM_BUFFERED_BLANKS / 48)
////////////////////
//
#define MAX_FILE_REQUESTS (16)

/*

	General addendum: This software-controlled buffer system is much much much slower than CDDA.
	With CDDA, you can get 44.1Khz *stereo* 16-bit sound. This can't even get a quarter of that.
	At best this system gets a fifth of that. Lol.
	But here, the CD system is not locked; you can do multiple things at once.
	
	So yes, this system is tremendously slower than it could be. 
	This is because the CD system is only scheduled to be active at the specific point where new data is needed,
	and the capability of the CD drive to deliver new data is more or less "near-instant".
	Obviously, it isn't near-instant. If you let it pull new data from CD every frame, it can deliver at least two sectors per frame.
	
	//
	// In case of space-optimized version, using PCM_BUFFERED_BLANKS of >>> 96 <<<.
	//
		Drain time: 96 blanks
	Bit rate	|	Byte rate	| Buffer size	| File sys margin	|	Transfer rate (sectors) : (transfer count)
	7680			8: 128			12	KB			84						3 : 2 
					16: 256			24	KB			72						4 : 3
	11520			8: 192			18	KB			78						4 : 3
					16: 384			36	KB			60						3 : 6
	15360			8:  256			24	KB			72						4 : 3
					16: 512			48	KB			48						4 : 6
	23040			8: 384			36	KB			60						3 : 6 
					16: 768			72	KB			24						4 : 9 Note: No ADX or file stream (Insufficient margin)
	30720			8: 512			48	KB			48						4 : 6
					16: 1024		96	KB			0						4 : 12 (Completely broken...)
																			(I had a system that could do that, but it had issues..)
*/



/**
In development commentary:

file handling required structure

1 -> User knows where the data from the file is going.
2 -> User can use a function to specify the function used to handle the data when it is completed.
3 -> Function handling the request inside the system is needed because of the next point..
4 -> System needs to allow queued requests.

**/

typedef struct {
	int pcm_num;
	int times_to_loop;
	int played_blanks;
	int total_blanks;
	int volume;
	bool playing;
	bool stopping;
	bool restarting;
	
} _pcm_stm_param;

typedef struct {
	GfsHn file_handle;
	Sint32 file_id;
	Sint32 total_bytes;
	void * buffer_location_in_sndram;
	int steps_of_new_data_in_buffer;
	int vblank_counter;
	int transfer_bytes;
	int transfer_sectors;
	int buffer_size_bytes;
	int transfer_timing;
	bool operating;
	bool needs_buffer_filled;
	bool setup_requested;
	
	bool segment_full[NUM_PCM_BUF];
	void * segment_locations[NUM_PCM_BUF];
	int	segment_refresh_timings[NUM_PCM_BUF];
	int active_buf_segment;
	int segment_size;
	int segment_transfer_time;
	
} _pcm_stm_buf_ctrl;

typedef struct {
	GfsHn handle;
	Sint32 id;
	Sint32 total_bytes;
	Sint32 total_sectors;
	int sectors_read_so_far;
	bool requested;
	bool setup_requested;
	bool transfer_lock;
	void * destination;

} _generic_file_ctrl;

typedef struct {
	_generic_file_ctrl file;
	void * front_buffer[2];
	void * back_buffer[2];
	bool front_buffer_okay;
	bool back_buffer_okay;
	bool front_buffer_filled[2];
	bool back_buffer_filled[2];
	bool request_stop;
	short volume;
	short pcm_number; //Used to fill data for the stream sys to know when to stop playing
	bool active;
	bool playing;
} adx_stream_param;

//
//Proprietary file stream manager, in case of using dynamic file loading.

typedef struct {
	Sint32 id; //File-system ID
	void * destination; //Destination address
	void (*handler_function)(void *); //Pointer to function used to handle this file
	bool active; // File request writes "1" when it wants this file served. Manager writes "0" when done.
	bool done; // File request writes "0" when it wants the file served. Manager writes "1" when done.
} _file_request_entry;

void	new_file_request(Sint8 * filename, void * destination, void (*handler_function)(void *));

//
//

extern _pcm_stm_param stm;

void	sdrv_stm_vblank_rq(void);

short	add_adx_front_buffer(short bit_rate);
void	add_adx_back_buffer(void * t18kb_buffer_location);
void	start_adx_stream(Sint8 * filename, short volume);

void	pcm_stream_init(int bitrate, int bit_depth);
void	start_pcm_stream(Sint8 * filename, int volume);
void	stop_adx_stream(void);
void	stop_pcm_stream(void);
void	pcm_stream_host(void(*game_code)(void));



#endif

