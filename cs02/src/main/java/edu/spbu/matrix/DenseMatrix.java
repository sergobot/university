package edu.spbu.matrix;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

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
    ArrayList<Double> temp = new ArrayList<Double>();
    try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
      String line;

      while ((line = br.readLine()) != null) {
        List<Double> matrixRow = Arrays.stream(line.split("\\s+")).mapToDouble(Double::parseDouble).boxed().collect(Collectors.toList());

        if (this.width == 0) {
          this.width = matrixRow.size();
        }
        if (matrixRow.size() != this.width) {
          throw new RuntimeException("Unable to load matrix from " + fileName + ": rows have different length!");
        }

        temp.addAll(matrixRow);

        ++this.height;
      }

      this.array = new double[this.height * this.width];
      for (int i = 0; i < this.height * this.width; ++i) {
        this.array[i] = temp.get(i);
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
      int newHeight = this.getHeight(), newWidth = o.getWidth();
      DenseMatrix out = new DenseMatrix(newHeight, newWidth);

      out.array = new double[newHeight * newWidth];
      int pos = 0;
      for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {
          for (int k = 0; k < this.width; ++k) {
            out.array[pos + j] += this.get(i, k) * o.get(k, j);
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
