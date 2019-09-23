package edu.spbu.matrix;

/**
 * Разряженная матрица
 */
public class SparseMatrix implements Matrix
{
  /**
   * загружает матрицу из файла
   * @param fileName - path to the text file with matrix
   */
  public SparseMatrix(String fileName) {

  }
  /**
   * однопоточное умнджение матриц
   * должно поддерживаться для всех 4-х вариантов
   *
   * @param o - another matrix to multiply by
   * @return resulting matrix of the multiplication
   */
  @Override public Matrix mul(Matrix o)
  {
    return null;
  }

  /**
   * многопоточное умножение матриц
   *
   * @param o - another matrix to multiply by
   * @return resulting matrix of the multiplication
   */
  @Override public Matrix dmul(Matrix o)
  {
    return null;
  }

  /**
   * спавнивает с обоими вариантами
   *
   * @param o - an object to compare against
   * @return true if equals
   */
  @Override public boolean equals(Object o) {
    return false;
  }

  @Override
  public double get(int i, int j) {
    return 0;
  }

  @Override
  public int getHeight() {
    return 0;
  }

  @Override
  public int getWidth() {
    return 0;
  }

}
