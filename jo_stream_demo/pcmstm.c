//
// pcmstm.c
// Note: this file is compiled separately
//
#include <jo/jo.h>
#include "pcmstm.h"

	_pcm_stm_param stm;
	_pcm_stm_buf_ctrl buf;
	_generic_file_ctrl file;
	
	void (*file_handler_function)(void *);
	
	int file_transfer_sector = 9;
	int file_transfer_size = (9 * 2048);

	adx_stream_param adx_stream;

/*

Will set the process-in-motion to open the (filename) and play it back as a PCM stream.
The parameters of the PCM stream are to be pre-set by the function "pcm_stream_init".
There is no check to see if it's set-up yet. Ah well, I'm sure you could figure it out.

Note, unless the game code is operating within the "pcm_stream_host" function, this will do nothing.

*/
void	start_pcm_stream(Sint8 * filename, int volume)
{
	
	buf.file_id = GFS_NameToId(filename);
	buf.setup_requested = true;
	stm.volume = volume;
}

// Will stop a PCM stream.
void	stop_pcm_stream(void)
{

	stm.stopping = true;
	
}

// Will stop an ADX stream.
// Note the driver needn't use this function to stop an ADX stream in case of it finishing the file.
// In that case, the driver will know when to properly stop playback.
// This function is for premature stoppage of the sound.
void		stop_adx_stream(void)
{
	
	m68k_com->pcmCtrl[adx_stream.pcm_number].sh2_permit = 0;
	adx_stream.request_stop = 1;
	
}

//
/*
	Add raw PCM buffer
	This function adds a PCM slot with parameters with a given size in sound RAM.
	It does so without loading any data to that region of sound RAM.
	The sound RAM pointer is properly incremented such that this region of memory, and this sound slot, are a playable buffer.
*/
//
short	add_raw_pcm_buffer(bool is8Bit, short sampleRate, int size)
{
	
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit
	
	m68k_com->pcmCtrl[numberPCMs].hiAddrBits = (unsigned short)( (unsigned int)scsp_load >> 16);
	m68k_com->pcmCtrl[numberPCMs].loAddrBits = (unsigned short)( (unsigned int)scsp_load & 0xFFFF);
	
	m68k_com->pcmCtrl[numberPCMs].pitchword = convert_bitrate_to_pitchword(sampleRate);
	m68k_com->pcmCtrl[numberPCMs].playsize = (is8Bit) ? size : size>>1;
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = calculate_bytes_per_blank(sampleRate, is8Bit, PCM_SYS_REGION); //Iniitalize as max volume
	m68k_com->pcmCtrl[numberPCMs].bitDepth = (is8Bit) ? PCM_TYPE_8BIT : PCM_TYPE_16BIT;
	m68k_com->pcmCtrl[numberPCMs].loopType = 0; //Initialize as non-looping
	m68k_com->pcmCtrl[numberPCMs].volume = 7; //Iniitalize as max volume
	numberPCMs++;
	scsp_load = (unsigned int *)((unsigned int )scsp_load + size);
	return (numberPCMs-1); //Return the PCM # this sound received
}


// Recursive function to return gcd of a and b 
inline short gcd(short a, short b) 
{ 
    if (a == 0)
        return b; 
    return gcd(b % a, a); 
} 
 
// Function to return LCM of two numbers 
// Used specifically to find the buffer size for ADX sound effects
inline short lcm(short a, short b) 
{ 
    return (a / gcd(a, b)) * b;
} 

