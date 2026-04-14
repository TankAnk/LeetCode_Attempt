/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
size_t capacity(struct ListNode* head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = (*head).next;
    }
    return count;
}

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    size_t s1 = capacity(list1), s2 = capacity(list2);
    if (s1 == 0 && s2 == 0)
        return NULL;
        
    if (s1 == 0)
        return list2;
    
    if (s2 == 0)
        return list1;
        
    struct ListNode *result = malloc(sizeof(*result));
    struct ListNode *tmp = result;
    while (list1 && list2)
    {
        if ((*list1).val < (*list2).val)
        {
            (*tmp).next = list1;
            list1 = (*list1).next;
        }
        
        else
        {
            (*tmp).next = list2;
            list2 = (*list2).next;
        }

        tmp = (*tmp).next;
    }
    
    while (list1)
    {
        
        (*tmp).next = list1;
        list1 = (*list1).next;
        tmp = (*tmp).next;
    }
    
    while (list2)
    {
        
        (*tmp).next = list2;
        list2 = (*list2).next;
        tmp = (*tmp).next;
    }
    
    return (*result).next;
}