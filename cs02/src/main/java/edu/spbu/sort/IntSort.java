package edu.spbu.sort;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * Created by artemaliev on 07/09/15.
 */
public class IntSort {
  private static void merge (int[] array, int l, int m, int r) {
    int leftLength = m - l + 1, rightLength = r - m;
    int[] leftArray = new int[leftLength], rightArray = new int[rightLength];

    System.arraycopy(array, l, leftArray, 0, leftLength);
    System.arraycopy(array, m + 1, rightArray, 0, rightLength);

    int i = 0, j = 0, k = l;
    while (i < leftLength && r < rightLength) {
      if (leftArray[i] < rightArray[j]) {
        array[k] = leftArray[i];
        ++i;
      } else {
        array[k] = rightArray[j];
        ++j;
      }
      ++k;
    }

    while(i < leftLength)
    {
      array[k] = leftArray[i];
      ++i;
      ++k;
    }

    while(j < rightLength)
    {
      array[k] = leftArray[j];
      ++j;
      ++k;
    }
  }

  private static void mergeSort(int[] array, int l, int r) {
    if (r <= l) {
      return;
    }

    int m = (l + r) / 2;
    mergeSort(array, l, m);
    mergeSort(array, m+1, r);

    merge(array, l, m, r);
  }

  private static void merge(List<Integer> list, int l, int m, int r) {
    List<Integer> leftList = list.subList(l, m + 1);
    List<Integer> rightList = list.subList(m + 1, r + 1);

    int i = 0, j = 0, k = l;
    while(i < leftList.size() && j < rightList.size()) {
      if (leftList.get(i) < rightList.get(j)) {
        list.set(k, leftList.get(i));
        ++i;
      } else {
        list.set(k, rightList.get(j));
        ++j;
      }
      ++k;
    }

    while (i < leftList.size()) {
      list.set(k, leftList.get(i));
      ++i;
      ++k;
    }

    while (j < rightList.size()) {
      list.set(k, rightList.get(j));
      ++j;
      ++k;
    }
  }

  private static void mergeSort(List<Integer> list, int l, int r) {
    if (r <= l) {
      return;
    }

    int m = (l + r) / 2;
    mergeSort(list, l, m);
    mergeSort(list, m+1, r);

    merge(list, l, m, r);
  }

  public static void sort (int[] array) {
    mergeSort(array, 0, array.length - 1);
  }

  public static void sort (List<Integer> list) {
    mergeSort(list, 0, list.size() - 1);
  }
}
