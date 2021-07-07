//Binary Tree Program

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<bitset>
#include<algorithm>
using namespace std;


class myTree
{
        private:
        
		//inorder traversal 
        void inorder(myTree* root, const int maxNumOfNodes, int &NumberOfNodes)
		{
                if(NumberOfNodes>=maxNumOfNodes)
                        return;
                if(root==NULL)
                        return;
                inorder(root->ToTheLeft, maxNumOfNodes, NumberOfNodes);
                if(NumberOfNodes<maxNumOfNodes){
                        cout<<root->data<<" ";
                        NumberOfNodes++;
                }
                inorder(root->ToTheRight, maxNumOfNodes, NumberOfNodes);
        }
        
		//preorder traversal 
        void preorder(myTree* root, const int maxNumOfNodes, int &NumberOfNodes)
		{
                if(NumberOfNodes>=maxNumOfNodes)
                        return;
                if(root==NULL)
                        return;
                if(NumberOfNodes<maxNumOfNodes){
                        cout<<root->data<<" ";
                        NumberOfNodes++;
                }
                preorder(root->ToTheLeft, maxNumOfNodes, NumberOfNodes);
                preorder(root->ToTheRight, maxNumOfNodes, NumberOfNodes);
        }
        
		//postorder traversal
        void postorder(myTree* root, const int maxNumOfNodes, int &NumberOfNodes)
		{
                if(NumberOfNodes>=maxNumOfNodes)
                        return;
                if(root==NULL)
                        return;
                postorder(root->ToTheLeft, maxNumOfNodes, NumberOfNodes);
                postorder(root->ToTheRight, maxNumOfNodes, NumberOfNodes);
                if(NumberOfNodes<maxNumOfNodes){
                        cout<<root->data<<" ";
                        NumberOfNodes++;
                }
        }
        
		//sum of all elements in the tree
        int sumOfTree(myTree* root)
		{
                if(root==NULL)
                return 0;
                return root->data+sumOfTree(root->ToTheLeft)+sumOfTree(root->ToTheRight);
        }
        
		//gets the deepest valueue in the tree
        void deepestvalue(myTree *root, int cur_depth, int &max_depth, int &valueue)
		{
                if(root==NULL)
                        return;
                if(cur_depth>max_depth)
				{
                        max_depth=cur_depth;
                        valueue=root->data;
                }
                deepestvalue(root->ToTheLeft, cur_depth+1, max_depth, valueue);
                deepestvalue(root->ToTheRight, cur_depth+1, max_depth, valueue);
        }
        
		//deletes the root
        myTree* delHead(myTree *root){
                if(root==NULL){
                        return NULL;
                }
                if(root->ToTheLeft==NULL)
                        return root->ToTheRight;
                if(root->ToTheRight==NULL)
                        return root->ToTheLeft;
                myTree* l = root->ToTheLeft;
                myTree* r= root->ToTheRight;
                delete root;
                myTree* temp = r;
                while(temp->ToTheLeft!=NULL){
                        temp=temp->ToTheLeft;
                }
                temp->ToTheLeft=l;
                return r;
        }
       
	   //the sum of the digits of a number
        int digitSum(int num)
		{
                int sum=0;
                while(num){
                        num/=10;
                }
                return sum;
        }
        
		public:
        int data;
        myTree* ToTheLeft;
        myTree* ToTheRight;
        
        myTree(int value)
		{
                data = value;
                ToTheLeft=NULL;
                ToTheRight=NULL;
        }
        
		//inserts an element into the tree
        static myTree* insertElement(int value, myTree* root=NULL)
		{
                if(root==NULL)
				{
                        return new myTree(value);
                }
                if(value<root->data)
				{
                                root->ToTheLeft=insertElement(value, root->ToTheLeft);
                }else{
                        root->ToTheRight=insertElement(value, root->ToTheRight);
                }
                return root;
        }
        
		//print the first number of inorder in the tree
        void inorder(myTree* root, int maxNumOfNodes)
		{
                if(root==NULL)
				{
                        return;
                }
                int NumberOfNodes = 0;
                inorder(root, maxNumOfNodes, NumberOfNodes);
                cout<<endl;
        }
        
		//print the first number of preorder in the tree
        void preorder(myTree* root, int maxNumOfNodes)
		{
                if(root==NULL){
                        return;
                }
                int NumberOfNodes = 0;
                preorder(root, maxNumOfNodes, NumberOfNodes);
                cout<<endl;
        }
        
		//print the first number of postorder in the tree
        void postorder(myTree* root, int maxNumOfNodes){
                if(root==NULL){
                        return;
                }
                int NumberOfNodes = 0;
                postorder(root, maxNumOfNodes, NumberOfNodes);
                cout<<endl;
        }
        
