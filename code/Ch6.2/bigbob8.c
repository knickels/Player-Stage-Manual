/* Simple C client example.
 * Based on simple.c from player distribution
 * K. Nickels 6/5/14
 */

#include <stdio.h>
#include <libplayerc/playerc.h>

int main(int argc, char *argv[]) {

  playerc_client_t *robot;
  playerc_position2d_t *p2dProxy;

  /* Create a client and connect it to the server. */
  robot = playerc_client_create(NULL, "localhost", 6665);
  if (0 != playerc_client_connect(robot)) return -1;

  /* Create and subscribe to a position2d device. */
  p2dProxy = playerc_position2d_create(robot, 0);
  if (playerc_position2d_subscribe(p2dProxy, PLAYER_OPEN_MODE)) return -1;

  /* read from the proxies */
  playerc_client_read(robot);

  /* for carlike robots ( XSpeed(m/s), steering_angle (radians) )
  //  playerc_position2d_set_cmd_car (P2dProxy, 0.2,dtor(30)); 
  // for holonomic robots (XSpeed (m/s), YSpeed (m/s), YawSpeed (rad/s), state)
  // *You* should check return values!!
  */
  /* playerc_position2d_set_speed(p2dProxy,0,0,0.1) ?? */
  playerc_position2d_set_cmd_vel(p2dProxy, 0, 0, DTOR(40.0), 1);

  for(int i=0;i<10;i++) {
        playerc_client_read(robot);
        printf("Iter %d\n",i);
        printf("XSpeed = %.2f m/s\t", robot->vx);
        printf("YSpeed = %.2f m/s\t", robot->vy);
        printf("YawSpeed = %.2f rad/s\n", robot->va);
        printf("XPos = %.2f m/s\t", robot->vx);
        printf("YPos = %.2f m/s\t", robot->vy);
        printf("Yaw = %.2f rad/s\n", robot->va);
    }

  /* Shutdown */
  playerc_position2d_unsubscribe(p2dproxy);
  playerc_position2d_destroy(p2dproxy);
  playerc_client_disconnect(robot);
  playerc_client_destroy(robot);

    return 0;
}