/*
	This function adds an ADX entry to the PCM CTRL list and allocates an 18KB front-buffer in sound RAM to play it back from.
	This is used for ADX streams only.  (Normal ADX sound effects do not use or need this)
	The only allowed bit-rates are 7680, 11520, 15360, and 23040.
	These are the specific bit-rates allowed due to the fact they coincide with the uncompressed byte-rates of:
	256, 384, 512, and 768. These are exact byte-rates, which is important.
*/
short	add_adx_front_buffer(short bit_rate)
{
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit

	int adx_buf_sz = (18 * 1024);
	/**
	NOTICE:
	When playing this back, you will need to offset the start by 2 frames.
	The driver should know to do that on its own when playing an ADX_STREAM.
	That will get over the header and offset to data (total 36 bytes).
	**/
	volatile int i = 0;
	for(i = 0; i < (int)scsp_load; i++)
	{
		//This is to pop the stack here. Because GCC.
	}
	adx_stream.front_buffer[0] = (void *)((unsigned int)scsp_load + SNDRAM);
	adx_stream.front_buffer[1] = (void *)((unsigned int)scsp_load + SNDRAM + (adx_buf_sz>>1));
	m68k_com->pcmCtrl[numberPCMs].hiAddrBits = (unsigned int)(scsp_load)>>16;
	m68k_com->pcmCtrl[numberPCMs].loAddrBits = (unsigned int)(scsp_load) & 0xFFFF;
	m68k_com->pcmCtrl[numberPCMs].pitchword = convert_bitrate_to_pitchword(bit_rate);
	m68k_com->pcmCtrl[numberPCMs].playsize = 18384; //TBD by stream system, so just set it at a high number.
	short bpb = calculate_bytes_per_blank((int)bit_rate, false, PCM_SYS_REGION); //Iniitalize as max volume
	if(bpb != 768 && bpb != 512 && bpb != 384 && bpb != 256)
	{
		jo_printf(0, 1, "!(ADX INVALID BYTE-RATE)!");
		return -2;
	}
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = bpb;
	m68k_com->pcmCtrl[numberPCMs].decompression_size = lcm(bpb, bpb + 64)<<1;
	m68k_com->pcmCtrl[numberPCMs].bitDepth = PCM_TYPE_ADX; //Select ADX type
	m68k_com->pcmCtrl[numberPCMs].loopType = ADX_STREAM; //Initialize as ADX stream.
	m68k_com->pcmCtrl[numberPCMs].volume = 7; //Iniitalize as max volume

	numberPCMs++;
	scsp_load = (unsigned int *)((unsigned int )scsp_load + adx_buf_sz);
	adx_stream.front_buffer_okay = true;
	adx_stream.pcm_number = numberPCMs-1;
	return (numberPCMs-1); //Return the PCM # this sound received
}


/*
	Allocate the ADX back-buffer. It can be anywhere in HWRAM or LWRAM.
	Technically plausible to put it in sound RAM, but this isn't recommended.
	This is used only for ADX streams. (Normal ADX sound effects do not use or need this)
*/
void	add_adx_back_buffer(void * t18kb_buffer_location)
{
	adx_stream.back_buffer[0] = t18kb_buffer_location;
	adx_stream.back_buffer[1] = t18kb_buffer_location + (9 * 1024);
	adx_stream.back_buffer_okay = true;
}

/*

This function performs the DMA transfers from the ADX back buffer to the front buffer.
Note that it does not schedule them; the M68k software schedules the transfers.

*/
void	operate_adx_stream(void)
{
	//This condition halts operation of the ADX Stream if the front/back buffer are not set up yet.
	if(!adx_stream.front_buffer_okay || !adx_stream.back_buffer_okay) return;
	if(adx_stream.active && !adx_stream.playing)
	{
		//This condition will read the header of the file and set it to play.
		//read_adx_at_front_buffer(stm);
		adx_stream.playing = true;
	} else if(adx_stream.active && adx_stream.playing)
	{
		//This condition will begin managing copying the back to the front buffer.
		//This management depends on the sound driver writing "1" to the adx_buffer_pass variable when it passes points in the buffer.
		//It only writes to them. The driver itself then depends on this software to exchange the front and back buffers as needed.
		if(m68k_com->adx_buffer_pass[0])
		{
			//In this condition, we are to copy back buffer [zero] to front buffer [zero].
			//This is 9KB of data (half of 18KB buffer).
			slDMACopy(adx_stream.back_buffer[0], adx_stream.front_buffer[0], (1024 * 9));
			m68k_com->adx_buffer_pass[0] = 0;
			adx_stream.back_buffer_filled[0] = false;
		}
		if(m68k_com->adx_buffer_pass[1])
		{
			//In this condition, we are to copy back buffer [one] to front buffer [one].
			//This is 9KB of data (half of 18KB buffer).
			slDMACopy(adx_stream.back_buffer[1], adx_stream.front_buffer[1], (1024 * 9));
			m68k_com->adx_buffer_pass[1] = 0;
			adx_stream.back_buffer_filled[1] = false;
		}
	}
}

