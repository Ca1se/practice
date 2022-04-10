/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr) return head;
        ListNode* tar = head;
        int i = 0;
        while(tar->next != nullptr) {
            i++;
            tar = tar->next;
        }
        tar->next = head;
        tar = head;
        for(int j = 0; j < i - (k % (i + 1)); j++) {
            tar = tar->next;
        }
        head = tar->next;
        tar->next = nullptr;
        return head;
    }
};