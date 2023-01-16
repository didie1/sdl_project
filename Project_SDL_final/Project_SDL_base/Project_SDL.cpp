// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <math.h>
#include <numeric>
#include <random>
#include <string>
#include <typeinfo>


void init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("init():" + std::string(SDL_GetError()));

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw std::runtime_error("init(): SDL_image could not initialize! "
                                 "SDL_image Error: "
                                 + std::string(IMG_GetError()));
}

namespace
{
    // Defining a namespace without a name -> Anonymous workspace
    // Its purpose is to indicate to the compiler that everything
    // inside of it is UNIQUELY used within this source file.

    SDL_Surface *load_surface_for(const char *path,
                                  SDL_Surface *window_surface_ptr)
    {
        // Helper function to load a png for a specific surface
        // See SDL_ConvertSurface
        SDL_Surface *img = IMG_Load(path);
        if (img == NULL)
        {
            std::cout << "Bug IMG LOAD" << std::endl;
            return NULL;
        }

        SDL_Surface *ret =
                SDL_ConvertSurface(img, window_surface_ptr->format, 0);
        if (ret == NULL)
        {
            std::cout << "BUG CONVERT SURFACE" << std::endl;
            return NULL;
        }

        SDL_FreeSurface(img);
        return ret;
    }
} // namespace

/*
 * 2D Vector
 */

float get_rand_float(int low, int high)
{
    return low + rand() / (RAND_MAX / (high - low + 1) + 1);
}

Vector2D::Vector2D()
{
    this->x = 0;
    this->y = 0;
}

Vector2D::Vector2D(float a, float b)
{
    this->x = a;
    this->y = b;
}

bool Vector2D::is_nan()
{
    return this->x != this->x || this->y != this->y;
}

void Vector2D::operator+=(const Vector2D &a)
{
    this->x += a.x;
    this->y += a.y;
}

Vector2D operator-(const Vector2D &a, const Vector2D &o)
{
    return Vector2D(a.x - o.x, a.y - o.y);
}

Vector2D operator*(const Vector2D &a, float b)
{
    return Vector2D(b * a.x, b * a.y);
}

std::ostream &operator<<(std::ostream &o, const Vector2D &a)
{
    return o << "(" << a.x << "," << a.y << ")";
}

float Vector2D::get_norm() const
{
    float res = sqrt(this->x * this->x + this->y * this->y);
    if (res != res)
    {
        std::cout << "NOT a NUMBER in get_norm" << std::endl;
        abort();
    }
    return res;
}

Vector2D normalize(const Vector2D &o)
{
    float norm = o.get_norm();
    if (norm == 0)
    {
        std::cout << "Norm = 0 in normalize" << std::endl;
    }
    Vector2D res = Vector2D(o.x / norm, o.y / norm);
    if (res.is_nan())
    {
        std::cout << "NaN in normalize" << std::endl;
        abort();
    }
    return res;
}

float vector_distance(const Vector2D &a, const Vector2D &b)
{
    return (a - b).get_norm();
}

Vector2D random_vector(float norm)
{
    float x = 0;
    while (x == 0)
        x = get_rand_float(-10, 10);
    float y = 0;
    while (y == 0)
        y = get_rand_float(-10, 10);

    Vector2D res = normalize(Vector2D(x, y)) * norm;
    if (res.is_nan())
    {
        std::cout << "NaN in random vector" << std::endl;
        abort();
    }
    return res;
}

//INTERACTING OBJECT

bool interacting_object::has_attribute(const std::string &att)
{
    return this->attribute == att;
}

std::string interacting_object::get_attribute()
{
    return this->attribute;
}

/*
 * ANIMAL
 */

animal::animal(const std::string &file_path, SDL_Surface *window_surface_ptr)
        : interacting_object::interacting_object(window_surface_ptr, file_path)
{
    this->hp = 600;
    this->speed = random_vector(this->speed_norm);
}

void animal::draw()
{
    SDL_Rect dst_rect = SDL_Rect{ int(this->pos.x), int(this->pos.y),
                                  int(this->pos.x + this->image_ptr_->w),
                                  int(this->pos.y + this->image_ptr_->h) };

    SDL_BlitSurface(this->image_ptr_, NULL, this->window_surface_ptr_,
                    &dst_rect);
}

