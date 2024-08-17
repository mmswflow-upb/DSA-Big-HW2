# DSA-Big-HW2

This is the second big assignment in the data structures course (in C++). In the following, the solutions will be explained.

## Exercise One Solution Description

- We use **ifstream** to read words from a given index.in file, pushing them into a queue until our program reads a dot “.” , then we check if our queue contains more than 1 word:  

  - **Case A**: The queue contains only one word; we will write in a given output file the first letter of the word only.

  - **Case B**: The queue is empty; we write in the output file that no valid input was provided.

  - **Case C**: The queue contains more than 1 word; we loop through the queue using a while loop with the condition that our queue contains more than one word, removing the first word and comparing it with the new first word in the queue. We use a for loop to go through the characters of these 2 words comparing them until we find a mismatch. The maximum number of iterations of this for loop is the minimum length of the current 2 words that we’re comparing.


    - Once we find a mismatch, we check if the 2 characters have already been added into our directed graph. To do this we use a function called findInfo, which is a member of the **DiGraph** class, and it returns the index of the info inside the nodes’ array. If it’s not found, then it returns -1.



    - We’re also using a method called **expandDiGraph**, which is used to generate new directed graphs every time we add a **node**, so we don’t just create a single graph with a fixed number of nodes, instead we do it dynamically. It first copies all the nodes and edges from the old given graph and inserts them into the new graph, after which it inserts the new **node**. This function takes as input the pointer to the old graph and the new **node**’s information, and it returns a pointer to the new one.

    - We add the character/s that was/were not found in the graph, then we add an edge between the two characters, oriented towards the character from the first word in our current queue (the second word). Before adding the edge, we check whether an edge already exists between them so that we don’t add a second one, in order to prevent loops from forming in our graph.


- We open the given output file and start writing in it the connections between all nodes in our graph. We do this using a 2 nested for loops that go through the entire **adjacency matrix** of our **DiGraph**. Then we instantiate a stack in which we will store the characters in the correct order.

- The method **topologicalSort** is used to find the correct order of the characters in the given ancient alphabet. We first initialize an array of characters called **visited** to keep track of the **visited** nodes and we set all the entries to 0. In the **topSort** method we use a for loop to call **topologicalSortTraversal** for each unvisited **node** in our graph; we pass the graph, stack and **visited** array to our function as pointers.

- Our **topologicalSortTraversal** method receives a pointer to the graph, stack, **visited** array and an integer value called **indx** which represents the index of the current **node** in the graph’s array of nodes. It marks the current **node** as **visited**, then loops through its neighbors, if an unvisited neighbor is found, it calls itself, but with the index of the neighbor **node**. After the for loop, the method pushes the current **node**’s info into the stack. This recursive method will provide us with the correct order of characters which are stored inside a stack called sequence.

- Once we’ve found the correct order of the characters, we write them in the output file by popping them from the stack sequence.


## Exercise Two Solution Description

- Our **QuadTree** template class implementation consists of: A pointer to the information stored in the root of the current subtree, 4 pointers to the (potential) children nodes and a method called **preOrderTraversal** which displays the preorder traversal of our entire subtree.

- Counting the number of black pixels is done recursively using the method **countBlackPixels**. We pass a pointer to our **QuadTree**’s root, an integer representing the current level we’re at and we pass by reference an integer called **sum**. We first check if the current **node** contains any info, then we check if the current **node** is black or not, if it’s black we add to the current **sum**: 
**(1024 / 4^level)**; this is because our images have 1024 pixels, we divide them into 4 quadrants, and each quadrant can be further divided into other 4 and so on. If, however, the current **node** is of type **“p”**, we call the same method for every child **node** of the current **node**, with the level incremented by 1.

- Generating the **QuadTree** representations of images is done using a recursive method called **createTreeFromPreOrder**. It takes as input a pointer to the current **node** and we pass by reference the string **“s”** which contains the preorder traversal of our image. The first step is to store the first character from **“s”** into the current **node**. Secondly, we check if the length of **“s”** is equal to 1, if it’s 1 we return, else we continue. Thirdly, we check if the current **node** is of type **“p”**, in that case, for every child of the current **node**, we cut the first character in **“s”**, assign the pointer to the current child **node** a new **QuadTree** and finally we call the same method for the current child **node**. After adding the child nodes, we use the **normalize** method on the current **node**.

- Merging two **QuadTrees** is done using another recursive method called **mergeQuadTrees**.  We pass to it the pointers to the first and second **QuadTree** **(t1, t2)** and the pointer to our resulting **QuadTree** (**node**):

  - **“t1”** & **“t2”** are **NULL**, we set **node** equal to **NULL** and return.
  -	**“t1”** is **NULL** & **“t2”** isn’t **NULL**, we set **node** equal to **“t2”**.
  - **“t1”** is **NULL** & **“t2”** is **NULL**, we set **node** equal to **“t1”**.
  - Either **“t1”** or **“t2”** is a black **node**, we set **node**’s info to “b”.
  - **“t1”** is of type **“p”** & **“t2”** is white, we set **node** equal to **“t1”**.
  - **“t1”** is white & **“t2”** is of type **“p”**, we set **node** equal to **“t2”**.
  - Both **“t1”** & **“t2”** are white, we set **node**’s info to **“w”**.
  - Both **“t1”** & **“t2”** are of type **“p”**, we set **node**’s info to **“p”**, then we set the pointers to its children nodes equal to new **QuadTrees**, then we call the same method for all 4 children of all 3 **QuadTrees**. Finally, we call the **normalize** method.

- Displaying the images is done using a recursive method of the **QuadTree** class called **displayAllLevelsRec** which takes as input the current level. This method prints a number of dashes corresponding to the current level of the current **node**, then the **node**’s info. After printing the current **node**, it will check if it’s a **node** of type **“p”**, then it will call the method on all its 4 children.

- The method called **normalize** is a member function of the **QuadTree** class and it is used to check whether a **node** of type **“p”** has 4 child nodes of the same color **(b/w)**. In that case we remove them all, and replace the information stored in that **“p”** **node** with the color of its child nodes.


