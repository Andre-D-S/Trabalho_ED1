#ifndef REGISTRODEHUMOR_H
#define REGISTRODEHUMOR_H

typedef enum{
    FELIZ,
    TRISTE,        
    ANSIOSO,
    CANSADO,
    MOTIVADO,
    ESTRESSADO,
    NEUTRO        
}Humor;

typedef struct registrodehumor{
    int id;
    char data[11];
    Humor humor;
    char motivo[101];
    int notaDoDia;
}RegistroDeHumor;


RegistroDeHumor* criarRegistro();

extern const char* Identificador[];

void ImprimirRegistro(RegistroDeHumor r);

void LiberarRegistro(RegistroDeHumor r);

#endif /* REGISTRODEHUMOR_H */

