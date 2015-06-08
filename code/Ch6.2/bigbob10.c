/* Simple C client example.
 * Based on simple.c from player distribution
 * K. Nickels 6/8/14
 */

#include <stdio.h>
#include <libplayerc/playerc.h>

int main(int argc, char *argv[]) {
  playerc_client_t *robot;
  playerc_blobfinder_t *blobfinderProxy;
  playerc_blobfinder_blob_t blob;

  /* Create a client and connect it to the server. */
  robot = playerc_client_create(NULL, "localhost", 6665);
  if (0 != playerc_client_connect(robot)) return -1;

  /* Create and subscribe to a blobfinder device. */
  blobfinderProxy = playerc_blobfinder_create(robot, 0);
  if (playerc_blobfinder_subscribe(blobfinderProxy, PLAYER_OPEN_MODE)) return -1;

  /* read from the proxies */
  playerc_client_read(robot);

  /* print out stuff for fun */
  printf("Blobfinder, width=%d, height=%d\n",
		  blobfinderProxy->width,
		  blobfinderProxy->height);
  printf("%d blobs found\n",
		  blobfinderProxy->blobs_count);

  for (int i=0;i<blobfinderProxy->blobs_count;i++) {
	  blob = blobfinderProxy->blobs[i];
	  printf("BLOB %d -----------\n", i);
	  printf("-id=%d\n",blob.id);
	  printf("-color=0x%06x\n",blob.color);
	  printf("-area=%d (pixels)\n",(int)blob.area);
	  printf("-range=%d (m)\n",(int)blob.range);
	  printf("-(x,y) = (%d,%d)\n",blob.x,blob.y);
	  printf("-box =   %3d\n",blob.top);
	  printf("-     %3d   %3d\n",blob.left,blob.right);
	  printf("-        %3d\n",blob.bottom);
  }

  /* Shutdown */
  playerc_blobfinder_unsubscribe(blobfinderProxy);
  playerc_blobfinder_destroy(blobfinderProxy);
  playerc_client_disconnect(robot);
  playerc_client_destroy(robot);

  return 0;
}

