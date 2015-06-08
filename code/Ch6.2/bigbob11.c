TODO - get this demo to work
TODO - play with store/retrieve
 


/* Simple C client example.
 * Based on simple.c from player distribution
 * K. Nickels 6/8/14
 */

#include <stdio.h>
#include <libplayerc/playerc.h>

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

  /* go forward */
  playerc_position2d_set_cmd_vel(pp, 0.1, 0.0, 0, 1);

  /* keep going till you see something */
  while (gp->beams==0) {
  		playerc_client_read(robot);
		playerc_gripper_printout(gp,"approach");
  }

  /* stop and close gripper */
  playerc_position2d_set_cmd_vel(pp, 0.0, 0.0, 0, 1);
  playerc_gripper_close_cmd(gp);
  while (gp->state != PLAYER_GRIPPER_STATE_CLOSED) {
  		playerc_client_read(robot);
		playerc_gripper_printout(gp,"grabbing");
  }

  /* back off, and give some time to move */
  playerc_position2d_set_cmd_vel(pp, -0.1, 0.0, 0, 1);
  for (int i=1;i<20;i++) {
  		playerc_client_read(robot);
		playerc_gripper_printout(gp,"dragging away");
  }

  /* Shutdown */
  playerc_gripper_unsubscribe(gp);
  playerc_position2d_unsubscribe(pp);
  playerc_gripper_destroy(gp);
  playerc_position2d_destroy(pp);
  playerc_client_disconnect(robot);
  playerc_client_destroy(robot);

  return 0;
}

