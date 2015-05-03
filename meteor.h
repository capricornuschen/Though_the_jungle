#ifndef METEOR__H
#define METEOR__H
#include <iostream>
#include "sprite.h"
#include "gamedata.h"

class Meteor : public Sprite {
public:
  explicit Meteor(const string& name,
                  const Vector2f& pos, const Vector2f vel,
                  const Frame* fm) :
    Sprite(name, pos, vel, fm),
    distance(0),
    maxDistance(Gamedata::getInstance().getXmlInt(name+"/Distance")),
    tooFar(false)
  {}
  virtual void update(Uint32 ticks);
  bool goneTooFar() const {return tooFar;}
  void reset() {
    tooFar = false;
    distance = 0;
  }

private:
  float distance;
  float maxDistance;
  bool tooFar;
};
#endif





























