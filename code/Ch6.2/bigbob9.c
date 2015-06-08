/* Simple C client example.
 * Based on simple.c from player distribution
 * K. Nickels 6/5/14
 */

#include <stdio.h>
#include <libplayerc/playerc.h>

int main(int argc, char *argv[]) {
  playerc_client_t *robot;
  playerc_ranger_t *sonarProxy;
  playerc_ranger_t *toothProxy;
  playerc_ranger_t *laserProxy;
  

  /* Create a client and connect it to the server. */
  robot = playerc_client_create(NULL, "localhost", 6665);
  if (0 != playerc_client_connect(robot)) return -1;

  /* Create and subscribe to a ranger device. */
  sonarProxy = playerc_ranger_create(robot, 0);
  if (playerc_ranger_subscribe(sonarProxy, PLAYER_OPEN_MODE)) return -1;
  toothProxy = playerc_ranger_create(robot, 1);
  if (playerc_ranger_subscribe(toothProxy, PLAYER_OPEN_MODE)) return -1;
  laserProxy = playerc_ranger_create(robot, 2);
  if (playerc_ranger_subscribe(laserProxy, PLAYER_OPEN_MODE)) return -1;

  /* read from the proxies */
  playerc_ranger_get_geom(sonarProxy);
  playerc_ranger_get_geom(toothProxy);
  playerc_ranger_get_geom(laserProxy);
  playerc_client_read(robot);

  printf("%d sonar ranges: ",sonarProxy->ranges_count);
  for(int i=0;i<sonarProxy->ranges_count-1;i++) 
        printf("%.3f, ", sonarProxy->ranges[i]);
  printf("%.3f\n",sonarProxy->ranges[sonarProxy->ranges_count-1]);

  printf("%d tooth laser ranges: ",toothProxy->ranges_count);
  for(int i=0;i<toothProxy->ranges_count-1;i++) 
        printf("%.3f, ", toothProxy->ranges[i]);
  printf("%.3f\n",toothProxy->ranges[toothProxy->ranges_count-1]);

  printf("%d laser ranges: ",laserProxy->ranges_count);
  for(int i=0;i<laserProxy->ranges_count-1;i++) 
        printf("%.3f, ", laserProxy->ranges[i]);
  printf("%.3f\n",laserProxy->ranges[laserProxy->ranges_count-1]);

  /* Shutdown */
  playerc_ranger_unsubscribe(sonarProxy);
  playerc_ranger_unsubscribe(toothProxy);
  playerc_ranger_unsubscribe(laserProxy);
  playerc_ranger_destroy(sonarProxy);
  playerc_ranger_destroy(toothProxy);
  playerc_ranger_destroy(laserProxy);
  playerc_client_disconnect(robot);
  playerc_client_destroy(robot);

  return 0;
}

