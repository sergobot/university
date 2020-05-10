package edu.spbu.matrix;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.LinkedList;

/**
 * Плотная матрица
 */
public class DenseMatrix implements Matrix {
  private int height, width;
  double[][] array;
  private int hashCode;

  DenseMatrix(int height, int width, double[][] array) {
    this.height = height;
    this.width = width;
    this.array = array;

    this.hashCode = Arrays.deepHashCode(this.array);
  }

  /**
   * загружает матрицу из файла
   *
   * @param fileName - path to the text file with matrix
   */
  public DenseMatrix(String fileName) throws RuntimeException {
    this.width = 0;
    this.height = 0;
    LinkedList<double[]> temp = new LinkedList<>();
    try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
      String line = br.readLine();
      double[] matrixRow = Arrays.stream(line.split("\\s+"))
          .mapToDouble(Double::parseDouble).toArray();
      this.width = matrixRow.length;
      this.height = 1;
      temp.add(matrixRow);

      while ((line = br.readLine()) != null) {
        matrixRow = Arrays.stream(line.split("\\s+"))
            .mapToDouble(Double::parseDouble).toArray();

        if (matrixRow.length != this.width) {
          throw new RuntimeException("Unable to load matrix from " + fileName + ": rows have different length!");
        }

        temp.add(matrixRow);
        ++this.height;
      }

      this.array = new double[this.height][];
      for (int i = 0; i < this.height; ++i) {
        array[i] = temp.get(i);
      }
      this.hashCode = Arrays.deepHashCode(this.array);
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  /**
   * однопоточное умнджение матриц
   * должно поддерживаться для всех 4-х вариантов
   *
   * @param o - another matrix to multiply by
   * @return resulting matrix of the multiplication
   */
  @Override
  public Matrix mul(Matrix o) {
    return MatrixMultiplier.mul(this, o);
  }

  /**
   * многопоточное умножение матриц
   *
   * @param o - another matrix to multiply by
   * @return resulting matrix of the multiplication
   */
  @Override
  public Matrix dmul(Matrix o) {
    return MatrixMultiplier.dmul(this, o);
  }

  /**
   * спавнивает с обоими вариантами
   *
   * @param o - an object to compare against
   * @return true if equals
   */
  @Override
  public boolean equals(Object o) {
    if (o == this) {
      return true;
    }

    if (o instanceof DenseMatrix) {
      DenseMatrix dm = (DenseMatrix) o;

      if (this.hashCode != dm.hashCode) {
        return false;
      }

      for (int i = 0; i < this.getHeight(); ++i) {
        for (int j = 0; j < this.getWidth(); ++j) {
          if (this.array[i][j] != dm.array[i][j]) {
            return false;
          }
        }
      }
      return true;
    }

    if (o instanceof SparseMatrix) {
      SparseMatrix sm = (SparseMatrix) o;
      if (this.width != sm.getWidth() || this.height != sm.getHeight()) {
        return false;
      }

      for (int i = 0; i < this.height; ++i) {
        for (int j = 0; j < this.width; ++j) {
          if (this.array[i][j] != sm.get(i, j)) {
            return false;
          }
        }
      }

      return true;
    }

    return false;
  }

  public DenseMatrix submatrix(int x1, int x2, int y1, int y2) {
    double[][] out = new double[x2 - x1][];

    for (int i = 0; i < x2 - x1; ++i) {
      out[i] = Arrays.copyOfRange(this.array[i + x1], y1, y2);
    }

    return new DenseMatrix(x2 - x1, y2 - y1, out);
  }

  @Override
  public double get(int i, int j) {
    return this.array[i][j];
  }

  @Override
  public int getHeight() {
    return this.height;
  }

  @Override
  public int getWidth() {
    return this.width;
  }

  public DenseMatrix transpose() {
    double[][] out = new double[this.width][this.height];
    for (int i = 0; i < this.height; ++i) {
      for (int j = 0; j < this.width; ++j) {
        out[j][i] = this.array[i][j];
      }
    }
    //noinspection SuspiciousNameCombination
    return new DenseMatrix(this.width, this.height, out);
  }
}
