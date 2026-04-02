#ifndef LCARTE_H
#define LCARTE_H

#ifdef __cplusplus
extern "C" {
#endif

void initialisations_ports(void);
void attente_insertion_carte(void);
int lecture_numero_carte(void);
void attente_retrait_carte(void);

#ifdef __cplusplus
}
#endif

#endif // LCARTE_H