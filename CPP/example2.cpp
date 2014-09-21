#include <stdio.h>
#include <stdlib.h>

void normal(char* stuff) {
// This function receives a pointer to char. This may well be simply a pointer
// to a single char, or, a pointer to a collection of consecutive chars in mem-
// ory, which is what we define as a string in pure C.
    char c = *stuff;
    // Lets dereference the pointer, so we get the current char it points at
    if(!c) return;
    // This can only be true if x is 0, which is the NULL character that termi-
    // nates strings, so this is the point that breaks the recursion.
    printf("%c", c);
    // If it gets here, lets print the current character.
    normal(stuff + 1);
    // Now lets recurse again, moving the pointer one position to the right!
}

void inverse(char* stuff) {
// This function receives a pointer to char. This may well be simply a pointer
// to a single char, or, a pointer to a collection of consecutive chars in mem-
// ory, which is what we define as a string in pure C.
    char c = *stuff;
    // Lets dereference the pointer, so we get the current char it points at
    if(!c) return;
    // This can only be true if x is 0, which is the NUL character that termi-
    // nates strings, so this is the point that breaks the recursion.
    inverse(stuff + 1);
    // Now lets recurse again, moving the pointer one position to the right!
    printf("%c", c);
    // If it gets here, lets print the current character. The deal with this
    // is that it prints after the recursive call, so it will reach the bottom
    // of the recursion, and only start printing once it starts backtracking!
}

void swap(int *n, int *m) {
// This function receives to pointers to integers, to swap them both without
// having to do this procedure everywhere inside a main code body. We get the
// pointers or their memory addresses, and we dereference those to do the swa-
// pping, affecting them in the original scope they were declared in.
    int temp;
    temp = *n;
    *n = *m;
    *m = temp;
}

struct Node {
// Classical definition of a Linked List, a structure/object holding a value
// or certain values, and a pointer to the next object. In Java this doesn't
// has to be a pointer (I think every object in Java is implicitly a pointer,
// because simply assigning an object to another will have both affecting the
// same object, in Java you need DEEP, HARD copies of objects, or cloning).
    int value;
    Node *next;
};

void traverseLL(Node *n) {
// Receive a pointer to a node as parameter, to print it backwards, do the same
// than before with the strings, put the printf after the recursive call, so it
// will only start printing once it has backtracked after reaching the end.
    if(!n) return;
    printf("%d ", (*n).value);
    traverseLL((*n).next);
}

// prev head  next
//   |    |    |
//   v    v    v
// NULL  [0]->[1]->[2]->NULL
//
//      prev head  next
//        |    |    |
//        v    v    v
// NULL<-[0]  [1]->[2]->NULL
//
// From: http://stackoverflow.com/a/14804810/1135812 :-)
Node* reverseLL(Node *head) {
    if(!head) return NULL;
    Node *prev = NULL;
    // Building from the left
    Node *next;
    // Putting a new head to the right
    while(head) {
    // While there's a head...
        next = head->next;
        // The next head will be the node to the right
        head->next = prev;
        // The next node of the current head will be the previous node
        // ...
        // Now, shift it
        prev = head;
        // The current head will now be the previous node
        head = next;
        // The new head will be the next node
    }
    // In the end, the head will be sitting at the originally ending NULL
    // pointer, and the reversed linked list will have the previous node.
    return prev;
}

void clearLL(Node *head) {
    if(!head) return;
    clearLL(head->next);
    free(head);
    // To free memory, free from the back to the top, since freeing from
    // left to right will free the head pointer, but not its recursive
    // nodes, while this assures that the cleaning is done at all nodes.
    // If we cleared the first head, then we'll have lost the address of
    // the next node, so thats memory that's being used without any add-
    // ress to get to it, the same for its next node, and the next, and...
}

