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



#define VSYNC true
#define TITLE "LittleEngine"
#define TIME_SCALE = 1;
#define LIMIT_FRAME_RATE true

// Time and Frame Configuration
const int  SCREEN_FPS = 60;
const int  SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
extern bool gameIsPaused;

//Window Default Configuration
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FULLSCREEN false
#define FULLSCREEN_DESKTOP false
#define RESIZABLE true
#define BORDERLESS false
#define BRIGHTNESS 1.0f

// Camera Default Configuration -----------
#define CAMERA_SPEED 0.05f
#define CAMERA_MAX_SPEED 10.0f
#define MAX_PLANE 1000.0f
#define MIN_PLANE -1000.0f

//Render options
#define OPENGL_MAJOR_VERSION 3
#define OPENGL_MINOR_VERSION 3

#endif // !_GLOBALS_
