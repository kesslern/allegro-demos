#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

// All measurements in meters unless otherwise specified

#define SCREEN_WIDTH_PX 640.0
#define SCREEN_HEIGHT_PX 480.0

#define SCREEN_HEIGHT 50.0
#define BALL_RADIUS 1.0
#define BALL_MASS 25.0

#define FPS 60.0
#define GRAVITY 8.87

#define M2PX(M) (SCREEN_HEIGHT_PX/SCREEN_HEIGHT*M)
#define PX2M(P) (SCREEN_HEIGHT/SCREEN_HEIGHT_PX*P)

#define SCREEN_WIDTH PX2M(SCREEN_WIDTH_PX)

#define BALL_WIDTH (BALL_RADIUS * 2)
#define BALL_HEIGHT (BALL_RADIUS * 2)

#define BALL_COLOR al_map_rgb(255, 0, 0)

#define BALL_X_MIN BALL_RADIUS
#define BALL_X_MAX (SCREEN_WIDTH - BALL_RADIUS)
#define BALL_Y_MIN BALL_RADIUS
#define BALL_Y_MAX (SCREEN_HEIGHT - BALL_RADIUS)

typedef struct {
  double x;
  double y;
} Coordinate;

typedef struct {
  double x;
  double y;
} Velocity;

typedef struct {
  Coordinate position;
  Velocity velocity;
} Ball;

int main()
{
  al_init();
  al_install_keyboard();
  
  ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX);
  ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
  ALLEGRO_EVENT_SOURCE* keyboard = al_get_keyboard_event_source();
  ALLEGRO_TIMER* timer = al_create_timer(1 / FPS);
  
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, keyboard);

  al_clear_to_color(al_map_rgb(0,0,0));
  al_flip_display();
  al_start_timer(timer);
  
  ALLEGRO_EVENT event;

  int go = 1;
  int redraw = false;
  Ball ball = {
               .velocity = {
                            .x = 0,
                            .y = 0
                            },
               .position = {
                            .x = SCREEN_WIDTH / 2,
                            .y = BALL_Y_MIN
                            }
  };
  
  double last_frame = al_get_time();

  while (go) {
    al_wait_for_event(event_queue, &event);
    if (event.type == ALLEGRO_EVENT_KEY_UP) {
      switch(event.keyboard.keycode) {
      case ALLEGRO_KEY_UP:
        printf("up\n");
        break;

      case ALLEGRO_KEY_DOWN:
        printf("down\n");
        break;

      case ALLEGRO_KEY_LEFT:
        printf("left\n");
        break;

      case ALLEGRO_KEY_RIGHT:
        printf("right\n");
        break;

      case ALLEGRO_KEY_Q:
      case ALLEGRO_KEY_ESCAPE:
        go = 0;
        break;
      }
    } else if(event.type == ALLEGRO_EVENT_TIMER) {
      redraw = true;
    }

    if(redraw && al_is_event_queue_empty(event_queue)) {
      redraw = false;
      double frame_time = al_get_time() - last_frame;
      last_frame = al_get_time();
      double delta_gravity = frame_time * GRAVITY;
      double delta_drag = frame_time * 0.45 * ball.velocity.y * ball.velocity.y * 0.25;
      ball.velocity.y += delta_gravity;

      if (ball.velocity.y > 0) {
        ball.velocity.y -= delta_drag;
      } {
        ball.velocity.y += delta_drag;
      }
      
      ball.position.y += ball.velocity.y * frame_time;

      if (ball.position.y > BALL_Y_MAX) {
        ball.position.y = BALL_Y_MAX;
        ball.velocity.y = -ball.velocity.y;
      }
      
      al_clear_to_color(al_map_rgb(0,0,0));
      al_draw_filled_circle(M2PX(ball.position.x), M2PX(ball.position.y), M2PX(BALL_RADIUS), BALL_COLOR);
      
      al_flip_display();
    }
}
 
  
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  
  return 0;
}
