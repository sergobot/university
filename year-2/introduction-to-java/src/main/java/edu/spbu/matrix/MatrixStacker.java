package edu.spbu.matrix;

class MatrixStacker {
  static Matrix hstack(Matrix m1, Matrix m2) {
    if (m1.getHeight() != m2.getHeight()) {
      return null;
    }

    if (m1 instanceof DenseMatrix) {
      if (m2 instanceof DenseMatrix) {
        return hstack((DenseMatrix) m1, (DenseMatrix) m2);
      }
    }
    if (m1 instanceof SparseMatrix) {
      if (m2 instanceof SparseMatrix) {
        return hstack((SparseMatrix) m1, (SparseMatrix) m2);
      }
    }
    return null;
  }

  static Matrix vstack(Matrix m1, Matrix m2) {
    if (m1.getWidth() != m2.getWidth()) {
      return null;
    }

    if (m1 instanceof DenseMatrix) {
      if (m2 instanceof DenseMatrix) {
        return vstack((DenseMatrix) m1, (DenseMatrix) m2);
      }
    }
    if (m1 instanceof SparseMatrix) {
      if (m2 instanceof SparseMatrix) {
        return vstack((SparseMatrix) m1, (SparseMatrix) m2);
      }
    }
    return null;
  }

  private static DenseMatrix hstack(DenseMatrix m1, DenseMatrix m2) {
    int newHeight = m1.getHeight(), newWidth = m1.getWidth() + m2.getWidth();
    double[][] out = new double[newHeight][newWidth];

    for (int i = 0; i < newHeight; ++i) {
      System.arraycopy(m1.array[i], 0, out[i], 0, m1.array[i].length);
      System.arraycopy(m2.array[i], 0, out[i], m1.array[i].length, m2.array[i].length);
    }

    return new DenseMatrix(newHeight, newWidth, out);
  }

  private static SparseMatrix hstack(SparseMatrix m1, SparseMatrix m2) {
    int newHeight = m1.getHeight(), newWidth = m1.getWidth() + m2.getWidth(), nnz = m1.values.length + m2.values.length;
    int[] newRows = new int[newHeight + 1];
    int[] newCols = new int[nnz];
    double[] newValues = new double[nnz];

    System.arraycopy(m1.values, 0, newValues, 0, m1.values.length);
    System.arraycopy(m2.values, 0, newValues, m1.values.length, m2.values.length);

    int newVal = 0, columnOffset = m1.getWidth();
    for (int i = 0; i < newHeight; ++i) {
      for (int j = m1.rows[i]; j < m1.rows[i + 1]; ++j) {
        newCols[newVal] = m1.cols[j];
        newValues[newVal] = m1.values[j];
        ++newVal;
      }
      for (int j = m2.rows[i]; j < m2.rows[i + 1]; ++j) {
        newCols[newVal] = m2.cols[j] + columnOffset;
        newValues[newVal] = m2.values[j];
        ++newVal;
      }
      newRows[i] = m1.rows[i] + m2.rows[i];
    }
    newRows[newHeight] = nnz;

    return new SparseMatrix(newHeight, newWidth, newRows, newCols, newValues);
  }

  private static DenseMatrix vstack(DenseMatrix m1, DenseMatrix m2) {
    int newHeight = m1.getHeight() + m2.getHeight(), newWidth = m1.getWidth();

    double[][] out = new double[newHeight][newWidth];
    System.arraycopy(m1.array, 0, out, 0, m1.array.length);
    System.arraycopy(m2.array, 0, out, m1.array.length, m2.array.length);

    return new DenseMatrix(newHeight, newWidth, out);
  }

  private static SparseMatrix vstack(SparseMatrix m1, SparseMatrix m2) {
    int newHeight = m1.getHeight() + m2.getHeight(), newWidth = m1.getWidth(), nnz = m1.values.length + m2.values.length;
    int[] newRows = new int[newHeight + 1];
    int[] newCols = new int[nnz];
    double[] newValues = new double[nnz];

    System.arraycopy(m1.rows, 0, newRows, 0, m1.rows.length);

    for (int i = 0; i < m2.rows.length - 1; ++i) {
      newRows[i + m1.rows.length] = m2.rows[i + 1] + m1.rows[m1.rows.length - 1];
    }

    System.arraycopy(m1.cols, 0, newCols, 0, m1.cols.length);
    System.arraycopy(m2.cols, 0, newCols, m1.cols.length, m2.cols.length);

    System.arraycopy(m1.values, 0, newValues, 0, m1.values.length);
    System.arraycopy(m2.values, 0, newValues, m1.values.length, m2.values.length);

    return new SparseMatrix(newHeight, newWidth, newRows, newCols, newValues);
  }
}
