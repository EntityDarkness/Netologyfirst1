@echo off
chcp 65001 > nul
REM Переход в директорию с вашим git-репозиторием
cd /d "C:\netology\Netologyfirst1"

REM Получение актуальной версии всех веток
git fetch --all

REM Переключение на ветку dev
echo Переключение на ветку dev...
git checkout dev
if %errorlevel% neq 0 (
    echo Ошибка: Не удалось переключиться на ветку dev.
    exit /b %errorlevel%
)

REM Слияние последней ревизии dev в prd
echo Переключение на ветку prd...
git checkout prd
if %errorlevel% neq 0 (
    echo Ошибка: Не удалось переключиться на ветку prd.
    exit /b %errorlevel%
)

echo Слияние изменений из dev в prd...
git merge dev
if %errorlevel% neq 0 (
    echo Ошибка: Не удалось выполнить слияние dev в prd.
    exit /b %errorlevel%
)

REM Создание тэга с текущей датой и временем
set TAG=v%date:~-4%%date:~3,2%%date:~0,2%_%time:~0,2%%time:~3,2%%time:~6,2%
echo Создание тэга %TAG%...
git tag %TAG%
if %errorlevel% neq 0 (
    echo Ошибка: Не удалось создать тэг.
    exit /b %errorlevel%
)

REM Отправка изменений и тэга в удалённый репозиторий
echo Отправка изменений в удалённый репозиторий...
git push origin prd
if %errorlevel% neq 0 (
    echo Ошибка: Не удалось отправить изменения в ветку prd.
    exit /b %errorlevel%
)

echo Отправка тэга в удалённый репозиторий...
git push origin %TAG%
if %errorlevel% neq 0 (
    echo Ошибка: Не удалось отправить тэг %TAG%.
    exit /b %errorlevel%
)

echo Готово! Ревизия из dev перенесена в prd и тэг %TAG% установлен.