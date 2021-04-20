

TODO

function BWT (string s)
   create a table, rows are all possible rotations of s
   sort rows alphabetically
   return (last column of the table)
 
function inverseBWT (string s)
   create empty table 
       
   repeat length(s) times
       // first insert creates first column
       insert s as a column of table before first column of the table
       sort rows of the table alphabetically
   return (row that ends with the 'EOF' character)


 The last column tells you all the characters in the text, so just sort these characters alphabetically to get the first column. Then, the first and last columns (of each row) together give you all pairs of successive characters in the document, where pairs are taken cyclically so that the last and first character form a pair. Sorting the list of pairs gives the first and second columns. Continuing in this manner, you can reconstruct the entire list. Then, the row with the "end of file" character at the end is the original text. Reversing the example above is done like this:
