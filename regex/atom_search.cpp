/**
 * use google::re2 to extract prefixes of regexp
 */
#include <re2/filtered_re2.h>
#include <iostream>
#include <set>
#include <iterator>
#include <string>

using namespace re2;

typedef uint32_t Trigram;
typedef std::set<Trigram> TrigramSet;

TrigramSet get_trigrams(const std::string& str) {
	TrigramSet trigrams;
	if (str.size() > 2) {
		Trigram t = (str[0] << 16) + (str[1] << 8) + str[2];
		trigrams.insert(t);
		for (size_t idx = 3; idx < str.size(); idx ++) {
			t = ((t << 8) & 0xFFFF00) + str[idx];
		}
	}
	return trigrams;
}

int main()
{
	const std::string regexp1 = "^(ab4|def).*c[0-9]jjj$";

	FilteredRE2 fre;
	RE2::Options opts;
	int id;
	fre.Add(regexp1, opts, &id);

	std::vector<std::string> atoms;
	// any string that is matching the regexp must begin with the prefixes
	// returned in required_prefixes
	fre.Compile(&atoms);
	std::cout << atoms.size() << std::endl;

	TrigramSet trigrams;
	for (auto& atom : atoms) {
		auto new_trigrams = get_trigrams(atom);
		TrigramSet combo;
		std::set_union(trigrams.begin(), trigrams.end(), 
				new_trigrams.begin(), new_trigrams.end(),
				std::inserter(combo, combo.end()));
		trigrams = combo;
	}

	for (auto& trigram: trigrams) {
		std::cout << trigram << std::endl;
	}
}
