#include<iostream>
#include<conio.h>
#include<fstream>
using namespace std;

template<class T>
class Node
{
public:

	Node(T value = NULL, Node<T> *_next = nullptr)
	{
		data = value;
		next = _next;
	}

	//data members
	T data;
	Node<T> * next;
};
template<class T>
class Stack
{
public:
	Stack(Node<T> * _top = nullptr)
	{
		top = _top; //last element added 
	}
	~Stack()
	{
		Node<T>*temp;
		while (top != 0)
		{
			temp = top;
			top = top->next; //update top to next element 
			delete temp;
		}

	}
	bool IsEmpty()
	{
		if (top == nullptr)		   //if stack is empty 
			return true;
		else
			return false;
	}
	bool push(const T & val)
	{
		if (IsEmpty() == true) //empty list 
		{
			Node<T> *newPush = new Node<T>(val); //creating new node 
			top = newPush;  //top is pointing to newly added element
			return true;
		}
		else
		{
			Node<T> *newPush = new Node<T>(val, top); //creating new node 
			top = newPush;  //top is pointing to newly added element
			return true;
		}
		return false;
	}
	bool pop(T & val)
	{
		if (IsEmpty())
			return false;
		else	   //if stack has some data
		{
			val = top->data;			//updaing parameter val				 
			Node<T>* temp = top;
			top = temp->next;  //pointing top to next element of stack
			delete temp;
			return true;
		}
	}
	T topValue()
	{
		return top->data;
	}
	void print()
	{
		for (Node<T>* temp = top; temp != 0; temp = temp->next)
		{
			cout << temp->data << "\t";
		}
		cout << endl;
	}
private:
	Node<T> * top;
};
class XML
{
	friend 	ostream& operator<<(ostream &out, XML x);

private:
	char * tag;
	int line;
public:
	XML(char* _tag = '\0', int _line = 0)
	{
		setTag(_tag);
		line = _line;
	}

	void setTag(char * arr)
	{
		if (arr != 0)
		{
			int i = 0;
			int  size = strlen(arr);
			tag = new char[size];
			for (i = 0; arr[i] != 0; i++)
			{
				tag[i] = arr[i];
			}
			tag[i] = 0;
		}
		else
			tag = 0;
	}
	const XML& operator=(const XML &rhs)
	{
		if (&rhs != this) //check for self assignment
		{
			setTag(rhs.tag);  //update tag
			line = rhs.line;  //update line
		}
		return *this;
	}
	void Print()
	{
		cout << tag << '\t' << line << endl;
	}
	bool operator==(const XML &rhs)
	{
		if (rhs.tag != 0)
		{
			if (strcmp(tag, rhs.tag) == 0)
				return true;
		}
		else
			return false;
	}

	XML checkXMLFile(Stack<XML>& S)
	{
		ifstream fin;
		char buffer[100];
		fin.open("Correct.txt");
		//fin.open("Error.txt");
		if (fin.is_open())
		{
			//For header or line number 1
			line = 1;							//updating line number
			int quote = 0;
			fin.getline(buffer, 100, '\n');
			XML temp(buffer, 1);
			int i = 0;
			int size = strlen(buffer) - 1;							  // stringlength -1 becuse last character is null
			while (buffer[i] != '<')						  //if any space before <
				i++;
			if (buffer[i] == '<')					   //checking  <
				i++;
			else
				return temp;
			if (buffer[size] == '>')				  //checking  >
				size = size - 1;
			else
				return temp;

			if (buffer[i] == buffer[size])  //check both ? from start and end
				i++;
			else
				return temp;
			size--;				 //now size is 2 less from original string length because ?> are present
			while (i <= size)
			{
				if (buffer[i] == '"')
					quote++;
				i++;
			}
			if (quote % 2 != 0)	 //if even quotes then XML tag is correct
			{
				cout << "Quotes Mismatch Error." << endl;
				return temp;
			}

			//from line 2 to onward
			char buffer2[100];
			i = 0, size = 0;
			while (!fin.eof())
			{
				if (i == size) //check for complete iteration of a line
				{
					fin.getline(buffer, 100, '\n');		    //read line
					line++;	   //updating line
					i = 0;
					size = strlen(buffer);	  //updating size
					quote = 0;
					this->setTag(buffer);
				}
				while (i < size)
				{
					while (buffer[i] != '<'&& i < size)  //contents 
					{
						if (buffer[i] == '"')						//check for quotes
							quote++;
						i++;
					}
					if (quote % 2 != 0)											  //if even quotes then XML tag is correct
					{
						cout << "Quotes Mismatch Error ";
						return *this;
					}
					if (buffer[i] == '<'&& i < size)						 //check for tag
					{
						if (buffer[i + 1] == '/')	 //check for closing tag 
						{
							i++;   //move from / of closing tag 
							i++;
							int k = 0;
							while (buffer[i] != '>'&&i < size)
							{
								buffer2[k] = buffer[i];							//copying closing tag in buffer 2
								i++; k++;
							}
							buffer2[k] = 0;
							if (i == size && buffer[i] != '>')
							{
								this->tag = S.topValue().tag;  //updating tag
								this->line = S.topValue().line;	 //updating line
								return S.topValue();
							}
							i++;
							XML pop;
							if (!S.IsEmpty())  //if there is anything on stack then pop
							{
								S.pop(pop);
							}
							else
								return pop;
							if (strcmp(pop.tag, buffer2) == 0)	   //if tags match 
								break;
							else
								return pop;
						}
						else if (buffer[i] == '<' && buffer[i + 1] == '!' && buffer[i + 2] == '-' && buffer[i + 3] == '-')  //Check for comments
						{
							i = i + 4;
							while (buffer[i] != '-' && buffer[i + 1] != '-' && buffer[i + 2] != '>' && i < size)
								i++;
							i = i + 3;
						}
						else		 //if starting tag
						{
							i++;
							int k = 0;
							while (buffer[i] != '>'&& i < size && buffer[i] != ' ')	 //read tag before space in case tag has some attributes else >
							{
								buffer2[k] = buffer[i];
								i++; k++;
							}
							buffer2[k] = 0;
							i++;
							temp.setTag(buffer2); //updating temp tag
							temp.line = line;	  //updating temp line
							S.push(temp);
						}
					}
				}
			}
			if (S.IsEmpty())
				return 0;
		}
		else
			cout << "File Not Find." << endl;
	}
};
ostream& operator<<(ostream &out, XML x) //friend of XML
{
	if (x.tag != 0)
	{
		cout << "Error is at line number:\t" << x.line << endl;
		cout << "Text at this line is:\t" << endl << x.tag;
	}
	else
		cout << "No error found.";
	return out;
}
void main()
{

	Stack<XML> S;					//creating stack
	XML error;
	cout << error.checkXMLFile(S);	 //function call
	_getch();
}