/*
 * SHEPHERD
 */

shepherd::shepherd(SDL_Surface *window_surface_ptr)
    : animal::animal("media/shepherd.png", window_surface_ptr)
{
    this->attribute = "shepherd";
}

void shepherd::interract(animal &other)
{
    return;
}

void shepherd::move()
{
    SDL_Event event;
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
    SDL_PollEvent(&event);
    //WSAD  & UP/DOWN/LEFT/RIGHT arrow
    if (keyboard_state_array[SDL_SCANCODE_W]
        || keyboard_state_array[SDL_SCANCODE_UP])
        this->speed.y -= 5;
    if (keyboard_state_array[SDL_SCANCODE_S]
        || keyboard_state_array[SDL_SCANCODE_DOWN])
        this->speed.y += 5;
    if (keyboard_state_array[SDL_SCANCODE_A]
        || keyboard_state_array[SDL_SCANCODE_LEFT])
        this->speed.x -= 5;
    if (keyboard_state_array[SDL_SCANCODE_D]
        || keyboard_state_array[SDL_SCANCODE_RIGHT])
        this->speed.x += 5;
    //Limitation inside the frame 
    if (this->pos.x + this->speed.x < frame_boundary
        || this->pos.x + this->speed.x
            > frame_width - this->image_ptr_->w - frame_boundary)
        this->speed.x = -this->speed.x;
    if (this->pos.y + this->speed.y < frame_boundary
        || this->pos.y + this->speed.y
            > frame_height - this->image_ptr_->h - frame_boundary)
        this->speed.y = -this->speed.y;

    this->pos.x += this->speed.x;
    this->pos.y += this->speed.y;
    this->speed.y = 0;
    this->speed.x = 0;
}
/*
 * WOLF
 */

wolf::wolf(SDL_Surface *window_surface_ptr)
        : animal::animal("media/wolf.png", window_surface_ptr)
{
    this->attribute = "wolf";
}

void wolf::interract(animal &other)
{
    if (other.has_attribute("sheep") == true)
    {
        float curr_distance = vector_distance(this->pos, other.pos);
        if (curr_distance < this->closest_dist)
        {
            this->closest_sheep = other.pos;
            this->closest_dist = curr_distance;
        }
    }
    else if (other.has_attribute("dog") == true)
    {
        Vector2D vector_to_dog = other.pos - this->pos;
        this->dog_position = other.pos;
        float distance_to_dog = vector_to_dog.get_norm();
        if (distance_to_dog < 250)
        {
            this->is_afraid = true;
        }
        else
        {
            this->is_afraid = false;
        }
    }
}
void wolf::move()
{
    if (this->hp != 0)
        this->hp--;

    this->speed = normalize(this->closest_sheep - this->pos) * this->speed_norm;
    this->closest_dist = FLT_MAX;

    if (this->is_afraid == true)
    {
        this->speed =
                normalize(this->pos - this->dog_position) * this->speed_norm;
    }

    if (this->pos.x + this->speed.x < frame_boundary
        || this->pos.x + this->speed.x
           > frame_width - this->image_ptr_->w - frame_boundary)
        this->speed.x = -this->speed.x;
    if (this->pos.y + this->speed.y < frame_boundary
        || this->pos.y + this->speed.y
           > frame_height - this->image_ptr_->h - frame_boundary)
        this->speed.y = -this->speed.y;
    this->pos.x += this->speed.x;
    this->pos.y += this->speed.y;
}

/*
 * DOG
 */

dog::dog(SDL_Surface *window_surface_ptr)
    : animal::animal("media/dog.png", window_surface_ptr)
{
    this->attribute = "dog";
}

void dog::interract(animal &other)
{
    if (other.has_attribute("shepherd") == false)
        return;
    this->speed = Vector2D(0, 0);
    this->pos =
        Vector2D(other.pos.x + this->circle * cos(this->phi / 50),
                other.pos.y + this->circle * sin(this->phi / 50));
}

void dog::move()
{
    if (this->pos.x < frame_boundary)
        this->pos.x = frame_boundary;
    else if (this->pos.x > frame_width - this->image_ptr_->w - frame_boundary)
        this->pos.x = frame_width - this->image_ptr_->w - frame_boundary;
    if (this->pos.y < frame_boundary)
        this->pos.y = frame_boundary;
    else if (this->pos.y > frame_height - this->image_ptr_->h - frame_boundary)
        this->pos.y = frame_height - this->image_ptr_->h - frame_boundary;

    this->phi++;
}
/*
 * SHEEP
*/

