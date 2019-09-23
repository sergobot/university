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
  private Integer height, width;
  private List<List<Double>> matrix;

  private DenseMatrix(Integer height, Integer width) {
    this.height = height;
    this.width = width;
    this.matrix = null;
  }

  /**
   * загружает матрицу из файла
   *
   * @param fileName - path to the text file with matrix
   */
  public DenseMatrix(String fileName) throws RuntimeException {
    this.width = 0;
    this.height = 0;
    this.matrix = new ArrayList<List<Double>>();
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

        matrix.add(matrixRow);
        ++height;
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
    if (o instanceof DenseMatrix && this.getWidth().equals(o.getHeight())) {
      int newHeight = this.getHeight(), newWidth = o.getWidth();
      DenseMatrix out = new DenseMatrix(newHeight, newWidth);

      out.matrix = new ArrayList<List<Double>>(newHeight);
      for (int i = 0; i < newHeight; ++i) {
        if (i % (newHeight / 50) == 0) {
          System.out.println("Milestone: " + i + " rows completed");
        }
        ArrayList<Double> matrixRow = new ArrayList<Double>(newWidth);
        for (int j = 0; j < newWidth; ++j) {
          double matrixElement = 0.;
          for (int k = 0; k < this.getWidth(); ++k) {
            matrixElement += this.get(i, k) * o.get(k, j);
          }
          matrixRow.add(matrixElement);
        }
        out.matrix.add(matrixRow);
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
      if (!this.getHeight().equals(dm.getHeight()) || !this.getWidth().equals(dm.getWidth())) {
        return false;
      }
      for (int i = 0; i < this.matrix.size(); ++i)
      {
        if (!this.matrix.get(i).equals(dm.matrix.get(i))) {
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
  public Double get(Integer i, Integer j) {
    if (i < this.getHeight() && j < this.getWidth()) {
      return this.matrix.get(i).get(j);
    }
    return null;
  }

  @Override
  public Integer getHeight() {
    return this.height;
  }

  @Override
  public Integer getWidth() {
    return this.width;
  }
}
