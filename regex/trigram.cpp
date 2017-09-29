#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdint>
#include <ftw.h>
#include <unordered_map>
#include <set>
#include <string>

typedef uint64_t FileNumber;
typedef std::set<FileNumber> FileNumberList;
typedef uint32_t Trigram;
std::unordered_map<Trigram, FileNumberList> trigrams;

void insert_trigram(Trigram t, FileNumber f) {
	auto iter = trigrams.find(t);
	if (iter != trigrams.end()) {
		iter->second.insert(f);
	} else {
		trigrams.insert({t, {f}});
	}
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
		std::cout << "processed=" << file_no << " trigrams=" << trigrams.size() << std::endl;
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

	std::cout << trigrams.size() << std::endl;
	for (auto& trigram: trigrams) {
		std::cout << trigram.first << std::endl;
	}
}
