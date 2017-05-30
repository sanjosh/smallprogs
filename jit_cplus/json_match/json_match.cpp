/**
 * supply "test.cpp" as first argument
 */

#include "clang/CodeGen/CodeGenAction.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/Tool.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/CompilerInvocation.h"
#include "clang/Frontend/FrontendDiagnostic.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include "llvm/ADT/SmallString.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/MemoryBuffer.h"
#include <memory>

#include <rapidjson/document.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

using namespace clang;
using namespace llvm;
using namespace clang::driver;

// This function isn't referenced outside its translation unit, but it
// can't use the "static" keyword because its address is used for
// GetMainExecutable (since some platforms don't support taking the
// address of main, and some platforms can't implement GetMainExecutable
// without being given the address of a function in the main executable).

std::string GetExecutablePath(const char *Argv0) {
  // This just needs to be some symbol in the binary; C++ doesn't
  // allow taking the address of ::main however.
  void *MainAddr = (void*) (intptr_t) GetExecutablePath;
  return llvm::sys::fs::getMainExecutable(Argv0, MainAddr);
}

static llvm::ExecutionEngine *
createExecutionEngine(std::unique_ptr<llvm::Module> M, std::string *ErrorStr) {
  return llvm::EngineBuilder(std::move(M))
      .setEngineKind(llvm::EngineKind::Either)
      .setErrorStr(ErrorStr)
      .create();
}

static int Execute(std::unique_ptr<llvm::Module> Mod, char *const *envp) {

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  llvm::Module &M = *Mod;
  std::string Error;
  std::unique_ptr<llvm::ExecutionEngine> EE(
      createExecutionEngine(std::move(Mod), &Error));
  if (!EE) {
    llvm::errs() << "unable to make execution engine: " << Error << "\n";
    return 255;
  }

  llvm::Function *matchFunc = M.getFunction("json_match");
  if (!matchFunc) {
    llvm::errs() << "function not found in module.\n";
    return 255;
  }

  EE->finalizeObject();

  /*
  std::cout << "ptr=" << (void*)&doc << std::endl;
  std::cout << "numargs=" << matchFunc->getFunctionType()->getNumParams() << std::endl;
  std::cout << "isptr=" << matchFunc->getFunctionType()->getParamType(0)->isPointerTy() << std::endl;
  */

  char line[1024];
  FILE* fp = fopen("./test.json", "r");
  while (fgets(line, 1024, fp))
  {
    rapidjson::Document doc;
    if (doc.ParseInsitu(line).HasParseError()) {
      std::cout << "failed parse" << doc.GetParseError() << "," << doc.GetErrorOffset() << std::endl;
      continue;
    }
    assert(doc.IsObject());
  
    std::vector<llvm::GenericValue> argVec(2);
    argVec[0].IntVal = 2123; // dummy arg
    argVec[1].PointerVal = (void*)&doc;
    llvm::GenericValue ret = EE->runFunction(matchFunc, argVec);
    bool res = ret.IntVal.getBoolValue();
    std::cout << "match=" << res << std::endl;
  }
  return 0;
}

