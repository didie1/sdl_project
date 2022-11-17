#include "wolf.h"

void wolf::move()
{
  if (this->pos.x + this->spd.x < frame_boundary || this->pos.x + this->spd.x > frame_width - this->image_ptr_->w - frame_boundary)
    this->spd.x = -this->spd.x;
  if (this->pos.y + this->spd.y < frame_boundary || this->pos.y + this->spd.y > frame_height - this->image_ptr_->h - frame_boundary)
    this->spd.y = -this->spd.y;
  this->pos.x += this->spd.x;
  this->pos.y  += this->spd.y;
}
