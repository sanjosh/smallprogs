
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# define NO_OF_CHARS 256
# define bool int
 
/* Function removes duplicate (not necc. consecutive) characters from the string
   This function work in-place and fills null characters
   in the extra space left */

char *removeDups(char *str)
{
  bool bin_hash[NO_OF_CHARS] = {0};
  int source = 0, target = 0;
  char temp;   
 
  /* In place removal of duplicate characters*/ 
  while(*(str + source))
  {
    temp = *(str + source);
    if(bin_hash[temp] == 0)
    {
        bin_hash[temp] = 1;
        if (target != source)
        {
            *(str + target) = *(str + source);
            printf("copying %d to %d\n ", source, target);
        }
        target++;        
    }
    source++;
  }     
 
  /* After above step string is stringiittg.
     Removing extra iittg after string*/       
  *(str+target) = '\0';  
   
  return str;
}
 
/* Driver program to test removeDups */
int main(int argc, char* argv[])
{
    char* str = strdup(argv[1]);
    printf("%s\n", removeDups(str));
    getchar();
    return 0;
} 
