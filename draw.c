#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z
Returns:
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
	if (points->lastcol == points-> cols){
		grow_matrix(points, points->cols+1); }

	points->m[0][points->lastcol] = x;
	points->m[1][points->lastcol] = y;
	points->m[2][points->lastcol] = z;
	points->m[3][points->lastcol] = 1;
	points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns:
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points,
	       double x0, double y0, double z0,
	       double x1, double y1, double z1) {
					 add_point(points, x0, y0, z0);
					 add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c
Returns:
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
	int cols = 0, x = 0, y = 0, x1 = 0, y1 = 0;
	while (cols < points->lastcol){
		x = points->m[0][cols];
		y = points->m[1][cols];
		cols++;

		x1 = points->m[0][cols];
		y1 = points->m[1][cols];
		draw_line(x, y, x1, y1, s, c);
		cols++;
	}
}

//assume line with defined slope
double slope(int x, int y, int x1, int y1){
  return ((double) y1 - y) / ((double) x1 - x); }

//assume that x0 < x1 (subsequent pixel is to right)
//return 1, 2, 7, 8 for octants
int octant(int x, int y, int x1, int y1){
  //note that we only need octs 1, 2, 7, 8
  //5 is 1, 6 is 2, 4 is 8, 3 is 7

  //undefined slope - vertical line
  if (x == x1){
    //octants 2 are closer to y axis
    return 2; }

  double line_slope = slope(x, y, x1, y1);

  //octant 1
  if (line_slope >= 0 && line_slope < 1){
    return 1; }

  //octant 2
  else if (line_slope >= 1){
    return 2; }

  //octant 7
  else if (line_slope < -1){
    return 7;
  }

  //octant 8
  else if (line_slope >= -1){
    return 8; }

  return 0; //error, debug code
}

//copied from old hw
//Insert your line algorithm here
//assume that we work from left to right (x0 < x1)
//we only need octants I, II, VII, VIII
void draw_line(int x, int y, int x1, int y1, screen s, color c) {

  if (x1 < x){
    int temp = x;
    x = x1;
    x1 = temp;
    temp = y;
    y = y1;
    y1 = temp; }

  int line_octant = octant(x, y, x1, y1);
  //use pseudo code from class
  int d; ///2A + B, varies based on octant
  int A = y1 - y, B = -(x1 - x); //A = delta y, B = negative delta x, constant for all octants

  //straight from class
  if (line_octant == 1){
    d = (2 * A) + B;

    while (x <= x1){
      plot(s, c, x, y);

      if (d > 0){
        y++;
        d += (2 * B); }

      x++;
      d += (2 * A);
    }
  }

  //also again, straight from class
  else if (line_octant == 2){
    d = A + (2 * B);

    while (y <= y1){
      plot(s, c, x, y);

      if (d < 0){
        x++;
        d += (2 * A); }

      y++;
      d += (2 * B);
    }
  }

  else if (line_octant == 7) {
    d = A - (2 * B);

    while (y >= y1) {
      plot(s, c, x, y);

      if (d > 0){
	       x++;
	       d += (2 * A); }

      y--;
      d -= (2 * B);
    }
  }

  else if (line_octant ==8 ) {
    d = (2 * A) - B;

    while (x <= x1){
      plot(s, c, x, y);

      if (d < 0){
	       y--;
	       d -= (2 * B); }

      x++;
      d += (2 * A);
    }
  }

}
