package edu.spbu.matrix;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * Разряженная матрица
 */
public class SparseMatrix implements Matrix
{
  private int height, width;
  private int[] rows, cols;
  private double[] values;
  private int hashCode;


  private SparseMatrix(int height, int width, int[] rows, int[] cols, double[] values) {
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
    if (o instanceof SparseMatrix && this.getWidth() == o.getHeight()) {
      return mul((SparseMatrix) o);
    } else if (o instanceof DenseMatrix && this.getWidth() == o.getHeight()) {
      DenseMatrix dm = (DenseMatrix) o;
      int newHeight = this.height, newWidth = dm.getWidth();

      double[][] out = new double[newHeight][newWidth];
      for (int k = 0; k < this.height; ++k) {
        for (int i = 0; i < this.height; ++i) {
          double sum = out[i][k];
          for (int jj = this.rows[i]; jj < this.rows[i + 1]; ++jj) {
            sum += this.values[jj] * dm.get(this.cols[jj], k);
          }
          out[i][k] = sum;
        }
      }

      return new DenseMatrix(newHeight, newWidth, out);
    }
    return null;
  }

  private SparseMatrix mul(SparseMatrix sm) {
    // Part 1: compute CSR row pointer (new_rows)
    int[] newRows = new int[this.height + 1];
    newRows[0] = 0;

    int[] mask = new int[this.width];
    Arrays.fill(mask, -1);

    int newNnzCount = 0;
    for (int i = 0; i < this.height; i++) {
      int rowNnz = 0;

      for (int jj = this.rows[i]; jj < this.rows[i + 1]; ++jj) {
        int j = this.cols[jj];
        for (int kk = sm.rows[j]; kk < sm.rows[j + 1]; kk++) {
          int k = sm.cols[kk];
          if (mask[k] != i) {
            mask[k] = i;
            rowNnz++;
          }
        }
      }

      newNnzCount = newNnzCount + rowNnz;
      newRows[i + 1] = newNnzCount;
    }

    // Part 2: computing column indices and array of nonzero elements
    int[] newCols = new int[newNnzCount];
    double[] newValues = new double[newNnzCount];
    int[] next = new int[this.width];
    int[] sums = new int[this.width];
    Arrays.fill(next, -1);
    Arrays.fill(sums, 0);

    newNnzCount = 0;

    for (int i = 0; i < this.height; ++i) {
      int head = -2;
      int length = 0;

      int jj_start = this.rows[i];
      int jj_end = this.rows[i + 1];
      for (int jj = jj_start; jj < jj_end; ++jj) {
        int j = this.cols[jj];
        double v = this.values[jj];

        int kk_start = sm.rows[j];
        int kk_end = sm.rows[j + 1];
        for (int kk = kk_start; kk < kk_end; ++kk) {
          int k = sm.cols[kk];

          sums[k] += v * sm.values[kk];

          if (next[k] == -1) {
            next[k] = head;
            head = k;
            ++length;
          }
        }
      }

      for (int jj = 0; jj < length; ++jj) {
        if (sums[head] != 0) {
          newCols[newNnzCount] = head;
          newValues[newNnzCount] = sums[head];
          ++newNnzCount;
        }

        int temp = head;
        head = next[head];

        next[temp] = -1; //clear arrays
        sums[temp] = 0;
      }
    }

    // Part 3: sort column indices
    for(int i = 0; i < this.height; i++){
      int row_start = newRows[i];
      int row_end = newRows[i+1];

      ArrayList<AbstractMap.Entry<Integer, Double>> temp = new ArrayList<>(Collections.nCopies(row_end - row_start, null));
      for (int jj = row_start, n = 0; jj < row_end; jj++, n++){
        temp.set(n, new AbstractMap.SimpleEntry<>(newCols[jj], newValues[jj]));
      }

      temp.sort(Comparator.comparing(Map.Entry::getKey));

      for(int jj = row_start, n = 0; jj < row_end; jj++, n++){
        newCols[jj] = temp.get(n).getKey();
        newValues[jj] = temp.get(n).getValue();
      }
    }

    return new SparseMatrix(this.height, sm.width, newRows, newCols, newValues);
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

  public String toString() {
    String str = "";

    for (int i = 0; i < this.height; ++i) {
      for (int j = 0; j < this.width; ++j) {
        str += this.get(i, j) + " ";
      }
      str += "\n";
    }
    return str;
  }

}
