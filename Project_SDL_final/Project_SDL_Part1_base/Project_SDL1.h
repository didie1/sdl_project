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
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
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

class animal;

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

class animal : public interacting_object
{
private:
    // todo: Attribute(s) to define its position
    std::string file_path;

protected:
    // SDL_Surface *image_ptr_; // The texture of the sheep (the loaded image),
    // use
    // load_surface_for

    float speed_norm = 5;

public:
    explicit animal(const std::string &file_path,
                    SDL_Surface *window_surface_ptr);
    // todo: The constructor has to load the sdl_surface that corresponds to the
    // texture
    ~animal(){}; // todo: Use the destructor to release memory and "clean up
                 // behind you"

    void draw(); // todo: Draw the animal on the screen <-> window_surface_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance

    virtual void move(){}; // todo: Animals move around, but in a different
                           // fashion depending on which type of animal

    bool male = true;
    unsigned int hp;
};



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
    // void detect(std::vector<sheep *> sheeplist);
    // implement functions that are purely virtual in base class
};
// class sheep, derived from animal
class sheep : public animal
{
public:
    long cooldown;
    sheep(SDL_Surface *window_surface_ptr);
    void move() final;
    void interract(animal &other) final;
    // void detect(std::vector<wolf *> wolfslist);
    // implement functions that are purely virtual in base class

private:
    Vector2D closest_wolf;
    float dist_wolf;
};


// The application class, which is in charge of generating the window
class application
{
private:
    // The following are OWNING ptrs
    SDL_Window *window_ptr_;
    SDL_Surface *window_surface_ptr_;
    SDL_Event window_event_;

    // Other attributes here, for example an instance of ground
    ground *my_ground;

public:
    application(unsigned int n_sheep, unsigned int n_wolf); // Ctor
    ~application(); // dtor

    int loop(unsigned int period); // main loop of the application.
                                   // this ensures that the screen is updated
                                   // at the correct rate.
                                   // See SDL_GetTicks() and SDL_Delay() to
                                   // enforce a duration the application should
                                   // terminate after 'period' seconds
};
