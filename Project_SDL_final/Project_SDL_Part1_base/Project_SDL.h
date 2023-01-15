#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>
// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
constexpr unsigned frame_boundary = 100;

//Initialize SDL
void init();

class Vector2D
{
public:
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    bool is_nan();

    void operator+=(const Vector2D &a);
    friend Vector2D operator-(const Vector2D &a, const Vector2D &o);
    friend Vector2D operator*(const Vector2D &a, float b);
    friend std::ostream &operator<<(std::ostream &o, const Vector2D &a);
    float get_norm() const;
};

Vector2D normalize(const Vector2D &o);
float vector_distance(const Vector2D &a, const Vector2D &b);

//class animal;
/*
 * INTERACTING OBJECT
 */
class interacting_object
{
public:
    interacting_object(SDL_Surface *window_surface_ptr,
                       const std::string &path);

    ~interacting_object();
    Vector2D pos;
    Vector2D spd;
    bool has_attribute(const std::string &att);
    std::string get_attribute();
    virtual void interract(animal &other){};

protected:
    std::string attribute;
    SDL_Surface *image_ptr_;
    SDL_Surface *window_surface_ptr_;

private:
};

/*
 * ANIMAL
 */

class animal : public interacting_object
{
private:
    std::string file_path;

protected:
    float speed_norm = 5;

public:
    explicit animal(const std::string &file_path,
                    SDL_Surface *window_surface_ptr);
    ~animal(){}; 

    void draw(); 
    virtual void move(){}; 
    bool male = true;
    unsigned int hp;
};


/*
 * WOLF
 */

class wolf : public animal
{
private:
    Vector2D closest_sheep;
    Vector2D dog_position;
    float closest_dist;
    bool is_afraid = false;

public:
    wolf(SDL_Surface *window_surface_ptr);
    void move() final;
    void interract(animal &other) final;
};

/*
 * SHEEP
 */

class sheep : public animal
{
public:
    long cooldown;
    sheep(SDL_Surface *window_surface_ptr);
    void move() final;
    void interract(animal &other) final;

private:
    Vector2D closest_wolf;
    float dist_wolf;
};

/*
 * GROUND
 */


/*
 * WINDOW
 */

class application
{
private:

    SDL_Window *window_ptr_;
    SDL_Surface *window_surface_ptr_;
    SDL_Event window_event_;

    ground *my_ground;

public:
    application(unsigned int n_sheep, unsigned int n_wolf); 
    ~application(); 

    int loop(unsigned int period); // main loop of the application.
};
