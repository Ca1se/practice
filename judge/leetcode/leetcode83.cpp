class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        int preNum = -101;
        ListNode *now = head, *pre = head;
        while(now != nullptr) {
            if(preNum == now->val) {
                pre->next = now->next;
                now = now->next;
                continue;
            }else {
                preNum = now->val;
            }
            if(now != pre)  pre = pre->next;
            now = now->next;
        }
        return head;
    }
};