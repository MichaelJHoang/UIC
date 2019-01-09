Name: Jon-Michael Hoang

-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)

    YES

Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?

    I added numLeft and numRight int variables inside the bst data structure
    to help process the geq and leq functions.

-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  

    The functions that were needed to be modified as a result of the augmentations from
    the previous function are num_geq (), _num_geq (), num_leq (), and _num_leq ().

-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?

    How I ensured that the runtime remained the same for each function was that I
    made sure that the "tracker" stayed within range and did not touch any
    unecessary nodes.

-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


to_vector level of completion:  4.5  


-----------------------------------------------
get_ith level of completion:  5  

    How did you ensure O(h) runtime?

    ANSWER: I ensured O(h) runtime by only traversing the leftmost branch of the
            tree and keeping track of the necessary amount of steps.

-----------------------------------------------
num_geq level of completion:  5  

    How did you ensure O(h) runtime?

    ANSWER: I ensured O(h) runtime by checking to see if the target is greater than
            or equal to the value.
            
            By creating a helper helper function which takes in a bst_node, the target,
            and the pass-by-referenced counter, I pretty much made sure that the
            current node stayed within range and accounted the node for it.

-----------------------------------------------
num_leq level of completion:  5

    How did you ensure O(h) runtime?

    ANSWER: I ensured O(h) runtime by checking to see if the target is lesser than
            or equal to the value.
            
            By creating a helper helper function which takes in a bst_node, the target,
            and the pass-by-referenced counter, I pretty much made sure that the
            current node stayed within range and accounted the node for it without
            traversing over any unecessary nodes.

-----------------------------------------------
num_range level of completion:  5

    How did you ensure O(h) runtime?

    ANSWER: I ensured O(h) runtime by checking to see if the target is greater than
            the max. If so, return.
            
            By creating a helper helper function which takes in a bst_node, the target,
            and the pass-by-referenced counter, I pretty much made sure that the
            current node stayed within range and accounted the node for it without
            traversing over any unecessary nodes.

-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: 1.5


Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?

How I tested my solutions was that I ran it through test text files. Not only that,
I traced it down on pen and paper to make sure that they are correct. The tests consisted
majorily of arbitrary integers values and several cases where there are chars instead.
However, because of the arbitrary values, tests cases that I wish I had done are
ones where they aren't chosen out of the blue but rather chosen specifically to
search for faults.