/*

	Will set the process in motion to start an ADX stream from (filename) with (volume).
	The ADX stream will be played back according to the parameters set by the front buffer (bitrate, mostly).
	Note that if your game code is not operating from with the "pcm_stream_host" function, this will do nothing.

*/
void	start_adx_stream(Sint8 * filename, short volume)
{
	// This condition halts operation of the ADX Stream if the front/back buffer are not set up yet.
	if(!adx_stream.front_buffer_okay || !adx_stream.back_buffer_okay) return;
	// This condition... prevents bugs.
	if(adx_stream.file.requested || adx_stream.file.setup_requested || adx_stream.active) return;

	adx_stream.file.id = GFS_NameToId(filename);
	//jo_printf(0, 17, "started ADX stm");
	adx_stream.active = true;
	adx_stream.file.setup_requested = true;
	adx_stream.volume = volume;
}


/*

	This function initializes the PCM stream buffer according to the parameters of the bit-rate and depth of the PCM files used.
	It's recommended to use 30720 KHz 8-bit PCMs.
	It is essential to use this function before the program enters pcm_stream_host.
	It is also helpful to use this function before any other sound effects are loaded.
	These parameters, currently, may only be set once. I haven't established the process required to change them mid-program.

*/
void	pcm_stream_init(int bitrate, int bit_depth)
{

	static bool only_run_once = false;
		
	if(only_run_once == false)
	{
		
		short byte_rate = calculate_bytes_per_blank(bitrate, bit_depth, PCM_SYS_REGION);
			
		buf.buffer_size_bytes = byte_rate * PCM_BUFFERED_BLANKS; //"byte_rate" being the bytes per blank of the music track
		buf.transfer_sectors = (((buf.buffer_size_bytes >> 13) << 13 ) == buf.buffer_size_bytes) ? 4 : 3;
		buf.transfer_bytes = (buf.transfer_sectors * 2048); 
		buf.transfer_timing = buf.buffer_size_bytes / buf.transfer_bytes;
		buf.segment_size = buf.buffer_size_bytes / NUM_PCM_BUF;
		buf.segment_transfer_time = buf.segment_size / buf.transfer_bytes;
		
		buf.buffer_location_in_sndram = (void *)((unsigned int)scsp_load + SNDRAM);
		for(short i = 0; i < NUM_PCM_BUF; i++)
		{
			buf.segment_locations[i] = (void *)((unsigned int)buf.buffer_location_in_sndram + (buf.segment_size * i));
			buf.segment_refresh_timings[i] = (PCM_BUFFERED_BLANKS / NUM_PCM_BUF) * (i+1);
		}
		stm.pcm_num = add_raw_pcm_buffer(bit_depth, bitrate, buf.buffer_size_bytes);
		only_run_once = true;
		// I almost forgot to post-increment the loading pointer by the size of the buffer
		scsp_load += buf.buffer_size_bytes;
	}
}

