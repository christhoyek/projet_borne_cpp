#ifndef MEM_SH_H
#define MEM_SH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "donnees_borne.h"

entrees* acces_memoire(int* shmid);

#ifdef __cplusplus
}
#endif

#endif // MEM_SH_H