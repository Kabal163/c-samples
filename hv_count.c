/*
 * You are given a 0-indexed integer array nums. An index i is part of a hill in
 * nums if the closest non-equal neighbors of i are smaller than nums[i].
 * Similarly, an index i is part of a valley in nums if the closest non-equal
 * neighbors of i are larger than nums[i]. Adjacent indices i and j are part of
 * the same hill or valley if nums[i] == nums[j].
 *
 * Note that for an index to be part of a hill or valley, it must have a
 * non-equal neighbor on both the left and right of the index.
 *
 * Return the number of hills and valleys in nums.
 *
 *
 *
 * Example 1:
 *
 * Input: nums = [2,4,1,1,6,5]
 * Output: 3
 * Explanation:
 * At index 0: There is no non-equal neighbor of 2 on the left, so index 0 is
 * neither a hill nor a valley.
 * At index 1: The closest non-equal neighbors of 4
 * are 2 and 1. Since 4 > 2 and 4 > 1, index 1 is a hill.
 * At index 2: The
 * closest non-equal neighbors of 1 are 4 and 6. Since 1 < 4 and 1 < 6, index 2
 * is a valley.
 * At index 3: The closest non-equal neighbors of 1 are 4 and 6.
 * Since 1 < 4 and 1 < 6, index 3 is a valley, but note that it is part of the
 * same valley as index 2.
 * At index 4: The closest non-equal neighbors of 6 are
 * 1 and 5. Since 6 > 1 and 6 > 5, index 4 is a hill.
 * At index 5: There is no
 * non-equal neighbor of 5 on the right, so index 5 is neither a hill nor a
 * valley. There are 3 hills and valleys so we return 3.
 *
 * Constraints:
 * 3 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 */
#import <stdio.h>
#import <stdlib.h>

int count_hv(int *nums, int nums_size);
static inline bool is_hill(int *nums, int p_cur, int p_next);
static inline bool is_valley(int *nums, int p_cur, int p_next);

int main(int ac, char **av) {
  int a[] = {2, 4, 1, 1, 6, 5};
  printf("Amount of hills and valleys of array [2, 4, 1, 1, 6, 5]: %d\n",
         count_hv(a, 6));
  return EXIT_SUCCESS;
}

int count_hv(int *nums, int nums_size) {
  int p_cur = 1;
  int p_next = 2;
  int cnt = 0;

  while (p_next < nums_size) {
    if (nums[p_cur] == nums[p_next]) {
      p_next++;
      continue;
    }
    if (is_hill(nums, p_cur, p_next) || is_valley(nums, p_cur, p_next)) {
      cnt++;
    }
    p_cur = p_next;
    p_next++;
  }
  return cnt;
}

static inline bool is_hill(int *nums, int p_cur, int p_next) {
  return nums[p_cur - 1] < nums[p_cur] && nums[p_cur] > nums[p_next];
}

static inline bool is_valley(int *nums, int p_cur, int p_next) {
  return nums[p_cur - 1] > nums[p_cur] && nums[p_cur] < nums[p_next];
}
