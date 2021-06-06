
**QUESTION: Design a C++ program that use a stack for matching tags and quotes in XML eXtensive Markup Language.**  

**Your program will get an XML code in an input file and it should figure out if tags and quotes are properly matched or not using stack. In case the tags are not properly matched then your program should report following** 

1) **the first error,**  
1) **print the mismatched tag and**  
1) **inform the line number where the starting tag occurred.**   

**What is XML?** XML is a markup language somewhat like HTML. It was designed to store and transport data. XML is just information wrapped in user defined tags which is both human- and machine-readable. The XML language has no predefined  tags  like  html.  The  tags  are  "invented"  by  the  author  of  the  XML  document.  For  details  see [https://www.w3schools.com/xml/xml_whatis.asp ](https://www.w3schools.com/xml/xml_whatis.asp)



|<p><?xml version="1.0" encoding="UTF-8"?> </p><p><note> </p><p>`  `<to>Tove</to> </p><p>`  `<from>Jani</from> </p><p>`  `<heading>Reminder</heading> </p><p>`  `<message>Don't forget me this weekend!</message> </note>**  </p>|
| - |
|<p>In above example  </p><p>**<?**xml version="1.0" encoding="UTF-8"**?>** </p><p>This is XML prolog (header). It starts with <? and ends with ?>. The header should come in the start of the document. </p>|
|<note>, <from>, <heading> and <message> are user defined tags and each must have a corresponding ending tag.  |
**Your program should handle the following features of XML:** 

1. **xml prolog (xml header)** 
1. **xml tags (xml elements). The xml tags are case sensitive.** 
1. **xml attribute**  
1. **xml comments, start with <!--  and ends with -->** 

**Consider another example**  

|<p><?xml version="1.0" encoding="UTF-8"?> <bookstore> </p><p>`  `<book category="cooking"> </p><p>`    `<title lang="en">Everyday Italian</title>     <author>Giada De Laurentiis</author> </p><p>`    `<year>2005</year> </p><p>`    `<price>30.00</price> </p><p>`  `</book> </p><p>`  `<book category="children"> </p><p>`    `<title lang="en">Harry Potter</title> </p><p>`    `<author>J K. Rowling</author> </p><p>`    `<year>2005</year> </p><p>`    `<price>29.99</price> </p><p>`  `</book> </p><p></bookstore>** </p>|
| :- |
|<p>In the example above: </p><p><title>, <author>, <year>, and <price> have **text content** because they contain text (like 2005). <bookstore> and <book> have **element contents**, because they contain elements. </p><p><book> has an **attribute** (category="children"). </p>|
|<p>**Note that Attribute values must always be quoted. Either single or double quotes can be used.** </p><p>**Your program should keep track that attributes have opening and closing quotes.** </p>|
***Your code will have template-based Node class and template-based Stack class. Implement stack using singly linked list.***   



|<p>template<class T> class Node { </p><p>public: </p><p>Node()  </p><p>T data; Node<T> \* next; </p><p>};</p>|<p>template<class T> </p><p>class Stack { </p><p>public: </p><p>Stack() ; </p><p>~Stack(); </p><p>bool IsEmpty(); </p><p>bool push(const T & val); bool pop(T & val); </p><p>T top(); </p><p>void print(); </p><p>private: </p><p>Node<T> \* top; };</p>|
| :- | - |
|<p>**Create XMLData class**  </p><p>**Think about its attributes carefully** </p>|<p>Void main(){ </p><p>`   `Stack<XMLData> S1; } </p>|
**CODE DESIGN GUIDLEINES** 

- Do template-based programming 
- Code should be properly intendent and commented (2 marks for this) 
- Make sure there are no memory leaks or dangling pointers 
- Don’t cheat or take too much unnecessary help from your friends 
