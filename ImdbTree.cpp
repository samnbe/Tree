//Worked with Trevor Gross :)

#include <iostream>
#include <string>
#include <vector>
#include "Bridges.h"
#include "DataSource.h"
#include "BSTElement.h"
#include <queue>
#include <stdlib.h>
using namespace std;
using namespace bridges;

/*
  Step 1: Get the Bridges USER ID and API KEY for your program
          by creating an account and signing up (You can use any
          email): https://bridges-cs.herokuapp.com/signup

  Step 2: User ID (Username) and Key (API Sha1 Key) can be
          found under Profile on the top left
*/

BSTElement<string, string>* insertIntoBST(string actor, string movie, BSTElement<string, string> *root) {
    if (root == nullptr)
    {
        root = new BSTElement<string, string>(actor);
        root->setLabel(movie);
        return root;
    }

    if (actor > root->getKey())
    {
        root->setRight(insertIntoBST(actor, movie, root->getRight()));
    }
    else
    {
        root->setLeft(insertIntoBST(actor, movie, root->getLeft()));
    }

    return root;
}

int main(int argc, char **argv) {

    // Step 3: Test if the following print statement is being run
  cout << "Bridges: IMDB Data in a BST\n";

    // Step 4: Add your User ID and API Key as secrets on Replit

    // Step 5: Print your User ID and API Key from secrets to the console
    // to test if secrets were properly loaded
  
  char* UserID = getenv("User ID");
  char* APIKey = getenv("API Key");
  cout << "User ID: " << UserID << endl;
  cout << "API Key: " << APIKey << endl; 
  
    /*
     Step 6: Create a Bridges object by uncommenting the next line
     and inserting the values from steps 1 and 2
    */
  Bridges bridges(1, UserID, APIKey);

    /*
       Step 7: Import IMDB data into a vector<ActorMovieIMDB> by
               referring to the Bridges IMDB documentation:
               https://bridgesuncc.github.io/tutorials/Data_IMDB.html
    */
  bridges.setTitle("Accessing IMDB Data");
  DataSource ds (&bridges);
  vector<ActorMovieIMDB> actor_list = ds.getActorMovieIMDBData(1814);
  
    // cout << "Actor-Movie Data:" << endl
		// << "\tActor: " << actor_list[0].getActor() << endl
		// << "\tMovie: " << actor_list[0].getMovie() << endl;
  
    /*
       Step 8: Open the file "insertIntoBST.txt" and copy the provided
               function for inserting an actor/movie pair into a BST.
               Paste the function into this file above your "main" function.
    */

    /*
       Step 9: Use the insertion function from the previous step to insert
               any 100 actor/movie pairs into a Bridges BST. Refer to the
               Bridges IMDB documentation:
               https://bridgesuncc.github.io/tutorials/Data_IMDB.html
    */
  //BSTElement<string, string> *root = new BSTElement<string, string>;
  // insertIntoBST(actor_list[0].getActor(), actor_list[0].getMovie(), root);

  BSTElement<string, string>* root = nullptr;
  vector<BSTElement<string, string>*> ptrvec; 
  
  for(int i = 1; i <= 100; i++){
    vector<ActorMovieIMDB> addList = ds.getActorMovieIMDBData(i);
    if(i == 1){
      root = insertIntoBST(addList[i-1].getActor(), addList[i-1].getMovie(), nullptr);
    }
    else{
      ptrvec.push_back(insertIntoBST(addList[i-1].getActor(), addList[i-1].getMovie(), root));
    }
  }

    /*
       Step 10: Visualize this tree by referring to the Bridges BST documentation:
               https://bridgesuncc.github.io/tutorials/BinarySearchTree.html
    */
    /*
       Step 11: Color each level of the tree using a level-order traversal.
               Every node in a given level should have the same color.
               Do not use the same color in two consecutive levels. A starter
               queue has been provided in case you wish to use an iterative
               implementation of BFS.

               Refer to the Bridges BST Styling documentation:
               https://bridgesuncc.github.io/tutorials/BinarySearchTree.html

    */
  

  
  queue<BSTElement<string, string> *> q;
  q.push(root);
  int count = 0;
  int level = 0;
  int prevChildCount = 1;
  int childCount = 0;

  while(!q.empty()){
    
    BSTElement<string, string>* node = q.front();

    if(node->getLeft() != nullptr){
      q.push(node->getLeft());
      count++;
      childCount++;
    }
    else if(node->getLeft() == nullptr){
      count++;
    }
    
    if(node->getRight() != nullptr){
      q.push(node->getRight());
      count++;
      childCount++;
    }
    else if(node->getRight() == nullptr){
      count++;
    }

    if(level % 2 == 0){
      node->setColor("black");
    }
    else{
      node->setColor("yellow");
    }

    if(prevChildCount * 2 == count){
      level++;
      prevChildCount = childCount;
      count = 0;
      childCount = 0;
    }
    
    q.pop();
  }



  
  //store child and level then store child and level + 1

    /*
      Step 12: Visualize the updated tree. Comment out or remove the old
               visualization code from Step 8
    */
  bridges.setDataStructure(root);
  bridges.visualize();
  

    return 0;
}