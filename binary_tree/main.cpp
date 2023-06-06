#include<bits/stdc++.h>
using namespace std;
struct node{
    char val;
    node *lnode;
    node *rnode;
    bool lflag;
    bool rflag;
    node(){
        val = '\0';
        lnode = nullptr;
        rnode = nullptr;
        lflag = true;
        rflag = true;
    };
};
class binary_tree{
private:
    node *root;
public:
    binary_tree(){
        root = nullptr;
    }
    binary_tree(node *Root){
        node *ptr = new node;
        ptr->val = Root->val;
        ptr->lnode = Root->lnode;
        ptr->rnode = Root->rnode;
        ptr->lflag = Root->lflag;
        ptr->rflag = Root->rflag;
    }
    binary_tree(char Val){
        node *ptr = new node;
        ptr->val = Val;
        ptr->lnode = nullptr;
        ptr->rnode = nullptr;
        ptr->lflag = true;
        ptr->rflag = true;
        root = ptr;
    }
    binary_tree(binary_tree& m){
        add_subtree(root, m.root);
    }
    ~binary_tree(){
            node *ptr = root;
            delete_subtree(ptr);
    }
    //ɾ�����ڵ�ΪROOT������
    void delete_subtree(node *ROOT){
        node *ptr = ROOT;
        if(!ROOT->lflag) {
            node *lptr = ptr->lnode;
            delete_subtree(lptr);
        }
        if(!ROOT->rflag) {
            node *rptr = ptr->rnode;
            delete_subtree(rptr);
        }
        delete ptr;
    }
    node *get_root(){
        return root;
    }
    //��c�ڵ㴦����������c�ڵ��滻Ϊ�������ڵ㣩
    void add_subtree(node* c,node *ROOT){
        node *p = ROOT;
        node *ptr = new node;
        ptr->val = ROOT->val;
        ptr->lflag = ROOT->lflag;
        ptr->rflag = ROOT->rflag;
        c = ptr;
        if(p->lnode!=nullptr){
            ptr->lnode = new node;
            add_subtree(ptr->lnode,p->lnode);
        }
        else{
            ptr->lnode = nullptr;
        }
        if(p->rnode!= nullptr){
            ptr->rnode = new node;
            add_subtree(ptr->rnode,p->rnode);
        }
        else{
            ptr->rnode = nullptr;
        }
    }
    //����ֵΪV�Ľڵ㣬���ҷ��ظýڵ�ָ��
    //ͨ������������Ҹýڵ�
    node *find(node* root,char V){
        node *ptr = root;
        if (root->val==V)
            return root;
        else if(!root->lflag)
            root = find(root->lnode,V);
        if(!ptr->rflag&&root->val!=V)
            root = find(ptr->rnode,V);
        return root;
    }
    //����Զ���ڵ�
    void add_node(){
        char tar;
        int c = -1;
        node *ptr = root;
        node *n;
        while (true) {
            cout << "���������ĸ��ڵ�����ӣ�" << endl;
            cin >> tar;
            n = find(ptr, tar);
            if (n->val != tar) {
                cout << "��ӵĽڵ㲻���ڣ�" << endl;
                continue;
            }
            else
                break;
        }
        while(c!=0&&c!=1) {
            cout << "������0��1��������ӽڵ�����ӣ�" << endl;
            cin >> c;
            if(c!=0&&c!=1)
                cout<<"��������ȷ�����֣�"<<endl;
        }
        char V;
        cout<<"������ýڵ��ֵ: "<<endl;
        cin>>V;
        switch(c){
            case 0:
                if(n->lflag){
                    n->lflag = false;
                    node *p = new node;
                    p->val = V;
                    n->lnode = p;
                }
                else{
                    node *l = n->lnode;
                    node *p = new node;
                    p->val = V;
                    p->lflag = false;
                    n->lnode = p;
                    p->lnode = l;
                }
                break;
            case 1:
                if(n->rflag){
                    n->rflag = false;
                    node *p = new node;
                    p->val = V;
                    n->rnode = p;
                }
                else{
                    node *r = n->rnode;
                    node *p = new node;
                    p->val = V;
                    p->rflag = false;
                    n->rnode = p;
                    p->rnode = r;
                }
                break;
            default:
                cout<<"ERROR: Unknown"<<endl;
        }
    }
};
//���root����ڵ�
void add_left_node(node* root,char V){
    node *ptr = new node;
    ptr->val = V;
    root->lnode = ptr;
    root->lflag = false;
}
//���root����ڵ�
void add_right_node(node* root,char V){
    node *ptr = new node;
    ptr->val = V;
    root->rnode = ptr;
    root->rflag = false;
}
//������������,cΪROOT���ڲ���
void inorderTraversal(node *ROOT,int c){
    if(ROOT==nullptr){
        return;
    }
    inorderTraversal(ROOT->lnode,c+1);
    cout<<ROOT->val<<":"<<c<<" ";
    inorderTraversal(ROOT->rnode,c+1);
}
//�������
node* preTraversal(node *root,node *pre){
    if(root->lflag)
        root->lnode = pre;
    if(pre!=nullptr) {
        if (pre->rflag)
            pre->rnode = root;
    }
    if(!root->lflag) {
        pre = root;
        root = preTraversal(root->lnode, root);
        if(!pre->rflag)
            root = preTraversal(pre->rnode,root);
    }
    else if(!root->rflag)
        root = preTraversal(root->rnode,root);
    return root;
}
//����������
void preThread(binary_tree &T){
    node *ptr = T.get_root();
    node *pre = nullptr;
    preTraversal(ptr,pre);
}
//�������
node *inTraversal(node *root, node *pre){
    if(!root->lflag){
        pre = inTraversal(root->lnode,pre);
    }
    else {
        root->lnode = pre;
    }
    if(pre!= nullptr&&pre->rflag)
        pre->rnode = root;
    if((!root->rflag))
        root = inTraversal(root->rnode,root);
    return root;
}
//����������
void inThread(binary_tree &T){
    node *ptr = T.get_root();
    node *pre = nullptr;
    inTraversal(ptr,pre);
}
//�������
node *postTraversal(node *root, node *pre){
    if(!root->lflag){
        pre = postTraversal(root->lnode,pre);
    }
    else{
        root->lnode = pre;
    }
    if((!root->rflag))
        pre = postTraversal(root->rnode,pre);
    if(pre!= nullptr&&pre->rflag)
        pre->rnode = root;
    return root;
}
//����������
void postThread(binary_tree &T){
    node *ptr = T.get_root();
    node *pre = nullptr;
    postTraversal(ptr,pre);
}
int main(){
    binary_tree T('A');
    node *A = T.get_root();
    add_right_node(A,'C');
    add_left_node(A,'B');
    add_left_node(A->lnode,'D');
    add_right_node(A->lnode,'E');
    add_left_node(A->rnode,'F');
    add_right_node(A->rnode,'G');
    inorderTraversal(A,1);
    cout<<endl;
    postThread(T);
    node *ptr = T.find(T.get_root(),'B');
    T.add_node();
    cout<<endl;
}