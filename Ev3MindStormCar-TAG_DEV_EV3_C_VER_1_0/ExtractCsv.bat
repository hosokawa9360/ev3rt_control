@echo off
SET DST_DIR_ROOT="extract_csv"
SET TIME_STUMP_D=%DATE:~,4%%DATE:~5,2%%DATE:~8,2%
SET TIME_STUMP_T=%TIME:~0,2%%TIME:~3,2%%TIME~6,2%%TIME~9,2%
SET TIME_STUMP_TMP=%TIME_STUMP_D%%TIME_STUMP_T%
SET TIME_STUMP=%TIME_STUMP_TMP: =0%
SET DST_DIR_SUB=%DST_DIR_ROOT%"\\"%TIME_STUMP%

MKDIR %DST_DIR_SUB%
FOR /f %%i IN ('dir /B /S H:\*.csv') DO (
    MOVE %%i %DST_DIR_SUB%
)
