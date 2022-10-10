#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>


#define DYLD_INTERPOSE(_replacment,_replacee) \
__attribute__((used)) static struct{ const void* replacment; const void* replacee; } _interpose_##_replacee \
__attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacment, (const void*)(unsigned long)&_replacee };


void* pMalloc(size_t size)
{
  static int counter = 0;
  if (counter < 1000)
  {
    counter++;
    return (malloc(size));
  }
  else
   return malloc(-1);
}

DYLD_INTERPOSE(pMalloc, malloc);