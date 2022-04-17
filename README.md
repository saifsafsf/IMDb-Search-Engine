# IMDb-Search-Engine
Search Engine to search anything from the given IMDb dataset.

### How to Run
Run Movie_new.cpp

### Structure
Organizes the given IMDb dataset into the following structures:
- HashMap
- Binary Search Tree

The keys for the hashmaps are the first letter of the name of any entity. For instance, key A has all the objects starting with the letter A attached to it.  
The values for these hashmaps are the Binary Search Trees conataining objects of a certain entity in a sorted way.  
A similar structure is shown below using AVL Trees instead of BST:  

![Picture1](https://user-images.githubusercontent.com/73883918/163707789-a2768477-3e95-442d-a418-bd24d0aaff0a.png)

Now there are many HashMaps in this program, each structured on a different basis such as:
- Map storing movies with BST sorted name-wise.
- Map storing movies with BST sorted genre-wise.
- Map storing movies with BST sorted release-year-wise.
- Map storing actors with BST sorted name-wise.
- Map storing directors with BST sorted name-wise.
- A BST storing all movies sorted IMDb rating-wise.

The program shows results for partial search queries too.

## Happy Coding!
