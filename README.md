# SCUdatabase

This is repository for homeworks of database course in SCU.

Each homework assignment is in its own branch.

## Student Name: 薛智涵

## Student Number: 2019141460081

### Teacher: 杨宁

[Homework0: Matrix](https://github.com/milky245/SCUdatabase/tree/homework0_matrix)

[Homework1: northwind](https://github.com/milky245/SCUdatabase/tree/Homework1_northwind)

[Homework2: Q&A](https://github.com/milky245/SCUdatabase/tree/homework2_Q%26A)


TASK 1 - B+TREE PAGES
You need to implement three Page classes to store the data of your B+Tree tree.
B+Tree Parent Page
B+Tree Internal Page
B+Tree Leaf Page

TASK 2 - B+TREE DATA STRUCTURE
Your B+Tree Index could only support unique key. That is to say, when you try to insert a key-value pair with 
duplicate key into the index, it should not perform the insertion and return false

TASK 3 - INDEX ITERATOR
You will build a general purpose index iterator to retrieve all the leaf pages efficiently. The basic idea is to 
organize them into a single linked list, and then traverse every key/value pairs in specific direction stored 
within the B+Tree leaf pages. Your index iterator should follow the functionality of Iterator defined in c++11, 
including the ability to iterate through a range of elements using a set of operators (with at least the 
increment and dereference operators).
