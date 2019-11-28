package edu.spbu.matrix;

import java.util.*;

class MatrixMultiplier {
  static Matrix mul(Matrix m1, Matrix m2) {
    if (m1.getWidth() != m2.getHeight()) {
      return null;
    }

    if (m1 instanceof DenseMatrix) {
      if (m2 instanceof DenseMatrix) {
        return mul((DenseMatrix) m1, (DenseMatrix) m2);
      } else if (m2 instanceof SparseMatrix) {
        return mul((DenseMatrix) m1, (SparseMatrix) m2);
      }
    } else if (m1 instanceof SparseMatrix) {
      if (m2 instanceof DenseMatrix) {
        return mul((SparseMatrix) m1, (DenseMatrix) m2);
      } else if (m2 instanceof SparseMatrix) {
        return mul((SparseMatrix) m1, (SparseMatrix) m2);
      }
    }

    return null;
  }

  private static DenseMatrix mul(DenseMatrix m1, DenseMatrix m2) {
    int newHeight = m1.getHeight(), newWidth = m2.getWidth();
    m2 = m2.transpose();

    double[][] out = new double[newHeight][newWidth];
    for (int i = 0; i < newHeight; ++i) {
      for (int j = 0; j < newWidth; ++j) {
        for (int k = 0; k < m1.getWidth(); ++k) {
          out[i][j] += m1.array[i][k] * m2.array[j][k];
        }
      }
    }

    return new DenseMatrix(newHeight, newWidth, out);
  }

  private static DenseMatrix mul(DenseMatrix m1, SparseMatrix m2) {
    return mul(m2.transpose(), m1.transpose()).transpose();
  }

  private static DenseMatrix mul(SparseMatrix m1, DenseMatrix m2) {
    int newHeight = m1.getHeight(), newWidth = m2.getWidth();
    m2 = m2.transpose();

    double[][] out = new double[newHeight][newWidth];
    for (int k = 0; k < newHeight; ++k) {
      for (int i = 0; i < newHeight; ++i) {
        double sum = out[i][k];
        for (int jj = m1.rows[i]; jj < m1.rows[i + 1]; ++jj) {
          sum += m1.values[jj] * m2.array[k][m1.cols[jj]];
        }
        out[i][k] = sum;
      }
    }

    return new DenseMatrix(newHeight, newWidth, out);
  }

  private static SparseMatrix mul(SparseMatrix m1, SparseMatrix m2) {
    // Part 1: compute CSR row pointer (new_rows)
    int[] newRows = new int[m1.getHeight() + 1];
    newRows[0] = 0;

    int[] mask = new int[m1.getWidth()];
    Arrays.fill(mask, -1);

    int newNnzCount = 0;
    for (int i = 0; i < m1.getHeight(); i++) {
      int rowNnz = 0;

      for (int jj = m1.rows[i]; jj < m1.rows[i + 1]; ++jj) {
        int j = m1.cols[jj];
        for (int kk = m2.rows[j]; kk < m2.rows[j + 1]; kk++) {
          int k = m2.cols[kk];
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
    int[] next = new int[m1.getWidth()];
    int[] sums = new int[m1.getWidth()];
    Arrays.fill(next, -1);
    Arrays.fill(sums, 0);

    newNnzCount = 0;

    for (int i = 0; i < m1.getHeight(); ++i) {
      int head = -2;
      int length = 0;

      int jj_start = m1.rows[i];
      int jj_end = m1.rows[i + 1];
      for (int jj = jj_start; jj < jj_end; ++jj) {
        int j = m1.cols[jj];
        double v = m1.values[jj];

        int kk_start = m2.rows[j];
        int kk_end = m2.rows[j + 1];
        for (int kk = kk_start; kk < kk_end; ++kk) {
          int k = m2.cols[kk];

          sums[k] += v * m2.values[kk];

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
    for(int i = 0; i < m1.getHeight(); i++){
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

    return new SparseMatrix(m1.getHeight(), m2.getWidth(), newRows, newCols, newValues);
  }
}
