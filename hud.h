#include <SDL.h>
#include "clock.h"

class Hud {
public:
  Hud();
  Hud(const Hud&);
  void drawHUD (SDL_Surface* screen, int x, int y, unsigned int mlsize, unsigned int flsize) const;
  void drawwinHUD (SDL_Surface* screen, int x, int y) const;
  void display(unsigned int mlsize, unsigned int flsize) const;
  void windisplay() const;
  unsigned int getmlsize() {return meteorlist_size;}
  unsigned int getflsize() {return freelist_size;}

private:
  unsigned int frames;
  unsigned int meteorlist_size;
  unsigned int freelist_size;
  Clock& hclock;
  const std::string title;

};

