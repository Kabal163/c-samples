/*
 * Maximum Unique Sabarray Sum After Deletion
 *
 * You are given an integer array nums.
 * You are allowed to delete any number of elements from nums without making it
 * empty. After performing the deletions, select a subarray of nums such that:
 * All elements in the subarray are unique.
 * The sum of the elements in the subarray is maximized.
 * Return the maximum sum of such a subarray.
 *
 * Example 1:
 *  Input: nums = [1,2,3,4,5]
 *  Output: 15
 *  Explanation:
 *  Select the entire array without deleting any element to obtain the maximum
 * sum.
 *
 * Example 2:
 *  Input: nums = [1,1,0,1,1]
 *  Output: 1
 *  Explanation:
 *  Delete the element nums[0] == 1, nums[1] == 1, nums[2] == 0, and nums[3]
 * == 1. Select the entire array [1] to obtain the maximum sum.
 *
 * Example 3:
 *  Input: nums = [1,2,-1,-2,1,0,-1]
 *  Output: 3
 *  Explanation:
 *  Delete the elements nums[2] == -1 and nums[3] == -2, and select the subarray
 * [2, 1] from [1, 2, 1, 0, -1] to obtain the maximum sum.
 */
#include <err.h>
#include <limits.h>
#include <malloc/malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_node {
  struct tree_node *left;
  struct tree_node *right;
  int val;
};
static int tree_len;
static bool only_negative;
static struct tree_node *head;

int max_sum(int *nums, int numsSize);
static inline void add(int val);
int calc();

int main(int ac, char **av) {
  int x[] = {1, 2, 3, 4};
  int y[] = {0, 0, 1, 1, 0};
  int z[] = {-1, -2, -3, 0};

  printf("Sum for array [1, 2, 3, 4]: %d\n", max_sum(x, 4));
  printf("Sum for array [0, 0, 1, 1, 0]: %d\n", max_sum(y, 5));
  printf("Sum for array [-1, -2, -3, 0]: %d\n", max_sum(z, 4));
}

int max_sum(int *nums, int numsSize) {
  int max = INT_MIN;
  tree_len = 0;
  only_negative = true;

  if (numsSize == 1) {
    return nums[0];
  }
  head = malloc(numsSize * sizeof(struct tree_node));
  if (head == NULL) {
    err(EXIT_FAILURE, "malloc()");
  }
  head->val = nums[0];
  head->left = NULL;
  head->right = NULL;
  tree_len++;
  for (int i = 1; i < numsSize; i++) {
    add(nums[i]);
  }
  int res = calc();
  free(head);
  return res;
}

static inline void add(int val) {
  struct tree_node *c = head;
  struct tree_node *prev = NULL;
  while (c != NULL) {
    if (c->val == val) {
      return;
    }
    prev = c;
    if (val < c->val) {
      c = c->left;
    } else {
      c = c->right;
    }
  }
  head[tree_len].left = NULL;
  head[tree_len].right = NULL;
  head[tree_len].val = val;
  if (val >= 0) {
    only_negative = false;
  }
  if (val < prev->val) {
    prev->left = &head[tree_len];
  } else {
    prev->right = &head[tree_len];
  }
  tree_len++;
}

int calc() {
  int sum = 0;
  if (only_negative) {
    int max = INT_MIN;
    for (int i = 0; i < tree_len; i++) {
      if (head[i].val > max) {
        max = head[i].val;
      }
    }
    return max;
  }
  for (int i = 0; i < tree_len; i++) {
    if (head[i].val < 0) {
      continue;
    }
    sum += head[i].val;
  }
  return sum;
}
