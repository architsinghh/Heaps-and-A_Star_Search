#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;

template <class T>
class MinHeap {
    public:
    MinHeap (int d);
    /* Constructor that builds a d-ary Min Heap
        This should work for any d >= 2,
        but doesn't have to do anything for smaller d.*/
    

    ~MinHeap ();

    void add (T item, int priority);

    /* adds the item to the heap, with the given priority. */

    const T & peek () const;
    /* returns the element with smallest priority.  
    Break ties however you wish.  
    Throws an exception if the heap is empty. */

    void remove ();
    /* removes the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */

    bool isEmpty () const;
    /* returns true iff there are no elements on the heap. */


    void bubble_up();

    void trickle_down();


    struct node{
        int priority;
        T val;
        node(T val, int priority){
            this->val = val;
            this->priority = priority;
        }
    };

    private:
        // whatever you need to naturally store things.
        // You may also add helper functions here.
        vector<node> tree;
        int d;
    };

    template <class T>
    MinHeap<T>::MinHeap(int d){
        if(d < 2){
            throw out_of_range("d is less than 2");
        }
        else{
            this->d = d;
        }
    }
    /* Constructor that builds a d-ary Min Heap
    This should work for any d >= 2,
    but doesn't have to do anything for smaller d.*/

    template <class T>
    MinHeap<T>::~MinHeap(){

    }

    template <class T>
    void MinHeap<T>::add(T item, int priority){
        //creates node and inserts into MinHeap and calls bubble_up
        tree.push_back(node(item, priority));
        bubble_up();
    }
    /* adds the item to the heap, with the given priority. */

    template <class T>
    const T & MinHeap<T>::peek() const{
        //returns root
        if(isEmpty()){
            throw out_of_range("heap is empty");
        }
        else{
            return tree[0].val;
        }
    }
    /* returns the element with smallest priority.  
    Break ties however you wish.  
    Throws an exception if the heap is empty. */

    template <class T>
    void MinHeap<T>::remove(){
        if(isEmpty()){
            throw out_of_range("heap is empty");
        }
        
        //swaps root with the last value, pops original root value, and then calls trickle_down
        swap(tree[0], tree[tree.size()-1]);
        tree.pop_back();
        trickle_down();
    }
    /* removes the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */

    template <class T>
    bool MinHeap<T>::isEmpty() const{

        //checks if tree size is 0 and returns true if so
        if(tree.size() == 0){
            return true;
        }
        else{
            return false;
        }
    }
    /* returns true iff there are no elements on the heap. */

    template <class T>
    void MinHeap<T>::bubble_up(){
        int index = tree.size() - 1;
        //loops through entire minheap and bubbles up to right spot
        while(index > 0){
            //swaps values if priority of current node is less
            if(tree[index].priority < tree[(index-1)/d].priority){
                swap(tree[index], tree[(index-1)/d]);
                index = (index-1)/d;
            }
            //swaps values if it is a tie and word is less than parent
            else if(tree[index].priority == tree[(index-1)/d].priority && tree[index].val < tree[(index-1)/d].val){
                swap(tree[index], tree[(index-1)/d]);
                index = (index-1)/d;
            }
            else{
                break;
            }

        }
    }

    template <class T>
    void MinHeap<T>::trickle_down(){
        int index = 0;
        size_t currChild = 0;
        int smallestChild = currChild;
        //loops through each child to find smallest one
        for(int i = 0; i < d; i++){
            currChild = (index * d) + i + 1;
            //checks priority and sets smallest child
            if(currChild < tree.size() && tree[currChild].priority < tree[smallestChild].priority){
                smallestChild = currChild;                
            }
            //accounts for edge case when priority is same so smaller word is chosen
            if(currChild < tree.size() && tree[currChild].priority == tree[smallestChild].priority && tree[currChild].val < tree[smallestChild].val){
                smallestChild = currChild;
            }
            if(currChild >= tree.size()){
                break;
            }
        }
        //loops through minheap to put node at correct spot by trickling down
        while((tree[index].priority == tree[smallestChild].priority && tree[index].val > tree[smallestChild].val) || tree[smallestChild].priority < tree[index].priority){
            swap(tree[smallestChild], tree[index]);
            index = smallestChild; 
            for(int i = 0; i < d; i++){
                currChild = (index * d) + i + 1;
                if(currChild >= tree.size()){
                    break;
                }
                //checks priority and sets smallest child
                if(currChild < tree.size() && tree[currChild].priority < tree[smallestChild].priority){
                    smallestChild = currChild;                
                }
                //accounts for edge case when priority is same so smaller word is chosen
                if(currChild < tree.size() && tree[currChild].priority == tree[smallestChild].priority && tree[currChild].val < tree[smallestChild].val){
                    smallestChild = currChild;
                }
            
            }
                
        }
            
    }