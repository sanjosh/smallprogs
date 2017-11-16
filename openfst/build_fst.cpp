
#include <memory>
#include <glog/logging.h>

#include <fst/fstlib.h>

using namespace fst;

int main(int argc, char* argv[]) {

	StdVectorFst fst;

	SymbolTable* isyms;
	SymbolTable* osyms;

	{
		isyms = new SymbolTable("isyms.txt");
		osyms = new SymbolTable("osyms.txt");

		isyms->AddSymbol("a");
		isyms->AddSymbol("b");
		isyms->AddSymbol("c");
		isyms->Write("isyms.txt");

		osyms->AddSymbol("x");
		osyms->AddSymbol("y");
		osyms->AddSymbol("z");
		osyms->Write("osyms.txt");
	}

	{
		fst.SetInputSymbols(isyms);
		fst.SetOutputSymbols(osyms);

		// Adds state 0 to the initially empty FST and make it the start state.
		fst.AddState(); // 1st state will be state 0 (returned by AddState)
		fst.SetStart(0); // arg is state ID

		// Adds two arcs exiting state 0.
		// Arc constructor args: ilabel, olabel, weight, dest state ID.
		fst.AddArc(0, StdArc(isyms->Find("a"), osyms->Find("x"), 0.5, 1)); // 1st arg is src state ID
		fst.AddArc(0, StdArc(isyms->Find("b"), osyms->Find("y"), 1.5, 1));

		// Adds state 1 and its arc.
		fst.AddState();
		fst.AddArc(1, StdArc(isyms->Find("c"), osyms->Find("z"), 2.5, 2));

		// Adds state 2 and set its final weight.
		fst.AddState();
		fst.SetFinal(2, 3.5); // 1st arg is state ID, 2nd arg weight

		fst.Write("example.fst");
	}

	StdVectorFst search_fst;
	{
		search_fst.SetInputSymbols(isyms);
		search_fst.SetOutputSymbols(osyms);

		search_fst.AddState(); // 1st state will be state 0 (returned by AddState)
		search_fst.SetStart(0); // arg is state ID

		// Adds two arcs exiting state 0.
		// Arc constructor args: ilabel, olabel, weight, dest state ID.
		search_fst.AddArc(0, StdArc(isyms->Find("a"), osyms->Find("x"), 0.5, 1)); // 1st arg is src state ID

		// Adds state 1 and its arc.
		search_fst.AddState();
		search_fst.AddArc(1, StdArc(isyms->Find("c"), osyms->Find("z"), 2.5, 2));

		// Adds state 2 and set its final weight.
		search_fst.AddState();
		search_fst.SetFinal(2, 3.5); // 1st arg is state ID, 2nd arg weight
	}

	static const ILabelCompare<StdArc> icomp;
	ArcSort(&fst, icomp);
	StdIntersectFst ofst(fst, search_fst);

	/*
	StateIterator<StdIntersectFst> siter(ofst);

	for (; !siter.Done(); siter.Next()) {
		StdIntersectFst::StateId s = siter.Value();
		std::cout << s << std::endl;
	}
	*/

}
