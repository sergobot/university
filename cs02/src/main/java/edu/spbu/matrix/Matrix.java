package edu.spbu.matrix;

/**
 * Matrix is a mathematical model usually represented by a 2D array of
 * floating point numbers with some operations defined. This interface requires
 * a minimal set of these operations.
 */
public interface Matrix
{
  /**
   * однопоточное умнджение матриц
   * должно поддерживаться для всех 4-х вариантов
   * @param o - another matrix to multiply by (this * o)
   * @return resulting matrix of the multiplication
   */
  Matrix mul(Matrix o);

  /**
   * многопоточное умножение матриц
   * @param o - another matrix to multiply by (this * o)
   * @return resulting matrix of the multiplication
   */
  Matrix dmul(Matrix o);

  /**
   * Transpose the matrix and return a copy
   * @return a copy of M^T
   */
  Matrix transpose();

  /**
   * Extract a submatrix contained within this square, including the edges:
   * (x1, y1) ----------- (x1, y2 - 1)
   * |                        |
   * |                        |
   * |                        |
   * (x2 - 1, y1) ------- (x2 - 1, y2 - 1)
   *
   * @param x1 - first coordinate of the first row
   * @param x2 - first coordinate of the row next to the last one
   * @param y1 - second coordinate of the first column
   * @param y2 - second coordinate of the column next to the last one
   * @return Matrix of the same type and size of (x2 - x1, y2 - y1)
   */
  Matrix submatrix(int x1, int x2, int y1, int y2);

  /**
   * Returns an element at specific position
   * @param i - vertical coordinate of the element
   * @param j - horizontal coordinate of the element
   * @return the element at (i, j)
   */
  double get(int i, int j);

  /**
   * Returns height of a matrix
   * @return height
   */
  int getHeight();

  /**
   * Returns width of a matrix
   * @return width
   */
  int getWidth();
}
