/*
TODO - get this demo to work
TODO - play with store/retrieve
*/
 
/* Example 'bigbob11.c' - show use of gripper
 * K. Nickels 6/8/14
 */

#include <stdio.h>
#include <unistd.h>
#include <libplayerc/playerc.h>

const char *gripper_state(int s) {
    switch(s) {
        case PLAYER_GRIPPER_STATE_OPEN: return "open"; break;
        case PLAYER_GRIPPER_STATE_CLOSED: return "closed"; break;
		case PLAYER_GRIPPER_STATE_MOVING: return "moving"; break;
        case PLAYER_GRIPPER_STATE_ERROR: return "error"; break;
        default: return "unknown"; break;
    }
}

int main(int argc, char *argv[]) {
  playerc_client_t *robot;
  playerc_gripper_t *gp;
  playerc_position2d_t *pp;

  /* Create a client and connect it to the server. */
  robot = playerc_client_create(NULL, "localhost", 6665);
  if (0 != playerc_client_connect(robot)) return -1;

  /* Create and subscribe to a blobfinder device. */
  gp = playerc_gripper_create(robot, 0);
  if (playerc_gripper_subscribe(gp, PLAYER_OPEN_MODE)) return -1;

  pp = playerc_position2d_create(robot, 0);
  if (playerc_position2d_subscribe(pp, PLAYER_OPEN_MODE)) return -1;

  /* read from the proxies */
  playerc_gripper_get_geom(gp);
  playerc_client_read(robot);
  playerc_gripper_printout(gp,"state of gripper");
  printf("Capacity of gripper: %d items\n",gp->capacity);

  /* go forward */
  playerc_position2d_set_cmd_vel(pp, 0.1, 0.0, 0, 1);

  /* approach orange - keep going till it's in the breakbeam */
  while (gp->beams==0) {
  		playerc_client_read(robot);
		printf("Gripper is %s\n", gripper_state(gp->state));
  }

  /* stop and close gripper */
  playerc_position2d_set_cmd_vel(pp, 0.0, 0.0, 0, 1);
  playerc_gripper_close_cmd(gp);
  while (gp->state != PLAYER_GRIPPER_STATE_CLOSED) {
  		playerc_client_read(robot);
		printf("Gripper is %s\n", gripper_state(gp->state));
  }
  /* Note - in stage there is a strange bug drawing the paddles on closing
   * the first time.
   */

  /* drive around with your box for a while */
  playerc_position2d_set_cmd_vel(pp, -0.1, 0.0, DTOR(30), 1);
  sleep(2);

  /* Now drop the box and speed up */
  playerc_position2d_set_cmd_vel(pp, -0.5, 0.0, 0, 1);
  playerc_gripper_open_cmd(gp);
  sleep(2);

  /* Shutdown */
  playerc_gripper_unsubscribe(gp);
  playerc_position2d_unsubscribe(pp);
  playerc_gripper_destroy(gp);
  playerc_position2d_destroy(pp);
  playerc_client_disconnect(robot);
  playerc_client_destroy(robot);

  return 0;
}

