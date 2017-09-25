/**
 * use google::re2 to extract prefixes of regexp
 */
#include <re2/filtered_re2.h>
#include <iostream>
#include <string>

using namespace re2;

int main()
{
	const std::string regexp1 = "^ab4.*c[0-9]$";
	const std::string regexp2 = "^de3.*c[0-9]$";

	FilteredRE2 fre;
	RE2::Options opts;
	int id;
	fre.Add(regexp1, opts, &id);
	std::cout << id << std::endl;
	fre.Add(regexp2, opts, &id);
	std::cout << id << std::endl;

	std::vector<std::string> required_prefixes;
	// any string that is matching the regexp must begin with the prefixes
	// returned in required_prefixes
	fre.Compile(&required_prefixes);

	for (auto& prefix : required_prefixes) {
		std::cout << prefix << ", ";
	}
	std::cout << std::endl;
}