sheep::sheep(SDL_Surface *window_surface_ptr)
    : animal::animal("media/sheep.png", window_surface_ptr)
{
    if (get_rand_float(0, 1) > 0)
        male = false;
    else
    {
        cooldown = 0;
    }
    this->attribute = "sheep";
}

void sheep::interract(animal &other)
{
    if (other.has_attribute("wolf"))
    {
        float temp = vector_distance(this->pos, other.pos);
        if (temp < 80)
        {
            this->hp = 0;
            other.hp = 600;
        }
        else if (temp < this->dist_wolf)
        {
            this->dist_wolf = temp;
            this->closest_wolf = other.pos;
        }
    }
    if (other.has_attribute("sheep"))
    {
        if (other.male && !this->male
            && vector_distance(this->pos, other.pos) < 80
            && this->cooldown == 0)
            this->hp = 60;
    }
}

void sheep::move()
{
    if (this->dist_wolf < 150)
    {
        this->speed =
            normalize(this->pos - this->closest_wolf) * this->speed_norm * 1.5;
    }
    else
    {
        this->speed = normalize(this->speed) * this->speed_norm;
    }

    if (this->cooldown != 0)
    {
        this->cooldown--;
    }

    if (this->pos.x + this->speed.x < frame_boundary
        || this->pos.x + this->speed.x
            > frame_width - this->image_ptr_->w - frame_boundary)
        this->speed.x = -this->speed.x;
    if (this->pos.y + this->speed.y < frame_boundary
        || this->pos.y + this->speed.y
            > frame_height - this->image_ptr_->h - frame_boundary)
        this->speed.y = -this->speed.y;
    this->pos.x += this->speed.x;
    this->pos.y += this->speed.y;

    this->dist_wolf = FLT_MAX;
}


/*
 * GROUND
 */

ground::ground(SDL_Surface *window_surface_ptr)
{
    this->window_surface_ptr_ = window_surface_ptr;
}

ground::~ground()
{
    std::cout << "Your final score is " << this->score << std::endl;
    SDL_FreeSurface(this->window_surface_ptr_);
    delete (this->player);
}

bool ground::update()
{
    std::vector<std::vector<std::unique_ptr<animal>>::iterator> dead;
    std::vector<Vector2D> babies;
    std::vector<std::unique_ptr<animal>> babie;
    for (auto i = this->animals.begin(); i != this->animals.end(); i++)
    {
        for (auto j = this->animals.begin(); j != this->animals.end(); j++)
        {
            if (i == j)
                continue;
            i->get()->interract(*(j->get()));
        }
        if (i->get()->has_attribute("sheep") && i->get()->hp == 60)
        {
            sheep *add = (sheep *)(i->get());
            babies.push_back(i->get()->pos);

            add->cooldown = 600;
            add->hp = 70;
        }
        if (i->get()->hp == 0)
            dead.push_back(i);
        if (i->get()->pos.is_nan())
        {
            std::cout << i->get()->get_attribute() << std::endl;
        }
        i->get()->move();
        i->get()->draw();
    }
    for (auto &i : dead)
    {
        this->animals.erase(i);
    }

    for (auto &i : babies)
    {
        sheep *new_sheep = new sheep(this->window_surface_ptr_);
        new_sheep->pos = i;
        new_sheep->cooldown = 3600;
        this->animals.push_back(std::unique_ptr<animal>(new_sheep));
    }
    babies.clear();
    dead.clear();
    int sheep = 0;
    int wolf = 0;
    for (auto i = this->animals.begin(); i != this->animals.end(); i++)
    {
        if (i->get()->has_attribute("sheep"))
            sheep++;
        else if (i->get()->has_attribute("wolf"))
        {
            wolf++;
        }
    }
    if (sheep == 0 || wolf == 0)
        return true;
    if (this->frame == 60)
    {
        this->score = this->score + double(sheep);
        this->score = this->score / 2.0;
        this->frame = 0;
    }
    else
        this->frame++;
    return false;
}


/*
 * APPLICATION
 */
