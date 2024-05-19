/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include "stdlib.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
     struct ListNode* sentinel = &(struct ListNode) { 0, NULL };
     struct ListNode* head = sentinel;
     struct ListNode* tail = sentinel;

     // use as boo
     do {
          int smallestVal = 0x7FFFFFFF;
          int smallestIndex = -1;

          for(int i = 0; i < listsSize; i++) {
               struct ListNode* node = lists[i];
               if (!node) continue;

               if (node->val < smallestVal) {
                    smallestVal = node->val;
                    smallestIndex = i;
                    node = node->next;
               }
          }

          if(smallestIndex == -1) break;

          tail->next = lists[smallestIndex];
          tail = tail->next;

          lists[smallestIndex] = lists[smallestIndex]->next;

     } while (1);

     return head->next;
}