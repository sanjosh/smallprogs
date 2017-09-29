/**
 * use google::re2 to extract prefixes of regexp
 */
#include <re2/filtered_re2.h>
#include <iostream>
#include <string>

using namespace re2;

int main()
{
	const std::string regexp1 = "^(ab4|def).*c[0-9]jjj$";

	FilteredRE2 fre;
	RE2::Options opts;
	int id;
	fre.Add(regexp1, opts, &id);
	std::cout << id << std::endl;

	std::vector<std::string> atoms;
	// any string that is matching the regexp must begin with the prefixes
	// returned in required_prefixes
	fre.Compile(&atoms);

	for (auto& atom : atoms) {
		std::cout << atom << ", ";
	}
	std::cout << std::endl;
}
