
boolean solve(Node n) {
    if n is a leaf node {
        if the leaf is a goal node, return true
        else return false
    } else {
        for each child c of n {
            if solve(c) succeeds, return true
        }
        return false
    }
}

==================
backtracking using a stack

boolean solve(Node n) {
    put node n on the stack;
    while the stack is not empty {
        if the node at the top of the stack is a leaf {
            if it is a goal node, return true
            else pop it off the stack
        }
        else {
            if the node at the top of the stack has untried children
                push the next untried child onto the stack
            else pop the node off the stack

    }
    return false
}


boolean solve(Node n) {
    if n is a leaf node {
        if the leaf is a goal node {
           print n
           return true
        }
        else return false
    } else {
        for each child c of n {
            if solve(c) succeeds {
                print n
                return true
            }
        }
        return false
    }
}
