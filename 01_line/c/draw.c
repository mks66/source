#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"


/* This is the single loop optimized version */
/* userful for dealing with z buffering and lighting */
/* do not show this at the beginning */
/* void draw_line(int x0, int y0, int x1, int y1, screen s, color c) { */
  
/*   int x, y, d, A, B; */
/*   int dy_east, dy_northeast, dx_east, dx_northeast, d_east, d_northeast; */
/*   int loop_start, loop_end; */
/*   double distance; */

/*   printf("(%d, %d) -> (%d, %d)\n", x0, y0, x1, y1); */
  
/*   //swap points if going right -> left */
/*   int xt, yt; */
/*   if (x0 > x1) { */
/*     xt = x0; */
/*     yt = y0; */
/*     x0 = x1; */
/*     y0 = y1; */
/*     x1 = xt; */
/*     y1 = yt; */
/*   } */
  
/*   x = x0; */
/*   y = y0; */
/*   A = 2 * (y1 - y0); */
/*   B = -2 * (x1 - x0); */
/*   int wide = 0; */
/*   int tall = 0; */
/*   //octants 1 and 8 */
/*   if ( abs(x1 - x0) >= abs(y1 - y0) ) { //octant 1/8 */
/*     wide = 1; */
/*     loop_start = x; */
/*     loop_end = x1; */
/*     dx_east = dx_northeast = 1; */
/*     dy_east = 0; */
/*     d_east = A; */
/*     distance = x1 - x; */
/*     if ( A > 0 ) { //octant 1 */
/*       d = A + B/2; */
/*       dy_northeast = 1; */
/*       d_northeast = A + B; */
/*     } */
/*     else { //octant 8 */
/*       d = A - B/2; */
/*       dy_northeast = -1; */
/*       d_northeast = A - B; */
/*     } */
/*   }//end octant 1/8 */
/*   else { //octant 2/7 */
/*     tall = 1; */
/*     dx_east = 0; */
/*     dx_northeast = 1; */
/*     distance = abs(y1 - y); */
/*     if ( A > 0 ) {     //octant 2 */
/*       d = A/2 + B; */
/*       dy_east = dy_northeast = 1; */
/*       d_northeast = A + B; */
/*       d_east = B; */
/*       loop_start = y; */
/*       loop_end = y1; */
/*     } */
/*     else {     //octant 7 */
/*       d = A/2 - B; */
/*       dy_east = dy_northeast = -1; */
/*       d_northeast = A - B; */
/*       d_east = -1 * B; */
/*       loop_start = y1; */
/*       loop_end = y; */
/*     } */
/*   } */

/*   while ( loop_start < loop_end ) { */

/*     printf("tall: %d A: %d\t(%d, %d)\t%d\n", tall, A, x, y, d); */
/*     plot( s, c, x, y ); */
/*     if ( (wide && ((A > 0 && d > 0) || */
/* 		   (A < 0 && d < 0))) */
/* 	 || */
/* 	 (tall && ((A > 0 && d < 0 ) || */
/* 		   (A < 0 && d > 0) ))) { */
/*       y+= dy_northeast; */
/*       d+= d_northeast; */
/*       x+= dx_northeast; */
/*     } */
/*     else { */
/*       x+= dx_east; */
/*       y+= dy_east; */
/*       d+= d_east; */
/*     } */
/*     loop_start++; */
/*   } //end drawing loop */
/*   plot( s, c, x1, y1 ); */
/* } //end draw_line */

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  
  int x, y, d, A, B;
  //swap points if going right -> left
  int xt, yt;
  if (x0 > x1) {
    xt = x0;
    yt = y0;
    x0 = x1;
    y0 = y1;
    x1 = xt;
    y1 = yt;
  }
  
  x = x0;
  y = y0;
  A = 2 * (y1 - y0);
  B = -2 * (x1 - x0);

  //octants 1 and 8
  if ( abs(x1 - x0) >= abs(y1 - y0) ) {

    //octant 1
    if ( A > 0 ) {
      
      d = A + B/2;
      while ( x < x1 ) {
	plot( s, c, x, y );
	if ( d > 0 ) {
	  y+= 1;
	  d+= B;
	}
	x++;
	d+= A;
      } //end octant 1 while
      plot( s, c, x1, y1 );
    } //end octant 1

    //octant 8
    else {
      d = A - B/2;
      
      while ( x < x1 ) {
	//printf("(%d, %d)\n", x, y);
	plot( s, c, x, y );
	if ( d < 0 ) {
	  y-= 1;
	  d-= B;
	}
	x++;
	d+= A;
      } //end octant 8 while
      plot( s, c, x1, y1 );
    } //end octant 8
  }//end octants 1 and 8

  //octants 2 and 7
  else {
    
    //octant 2
    if ( A > 0 ) {
      d = A/2 + B;

      while ( y < y1 ) {
	plot( s, c, x, y );
	if ( d < 0 ) {
	  x+= 1;
	  d+= A;
	}
	y++;
	d+= B;
      } //end octant 2 while
      plot( s, c, x1, y1 );
    } //end octant 2

    //octant 7
    else {
      d = A/2 - B;
      
      while ( y > y1 ) {
	plot( s, c, x, y );
	if ( d > 0 ) {
	  x+= 1;
	  d+= A;
	}
	y--;
	d-= B;
      } //end octant 7 while
      plot( s, c, x1, y1 );
    } //end octant 7
  }//end octants 2 and 7
} //end draw_line

