//psm_stm.c
//this file is compiled separately
#include "pcm_stm.h"

GfsHn music_GFS;
unsigned short music_pitchword;
unsigned short music_bytes_per_blank;
unsigned short music_volume;


int			buffer_blank_timer = 0;
int			music_play_buffer = 0;
int			system_set_blank_timer = 0;
int			CDB_cd_read_size = 0;
int 		CDB_dma_size_sectors = 0;
int			seek_sector_offset = 0;
int			frames_to_write_buffer = 0;
int			music_write_buffer = 0;
int			music_frames_written = 0;

bool		request_music_change = false;
bool		trigger_music_playback = false;

snd_ring	music_ring_buffer[MUS_BUFCNT];
int			pcm_stream_control_slots[MUS_BUFCNT];

Sint8*	music = (Sint8*)"EVE.MUS";

void	music_vblIn(void){
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// The awful playback sections
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	if(trigger_music_playback == true)
	{
		//If we want to trigger playback, well, do it. But only start the playback if the blank timer is at 0,
		//in other words, when we've changed buffers.
	if(buffer_blank_timer == 0){
		pcm_play(pcm_stream_control_slots[music_play_buffer], PCM_SEMI, music_volume);
	}
		//So we're playing back, this is at vblank, add to the blank play timer.
		buffer_blank_timer++;
		
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Stop & change buffers
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	//This might be part of the reason the playback sounds so choppy at times. Dunno.
	if(buffer_blank_timer >= system_set_blank_timer)
	{
		//If the blank timer has run over the set blank timer, stop the currently playing sound,
		pcm_cease(pcm_stream_control_slots[music_play_buffer]);
		//and move the buffer array index up one.
		music_play_buffer++;
///Ring buffer wrap. If the buffer array index has gone to equal the total # of buffers (as the array starts at 0), reset it.
	if(music_play_buffer >= MUS_BUFCNT){
		music_play_buffer = 0;
	}
	// We're changing buffers, so reset the blank timer.
		buffer_blank_timer = 0;
	}
	}
}

void		init_music(char bitrate_select, Sint8 * music_file_name, unsigned char volume)
{
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Bitrate selection
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	if(bitrate_select == 'H')
	{
		//"H" selects high bitrate. Use 30.72.
		music_pitchword = S3072KHZ; //Pre-calculated pitchword, via pwordprog.c 
		music_bytes_per_blank = (30720<<1) / 60; //If you wanted to use 8-bit, you would just not bitshift (multiply).
	} else if(bitrate_select == 'L')
	{
		//"L" selects low bitrate. Use 15.36.
		music_pitchword = S1536KHZ; //Pre-calculated pitchword, via pwordprog.c 
		music_bytes_per_blank = (15360<<1) / 60; //If you wanted to use 8-bit, you would just not bitshift (multiply).
	}
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Static information that you SHOULD NOT CHANGE!! that's here because C won't let you make static variable calculations
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	CDB_dma_size_sectors = 4;
	CDB_cd_read_size = CDB_dma_size_sectors * 2048; //2048 being sector size
	frames_to_write_buffer = BUFFER_SIZE / CDB_cd_read_size; //You write the CD read size each frame, so... can you do the math?
	
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Read it, i guess
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	music_volume = volume;
	//music = music_file_name;
	
}


