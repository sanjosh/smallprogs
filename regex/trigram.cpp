#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdint>
#include <ftw.h>
#include <unordered_map>
#include <set>
#include <iterator>
#include <algorithm>
#include <string>

typedef uint64_t FileNumber;
typedef std::set<FileNumber> FileNumberList;
typedef uint32_t Trigram;
std::unordered_map<Trigram, FileNumberList> trigram_map;

void insert_trigram(Trigram t, FileNumber f) {
	auto iter = trigram_map.find(t);
	if (iter != trigram_map.end()) {
		iter->second.insert(f);
	} else {
		trigram_map.insert({t, {f}});
	}
}

FileNumberList get_intersection(const std::set<Trigram>& trigrams) {
	FileNumberList f;
	for (auto trigram : trigrams) {
		FileNumberList result;
		auto iter = trigram_map.find(trigram);
		std::set_intersection(f.begin(), f.end(),
			iter->second.begin(), iter->second.end(),
			std::inserter(result, result.end()));
		f = result;
	}
	return f;
}

FileNumber file_no = 1;

void process_file(const char* filename) {

	std::string s;
	std::ifstream myfile(filename);
	while (myfile >> s) {
		if (s.size() >= 2) {
			uint32_t trigram = (s[0] << 16) + (s[1] << 8) + s[2];
			insert_trigram(trigram, file_no);
			for (size_t i = 3; i < s.size(); i ++) {
				trigram = ((trigram << 8) & 0xFFFF00) + s[i];
				insert_trigram(trigram, file_no);
			}
		}
	}
	file_no ++;
	if (file_no % 10 == 0) {
		std::cout << "processed=" << file_no << " trigrams=" << trigram_map.size() << std::endl;
	}
}

int nftw_callback(const char* fpath, 
		const struct stat* sb, 
		int typeflag, 
		struct FTW* ftwbuf) {

	if (typeflag == FTW_F) {
		process_file(fpath);
	}
	return FTW_CONTINUE;
}

int main(int argc, char* argv[]) 
{
	if (argc == 1) { exit(1); }

	int err = nftw(argv[1], nftw_callback, 10, FTW_PHYS | FTW_MOUNT);
	if (err != 0) { 
		exit(1); 
	}

	std::cout << trigram_map.size() << std::endl;
	for (auto& trigram: trigram_map) {
		std::cout << trigram.first << std::endl;
	}
}
