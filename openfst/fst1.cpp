#include <memory>
#include <glog/logging.h>

//#include <fst/fstlib.h>
#include <fst/script/getters.h>
#include <fst/script/intersect.h>

using namespace fst::script;
using fst::ComposeFilter;

int main(int argc, char* argv[]) {
	std::unique_ptr<FstClass> fst1;
	std::unique_ptr<FstClass> fst2;

	VectorFstClass ofst(fst1->ArcType());

	ComposeFilter compose_filter;
	if (!GetComposeFilter("auto", &compose_filter)) {
		LOG(ERROR) << "failed";
		exit(1);
	}

	const fst::IntersectOptions opts(true, compose_filter);

	Intersect(*fst1, *fst2, &ofst, opts);
}
