#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"

#include "Textures.h"

#include "Simon.h"


#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"CASTLEVANIA"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 830
#define SCREEN_HEIGHT 625

#define MAX_FRAME_RATE 120