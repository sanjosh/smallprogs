#include <stdio.h> 
#include <rapidjson/document.h> 

extern "C" int json_match(int a, void* void_doc)
{ 
  if (void_doc == NULL) { return 0; }

  rapidjson::Document* doc = (rapidjson::Document*)(void_doc); 
  assert(doc->IsObject());
  bool res = ((*doc)["ID"] == 2) && ((*doc)["Age"] == 38); 
  return res; 
}
