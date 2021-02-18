#include<stack>

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        std::stack<ListNode*> Stack{};
        ListNode * pTemp=pHead;
        
        while(pTemp->next!=NULL)
        {
            Stack.push(pTemp);
            pTemp=pTemp->next;
        }
        Stack.push(pTemp);
        pHead=pTemp;
        while(!Stack.empty())
        {
            Stack.pop();
            pTemp->next=Stack.top();
            pTemp=Stack.top();
        }
        pTemp->next=NULL;
        return pHead;
    }
};
int main(){
    ListNode* p1=new ListNode(1);
    ListNode* p2=new ListNode(2);
    ListNode* p3=new ListNode(3);
    p1->next=p2;
    p2->next=p3;
    Solution s1;
    s1.ReverseList(p1);

    return 0;
}