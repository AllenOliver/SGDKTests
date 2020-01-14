#include <genesis.h>
#include "music.h"
#include "gfx.h"


//Variables
u8 Intro = 66; //The intro sound index in memory
int scrollspeed = 1; //speedat which scrolling happens

//Declarations;
void DrawUI();
void Init();
void HandleInput(u16 joy, u16 changed, u16 state);
void fillLines();


int main()
{
    Init();    

    //Set tile size
    VDP_setPlanSize(32,32);

    //Load in our tile
    VDP_loadTileSet(block.tileset, 1, DMA);
    VDP_setPalette(PAL1, block.palette->data);

    //Fill the lines on the screen
    fillLines();

    //Set sounds up
    XGM_setPCM(Intro, intro, sizeof(intro));

    //Do some joypad stuff
    JOY_init();
    JOY_setEventHandler(&HandleInput);

    SND_startPlayPCM_XGM(Intro, 2, SOUND_PCM_CH2);
    int offset = 0;
    //Game Loop
    while (1)
    {
                DrawUI();

        VDP_setHorizontalScroll(PLAN_A, offset -= scrollspeed);
        //VDP_setHorizontalScroll(PLAN_B, offset += scrollspeed);

        if(offset <= -256) //prevent overflow
            offset = 0;

        VDP_waitVSync();
    }
    return (0);
}

void Init()
{
    // initialization
    VDP_setScreenWidth320();
    VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x453A37)); //Setting palette 0 to the background
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
}

void fillLines()
{
 for (int i = 0; i < 30; i++) //fill the 30 lines on the screen
 {
     if(i % 2 == 0) //even lines
         VDP_fillTileMapRect(PLAN_A, TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),0,i,32,1);
     else //odd lines
         VDP_fillTileMapRect(PLAN_B, TILE_ATTR_FULL(PAL0,0,FALSE,FALSE,1),0,i,32,1);
 }
}

void DrawUI()
{
    VDP_drawText("Scrolling Test 0.4", 10, 1);
    VDP_drawText("Allen Oliver 2019", 10, 4);

}

// Handles input of the first controller
//Changes the scrolling based on input
void HandleInput(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if(state && BUTTON_RIGHT)
            scrollspeed = 2;
        else if (state && BUTTON_LEFT)
            scrollspeed= -2;
    }
}