		//count the number of elements that are in the tree
        int counting(myTree* root){
                if(root==NULL)
                return 0;
                return 1+counting(root->ToTheLeft)+counting(root->ToTheRight);
        }
        
		
		//get the sum and average, then print out both
        void mySumAndAverage(myTree* root){
                int elementcounting = counting(root);
                if(elementcounting==0){
                        cout<<"No elements in the tree!"<<endl;
                        return;
                }
                int sum = sumOfTree(root);
                cout<<"Sum = "<<sum<<endl;
                float average = sum/(elementcounting*1.0);
                cout<<"Average = "<<average<<endl;
        }
        
		//find the number of the leaf nodes that are in the tree
        int NumberOfLeafs(myTree* root)
		{
                if(root==NULL)
                return 0;
                if(root->ToTheLeft==NULL&&root->ToTheRight==NULL){
                        return 1;
                }
                return NumberOfLeafs(root->ToTheLeft)+NumberOfLeafs(root->ToTheRight);
        }
        
		//find the deepest value in the tree
        int TheDeepestValue(myTree *root)
		{
                int TheDeepestValue=0;
                int maxDepth=-1;
                deepestvalue(root, 0, maxDepth, TheDeepestValue);
                return TheDeepestValue;
        }
        
		//find the nodes with only one child
        int OneChildNodes(myTree* root)
		{
                if(root==NULL)
                        return 0;
                if(root->ToTheLeft!=NULL && root->ToTheRight!=NULL)
				{
                        return OneChildNodes(root->ToTheLeft) +OneChildNodes(root->ToTheRight);
                }
                return 1 + OneChildNodes(root->ToTheLeft) +OneChildNodes(root->ToTheRight);
        }
        
		//search for an element
        myTree* searchElement(myTree *root, int value)
		{
                if(root==NULL)
                        return NULL;
                if(value==root->data)
				{
                        return root;
                }
                if(value<root->data)
				{
                        //search going left in the subtree
                        return searchElement(root->ToTheLeft, value);
                }else{
                        //search going right in the subtree
                        return searchElement(root->ToTheRight, value);
                }
        }
       
	   //deletes all elements with digits that are less than the sum of 10
        myTree* deleteLessThan10(myTree* root)
		{
                if(root==NULL)
                        return NULL;
                if(digitSum(root->data)<10)
				{
                        root=delHead(root);
                }
                if(root!=NULL){
                        root->ToTheLeft=deleteLessThan10(root->ToTheLeft);
                        root->ToTheRight=deleteLessThan10(root->ToTheRight);
                }
                return root;
        }
};

int main()
{
        
        ifstream infile("TreeRandNbrs.txt");
        int value;
        myTree *root = NULL;
        while(infile>>value){
                root = myTree::insertElement(value, root);
        }
        cout<<"Print first 20 elements in inorder:"<<endl;
        root->inorder(root, 20);
		cout << endl;

        cout<<"Print first 20 elements in preorder:"<<endl;
        root->preorder(root, 20);
		cout << endl;

        cout<<"Print first 20 elements in postorder:"<<endl;
        root->postorder(root, 20);
		cout << endl;

        cout<<"Number of nodes in the tree : "<<root->counting(root)<<endl;
		root->mySumAndAverage(root);
		cout << endl;

        cout<<"Number of leafs in the tree : "<<root->NumberOfLeafs(root)<<endl;
		cout << endl;

        cout<<"Deepest value in the tree :  "<<root->TheDeepestValue(root)<<endl;
		cout << endl;

        cout<<"Number of nodes with one child :  "<<root->OneChildNodes(root)<<endl;
		cout << endl;

        cout<<"Subtree of the node value of 253 in inorder:"<<endl; 
        myTree* subtree = root->searchElement(root,253);
        subtree->inorder(subtree, subtree->counting(subtree));
		cout << endl;

        cout<<"Right subtree of node value 471 in postorder:"<<endl; 
        subtree = root->searchElement(root,471);
        subtree->postorder(subtree->ToTheRight, subtree->counting(subtree));
		cout << endl;

        cout<<"Number of nodes that are to the left of the root : "<<root->counting(root->ToTheLeft)<<endl; 
		cout << endl;

        cout<<"Number of nodes that are to the right of the root : "<<root->counting(root->ToTheRight)<<endl;
		cout << endl;
        
        cout<<"Delete all the nodes in the tree that the sum of the digits is less than 10:"<<endl;
        root = root->deleteLessThan10(root);

        root->mySumAndAverage(root);
}