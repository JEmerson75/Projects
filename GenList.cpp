//General List Program

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

typedef int ElementType;
const int CAPACITY = 20;

class List
{
private:
    ElementType aryList[CAPACITY];
    int arySize; //next available place in array
    int pos;    //points to the last element inserted,  can't be outside array


public:
    
    List();
    List(List& aryList);
    
    void clear();
    void first();
    void prev();
    void next();
    void last();
    void replace(ElementType);
    void setPos(int);
    void erase();
    void insertAfter(ElementType);
    void insertBefore(ElementType);
	void swap(List &);
    int size();
    bool empty();
    ElementType getElement();
    int getPos();
    
    List operator= (List& aryListB);
   
    friend List operator + (List& ListA, List& ListB);
};

    
    ostream& operator <<(ostream& outs, List& aryList);
    List operator + (List& ListA, List& ListB);
    bool operator == (List aryList1, List aryList2);
    void open_outfile(ofstream&);
    void close_outfile(ofstream&);
	void swap(List &secondList);


List::List()
{
    this->clear();
};

List::List(List& aryListB)
{
    this->clear();
    int orig_pos = aryListB.getPos();
    aryListB.first();
    for(int i = 0; i < aryListB.size(); aryListB.next(), i++){
            this->aryList[i] = aryListB.getElement();
            this->arySize++;
    }
    this->pos = orig_pos;
    aryListB.setPos(orig_pos);
}

void List::clear()

{
    arySize = 0;
    pos = 0;
    int i;

    for(i=0; i < CAPACITY; i++)
    {
        
        aryList[i] = 0;
        
    }
}
void List::first()
//sets current position to 0
{
    pos = 0;
}
void List::prev()
//set position back one 
{
    if (pos > 0)
        pos--;
}
void List::next()
//sets the position ahead one 
{
    if (pos < (arySize-1))
        pos++;
}
void List::last()
//sets position to last element in the list
{
    if (arySize > 0)
        pos = (arySize - 1);
    else
        pos = 0;
}
void List::replace(ElementType val)
//replaces current at position with new value
{
    aryList[pos] = val;
}
void List::setPos(int newPos)
//changes the current position
{
    if(newPos >= 0 && newPos < arySize)
        pos = newPos;
}
void List::erase()
//erases the current position element and shift all remaining values left one
{
    if(arySize > 0)
    {
        for(int i = pos; i < arySize - 1; i++)
        {
            aryList[i] = aryList[i+1];
        }
        aryList[arySize-1] = 0;
        arySize -= 1;
    }
}
void List::insertAfter(ElementType val)
//insert element after current position
{
    if (pos >= CAPACITY-1) 
        cout << "No insert made" << endl;
    else {
        for(int i = arySize; i > pos; i--) 
            aryList[i] = aryList[i-1];
        if (arySize == 0) 
            aryList[pos] = val;
        else {
            aryList[pos+1] = val;
            pos++; 
        }
        
            arySize++;
    }
}
void List::insertBefore(ElementType val)
//insert new element before current position
{
    if(pos == (int)CAPACITY -1){
        aryList[pos] = val;
    }
    else {
        for(int i = arySize; i >= pos && i !=0 ; i--)
            aryList[i] = aryList[i-1];
        aryList[pos] = val;
        if (arySize < CAPACITY)
            arySize++;
    }
}

 void List::swap(List &secondList)
	{
		  int temp = 0;
		  int elements[20];
		  if(secondList.size() == this->size())
		{            
			for(int i=0;i<this->size();i++)
			{
				temp = elements[i];
				secondList.setPos(i);
				setPos(i);
				replace(secondList.getElement());
				secondList.replace(temp);
				}
				}
				else
				throw std::invalid_argument("fix it");
			}

int List::size()
//gets the size of the array
{
    return arySize;
}
bool List::empty()
{
    return (size() == 0);
}
ElementType List::getElement()
//returns the list value stored at current position
{
    if(size() <= 0)
        return 0;
    else
        return aryList[pos];
}
int List::getPos()
//returns the current position
{
    return pos;
}

