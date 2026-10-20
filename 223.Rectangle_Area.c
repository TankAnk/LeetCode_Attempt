/*
Computes area of a single rectangle.
*/
int compute_rectangle_area(int bot_left_x, int bot_left_y, int top_right_x, int top_right_y)
{
  if (bot_left_x == top_right_x || bot_left_y == top_right_y)
    return 0;

  int width = top_right_x - bot_left_x;
  int height = top_right_y - bot_left_y;
  return width * height;
}

/*
- Computes the overlapped rectangle area formed by 2 rectangles.

- Checks:
  + [ax1, ax1] vs [bx1, bx2].
  + [ay1, ay2] vs [by1, by2].

- There will be NO overlapped rectangle when EITHER:
  - ax2 <= bx1 || bx2 <= ax1.
  - ay2 <= by1 || by2 <= ay1.

- Width of the overlapped reactangle is EITHER:
  + ax2 - ax1 when bx1 <= ax1 && ax2 <= bx2.
  + bx2 - bx1 when ax1 <= bx1 && bx2 <= ax2.
  + ax2 - bx1 when ax1 <= bx1 && ax2 <= bx2.
  + bx2 - ax1 when bx1 <= ax1 && bx2 <= ax2.

- Height of the overlapped reactangle is EITHER:
  + ay2 - ay1 when by1 <= ay1 && ay2 <= by2.
  + by2 - by1 when ay1 <= by1 && by2 <= ay2.
  + ay2 - by1 when ax1 <= by1 && ay2 <= by2.
  + by2 - ay1 when by1 <= ay1 && by2 <= ax1.
*/
int compute_overlapped_rectangle_area(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
  if (ax2 <= bx1 || bx2 <= ax1 || ay2 <= by1 || by2 <= ay1)
    return 0;

  int width, height;

  if (ax1 <= bx1)
    width = (ax2 <= bx2) ? ax2 - bx1 : bx2 - bx1;
  else
    width = (ax2 <= bx2) ? ax2 - ax1 : bx2 - ax1;

  if (ay1 <= by1)
    height = (ay2 <= by2) ? ay2 - by1 : by2 - by1;
  else
    height = (ay2 <= by2) ? ay2 - ay1 : by2 - ay1;

  return width * height;
}

int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
  return compute_rectangle_area(ax1, ay1, ax2, ay2) + compute_rectangle_area(bx1, by1, bx2, by2) - compute_overlapped_rectangle_area(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2);
}
