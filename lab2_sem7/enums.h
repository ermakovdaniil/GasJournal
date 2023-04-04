#pragma once

enum Menu { NoMenuItem = 0, ShowJournalMenuItem, AddRecordMenuItem, AddGasBrandMenuItem, CreateTextFileMenuItem, ShowAverageBetweenRefuelingMenuItem, ShowGasBrandsStatsMenuItem, RunTestsMenuItem, ShowInfoMenuItem, ExitMenuItem };

enum InputMenu { ManualInputMenuItem = 1, FileInputMenuItem, GoBackInputMenuItem };

enum SaveAnswer { Yes = 1, No };

enum PathContext { SaveContext = 1, InputContext };

enum SaveContext { SaveInitialData = 1, SaveResultContext };

enum ErrorCodes { NoError, ErrorInPathInput, ErrorInFileData, ErrorInDateInput, ErrorInNumberInput, ErrorInGasBrandInput, GoBack, TestError };

enum ErrorMenuItems { EnterDataAgainMenuItem = 1, GoBackToMainMenuMenuItem };

enum AdditionalSaveMenuItems { RewriteMenuItem = 1, CreateNewFileMenuItem, GoBackAdditionalSaveMenuItem };

enum SaveMenuItems { SaveJournalResultMenuItem = 1, SaveJournalInitialDataMenuItem, SaveGasBrandsResultMenuItem, SaveGasBrandsInitialDataMenuItem, GoBackSaveMenuItem };