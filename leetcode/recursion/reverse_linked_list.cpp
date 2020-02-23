/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head, ListNode* prev = nullptr) {
        if (head == nullptr) return nullptr;
        auto *next = head->next;
        head->next = prev;
        if(next == nullptr) return head;
        else return reverseList(next, head);
    }
};
