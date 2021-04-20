

depth first search 
    with current state passed on stack

recurse(nextNode, CurState)
{
    if node = null return true

    for (all possibilities)
    {
        state[node] = X;
    
        if (recurse(node->next, CurState + 1) ==true)
            return true;

        // val = recurse(node->next, CurState + 1)
        // if (val > max) max = val
        
        state[node] = 0; // restore old state
    }

    // append val to curMax and return
    return false;
}

==========================


