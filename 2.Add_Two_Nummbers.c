
 //Definition for singly-linked list.
 struct ListNode {
 	int val;
 	struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carry = 0, sum, val1, val2;
    struct ListNode *curr1 = l1, *curr2 = l2;
    //struct ListNode *result = malloc(max_size * sizeof(ListNode));
    struct ListNode *result = NULL;
    
    while (curr1 != NULL || curr2 != NULL || carry != 0)
    {
    	val1 = (curr1 != NULL) ? (*curr1).val : 0;
    	val2 = (curr2 != NULL) ? (*curr2).val : 0;
    	sum = val1 + val2 + carry;
    	struct ListNode *tmp_node = malloc(sizeof(struct ListNode));
    	if (tmp_node == NULL) return NULL;
    	(*tmp_node).val = sum % 10;
    	
    	//Inset at the beginnning
    	if (result == NULL)
    	{
	    	(*tmp_node).next = result;
	    	result = tmp_node;
    	}
    	//Insert at the end
    	else
		{
            struct ListNode *traverse = result;
    		while ((*traverse).next) traverse = (*traverse).next;//Go to the last node
    		(*tmp_node).next = NULL;
    		(*traverse).next = tmp_node;
    	}
    	
    	carry = sum / 10;
    	if (curr1 != NULL) curr1 = (*curr1).next;
    	if (curr2 != NULL) curr2 = (*curr2).next;
    }
    return result;
}
