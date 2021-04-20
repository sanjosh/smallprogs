/*
 *
gcc mem.c `pkf-config --cflags --libs glib-2.0`  -lcrypto
 */

#include <glib.h>
#include <glib/gstring.h>
#include <openssl/rand.h>

#include <stdio.h>

int main()
{
    char a[256];
    RAND_bytes(&a[0], 256);
    gsize bread = 0;
    gsize bwritten = 0;
    GError *error = NULL;
    gchar* c = g_convert(a, 256, "UTF-8", "UCS-4", &bread, &bwritten, &error);
    if (error) {
        printf("%ld %d %s %d\n", bread, error->domain, error->message, error->code);
        exit(1);
    } 

    printf("%ld %ld %s\n", bread, bwritten, c);

    gchar* d = g_convert(c, bwritten, "UCS-2", "UTF-8", &bread, &bwritten, &error);
}
