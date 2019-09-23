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
