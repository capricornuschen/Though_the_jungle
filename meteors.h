#ifndef METEORS__H
#define METEORS__H
#include <list>
#include "meteor.h"
#include "drawable.h"

class Meteors {
public:
  Meteors(const std::string&);
  Meteors(const Meteors&);
  ~Meteors();
  void draw() const;
  void reset();
  void update(Uint32 ticks);
  void fall(const Vector2f& pos, const Vector2f& vel);

  unsigned int meteorCount() const {return meteorList.size();}
  unsigned int freeCount() const {return freeList.size();}
  std::list<Meteor> getmeteorlist(){return meteorList;}
  std::list<Meteor> getfreelist(){return freeList;}
//  bool collidedWith(const Sprite* obj) const;
private:
  std::string name;
//  CollisionStrategy* strategy;
  SDL_Surface *meteorSurface;
  Frame* meteorFrame;
  int frameWidth;
  int frameHeight;
  float meteorInterval;
  float timeSinceLastFrame;
  mutable std::list<Meteor> meteorList;
  mutable std::list<Meteor> freeList;

  Meteors& operator=(const Meteors&);
};
#endif
