package edu.spbu.matrix;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

/**
 * Плотная матрица
 */
public class DenseMatrix implements Matrix {
  private int height, width;
  private double[] array;

  private DenseMatrix(int height, int width) {
    this.height = height;
    this.width = width;
    this.array = null;
  }

  /**
   * загружает матрицу из файла
   *
   * @param fileName - path to the text file with matrix
   */
  public DenseMatrix(String fileName) throws RuntimeException {
    this.width = 0;
    this.height = 0;
    ArrayList<double[]> temp = new ArrayList<>();
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

      this.array = new double[this.height * this.width];
      for (int i = 0; i < this.height; ++i) {
        System.arraycopy(temp.get(i), 0, this.array, this.width * i, this.height);
      }
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
    if (o instanceof DenseMatrix && this.getWidth() == o.getHeight()) {
      DenseMatrix dm = (DenseMatrix) o;
      int newHeight = this.height, newWidth = dm.width;
      DenseMatrix out = new DenseMatrix(newHeight, newWidth);

      out.array = new double[newHeight * newWidth];
      int pos = 0;
      for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {
          for (int k = 0; k < this.width; ++k) {
            out.array[pos + j] += this.array[pos + k] * dm.array[k * dm.width + j];
          }
        }
        pos += newWidth;
      }
      return out;
    }
    return null;
  }

  /**
   * многопоточное умножение матриц
   *
   * @param o - another matrix to multiply by
   * @return resulting matrix of the multiplication
   */
  @Override
  public Matrix dmul(Matrix o) {
    return null;
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
      if (this.getHeight() != dm.getHeight() || this.getWidth() != dm.getWidth()) {
        return false;
      }

      for (int i = 0; i < this.getHeight() * this.getWidth(); ++i) {
        if (this.array[i] != dm.array[i]) {
          return false;
        }
      }
      return true;
    }

    if (o instanceof SparseMatrix) {
      return false;
    }

    return false;
  }

  @Override
  public double get(int i, int j) {
    if (i < this.getHeight() && j < this.getWidth()) {
      return this.array[this.width * i + j];
    }
    return 0;
  }

  @Override
  public int getHeight() {
    return this.height;
  }

  @Override
  public int getWidth() {
    return this.width;
  }
}
