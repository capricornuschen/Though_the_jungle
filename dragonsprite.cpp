#include <cmath>
#include "dragonsprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "SDL/SDL_rotozoom.h"
#include "bulletsprite.h"

using namespace std; 

DragonSprite::~DragonSprite() {
  for (unsigned int i = 0; i < bullets.size(); i++)  {
    delete bullets[i];
  }
} 

void DragonSprite::advanceFrame(Uint32 ticks) {
	/*
  float ms = 1000.0/frameInterval;
	timeSinceLastFrame += ticks;
  int df = timeSinceLastFrame / ms;
  timeSinceLastFrame -= df * ms;
  currentFrame = (currentFrame + df) % numberOfFrames;
  */
	timeSinceLastFrame += ticks;
 //       int flag += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
    /*
    if (booRight){
    bullets.push_back(new BulletSprite("dragonbullet_right",Vector2f(X()+frameWidth/2,Y()+frameHeight/3),Vector2f(velocityX() * 5,0)));
    }
    else {
    bullets.push_back(new BulletSprite("dragonbullet_left",Vector2f(X()-frameWidth/2,Y()+frameHeight/3),Vector2f(velocityX() * 5,0)));
    }
    */
    timeSinceLastFrame = 0;
	}
  
}

DragonSprite::DragonSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frames( FrameFactory::getInstance().getFrames(name) ),
  // anson debug
  booRight(true),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  bullets(0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  frameName(name)
  { 
  }

DragonSprite::DragonSprite(const DragonSprite& s) :
  Drawable(s), 
  frames(s.frames),
  booRight(s.booRight),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  bullets(s.bullets),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  frameName(s.frameName)
  { }

void DragonSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
  for (unsigned int i = 0; i < bullets.size(); i++)  {
    bullets[i]->draw();
  }
}

void DragonSprite::update(Uint32 ticks) { 

  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
  for (unsigned int i = 0; i < bullets.size(); ++i){
    bullets[i]->update(ticks);
  }
  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
  if ( velocityX() < 0 && booRight ) {
    booRight = false;
    //SDL_Surface* surface = frame->getSurface();
    for(unsigned int i = 0; i < numberOfFrames; i++){
      SDL_Surface* surface = frames[i]->getSurface();
      // Zoomes a 32bit or 8bit 'src' surface to newly created 'dst' surface.'zoomx' and 'zoomy' are scaling factors for width and height. If 'smooth' is 1 then the destination 32bit surface is anti-aliased. If the surface is not 8bit or 32bit RGBA/ABGR it will be converted into a 32bit RGBA format on the fly.
      // and zoomx = -1 means not scale but reverse the frame by 180 angle. 
      
      SDL_Surface* pic = zoomSurface(surface, -1, 1, SMOOTHING_ON);
      if ( pic != NULL ) {
        //anson check if this lead to a double free, maybe the pointer is shallow copy.
        //SDL_FreeSurface(surface);
        frames[i]->setSurface(pic);
      }
      else throw "zoomSurface failed in TwowayEffectsSprite";
    }
  }
  if ( velocityX() > 0 && !booRight) {
    booRight = true;
    //SDL_Surface* surface = frame->getSurface();
    for(unsigned int j = 0; j < numberOfFrames; j++){
      SDL_Surface* surface = frames[j]->getSurface();
      SDL_Surface* pic = zoomSurface(surface, -1, 1, SMOOTHING_ON);
      if ( pic != NULL ) {
        //anson check if this lead to a double free, maybe the pointer is shallow copy.
        //SDL_FreeSurface(surface);
        frames[j]->setSurface(pic);
      }
      else throw "zoomSurface failed in TwowayEffectsSprite";
    }
  }
  std::vector<BulletSprite*>::iterator it;
  for(it = bullets.begin();it != bullets.end();)
  { 
    if ((*it)->isFinish())  {it = bullets.erase(it);}
    else ++it;
  }

}
