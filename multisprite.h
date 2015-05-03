#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"


class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&);
  MultiSprite(const MultiSprite&);
  virtual ~MultiSprite() { } 

  void resetplayer();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  void addShield(){shieldflag = !shieldflag;}
  void addgodShield(){shieldgodflag = !shieldgodflag;}
  void changeflag(){explodingflag = true;}
protected:
  std::vector<Frame *> frames;
  std::vector<Frame *> shieldframe;
  std::vector<Frame *> explodingframe;
  bool booRight;
  int worldWidth;
  int worldHeight;
  int shieldTime;
  int waitTime;
  int explodingTime;
  unsigned currentFrame;
  unsigned currentexplodingFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  float timeSinceLastExplodingFrame;
  int frameWidth;
  int frameHeight;
  int shieldWidth;
  int shieldHeight;
  int explodingWidth;
  int explodingHeight;
  
  std::string frameName;
  bool shieldflag;
  bool shieldgodflag;
  bool explodingflag;
  bool gone;
  void advanceFrame(Uint32 ticks);
};

#endif
