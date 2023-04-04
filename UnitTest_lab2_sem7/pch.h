// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

#include "../lab2_sem7/fileSystem.h"
#include "../lab2_sem7/fileSystem.cpp"

#include "../lab2_sem7/userInterface.h"
#include "../lab2_sem7/userInterface.cpp"

#include "../lab2_sem7/inputValidation.h"
#include "../lab2_sem7/inputValidation.cpp"

#include "../lab2_sem7/textCreator.h"
#include "../lab2_sem7/textCreator.cpp"

#include "../lab2_sem7/manualInput.h"
#include "../lab2_sem7/manualInput.cpp"

#include "../lab2_sem7/workWithDB.h"
#include "../lab2_sem7/workWithDB.cpp"

#include "../lab2_sem7/enums.h"
#include "../lab2_sem7/structures.h"
#include "../lab2_sem7/sqlite3.h"

#endif //PCH_H
