#ifndef _ada_GFX_ext_
#define _ada_GFX_ext_
#include <Adafruit_GFX.h> 
class Adafruit_GFX_Progress_Bar
{
public:
   Adafruit_GFX_Progress_Bar(Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
   uint16_t outline, uint16_t fill, uint16_t bar)
   {
    Progress_Bar_Init(gfx, x , y, w, h, outline, fill,
        bar);
   }
  void Progress_Bar_Init(Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
   uint16_t outline, uint16_t fill, uint16_t bar)
   {
    Progress_Bar_InitUI(gfx, x - (w / 2), y - (h / 2), w, h, outline, fill,
        bar);
   }
  void Progress_Bar_InitUI(Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
   uint16_t outline, uint16_t fill, uint16_t bar)
   {
      _x1           = x;
      _y1           = y;
      _w            = w;
      _h            = h;
      _outlinecolor = outline;
      _fillcolor    = fill;
      _barcolor    = bar;
      _gfx          = gfx;
   }
  void Draw(uint8_t per)
  {
    per = min(per, 100);
    uint8_t r = min(_w, _h) / 4;
     _gfx->fillRect(_x1, _y1, _w, _h, _fillcolor);
     _gfx->drawRect(_x1, _y1, _w, _h, _outlinecolor);
     _gfx->fillRect(_x1+1, _y1+1, (_w-2) * per / 100, _h-2, _barcolor);
    
  }

private:
    Adafruit_GFX *_gfx;
    int16_t       _x1, _y1; // Coordinates of top-left corner
    uint16_t      _w, _h;
    uint16_t      _outlinecolor, _fillcolor, _barcolor;
};
class Adafruit_GFX_Scale
{
public:
  Adafruit_GFX_Scale(Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
   uint16_t scale, uint16_t font, uint16_t minV, uint16_t maxV)
   {
     Scale_Init(gfx, x, y, w, h, scale, font, minV, maxV);
   }
  void Scale_Init(Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
   uint16_t scale, uint16_t font, uint16_t minV, uint16_t maxV)
   {
    Scale_InitUI(gfx, x - (w / 2), y - (h / 2), w, h, scale, font, minV, maxV);
   }
  void Scale_InitUI(Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
   uint16_t scale, uint16_t font, uint16_t minV, uint16_t maxV)
   {
    _x1           = x;
    _y1           = y;
    _w            = w;
    _h            = h;
    _scalecolor   = scale;
    _fontcolor    = font;
    _min          = minV;
    _max      = maxV;
    _gfx          = gfx;
   }
   void Draw()
   {
     uint16_t inter = (_max - _min) / _w;

     _gfx->drawFastHLine(_x1-2, _y1, _w+5, _scalecolor);
     for (int i=0; i<=_w; i=i+20)
     {
      _gfx->drawFastVLine(_x1 + i, _y1-_h, _h, _scalecolor);
      _gfx->setTextSize(0);
      _gfx->setTextColor(0xffff);
      _gfx->setCursor(_x1+i-3, _y1-_h - 10);
      _gfx->print(i);

     }
     for (int i=10; i<=_w; i=i+20)
     {
      _gfx->drawFastVLine(_x1+i, _y1-_h/2, _h/2, _scalecolor);
     }
   }
private:
    Adafruit_GFX *_gfx;
    int16_t       _x1, _y1; // Coordinates of top-left corner
    uint16_t      _w, _h;
    uint16_t      _scalecolor, _fontcolor;
    uint16_t _min, _max;
};
#endif
