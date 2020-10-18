#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <set>
#include <iostream>

//
// These two type definitions are used to enforce type safety, and 
// to make the code easier to read. In addition they provide a 
// framework for extending it in the future by using a custom type.
//

typedef std::string CustomerId;
typedef std::string ProductId;

std::vector<CustomerId> getFriendListForUser(const CustomerId &user );
std::vector<ProductId> getPurchasesForUser(const CustomerId &user );

//
// This function returns a ranked list of recommendations 
// for a given user. It creates thist list by performing
// three steps.
//
// First, iterate over the friends, getting a list of products
// that each friend has purchased. A tally is kept for every
// product found this way.
//
// Second, identify all the products the user has purchased
// and remove them from the list - we aren't going to provide
// recommendations for things he or she has already purchased.
//
// Finally, sort the list of products, and use the resulting
// list to create the return value.
//
// To keep things simple, I'm not using C++11, sticking with
// the language definition circa TR1.
//
std::vector<ProductId> getRecommendations(const CustomerId &user)
{
  //
  // Iterate over the friends, getting a list of products that each
  // friend has purchased, and add each one to product_counts
  //
  std::map<ProductId,int> product_counts;
  std::vector<CustomerId> friends = getFriendListForUser(user);
  for ( size_t i = 0 ; i < friends.size() ; i++ ) {
    std::vector<ProductId> friend_purchases = getPurchasesForUser( friends[i] );
    for ( size_t j = 0 ; j < friend_purchases.size() ; j++ ) 
      product_counts[friend_purchases[j]]++; 
  }
  //
  // Now remove any products that the user has already purchased
  //
  std::vector<ProductId> user_purchases = getPurchasesForUser( user );
  for ( size_t i = 0 ; i < user_purchases.size() ; i++ ) {
    std::map<ProductId,int>::iterator ii = product_counts.find(user_purchases[i]);
    if ( ii != product_counts.end() )
      product_counts.erase(ii);
  }
  //
  // I know have a map of valid product counts that we want to return to the 
  // user. Problem - it is not sorted. Rather than explicitly sort, I will
  // copy it into a map, implicitly sorting it along the way.
  std::multimap<int,ProductId> sorted_products;
  for (std::map<ProductId,int>::iterator ii = product_counts.begin() ; 
       ii != product_counts.end();
       ii++ )
    sorted_products.insert(std::make_pair(ii->second,ii->first));
  //
  // Finally, place it in to a vector for return. Note that the
  // map is sorted in the reverse order that I want it to be.
  //
  std::vector<ProductId> result;
  for ( std::multimap<int,ProductId>::reverse_iterator ii = sorted_products.rbegin();
        ii != sorted_products.rend();
        ii++ )
    result.push_back(ii->second);
  return result;
}
//
// No unit test framework handy for this project, so I will 
// blunder through doing it manually. Main will call a batch 
// of test functions. These test functions will rely on 
// mocked copies of the two supplied library functions that 
// are initialized with some global data sets
//

//
// Mocked function for unit test, reads lists from the global
// variable initialized before a test
//
std::map<CustomerId, std::vector<CustomerId> > mockFriends;

std::vector<CustomerId> getFriendListForUser(const CustomerId &user )
{
  std::map<CustomerId, std::vector<CustomerId> >::iterator ii = mockFriends.find(user);
  if ( ii == mockFriends.end() )
    return std::vector<CustomerId>();
  else
    return ii->second;
}

//
// Mocked function for unit test, reads list from the global variable initialized before a test
//

std::map<CustomerId, std::vector<ProductId> > mockPurchases;

std::vector<ProductId> getPurchasesForUser(const CustomerId &user )
{
  std::map<CustomerId, std::vector<ProductId> >::iterator ii = mockPurchases.find(user);
  if ( ii == mockPurchases.end() )
    return std::vector<ProductId>();
  else
    return ii->second;
}

//
// Verify that nothing bad happens and we get the expected 
// results with empty data.
//
void test_00()
{
  std::cout << "Test 00 - empty dataset\n";
  mockFriends.clear();
  mockPurchases.clear();
  std::vector<ProductId> results = getRecommendations("alice");
  bool pass = results.size() == 0;
  std::cout << "Result : " << (pass ? "passed" : "failed") << "\n";

}

//
// Verify that all the recommendations from a single user are copied into the 
// results.
//
void test_01()
{
  std::cout << "Test 01 - a single friend\n";
  mockFriends.clear();
  std::vector<CustomerId> temp1;
  temp1.push_back("bob");
  mockFriends["alice"] = temp1;

  mockPurchases.clear();
  std::vector<ProductId> temp2;
  temp2.push_back("Product1");
  temp2.push_back("Product2");
  temp2.push_back("Product3");
  mockPurchases["bob"] = temp2;

  std::vector<ProductId> results = getRecommendations("alice");
  bool pass = results.size() == 3;
  std::set<ProductId> temp3;
  temp3.insert("Product1");
  temp3.insert("Product2");
  temp3.insert("Product3");
  for (size_t i = 0 ; i < results.size() ; i++ ) {
    std::set<ProductId>::iterator ii = temp3.find(results[i]);
    if ( ii != temp3.end() )
      temp3.erase(ii);
  }
  if ( temp3.size() != 0 )
    pass = false;
  std::cout << "Result : " << (pass ? "passed" : "failed") << "\n";

}
//
// Additional test cases needed
//
// Verify that all products from multiple friends are added to the results
// Verify that when product counts are not 1 (multiple friends/same product) the results are returned in sorted order
// Verify that user purchases are not present in the results
// Verify that user purchases not purchased by friends don't cause problems
// Verify that friends with no purchases don't cause problems

//
// Space and time complexity analysis
//
// Remember that the algorithm has several steps. Use the following
// variables to characterize the algorithm:
//
// FP: Number of products purchased by friends
// FUP: Number of unique products purchased by friends (overlapping products removed)
// P: Number of products purchased by the user
// F: Number of friends for the user
//
// Because we don't write the code that returns the list of friends, and we don't write
// the code that returns the list of products, we have to wave hands at those in
// complexity analysis. Let's assume that they are coming from a magic database in 
// constant time, so we will exclude them from the analyssis.
// 
// Step 1: create a list of all the products purchased by all the friends
//
// time:
// 1 call to a constant function
// F calls to a constant function
// FP insertions into a map - insertion cost is log(FUP)
// time: O(F*log(FUP))
// 
// space:
// F for the list of friends
// maximum of FUP - for each list of friend purchases
// FUP for the map of purchases
// space: O(FUP + F)
//
// Step 2 - remove the user's products from the list
//
// time: O(P*log(FUP)) - potentially one tree operation for each product the user has purchases
// space: O(P) - the list of user purchases
//
// Step 3 - Sort the list
//
// time: O(FUP*log(FUP))
// space: O(FUP)
//
// Step 4: Create a list to return
//
// time: O(FUP*log(FUP))
// space: O(FUP)
//
// Overall analysis: 
//
// time: O(F*log(FUP) + P*log(FUP) + 2*FUP*log(FUP))
//       O( (F+P+2*FUP)*log(FUP) )
//
// space: O(FUP+F + P + FUP + FUP)
//
// What's useful out of this:
//
// The time of this routine is going to be roughly N*log(N), with N being the size of the result list
// The space is dominated by the max of the user purchase or FUP, the friend unique purchases
//
int main(int argc, char *argv[] )
{
  test_00();
  test_01();
  return 0;
}
