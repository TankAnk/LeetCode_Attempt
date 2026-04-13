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

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {  
    size_t size = capacity(head);
    printf("%zu\n", size);
    
    if (n == size)
    {
        head = (*head).next;
        return head;
    }
    
    struct ListNode *traverse = head;    
    for (int i = 0; i < size - n - 1; i++)
        traverse = (*traverse).next;
    
    struct ListNode *tmp = (*traverse).next;
    (*traverse).next = (*tmp).next;
    free(tmp);
    return head;
}