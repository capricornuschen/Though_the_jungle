#include "SDL/SDL_rotozoom.h"
#include "drawable.h"
#include "frame.h"
#include "ioManager.h"
#include "viewport.h"

Frame::Frame( const std::string& name, SDL_Surface* surf) : 
  screen(IOManager::getInstance().getScreen()),
  surface( surf ),
  width(Gamedata::getInstance().getXmlInt(name+"/width")), 
  height(Gamedata::getInstance().getXmlInt(name+"/height")),
  sourceX(0),
  sourceY(0)
{ }

Frame::Frame( const std::string& name, SDL_Surface* surf, double zoom) : 
  screen(IOManager::getInstance().getScreen()),
  surface( surf ),
  width(Gamedata::getInstance().getXmlInt(name+"/width") * zoom), 
  height(Gamedata::getInstance().getXmlInt(name+"/height")* zoom),
  sourceX(0),
  sourceY(0)
{ }


Frame::Frame( SDL_Surface* spr, Uint16 w, Uint16 h,
              Sint16 src_x, Sint16 src_y) :
  screen(IOManager::getInstance().getScreen()),
  surface(spr), 
  width(w), height(h),
  sourceX(src_x), sourceY(src_y) {
}

Frame::Frame( const Frame& frame ) :
  screen(frame.screen),
  surface(frame.surface), 
  width(frame.width), 
  height(frame.height),
  sourceX(frame.sourceX), 
  sourceY(frame.sourceY) 
  { }

Frame& Frame::operator=(const Frame& rhs) {
  surface = rhs.surface;
  screen = rhs.screen;
  width = rhs.width;
  height = rhs.height;
  sourceX = rhs.sourceX;
  sourceY = rhs.sourceY;
  return *this;
}

void Frame::draw(Sint16 x, Sint16 y) const {
  SDL_Rect src = { sourceX, sourceY, width, height };    
// 1. At first time,x minus startLoc x of the sprite,we get the displacement of the sprite.
// 2. after update   
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, width, height };
  // use which part of source surface(determined by sourceX, sourceY, width,height in SDL_Rect src to draw on specific part of destination surface)
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const {
  //SDL_Rect -- Defines a rectangular area 
  // typedef struct{
  // Sint16 x, y;
  // Uint16 w, h;
  // }SDL_Rect;
  // x, y Position of the upper-left corner of the rectangle
  // w, h The width and height of the rectangle
  //width and height were get from xml in constructor.
  SDL_Rect src = { sx, sy, width, height };    
  SDL_Rect dest = {dx, dy, width, height };
  //This performs a fast blit from the source surface to the destination surface. If srcrect is NULL, the entire surface is copied. If dstrect is NULL, then the destination position (upper left corner) is (0, 0). 
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 x, Sint16 y, double angle) const {
  SDL_Surface* tmp = rotozoomSurface(surface, angle, 1, 1);
  Sint16 zero = 0;
  Uint16 width = tmp->w;
  Uint16 height = tmp->h;
  SDL_Rect src = { zero, zero, width, height };    
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, 0, 0 };
  SDL_BlitSurface(tmp, &src, screen, &dest);
  SDL_FreeSurface( tmp );
}

