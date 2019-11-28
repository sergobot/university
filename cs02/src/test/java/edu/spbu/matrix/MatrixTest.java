package edu.spbu.matrix;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MatrixTest
{
  @Test
  public void mulDD() {
    Matrix m1 = new DenseMatrix("m1.txt");
    Matrix m2 = new DenseMatrix("m2.txt");
    Matrix expected = new DenseMatrix("result.txt");

    long start = System.currentTimeMillis();
    Matrix received = m1.mul(m2);
    long finish = System.currentTimeMillis();
    System.out.println(finish - start);

    assertEquals(expected, received);
  }

  @Test
  public void mulDS() {
    Matrix m1 = new DenseMatrix("m1.txt");
    Matrix m2 = new SparseMatrix("m2.txt");
    Matrix expected = new DenseMatrix("result.txt");

    long start = System.currentTimeMillis();
    Matrix received = m1.mul(m2);
    long finish = System.currentTimeMillis();
    System.out.println(finish - start);

    assertEquals(expected, received);
  }

  @Test
  public void mulSD() {
    Matrix m1 = new SparseMatrix("m1.txt");
    Matrix m2 = new DenseMatrix("m2.txt");
    Matrix expected = new DenseMatrix("result.txt");

    long start = System.currentTimeMillis();
    Matrix received = m1.mul(m2);
    long finish = System.currentTimeMillis();
    System.out.println(finish - start);

    assertEquals(expected, received);
  }


  @Test
  public void mulSS() {
    Matrix m1 = new SparseMatrix("m1.txt");
    Matrix m2 = new SparseMatrix("m2.txt");
    Matrix expected = new SparseMatrix("result.txt");

    long start = System.currentTimeMillis();
    Matrix received = m1.mul(m2);
    long finish = System.currentTimeMillis();
    System.out.println(finish - start);

    assertEquals(expected, received);
  }
}
