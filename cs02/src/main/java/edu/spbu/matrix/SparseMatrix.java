package edu.spbu.matrix;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;

/**
 * Разряженная матрица
 */
public class SparseMatrix implements Matrix
{
  private int height, width;
  int[] rows, cols;
  double[] values;
  private int hashCode;

  SparseMatrix(int height, int width, int[] rows, int[] cols, double[] values) {
    this.height = height;
    this.width = width;
    this.rows = rows;
    this.cols = cols;
    this.values = values;

    this.hashCode = Arrays.hashCode(this.rows) + Arrays.hashCode(this.cols) + Arrays.hashCode(this.values);
  }

  /**
   * загружает матрицу из файла
   * @param fileName - path to the text file with matrix
   */
  public SparseMatrix(String fileName) {
    this.width = 0;
    this.height = 0;

    LinkedList<Integer> rows = new LinkedList<>();
    LinkedList<Integer> cols = new LinkedList<>();
    LinkedList<Double> values = new LinkedList<>();

    try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
      String line;
      Iterator<Double> rowIterator;
      while ((line = br.readLine()) != null) {
        rowIterator = Arrays.stream(line.split("\\s+"))
            .mapToDouble(Double::parseDouble).iterator();

        int i = 0;
        double v;
        while (rowIterator.hasNext()) {
          v = rowIterator.next();
          if (v != 0.) {
            rows.add(height);
            cols.add(i);
            values.add(v);
          }
          ++i;
        }

        if (i != this.width) {
          if (this.width == 0) {
            this.width = i;
          } else {
            throw new RuntimeException("Unable to load matrix from " + fileName + ": rows have different length!");
          }
        }

        ++this.height;
      }

      // Convert COO to CSR for faster operations
      this.rows = new int[this.height + 1];

      for (Integer row : rows) {
        ++this.rows[row];
      }

      for (int i = 0, sum = 0, temp; i <= this.height; ++i) {
        temp = this.rows[i];
        this.rows[i] = sum;
        sum += temp;
      }

      this.cols = new int[this.rows[this.height]];
      this.values = new double[this.rows[this.height]];

      Iterator<Integer> rowsIterator = rows.iterator();
      Iterator<Integer> colsIterator = cols.iterator();
      Iterator<Double> valuesIterator = values.iterator();
      while (rowsIterator.hasNext() && colsIterator.hasNext() && valuesIterator.hasNext()) {
        int row = rowsIterator.next();
        int dest = this.rows[row];

        this.cols[dest] = colsIterator.next();
        this.values[dest] = valuesIterator.next();

        ++this.rows[row];
      }

      for (int i = 0, last = 0; i <= this.height; i++) {
        int temp = this.rows[i];
        this.rows[i] = last;
        last = temp;
      }

      this.hashCode = Arrays.hashCode(this.rows) + Arrays.hashCode(this.cols) + Arrays.hashCode(this.values);
      // Now the matrix is in the CSR format
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
  @Override public Matrix mul(Matrix o)
  {
    return MatrixMultiplier.mul(this, o);
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
   /*
   * @param o - an object to compare against
   * @return true if equals
   */
  @Override public boolean equals(Object o) {
    if (o == this) {
      return true;
    }

    if (o instanceof SparseMatrix) {
      SparseMatrix sm = (SparseMatrix) o;

      if (this.hashCode != sm.hashCode) {
        return false;
      }

      if (this.width != sm.width || this.height != sm.height ||
          this.values.length != sm.values.length) {
        return false;
      }

      for (int i = 0; i < this.height; ++i) {
        if (this.rows[i] != sm.rows[i]) {
          return false;
        }
      }

      for (int i = 0; i < this.values.length; ++i) {
        if (this.values[i] != sm.values[i] || this.cols[i] != sm.cols[i]) {
          return false;
        }
      }

      return true;
    }

    if (o instanceof DenseMatrix) {
      DenseMatrix dm = (DenseMatrix) o;
      if (this.width != dm.getWidth() || this.height != dm.getHeight()) {
        return false;
      }

      for (int i = 0; i < this.height; ++i) {
        for (int j = 0; j < this.width; ++j) {
          if (this.get(i, j) != dm.get(i, j)) {
            return false;
          }
        }
      }

      return true;
    }

    return false;
  }

  @Override
  public double get(int i, int j) {
    if (this.rows[i + 1] - this.rows[i] == 0) {
      return 0;
    }

    for (int k = rows[i]; k < rows[i + 1]; ++k) {
      if (this.cols[k] == j) {
        return this.values[k];
      }
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

  @Override
  public int hashCode() {
    return this.hashCode;
  }

  public SparseMatrix transpose() {
    final int nnz = this.rows[this.height];

    int[] newRows = new int[this.width + 1];
    int[] newCols = new int[nnz];
    double[] newValues = new double[nnz];

    for (int i = 0; i < nnz; ++i){
      ++newRows[this.cols[i]];
    }

    for(int col = 0, sum = 0; col <= this.width; ++col){
      int temp  = newRows[col];
      newRows[col] = sum;
      sum += temp;
    }

    for(int row = 0; row < this.height; ++row){
      for(int jj = this.rows[row]; jj < this.rows[row + 1]; ++jj){
        int col  = this.cols[jj];
        int dest = newRows[col];

        newCols[dest] = row;
        newValues[dest] = this.values[jj];

        ++newRows[col];
      }
    }

    for(int col = 0, last = 0; col <= this.width; col++){
      int temp  = newRows[col];
      newRows[col] = last;
      last    = temp;
    }

    return new SparseMatrix(this.width, this.height, newRows, newCols, newValues);
  }

  public String toString() {
    StringBuilder str = new StringBuilder();

    for (int i = 0; i < this.height; ++i) {
      for (int j = 0; j < this.width; ++j) {
        str.append(this.get(i, j)).append(" ");
      }
      str.append("\n");
    }
    return str.toString();
  }

}