void		master_file_system(void(*game_code)(void))
{	

	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Music buffer setup
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	//The array tells the system, when at this buffer position, where to play and where to write.
	//You never want to play and write to the same spot!
music_ring_buffer[0].rd_pcmbuf = (void*)PCMBUF0;
music_ring_buffer[0].play_pcmbuf = MAP_TO_SCSP(PCMBUF2);
music_ring_buffer[1].rd_pcmbuf = (void*)PCMBUF1;
music_ring_buffer[1].play_pcmbuf = MAP_TO_SCSP(PCMBUF3);
music_ring_buffer[2].rd_pcmbuf = (void*)PCMBUF2;
music_ring_buffer[2].play_pcmbuf = MAP_TO_SCSP(PCMBUF0);
music_ring_buffer[3].rd_pcmbuf = (void*)PCMBUF3;
music_ring_buffer[3].play_pcmbuf = MAP_TO_SCSP(PCMBUF1);

	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Driver communication & PCM slot initilization
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	//Before we can properly initilize this, we need to tell the system which PCM slot at least one buffer is.
	pcm_stream_control_slots[0] = 127;
	//Then we check if that PCM slot has playsize information in it. Or really, any non-zero information.
	if(m68k_com->pcmCtrl[pcm_stream_control_slots[0]].playsize == 0)
	{
	//If it has non-zero information, that means the sound slots have yet to be initiliazed. So we do that.
for(int i = 0; i < MUS_BUFCNT; i++)
{
	//Select the PCM slot to use
	pcm_stream_control_slots[i] = 127-i;
	//Arrange the correct address in the PCM slot
	m68k_com->pcmCtrl[pcm_stream_control_slots[i]].hiAddrBits = (unsigned short)( (unsigned int)music_ring_buffer[i].play_pcmbuf >> 16);
	m68k_com->pcmCtrl[pcm_stream_control_slots[i]].loAddrBits = (unsigned short)( (unsigned int)music_ring_buffer[i].play_pcmbuf & 0xFFFF);
	//Set the correct pitchword
	m68k_com->pcmCtrl[pcm_stream_control_slots[i]].pitchword = music_pitchword;
	//Set the playsize to the buffer size, divided by two, because music is just 16-bit right now. Could be changed.
	m68k_com->pcmCtrl[pcm_stream_control_slots[i]].playsize = BUFFER_SIZE>>1;
	//Tell the driver the bytes per blank. It needs to know.
	m68k_com->pcmCtrl[pcm_stream_control_slots[i]].bytes_per_blank = music_bytes_per_blank;
	m68k_com->pcmCtrl[pcm_stream_control_slots[i]].bitDepth = 0; //Select 16-bit
	//Initialize the semi-protected loop type. Doesn't do anything here, really.
	m68k_com->pcmCtrl[pcm_stream_control_slots[i]].loopType = PCM_SEMI; //
	//Initialize to the volume. It's set elsewhere, so it doesn't matter here.
	m68k_com->pcmCtrl[pcm_stream_control_slots[i]].volume = music_volume;
}
	}

	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Music Change Handler
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	//If the music is requested to be changed, re-set all the music control information.
	if(request_music_change == true){
		//Turn off the music.
		trigger_music_playback = false;
			buffer_blank_timer = 0;
			music_write_buffer = 0;
			music_play_buffer = 0;
			music_frames_written = 0;
			seek_sector_offset = 0;
		//Signal no more change is needed.
		request_music_change = false;
	}
	//The rest of the change is handled by the game simply changing the music file name.
	/////////////////////////////////////////////////////////////////////////////////////////////////
	
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Music Blank Counter Settings
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	//If the music bitrate is set to 30.72 KHz or 15.36 (the allowed bitrates),
	//set the blanks to play before buffer change to an intelligent multiple of
	//the # of frames that the CDB will need to fill a buffer.
	//The lower bitrate can use the same buffer size for longer, so it is multiplied more.
	if(music_pitchword == S3072KHZ){
		system_set_blank_timer = (frames_to_write_buffer<<3);
	} else if(music_pitchword == S1536KHZ){
		system_set_blank_timer = (frames_to_write_buffer<<4);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
					/**FILE SYSTEM SETUP**/
	
//					This number will represent the local file # of the file in the file system.
static Sint32			music_file_id;

//					This number will represent the size of the music file in bytes.
static Sint32			music_size_bytes;

//					This number will represent the size of the music file, in sectors (2KB each).
static Sint32			music_size_sectors;

//					This number will represent the GFS error status. Non-zero values are problems.
static Sint32			GFS_read_status;

//					This number will represent the amount that the CDB has copied over to memory from CD on a per-request basis.
static Sint32			GFS_active_write_amount;

					//This will convert the file name to a file system ID.
					music_file_id = GFS_NameToId(music);
					
					//This will open the file, making it the target of any file serving requests.
					music_GFS = GFS_Open(music_file_id);

//HEY! SBL DOCUMENTATION IS WRONG! THIRD ITEM NSCT IS GFS SECTOR COUNT. SECOND ITEM IS CD SECTOR SIZE.
//This gets us some information about the file we've opened. This particular macro gets us the sector count.
	GFS_GetFileSize(music_GFS, NULL, &music_size_sectors, NULL);
//This macro will then get us the exact file size, in bytes.
	GFS_GetFileInfo(music_GFS, NULL, NULL, &music_size_bytes, NULL);
	
//This tells the CDB how much data to read from the CD per request cycle, in bytes.
	GFS_SetReadPara(music_GFS, CDB_cd_read_size);
//This tells the CDB how much data to DMA over per request cycle, in sectors.
	GFS_SetTransPara(music_GFS, CDB_dma_size_sectors);
//This tells SBL which DMA type to use to transfer from the CDB.
//SDMA0 and SDMA1 use cycle-stealing DMAs that can use idle time on the CPUs to achieve lower DMA latency.
//If you have a problem, you can try GFS_TMODE_CPU or GFS_TMODE_SCU. All are valid due to the destination being in SCSP memory.
	GFS_SetTmode(music_GFS, GFS_TMODE_SDMA1);
//If you've somehow jumped out of the function and got back here, this will seek the CDB to the correct location in the music
//to play it back seamlessly.
	GFS_Seek(music_GFS, seek_sector_offset, GFS_SEEK_SET);

for( ; ; ){
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Music Reset Handler
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	//If the seek offset is less than the music size, we haven't reached EOF yet. So we want to continue playing back the music.
	if(seek_sector_offset < music_size_sectors)
	{
	trigger_music_playback = true;
	} else if(seek_sector_offset >= music_size_sectors)
	{
		//If the seek offset is larger or equal to the music size, we've reached EOF. We want to re-set all control information,
		//and exit the loop, to re-open the file and seek to beginning of file.
	trigger_music_playback = false;
		buffer_blank_timer = 0;
		music_write_buffer = 0;
		music_play_buffer = 0;
		music_frames_written = 0;
		seek_sector_offset = 0;
	break; //"Break" will exit the otherwise endless for loop.
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Music Buffer Reading Handler
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
	//If the music frames written is less than the music frames needed,
	//and the music is now playing from a buffer it hasn't written to,
	//it is the right time to issue a new read request to the CDB to fill a buffer.
 	if(music_frames_written < frames_to_write_buffer && music_write_buffer != music_play_buffer)
	{
		
	GFS_NwFread(music_GFS,	//The GFS handle
	CDB_dma_size_sectors,	//The DMA size we want from the CDB
	(void*)music_ring_buffer[music_write_buffer].rd_pcmbuf + (music_frames_written * CDB_cd_read_size), //The address
	CDB_cd_read_size); //The # of bytes we want the CDB to give us
	
	seek_sector_offset += CDB_dma_size_sectors; //Increment the seek sector offset by the # of sectors the CDB will give us
	music_frames_written++; //Imply that the following code below has successfully written the data frame 
	}
do{
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// CDB Request Server Loop
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	*/
		game_code(); //Run your game
		GFS_NwExecOne(music_GFS); //Tell the SBL library to order the CDB to serve the read request we've given
		GFS_NwGetStat(music_GFS, &GFS_read_status, &GFS_active_write_amount); //Get the status of that read request
		//CDB = CD Block
	if(music_frames_written == frames_to_write_buffer){ //If we've written the number of frames we need for this buffer,
													//some things need to change.
		if(music_write_buffer != music_play_buffer){ //First, if we still haven't written up to the buffer being played back,
			music_write_buffer++;					//increment the write buffer upwards.
			}
		music_frames_written = 0;					//In any case, we re-set the # of frames written, because the buffer is done.
								//So the next time we start writing to a buffer, it knows we've not written any frames yet.
		}


	jo_printf(0, 20, "(%i rd amt)", GFS_active_write_amount);
	jo_printf(20, 20, "(%i stat)", GFS_read_status);
	jo_printf(0, 21, "(%i frames written)", music_frames_written);
	jo_printf(0, 22, "(MA) loop label");
	jo_printf(0, 23, "(%i) cur write case", music_write_buffer);
	jo_printf(0, 24, "(%i) cur play case", music_play_buffer);

//Continue serving the request and running your game code as long as the request is not done,
// and we've not written the requested data size.
}while(GFS_read_status != GFS_SVR_COMPLETED && GFS_active_write_amount < CDB_cd_read_size);

//If the music buffer we're writing to is greater than or equal to the # of buffers, we should go back to buffer 0.
//In other words, wrap the ring buffer.
if(music_write_buffer >= MUS_BUFCNT){
	music_write_buffer = 0;
	}

//If the game requested that the music file be changed, break from the loop to reinitialize the music system
//on the new music file-name and parameters.
if(request_music_change == true)
{
	break;
}

}
					/**END MUSIC SYSTEM SETUP**/
	GFS_Close(music_GFS);

}