/////////////////////
/*

	Important Notice
	
	The following is a *unique* function for operating the driver and PCM/ADX streams.
	Do not run this function alongside the normal "sdrv_vblank_rq".
	Run this function instead of that one only in case where the project will use PCM and/or ADX streams.

*/
/////////////////////
void		sdrv_stm_vblank_rq(void)
{
	if(buf.operating)
	{
		///////////////////////////
		// TIME COUNTERS (VBLANKS)
		if(stm.playing) stm.played_blanks++;
		buf.vblank_counter++;

		for(short b = 0; b < NUM_PCM_BUF; b++)
		{
			if(buf.vblank_counter == buf.segment_refresh_timings[b] && buf.segment_full[b] == true)
			{
				///////////////////////////////////
				//	BUFFER CONSUMPTION CONTROL
				buf.active_buf_segment = b;
				buf.segment_full[b] = false;
				buf.needs_buffer_filled = true;
				buf.steps_of_new_data_in_buffer = 0;
			}
		}
		
		if(buf.vblank_counter >= PCM_BUFFERED_BLANKS)
		{
		buf.steps_of_new_data_in_buffer = 0;
		buf.vblank_counter = 0;
			////////////////////////////////////
			// SOUND STARTING
			// This is the appropriate place to start playing the sound if this loading period was the first one.
			// This ensures we don't play old/garbage data in the buffer: playing starts always after new loading is done.
			// The control data is flagged here so we don't needlessly re-send the command (though, it wouldn't hurt if we do).
			// Thought: If you wanted to change the pitch word / effective bit-rate of the music, this is also where you'd do that.
			// But that's a lot of math (like changing the vblank timer) to do.
			if(!stm.playing)
			{
				stm.playing = true;
				pcm_play(stm.pcm_num, PCM_FWD_LOOP, stm.volume);
			}
		}
		/////////////////////////////////////////////
		//	STREAM ENDING / LOOPING
		//	This is the appropriate place & time to set up looping or ending for a PCM stream.
		//	I admit, it is slightly off. The mathemagics suggest that the timing must be shifted forward.
		//	The forward-time-shift of the loop or ending is caused by the delay in playing the sound from when the sound was loaded.
		//	Or another effect, that I documented in the driver binary, but that's not important. At least, THAT important.
		//	When a stream is set to loop, note that it will close and re-open the file. It will not stop the sound, though.
		//
		if(stm.played_blanks > (stm.total_blanks - (PCM_BUFFERED_BLANKS)))
		{
			if(stm.times_to_loop <= 0)
			{
				stm.stopping = true;
			} else {
				stm.stopping = true;
				stm.times_to_loop--;
				stm.restarting = true;
				stm.played_blanks = 0;
			}
		}

		//jo_printf(2, 7, "blanks(%i)", buf.vblank_counter);
	}
	
	///////////////////////////////
	// ADX STREAM OPERATOR
	// Side-note: Because of how ADX works, streaming ADX is oddly more well-developed. The M68K handles a lot of the timing.
	if(adx_stream.active)
	{
		operate_adx_stream();
	}
	//jo_printf(0, 0, "drv_stat(%i)", m68k_com->start);
	m68k_com->start = 1;	
}