int main(int argc, const char **argv, char * const *envp) {

  void *MainAddr = (void*) (intptr_t) GetExecutablePath;
  std::string Path = GetExecutablePath(argv[0]);
  IntrusiveRefCntPtr<DiagnosticOptions> DiagOpts = new DiagnosticOptions();
  TextDiagnosticPrinter *DiagClient =
    new TextDiagnosticPrinter(llvm::errs(), &*DiagOpts);

  IntrusiveRefCntPtr<DiagnosticIDs> DiagID(new DiagnosticIDs());
  DiagnosticsEngine Diags(DiagID, &*DiagOpts, DiagClient);

  std::string TripleStr = llvm::sys::getProcessTriple();
  llvm::Triple T(TripleStr);
  if (T.isOSBinFormatCOFF())
    T.setObjectFormat(llvm::Triple::ELF);

  // Driver is required to ensure compiler env is accurately created inside program!
  Driver TheDriver(Path, T.str(), Diags);
  TheDriver.setTitle("clang interpreter");
  TheDriver.setCheckInputsExist(false);

  SmallVector<const char *, 16> Args(argv, argv + argc);
  Args.push_back("-fsyntax-only");
  Args.push_back("-I/usr/lib/llvm-3.8/lib/clang/3.8.0/include");
  Args.push_back("-I/usr/include/llvm");
  Args.push_back("-I/usr/lib/llvm-3.8/include/clang");
  Args.push_back("-I/usr/lib/llvm-3.8/include");
  std::unique_ptr<Compilation> C(TheDriver.BuildCompilation(Args));
  if (!C)
    return 0;

  const driver::JobList &Jobs = C->getJobs();
  if (Jobs.size() != 1 || !isa<driver::Command>(*Jobs.begin())) {
    SmallString<256> Msg;
    llvm::raw_svector_ostream OS(Msg);
    Jobs.Print(OS, "; ", true);
    Diags.Report(diag::err_fe_expected_compiler_job) << OS.str();
    return 1;
  }

  const driver::Command &Cmd = cast<driver::Command>(*Jobs.begin());
  if (llvm::StringRef(Cmd.getCreator().getName()) != "clang") {
    Diags.Report(diag::err_fe_expected_clang_command);
    return 1;
  }

  // Initialize a compiler invocation object from the clang (-cc1) arguments.
  const driver::ArgStringList &CCArgs = Cmd.getArguments();
  std::unique_ptr<CompilerInvocation> CI(new CompilerInvocation);
  CompilerInvocation::CreateFromArgs(*CI,
                                     const_cast<const char **>(CCArgs.data()),
                                     const_cast<const char **>(CCArgs.data()) +
                                       CCArgs.size(),
                                     Diags);

    /*
    constexpr auto testCodeFileName = "test.cpp";
    const std::string testCode = " \n \
        #include <stdio.h> \n  \
        #include <rapidjson/document.h> \n \
        extern \"C\" int dome(void* void_doc) \
        { \
          rapidjson::Document* doc = (rapidjson::Document*)(void_doc); \
          bool res = ((*doc)[\"col1\"] == 10) && ((*doc)[\"col2\"] == \"abc\"); \
          return res; \
        }";

    // Map code filename to a memoryBuffer
    StringRef testCodeData(testCode);
    std::unique_ptr<MemoryBuffer> buffer = MemoryBuffer::getMemBufferCopy(testCodeData);
    CI->getPreprocessorOpts().addRemappedFile(testCodeFileName, buffer.get());
    */

  CI->getHeaderSearchOpts().Verbose = 1;
  CI->getHeaderSearchOpts().UseStandardSystemIncludes = 1;
  CI->getHeaderSearchOpts().UseStandardCXXIncludes = 1;
  CI->getHeaderSearchOpts().UseBuiltinIncludes = 1;
  CI->getLangOpts()->CPlusPlus = 1;
  CI->getLangOpts()->GNUMode = 1;

  // Show the invocation, with -v.
  if (CI->getHeaderSearchOpts().Verbose) {
    llvm::errs() << "clang invocation:\n";
    Jobs.Print(llvm::errs(), "\n", true);
    llvm::errs() << "\n";
  }

  // Create a compiler instance to handle the actual work.
  CompilerInstance Clang;
  Clang.setInvocation(CI.get());

  // Create the compilers actual diagnostics engine.
  Clang.createDiagnostics();
  if (!Clang.hasDiagnostics())
    return 1;

  // Infer the builtin include path if unspecified.
  if (Clang.getHeaderSearchOpts().UseBuiltinIncludes &&
      Clang.getHeaderSearchOpts().ResourceDir.empty())
    Clang.getHeaderSearchOpts().ResourceDir =
      CompilerInvocation::GetResourcesPath(argv[0], MainAddr);

  // Create and execute the frontend to generate an LLVM bitcode module.
  std::unique_ptr<CodeGenAction> Act(new EmitLLVMOnlyAction());
  if (!Clang.ExecuteAction(*Act))
    return 1;

  int Res = 255;
  if (std::unique_ptr<llvm::Module> Module = Act->takeModule()) {
    Res = Execute(std::move(Module), envp);
  }

  // Shutdown.
  llvm::llvm_shutdown();

  return Res;
}
