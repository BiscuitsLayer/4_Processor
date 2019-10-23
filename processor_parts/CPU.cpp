#include <cstdio>
#include <cstdlib>
#include "CPU.h"
#include "../cmake-build-debug/program_data/program.commands"

void CPUMain () {
    CPU_t CPU = {}; //Структура процессора
    CPU.stk = StackInit (); //Инициализация процессора
    CPU.func = StackInit (); //Инициализация стека вызовов функций

    FILE *program_info = fopen ("program_data/program.info", "rb"); //Дополнительная информация о программе
    size_t program_len = 0; //Длина машинного кода
    fscanf (program_info, "%zd", &program_len); //Ввод длины машинного кода
    fclose (program_info);

    FILE *program_code = fopen ("program_data/program.code", "rb"); //Машинный код
    LoadData (&CPU, program_code, program_len); //Загрузка машинного кода в процессор

    /*//Вывод машинного кода, принятого процессором
    printf ("PROGRAM LOADED:\n");
    for (int i = 0; i < program_len; ++i)
        printf ("%d ", CPU.data[i]);
    printf ("\nEND OF PROGRAM\n");
    */

    DataHandle (&CPU, program_len); //Исполнение машинного кода

    fclose (program_code);
}

void LoadData (CPU_t *CPU, FILE *program_code, size_t program_len) {
    CPU->data = (int *) calloc (program_len, sizeof(int)); //Выделение памяти под машинный код
    fread (CPU->data, sizeof(int), program_len, program_code); //Чтение машинного кода
}

void DataHandle (CPU_t *CPU, size_t program_len) {
    for (CPU->it = 0; CPU->it < program_len; ++CPU->it) {
        switch (CPU->data[CPU->it]) { //Обработка машинного кода
            #include "../cmake-build-debug/program_data/program.lang"
            #define DEF_CMD(name, num, code) case CMD_##name COLON { code; break; }
            #include "../cmake-build-debug/program_data/program.operations"
            #undef DEF_CMD
        }
    }
}