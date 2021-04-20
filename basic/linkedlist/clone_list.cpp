
problem 35 karumanchi

list with random and next ptr  has to be cloned


Step1:
// save random of oldNode in newNode
newNode->next = oldNode->random
oldNode->random = newNode
// newNode->random is not set

Step2:
//set random of newNode
newNode->random = newNode->next->random

Step3:
//reset random of old & next of newNode
oldNode->random = oldNode->random->next
newNode->next = oldNode->next->random

