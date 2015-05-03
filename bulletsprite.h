#ifndef BULLETSPRITE__H
#define BULLETSPRITE__H
#include <string>
#include "drawable.h"

class BulletSprite : public Drawable {
public:
  BulletSprite(const std::string&);
  BulletSprite(const std::string&, const Vector2f& pos, const Vector2f& vel);
  BulletSprite(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  BulletSprite(const BulletSprite& s);
  virtual ~BulletSprite() { } 
  BulletSprite& operator=(const BulletSprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  bool isFinish(){return finish;}
  virtual void update(Uint32 ticks);

private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  bool finish;
  int getDistance(const BulletSprite*) const;
};
#endif