void		pcm_stream_host(void(*game_code)(void), void * file_system_buffer_location)
{
	
	static Sint32 gfs_svr_status;
	static Sint32 bytes_read_now;
	static Sint32 byte_dummy;

	while(1)
	{
	//Main system loop - system doesn't break away from this.
	/*
		Hi. This is a mess. Spaghetti, if you will. Don't you just love it?
	Branches:
	--> PCM needs setup...
	|	File system set-up
	--> PCM should stop...
	|	Clean stream parameters
	|	| -> Restarting, stop sound, queue setup again
	|	| -> Not restarting, stop sound
	|	Close file
	-->	PCM Inactive...
	|		| -> No activity
	|		| -> File system CD -> RAM
	|		| -> File system completion
	|		| -> File system set-up
	|		| -> ADX, set-up 
	|		| -> ADX, CD -> RAM, 18KB
	|		| -> ADX, Completion / closure
	--> PCM Active...
			| -> Operate CD -> RAM Activity, one-buffer segment
	
	*/
	
		if(buf.setup_requested)
		{
				game_code();
			/////////////
			buf.file_handle = GFS_Open(buf.file_id);
			
			/*
				In testing, it has been found that these lines are _strictly necessary_ for this to work.
				SetReadPara sets the bytes per request to be retrieved from CD to the CD block buffer.
				SetTransPara sets the sectors per request to be transferred from the CD block buffer to system addressable memory.
				SetTmode sets the DMA channel to be used for the request. We set SDMA1 specifically. SDMA0 can be used.
			*/
			GFS_SetReadPara(buf.file_handle, buf.buffer_size_bytes);
			GFS_SetTransPara(buf.file_handle, buf.transfer_sectors);
			GFS_SetTmode(buf.file_handle, GFS_TMODE_SDMA0);
			
			GFS_GetFileInfo(buf.file_handle, NULL, NULL, &buf.total_bytes, NULL);
			stm.total_blanks = buf.total_bytes / (int)m68k_com->pcmCtrl[stm.pcm_num].bytes_per_blank;
			stm.played_blanks = 0;
			
			for(short b = 0; b < NUM_PCM_BUF; b++)
			{
				buf.segment_full[b] = true;
			}
			buf.vblank_counter = 0;
			buf.operating =  true;
			
			buf.setup_requested = false;
			//////////////
				slSynch();
		} else if(stm.stopping)
		{
				game_code();
			buf.operating = false;
			buf.needs_buffer_filled = false;
			stm.stopping = false;
			if(stm.restarting) 
			{
				buf.setup_requested = true;
				stm.restarting = false;
			} else {
				stm.playing = false;
				pcm_cease(stm.pcm_num);
			}
			GFS_Close(buf.file_handle);
				slSynch();
		} else if(!buf.needs_buffer_filled)
		{
		//Broadly speaking, this branch is generic file system or ADX streaming in the PCM stream's free time.
			if((file.transfer_lock || !file.requested) && !file.setup_requested && !adx_stream.file.setup_requested
			&& (!adx_stream.file.requested || (adx_stream.back_buffer_filled[0] || adx_stream.back_buffer_filled[1])) )
			{
			//This branch is for no file system activity. Nothing is being presently accessed or requested to be set up.
				game_code();
					jo_printf(16, 2, "--PLAY--");
					// jo_printf(16, 6, "bufrq(%i)", buf.needs_buffer_filled);
					// jo_printf(2, 8, "buf0f(%i)", buf.segment_full[0]); 
					// jo_printf(2, 9, "buf1f(%i)", buf.segment_full[1]); 
					// jo_printf(16, 8, "filerq(%i)", file.requested);
					// jo_printf(16, 9, "ftrans(%i)", file.transfer_lock);
					// jo_printf(2, 10, "fsetup(%i)", file.setup_requested);
					// jo_printf(16, 10, "fsect(%i)", file.sectors_read_so_far);
					// jo_printf(2, 12, "fsize(%i)", file.total_sectors);
					// jo_printf(16, 12, "fnsct(%i)", file.total_bytes);
					// jo_printf(2, 6, "bytes(%i)", bytes_read_now);
					// jo_printf(16, 6, "bufrq(%i)", buf.needs_buffer_filled);
					// jo_printf(2, 8, "adx0f(%i)", adx_stream.back_buffer_filled[0]); 
					// jo_printf(2, 9, "adx1f(%i)", adx_stream.back_buffer_filled[1]); 
					// jo_printf(16, 8, "adxrq(%i)", adx_stream.file.requested);
					// jo_printf(16, 9, "atrans(%i)", gfs_svr_status);
					// jo_printf(2, 10, "asetup(%i)", adx_stream.file.setup_requested);
					// jo_printf(16, 10, "asect(%i)", adx_stream.file.sectors_read_so_far);
					// jo_printf(2, 12, "asize(%i)", adx_stream.file.total_bytes);
					// jo_printf(16, 12, "ansct(%i)", adx_stream.file.total_sectors);
				/////////////
				if(!buf.operating)
				{
					//Un-lock file system in case of PCM stream being paused.
					file.transfer_lock = false;
				}
				/////////////
				slSynch();
			} else if(file.requested && file.sectors_read_so_far < file.total_sectors)
			{
			//This branch is for serving an active file request from CD to RAM.
			GFS_NwFread(file.handle, file_transfer_sector,
			file_system_buffer_location + (file.sectors_read_so_far * file_transfer_size), file_transfer_size);
				do{
					game_code();
						jo_printf(16, 2, "--FILE--");
						// jo_printf(2, 6, "bytes(%i)", byte_dummy);
						// jo_printf(16, 6, "bufrq(%i)", buf.needs_buffer_filled);
						// jo_printf(2, 8, "buf0f(%i)", buf.segment_full[0]); 
						// jo_printf(2, 9, "buf1f(%i)", buf.segment_full[1]); 
						// jo_printf(16, 8, "filerq(%i)", file.requested);
						// jo_printf(16, 9, "ftrans(%i)", file.transfer_lock);
						// jo_printf(2, 10, "fsetup(%i)", file.setup_requested);
						// jo_printf(16, 10, "fsect(%i)", file.sectors_read_so_far);
						// jo_printf(2, 12, "fsize(%i)", file.total_sectors);
						// jo_printf(16, 12, "fnsct(%i)", file.total_bytes);
					////////////
					slSynch();
					GFS_NwExecOne(file.handle);
					GFS_NwGetStat(file.handle, &gfs_svr_status, &byte_dummy);
				}while(gfs_svr_status != GFS_SVR_COMPLETED);
				file.sectors_read_so_far += file_transfer_sector;
				file.transfer_lock = true;
			} else if(file.requested && file.sectors_read_so_far >= file.total_sectors)
			{
			//This branch is for when the file transfer is complete. It also triggers the data handling function.
			//The file handler function is a function pointer, not a direct reference, so user can change it when file type changes.
				game_code();
			/////////////////
				file_handler_function(file_system_buffer_location);
				file.requested = false;
				GFS_Close(file.handle);
				slSynch();
			} else if(!file.requested && file.setup_requested && !adx_stream.file.transfer_lock)
			{
			//This branch is for when a file is requested, but the file system parameters for that file are not yet set.
			//The parameters are set and other important parameters are re-set here, too.
				game_code();
			//////////////////
				file.handle = GFS_Open(file.id);
				GFS_SetReadPara(file.handle, (64 * 1024));
				GFS_SetTransPara(file.handle, file_transfer_sector);
				GFS_SetTmode(file.handle, GFS_TMODE_SDMA0);
				GFS_GetFileSize(file.handle, NULL, &file.total_sectors, NULL);
				GFS_GetFileInfo(file.handle, NULL, NULL, &file.total_bytes, NULL);
				file.sectors_read_so_far = 0;
				file.setup_requested = false;
				file.requested = true;
				file.transfer_lock = true;
			//////////////////
				slSynch();
			} else if(!adx_stream.file.requested && adx_stream.file.setup_requested && adx_stream.front_buffer_okay && adx_stream.back_buffer_okay)
			{
			/////////////////////////////////
			//
			//	This branch is for when an ADX file is requested, but the file system parameters for it are not yet set.
			//	This broadly sets up the file system to stream the ADX. It also prepares the driver for the sound.
			//
				game_code();
			////////////////////////////
				adx_stream.file.handle = GFS_Open(adx_stream.file.id);
				GFS_SetReadPara(adx_stream.file.handle, (64 * 1024));
				GFS_SetTransPara(adx_stream.file.handle, file_transfer_sector);
				GFS_SetTmode(adx_stream.file.handle, GFS_TMODE_SDMA0);
				GFS_GetFileSize(adx_stream.file.handle, NULL, &adx_stream.file.total_sectors, NULL);
				GFS_GetFileInfo(adx_stream.file.handle, NULL, NULL, &adx_stream.file.total_bytes, NULL);
				adx_stream.file.sectors_read_so_far = 0;
				adx_stream.file.setup_requested = false;
				adx_stream.file.requested = true;
				adx_stream.file.transfer_lock = true;
				//////////////////////
				adx_stream.back_buffer_filled[0] = false;
				adx_stream.back_buffer_filled[1] = false;
				/////////////////////
				// Tell Driver how long to play the sound
				// It's approximate, but should be ok.
				m68k_com->adx_stream_length = (adx_stream.file.total_bytes / 18)-1;
				/////////////////////
				slSynch();
			} else if(adx_stream.file.sectors_read_so_far >= adx_stream.file.total_sectors || adx_stream.request_stop == true)
			{
				////////////////////////
				//End handling ADX file. The driver should know when to properly stop playback.
				game_code();
				////////////////////////
				adx_stream.file.requested = false;
				adx_stream.file.transfer_lock = false;
				adx_stream.active = false;
				adx_stream.playing = false;
				adx_stream.request_stop = false;
				GFS_Close(adx_stream.file.handle);
				slSynch();
			} else if(adx_stream.file.requested && !adx_stream.back_buffer_filled[0] && !adx_stream.back_buffer_filled[1]
						&& adx_stream.file.sectors_read_so_far < adx_stream.file.total_sectors)
			{
			//Basically, we set-up the ADX file, and trigger it to read in new data when the back buffer is empty.
			//This branch is for serving an active file request from CD to RAM.
			GFS_NwFread(adx_stream.file.handle, file_transfer_sector,
			adx_stream.back_buffer[0], file_transfer_size);
				do{
					game_code();
						jo_printf(16, 2, "--ADX--");
						// jo_printf(2, 6, "bytes(%i)", byte_dummy);
						// jo_printf(16, 6, "bufrq(%i)", buf.needs_buffer_filled);
						// jo_printf(2, 8, "adx0f(%i)", adx_stream.back_buffer_filled[0]); 
						// jo_printf(2, 9, "adx1f(%i)", adx_stream.back_buffer_filled[1]); 
						// jo_printf(16, 8, "adxrq(%i)", adx_stream.file.requested);
						// jo_printf(16, 9, "atrans(%i)", gfs_svr_status);
						// jo_printf(2, 10, "asetup(%i)", adx_stream.file.setup_requested);
						// jo_printf(16, 10, "asect(%i)", adx_stream.file.sectors_read_so_far);
						// jo_printf(2, 12, "asize(%i)", adx_stream.file.total_bytes);
						// jo_printf(16, 12, "ansct(%i)", adx_stream.file.total_sectors);
					////////////
					slSynch();
					GFS_NwExecOne(adx_stream.file.handle);
					GFS_NwGetStat(adx_stream.file.handle, &gfs_svr_status, &byte_dummy);
				}while(gfs_svr_status != GFS_SVR_COMPLETED);
				adx_stream.file.sectors_read_so_far += file_transfer_sector;
				//////////////////////
				adx_stream.back_buffer_filled[0] = true;
				adx_stream.back_buffer_filled[1] = true;
				/////////////////////
				//
				// In case of the sound not playing yet, this buffer fill was a pre-buffer.
				// Now we should start playing the sound.
				//
				if(!m68k_com->pcmCtrl[adx_stream.pcm_number].sh2_permit)
				{
					pcm_play(adx_stream.pcm_number, ADX_STREAM, adx_stream.volume);
				}
			}
		} else if(buf.needs_buffer_filled && buf.operating)
		{
		//This branch serves the PCM stream new data when it needs it.
			GFS_NwFread(buf.file_handle, buf.transfer_sectors,
			buf.segment_locations[buf.active_buf_segment] + (buf.steps_of_new_data_in_buffer * buf.transfer_bytes), buf.transfer_bytes);
			buf.steps_of_new_data_in_buffer++;
			do{
				game_code();
					jo_printf(16, 2, "--MUSI--");
					// jo_printf(2, 5, "steps(%i)", buf.steps_of_new_data_in_buffer);
					// jo_printf(2, 6, "bytes(%i)", bytes_read_now);
					// jo_printf(16, 5, "act(%i)", buf.active_buf_segment);
					// jo_printf(16, 6, "bufrq(%i)", buf.needs_buffer_filled);
					// jo_printf(2, 8, "buf0f(%i)", buf.segment_full[0]); 
					// jo_printf(2, 9, "buf1f(%i)", buf.segment_full[1]); 
					// jo_printf(0, 19, "stat(%i)", gfs_svr_status);
				slSynch();
					if(buf.steps_of_new_data_in_buffer > buf.segment_transfer_time)
					{
						file.transfer_lock = false;
						buf.needs_buffer_filled = false;
						buf.segment_full[buf.active_buf_segment] = true;
						break;
					}
				GFS_NwExecOne(buf.file_handle);
				GFS_NwGetStat(buf.file_handle, &gfs_svr_status, &bytes_read_now);
			}while(gfs_svr_status != GFS_SVR_COMPLETED);
				
		}
	}

}



