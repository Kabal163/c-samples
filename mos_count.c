/*
 * Given an integer array nums, find the maximum possible bitwise OR of a subset
 * of nums and return the number of different non-empty subsets with the maximum
 * bitwise OR.
 *
 * An array a is a subset of an array b if a can be obtained from b by deleting
 * some (possibly zero) elements of b. Two subsets are considered different if
 * the indices of the elements chosen are different.
 *
 * The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length -
 * 1] (0-indexed).
 *
 *
 *
 * Example 1:
 * Input: nums = [3,1]
 * Output: 2
 * Explanation: The maximum possible bitwise OR of a subset is 3. There are 2
 * subsets with a bitwise OR of 3:
 * - [3]
 * - [3,1]
 *
 * Example 2:
 * Input: nums = [2,2,2]
 * Output: 7
 * Explanation: All non-empty subsets of [2,2,2] have a bitwise OR of 2. There
 * are 2^3 - 1 = 7 total subsets.
 *
 * Example 3:
 * Input: nums = [3,2,1,5]
 * Output: 6
 * Explanation: The maximum possible bitwise OR of a subset is 7. There are 6
 * subsets with a bitwise OR of 7:
 * - [3,5]
 * - [3,1,5]
 * - [3,2,5]
 * - [3,2,1,5]
 * - [2,5]
 * - [2,1,5]
 *
 * Constraints:
 * 1 <= nums.length <= 16
 * 1 <= nums[i] <= 105
 */
#include <stdio.h>
#include <stdlib.h>

int count_max_or_subsets(int nums[], int nums_size) {
  int result = 0;
  int or_max = 0;
  int subset_ptrs[nums_size];

  for (int i = 0; i < nums_size; i++) {
    or_max |= nums[i];
  }

  /*
   * Check all possible subsets of nums[]. The ss - subset-size controls the
   * size of checking subset.
   */
  for (int ss = 0; ss < nums_size; ss++) {

    /* Reset all pointers to initial position */
    for (int p = 0; p <= ss; p++) {
      subset_ptrs[p] = p;
    }

    while (subset_ptrs[0] < nums_size - ss) {

      /* Find OR of the subset and move the fastest pointer */
      int or_subset = 0;
      for (int p = 0; p <= ss; p++) {
        or_subset |= nums[subset_ptrs[p]];
      }
      if (or_subset == or_max) {
        result++;
      }
      subset_ptrs[ss]++;

      /*
       * If the fastest pointer is out of nums[] array then move the
       * slower pointer and check again. If we moved the slowest
       * pointer and the fastest pointer is still out of nums[] array -
       * break and add new the fastest pointer
       */
      int slower_ptr = ss - 1;
      while (subset_ptrs[ss] >= nums_size) {
        if (slower_ptr < 0) {
          break;
        }
        subset_ptrs[slower_ptr]++;
        for (int p = slower_ptr; p < ss; p++) {
          subset_ptrs[p + 1] = subset_ptrs[p] + 1;
        }
        slower_ptr--;
      }
    }
  }

  return result;
}

int main(int ac, char **av) {
  int nums1[4] = {3, 2, 1, 5};
  int result = count_max_or_subsets(nums1, 4);
  printf("Result of [3, 2, 1, 5] is: %d\n", result);

  int nums2[3] = {2, 2, 2};
  result = count_max_or_subsets(nums2, 3);
  printf("Result of [2, 2, 2] is: %d\n", result);

  int nums3[2] = {3, 1};
  result = count_max_or_subsets(nums3, 2);
  printf("Result of [3, 1] is: %d\n", result);

  return EXIT_SUCCESS;
}
