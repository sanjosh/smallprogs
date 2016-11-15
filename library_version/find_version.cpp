/*
 * sample code to find version of library (boost here)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

int main(int argc, char* argv[])
{
  std::string all = "LD_TRACE_LOADED_OBJECTS=1 ";
  all.append(argv[1]);
  char mode[] = "r";
  FILE *ldd = popen(all.c_str(), mode);

  while (!feof(ldd))
  {
    char buffer[8192];
    buffer[0] = '\0';
    int ret = fscanf(ldd, "%s\n", buffer);
    if (ret <= 0) break;
    if (strstr(buffer, "boost"))
    {
      if (strstr(buffer, "1.54")) {
        printf("matches %s\n", buffer);
      } else {
        printf("DOESNT match %s\n", buffer);
      }
    }
  }
  pclose(ldd);
}

