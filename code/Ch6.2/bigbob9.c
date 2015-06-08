/* Simple C client example.
 * Based on simple.c from player distribution
 * K. Nickels 6/5/14
 */

#include <stdio.h>
#include <libplayerc/playerc.h>

int main(int argc, char *argv[]) {
  playerc_client_t *robot;
  playerc_ranger_t *sonarProxy;
  //playerc_ranger_t *toothProxy;
  //playerc_ranger_t *laserProxy;
  

  /* Create a client and connect it to the server. */
  robot = playerc_client_create(NULL, "localhost", 6665);
  if (0 != playerc_client_connect(robot)) return -1;

  /* Create and subscribe to a ranger device. */
  sonarProxy = playerc_ranger_create(robot, 0);
  if (playerc_ranger_subscribe(sonarProxy, PLAYER_OPEN_MODE)) return -1;

  /* read from the proxies */
  playerc_client_read(robot);
  playerc_ranger_get_geom()

  printf(" sonar ranges: ");
  for(int i=0;i<sonarProxy->ranges_count;i++) {
        printf("%.3f ", sonarProxy->ranges[i]);
    }

  /* Shutdown */
  playerc_position2d_unsubscribe(sonarProxy);
  playerc_position2d_destroy(sonarProxy);
  playerc_client_disconnect(robot);
  playerc_client_destroy(robot);

  return 0;
}

