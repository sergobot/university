package edu.spbu;

public class MatrixTest
{
  public static final String MATRIX1_NAME = "m1.txt";
  public static final String MATRIX2_NAME = "m2.txt";

  public static void main(String s[])
  {

    System.out.println("Starting loading dense matrices");
    Matrix m1 = new DMat(MATRIX1_NAME);
    System.out.println("1 loaded");
    Matrix m2 = new DMat(MATRIX2_NAME);
    System.out.println("2 loaded");
    long start = System.currentTimeMillis();
    m1.mul(m2);
    System.out.println("Dense Matrix time: " +(System.currentTimeMillis() - start));

    System.out.println("Starting loading sparse matrices");
    m1 = new SMat(MATRIX1_NAME);
    System.out.println("1 loaded");
    m2 = new SMat(MATRIX2_NAME);
    System.out.println("2 loaded");
    start = System.currentTimeMillis();
    m1.mul(m2);
    System.out.println("Sparse Matrix time: " +(System.currentTimeMillis() - start));
  }
}
