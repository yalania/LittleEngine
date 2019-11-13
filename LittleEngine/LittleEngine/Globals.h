#ifndef _GLOBALS_
#define _GLOBALS_

#include <windows.h>
enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FULLSCREEN false
#define RESIZABLE true
#define VSYNC true
#define TITLE "LittleEngine"
#define TIME_SCALE = 1;
#define LIMIT_FRAME_RATE true

const int  SCREEN_FPS = 60;
const int  SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

// Camera Default Configuration -----------
#define CAMERA_SPEED 0.05


#endif // !_GLOBALS_
