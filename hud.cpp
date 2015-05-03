#include <iostream>
#include "ioManager.h"
#include "aaline.h"
#include "hud.h"
#include "gamedata.h"


const int HUD_WIDTH = 300;
const int HUD_HEIGHT = 280;

Hud::Hud() : 
frames(0),
meteorlist_size(0),
freelist_size(0),
hclock( Clock::getInstance() ),
title( Gamedata::getInstance().getXmlStr("screenTitle") )
{}

Hud::Hud(const Hud& chud) : 
frames(chud.frames),
meteorlist_size(chud.meteorlist_size),
freelist_size(chud.freelist_size),
hclock( Clock::getInstance() ),
title( Gamedata::getInstance().getXmlStr("screenTitle") )
{}

void Hud::drawHUD (SDL_Surface* screen, int x, int y, unsigned int mlsize, unsigned int flsize) const {
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, x, y+HUD_HEIGHT/2, 
                      x+HUD_WIDTH,y+HUD_HEIGHT/2, 
                      HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, x,y, x+HUD_WIDTH,y, RED);
  Draw_AALine(screen, x,y, x,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x+HUD_WIDTH,y, x+HUD_WIDTH,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x,y+HUD_HEIGHT, x+HUD_WIDTH,y+HUD_HEIGHT, RED);
  display(mlsize, flsize);
}

void Hud::drawwinHUD (SDL_Surface* screen, int x, int y) const {
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, x, y+HUD_HEIGHT/2, 
                      x+HUD_WIDTH,y+HUD_HEIGHT/2, 
                      HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, x,y, x+HUD_WIDTH,y, RED);
  Draw_AALine(screen, x,y, x,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x+HUD_WIDTH,y, x+HUD_WIDTH,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x,y+HUD_HEIGHT, x+HUD_WIDTH,y+HUD_HEIGHT, RED);
  windisplay();
}

void Hud::display(unsigned int mlsize, unsigned int flsize) const { 
  static unsigned int lastFrames = 0;
  static unsigned int oldFrames = 0;
  static unsigned int seconds = hclock.getSeconds();

  if ( hclock.getSeconds() > seconds ) {
    seconds = hclock.getSeconds();
    lastFrames = frames - oldFrames;
    oldFrames = frames;
  }
  IOManager::getInstance().printMessageValueAt("Seconds: ", hclock.getSeconds(), 30, 20);
  IOManager::getInstance().printMessageValueAt("fps: ", hclock.getAvgFps(), 30, 40);
  IOManager::getInstance().printMessageAt("Press P to pause sprites", 30, 80);
  IOManager::getInstance().printMessageAt("Press left: backwards", 30, 100);
  IOManager::getInstance().printMessageAt("Press right: forwards", 30, 120);
  IOManager::getInstance().printMessageAt("Press up: upwards", 30, 140);
  IOManager::getInstance().printMessageAt("Press down: downwards", 30, 160);
  IOManager::getInstance().printMessageAt("Press space: shield lasting 3 s", 30, 180);
  IOManager::getInstance().printMessageAt("Press g: god mode", 30, 200);
  IOManager::getInstance().printMessageAt("Press r: reset game", 30, 220);
  IOManager::getInstance().printMessageValueAt("meteor size: ", mlsize, 30, 240);
  IOManager::getInstance().printMessageValueAt("free size: ", flsize, 30, 260);
  IOManager::getInstance().printMessageAt(title, 30, 450);
  IOManager::getInstance()
    .printMessageValueAt("frames in sec: ", lastFrames, 30, 60);
}

void Hud::windisplay() const { 
  static unsigned int lastFrames = 0;
  static unsigned int oldFrames = 0;
  static unsigned int seconds = hclock.getSeconds();

  if ( hclock.getSeconds() > seconds ) {
    seconds = hclock.getSeconds();
    lastFrames = frames - oldFrames;
    oldFrames = frames;
  }
  IOManager::getInstance().printMessageAt("Congratulations, you win!", 30, 20);
}