ostream& operator <<(ostream& outs, List& aryList)
{
    int orig_pos = aryList.getPos();
    aryList.first();
    outs << "[ ";
    for (int i = 0; i < aryList.size(); aryList.next(), i++)
        outs << aryList.getElement() << " ";
    outs << " ]";
    aryList.setPos(orig_pos);
    return outs;
}
List operator+(List& ListA, List& ListB)
{
    List ListC(ListA);
    int orig_pos = ListB.getPos();
    ListC.first();
    ListB.first();

    for(int i = 0; i < ListB.size(); ListB.next(), ListC.next(), i++){
        ListC.replace(ListB.getElement() + ListC.getElement());
    }
    ListB.setPos(orig_pos);
    return ListC;
}
bool operator == (List aryList1, List aryList2)
{
    if(aryList1.size() == aryList2.size()){
        int orig_pos1 = aryList1.getPos();
        int orig_pos2 = aryList2.getPos();
        aryList1.first();
        aryList2.first();

        for(int i = 0; i < aryList1.size(); i++, aryList1.next(), aryList2.next()){
            if(aryList1.getElement() != aryList2.getElement()){
               aryList1.setPos(orig_pos1);
               aryList2.setPos(orig_pos2);
               return false;
            }
        }
        aryList1.setPos(orig_pos1);
        aryList2.setPos(orig_pos2);
        return true;
    }
    return false;
}
List List::operator = (List& aryListB)
{
    int orig_pos = aryListB.getPos();
    aryListB.first();
    first();
    arySize = 0;

    for(int i = 0; i < aryListB.size(); aryListB.next(), this->next(), i++){
        this->aryList[i] = aryListB.getElement();
        this->arySize++;
    }
    pos = orig_pos;
    aryListB.setPos(orig_pos);
    return aryListB;
}

void open_outfile(ofstream& outfile)
{   
    outfile.open("General_List.txt");
    if (!outfile) {
        cout << "outfile open failure!";
        exit(0); 
    }
}
void close_outfile(ofstream& outfile)
{   
    outfile.close();
    if (outfile.is_open()) {
        cout <<"outfile is still open" << endl;
    }
}

int main()
  {
  	List a,b;  int endit;

	for (int i=1;i<=20;i++)
	   a.insertAfter(i*2);
	cout << "List a : " << endl;
    	cout << "  "  << a << endl;
	cout << "Number of elements in a - " << a.size() << endl;

	for (int i=1;i<=10;i++)
	   b.insertBefore(i*3);
	cout << "List b : " << endl;
    	cout << "  "  <<  b << endl;
	cout << "Number of elements in b - " << b.size() << endl;

	if ( a == b )
	    cout << "List a & b are equal" << endl;
	  else
	    cout << "List a & b are Not equal" << endl;

	a.first();
	b.first();
	cout << "First elmenet in list a & b: " << a.getElement() << ", "
				       << b.getElement() << endl;
	a.last();
	b.last();
	cout << "Last elmenet in list a & b: " << a.getElement() << ", "
				     << b.getElement() << endl;
					 
	cout << endl << endl << " Start of new stuff" << endl;

	b.clear();
	cout << "Empty List b:  " << b << endl;

	if ( a == b )
	    cout << "List a & b are equal" << endl;
	  else
	    cout << "List a & b are Not equal" << endl;

	for (int i=1;i<=10;i++)
	   b.insertBefore(i*5);
	cout << "List b : " << endl << b << endl;

	a.setPos(5);
	b.first();
	for ( int i=1; i<4; i++)
	{
	   a.erase();
	   b.replace(i);
	   b.next();
	}

	cout << "Modified Object 'a' (shorter) " << endl;
    	cout << "List a: " << a << endl;
	cout << "Modified Object 'b' " << endl;
    	cout << "List b: " << b << endl;

	List c(b);
	cout << "Copy Constructor c(b)" << endl;
    	cout << "List b : " << b << endl;
    	cout << "List c : " << c << endl;

	if ( c == b )
	    cout << "List c & b are equal" << endl;
	  else
	    cout << "List c & b are Not equal" << endl;


	List e;
	e = c;
	cout << "Object 'c' assigned to Object 'e':" << endl;
    	cout << "List c : " << c << endl;
    	cout << "List e : " << e << endl;

    	List d;
	d=a;
	
	d.first();
	endit = d.size();
	for ( int i = 1; i < endit; d.next(), i++)
	{
		d.insertBefore(d.getElement()*(-2));
		d.next();
	}
	cout << "Results after some Replaces on d " << endl;
    	cout << "List d : " << d << endl;

	a.first();
	endit = a.size();
	for ( int i = 1; i < endit; a.next(), i++)
	{
		a.replace(a.getPos()+a.getElement());
		a.next();
	}
	cout << "Results after some weird stuff on list a" << endl;
    	cout << "List a : " << a << endl;

    	List alist(b);
    	alist.clear();
    	for (int i=1;i<=10;i++)
	   alist.insertAfter(i);
	alist.first();
	cout << "New List alist with positions above: " << endl;
    	for (int i=1;i<=10;i++) {
		cout << setw(5) << alist.getPos();
		alist.next();
	}
	cout << endl;
	alist.first();
	for (int i=1;i<=10;i++) {
		cout << setw(5) << alist.getElement();
		alist.next();
	}
	cout << endl;
	
	cout << endl << "  check out boundary conditions" << endl;
	List sq;
	cout << "number of elements in empty sq list = " << sq.size() << endl;
	sq.first();
	sq.erase();
	sq.setPos(5);
	cout << "empty sq values " << sq << endl;
	sq.insertBefore(777);
	cout << "sq values " << sq << endl;
	sq.next(); sq.next();
	cout << "sq.getElement() = " << sq.getElement() << endl;
	cout << "sq list = " << sq << endl;
	return 0;
  }