int main() {
    printf("NOW YOU WILL LEARN SOME CRAZY STUFF, C STYLE!\n\n\n");
    // printf is the preferred method to print stuff in C, and it allows for
    // formatting! There are special characters like \n, which inserts a new
    // line, or \t, which inserts a tabulation character! For printing, trust
    // in printf, its fast, its formattable, its cooler than cout! The only
    // good thing about cout is that it doesn't needs types, but that is just
    // you being lazy not putting the types of the printed stuff in printf! 
    printf("#### Strings C Style ####\n");
    // Lets learn about Strings, C Style! (C++ makes this so much easier...)
    char stuff[50];
    // There is no 'string' type in C, there's char, and char pointers/arrays.
    // This could've been declared as stuff[50] (for a specified limit and
    // known length) or as *stuff (simply as a pointer). Having a limit is
    // good for buffered reading, to read something by chunks in case its
    // too big to handle in just a single shot!
    printf("Write a word and press enter: \n");
    scanf("%49s", stuff);
    // scanf is the good old partner of printf. It will detail a formatted
    // string to read from standard input, and then a list of pointers to var-
    // iables to store the read values in them. In the case of 'strings' this
    // isn't necessary, because the array of characters is like a pointer 'by
    // definition'. When you add 'n' to a pointer, you move it n positions in
    // memory. Doing stuff[42] is like moving the head pointer of the 'stuff'
    // array, 42 positions (each one with sizeof(char)), or like 'stuff + 42',
    // successfully pointing to the 42nd position, which by dereferencing the
    // pointer we can gain access to whatever its stored in the 42th position.
    // ...
    // In strings, a character is needed for the null terminator, so for a 50
    // sized array, only 49 can be characters, the remainding reserved space
    // is for the \0. If 'stuff' was declared not as an array but as '*stuff', 
    // then no number is speficied here for the amount of characters to read.
    printf("The string in normal order is: ");
    normal(stuff);
    // Print normally the read string recursively! Refer to the 'normal'
    // function above to see how it works.
    puts("");
    // puts prints a string with a newline included
    printf("The string in inverse order is: ");
    inverse(stuff);
    // Print the inverse of the read string recursively! Refer to the 'inverse'
    // function above to see how it works
    puts("");
    // puts prints a string with a newline included
    printf("The size limit for this string is: ");
    printf("%lu\n", sizeof(stuff)/sizeof(stuff[0]));
    // This will get the size in bytes of the array, then divide by the size
    // of the first element, to get the number of elements. Mind that even if
    // a string of less than 50 characters is read, this will still report
    // 50 elements, with a lot of wasted blank positions in memory.
    // ...
    // ...
    // ...
    // ...
    // ...
    // ...
    // ...
    printf("\n\n\n#### Numbers C Style ####\n");
    // Now, lets learn about Numbers, C Style!
    int n, m;
    // Lets declare two integers, n and m.
    printf("Input two integer numbers: ");
    scanf("%d %d", &n, &m);
    // In this case, we need to get the addresses to n and m, only 'strings'
    // are excluded from this because of their 'pointer nature'.
    printf("n = %d, m = %d\n", n, m);
    printf("n + m = %d, n * m = %d\n", n+m, n*m);
    // Now, lets swap values using pointers!
    swap(&n, &m);
    // Refer to the swap function above to see how this beauty works
    printf("We've just swapped the values! now they are...\n");
    printf("n = %d, m = %d\n", n, m);
    // Indeed they are swapped now!
    double x, y;
    // Now, lets declare two double numbers. These will hold rational numbers,
    // with double the amount of bits than floats, useful when you need lots
    // of precision (but still, computers tend to make results of operations
    // regarding this kind of numbers awfully imprecise, so try to keep them
    // to a minimun if possible).
    printf("Now input two rational numbers: ");
    scanf("%lf %lf", &x, &y);
    // lf for long float. f for float. u for unsigned. l for long. i for int,
    // s for string, c for char, lu for long unsigned, ll for long long...
    printf("x = %.3lf, y = %.3lf\n", x, y);
    // .3 modifier is to control decimal places, it will cut and round there.
    // If a number has less than 3 decimal places, it will be padded with 0's.
    printf("x + y = %.3lf, x * y = %.3lf\n\n", x + y, x * y);
    // The same that we did before with the integers, a formated string, and
    // then a list of values to fit in that string's specifiers. There's much
    // more to specifiers than precision and type, like flags, widths, lengths,
    // so look that up here:
    // http://www.cplusplus.com/reference/cstdio/printf/
    // ...
    // ...
    // ...
    // ...
    // ...
    // ...
    // ...
    printf("\n\n\n#### Linked Lists C Style ####\n");
    // Linked lists, the good old data structure that contains a pointer to the
    // next one. Understanding how this works can allow you to implement more
    // 'complex' data structures using only structs and pointers, like trees,
    // graphs, stacks, queues, etc. The linked list is linear, can be double
    // linked, and its nice for using it to implement stacks and queues!.
    printf("Now input five integers, which will be put into a linked list:\n");
    Node *base = (Node *)(malloc(sizeof(Node *)));
    // When declaring a pointer, malloc must be used to allocate memory accor-
    // ding to the pointer's size, and then casting it to a pointer of this
    // type. If possible, after a pointer is no longer needed, try to free
    // the memory its using! This way you reduce memory leaking in a program.
    Node *llist = base;
    // We'll have a pointer called llist, a copy of the address to the first 
    // allocated block of memory, which was called base. We'll create the lin-
    // ked list advancing the base pointer, so we need to keep a record of what
    // it was originally pointing at.
    int i;
    // In C, iterator variables must be declared outside of the for.
    for(i = 0; i < 5; i++) {
        scanf("%d", &(base->value));
        // x->y is just a shortcut for (*x).y, or, dereference the x pointer,
        // and then access to its y value. In this case, we dereference the
        // base pointer, we access to its value, and then get the address to
        // this value, so we can use scanf with it.
        if(i + 1 < 5) {
        // If we are not at the last node yet
            base->next = (Node *)(malloc(sizeof(Node *)));
            // Allocate memory for a new node
            base = base->next;
            // Move the current pointer to the next node address
        }
    }
    base->next = NULL;
    // The last node will have a NULL as the next
    printf("Traversing the linked list we get this:\n");
    // Now, lets traverse the linked list, recursively! We'll use the original
    // copied pointer at the very first position of the linked list.
    traverseLL(llist);
    puts("");
    // Now the canonical exercise on linked lists, which is reversing them. A
    // 'trivial' solution is traversing it and putting its elements on a stack,
    // then creating a new list from scratch after popping every element on the
    // stack. But what if we don't have a explicit stack structure, but only ac
    // cess to other linked lists? As I said before, linked lists are nice for
    // implementing stacks, so thats kinda where I'm going, using a linked list
    // to create a structure that keeps putting stuff at the 'top'.
    llist = reverseLL(llist);
    printf("The list in reverse order is: \n");
    traverseLL(llist);
    puts("");
    clearLL(llist);
    // Remember to clear the space used by the Linked List
    printf("\n\n\nNOW YOU ARE A C WIZARD!.. kinda.\n");
}