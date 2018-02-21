#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  c.red = 75;
  c.green = 0;
  c.blue = 130;


  printf("\nidentity matrix \n");
  struct matrix *a = new_matrix(3, 3);
  a->lastcol = 3;
  ident(a);
  print_matrix(a);

  printf("\nmultiplying matrix b with identity matrix\n");
  struct matrix *b = new_matrix(3, 3);
  b->lastcol = 2;
  b->m[0][0] = 12;
  b->m[1][0] = 15;
  b->m[2][0] = 18;
  b->m[0][1] = 21;
  b->m[1][1] = 24;
  b->m[2][1] = 27;
  printf("here is matrix b: \n");
  print_matrix(b);
  matrix_mult(a, b);
  printf("multiplied b with identity matrix: \n");
  print_matrix(b);

  printf("\nmultiplying matrix a with b\n");
  a->m[0][0] = 30;
  a->m[0][1] = 33;
  a->m[0][2] = 36;
  a->m[1][0] = 39;
  a->m[1][1] = 42;
  a->m[1][2] = 45;
  a->m[2][0] = 48;
  a->m[2][1] = 51;
  a->m[2][2] = 54;
  printf("\nhere is matrix a: \n");
  print_matrix(a);
  printf("\nhere is matrix b: \n");
  print_matrix(b);
  matrix_mult(a, b);
  printf("\nhere is product of a and b\n");
  print_matrix(b);
  free_matrix(a);
  free_matrix(b);

  struct matrix *edges;

  edges = new_matrix(4, 4);
  printf("\nnow lets make an image\n");
  //ignore z
  add_edge(edges, 0, 500, 0, 500, 0, 0);
  add_edge(edges, 500, 500, 0, 0, 0, 0);
  add_edge(edges, 250, 400, 0, 300, 350, 0);
  add_edge(edges, 250, 400, 0, 200, 350, 0);
  add_edge(edges, 200, 350, 0, 300, 350, 0);
  add_edge(edges, 150, 300, 0, 100, 275, 0);
  add_edge(edges, 100, 275, 0, 150, 250, 0);
  add_edge(edges, 150, 300, 0, 150, 250, 0);




  draw_lines(edges, s, c);
  display(s);
  free_matrix( edges );
  save_extension(s, "matrix.png");
}
