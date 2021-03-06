#include "player.h"
#include "mapAsm.h"
#include "updateInput.h"
#include "drawColumn.h"
#include "playSound.h"
#include "util.h"

#include "automap.h"

#pragma staticlocals(on)

#define POKE(addr,val) ((*(unsigned char *)(addr)) = val)
#define PEEK(addr) (*(unsigned char *)(addr))

#define MAX_OFFSET 200
#define OFFSET_STEP 4

int offsetX, offsetY;
char zoom;

void __fastcall__ automap_draw(int offsetX, int offsetY, char zoom, char player_x, char player_y, char player_a);

void __fastcall__ automap_enter(void)
{
  // write white/mono to the colour memory
  POKE(0x900F, 8 + 3);
  setupBitmap(1); // mono, white
  // reset offset
  offsetX = 0;
  offsetY = 0;
  zoom = 1;
}

void wait_for_ctrl_release(void)
{
  char ctrlKeys;
  do
  {
    readInput();
    ctrlKeys = getControlKeys();
  }
  while (ctrlKeys & KEY_CTRL);
}

char __fastcall__ automap_update(void)
{
  // check for scrolling
  char keys = readInput();
  char ctrlKeys = getControlKeys();
  char pxhi, pyhi;
  if (ctrlKeys & KEY_CTRL)
  {
    wait_for_ctrl_release();
    return 0;
  }
  if ((keys & KEY_MOVERIGHT) && offsetX > -MAX_OFFSET)
  {
    offsetX -= OFFSET_STEP;
  }
  if ((keys & KEY_MOVELEFT) && offsetX < MAX_OFFSET)
  {
    offsetX += OFFSET_STEP;
  }
  if ((keys & KEY_FORWARD) && offsetY < MAX_OFFSET)
  {
    offsetY += OFFSET_STEP;
  }
  if ((keys & KEY_BACK) && offsetY > -MAX_OFFSET)
  {
    offsetY -= OFFSET_STEP;
  }
  if (keys & KEY_FIRE)
  {
    zoom = 2;
  }
  if (keys & KEY_USE)
  {
    zoom = 1;
  }

  clearSecondBuffer();
  pxhi = *(((char *)(&playerx))+1);
  pyhi = *(((char *)(&playery))+1);
  automap_draw(offsetX, offsetY, zoom, pxhi, pyhi, playera);
  copyToPrimaryBuffer();
  
  return 1;
}

void __fastcall__ automap(void)
{
  automap_enter();
  wait_for_ctrl_release();
  while (automap_update()) ;
}
