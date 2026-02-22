# Лабораторная работа №1. Базовая работа с git.

## Ход выполнения работы

### Установка и настройка

Git установлен с оффициального [сайта](https://git-scm.com/install/windows). 

Проверка версии:

```bash
C:\Users\orbit>git version
git version 2.45.2.windows.1
```

Указал name, email с помощью `git config`.

Узнал основные команды с помощью `git --help`.

### Начало работы с новым проектом

Изучил синтаксис [Markdown](https://www.markdownguide.org/basic-syntax/).

Создал папки репозитория и инициализировал его: 

```bash
git init
Initialized empty Git repository in /mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all/.git/
```

Составил README.md файл с основной информацией

Выполнение коммита (README не показывается, т.к. я его коммитил при пуше лабораторной работы №1 по дисциплине "Структуры данных"):

```bash
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git add strpo 
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git commit -m "(strpo): first commit"
[lab1-strpo 3a30f82] (strpo): first commit
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 strpo/lab1.md
```

### Отслежавание состояние кода

`git status`: показывает текущее состояние репозитория.

`git diff`: Показывает изменения между рабочей директорией и индексом.

Вывод `git status` означает, что есть изменение, но они не добавлены в индекс:
```bash 
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git status
On branch lab1-strpo
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   strpo/lab1.md

no changes added to commit (use "git add" and/or "git commit -a")
```

Вывод `git diff` показывает какие именно изменения:
```bash
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git diff
diff --git a/strpo/lab1.md b/strpo/lab1.md
index e69de29..6acd06e 100644
--- a/strpo/lab1.md
+++ b/strpo/lab1.md
@@ -0,0 +1,61 @@
+# Лабораторная работа №1. Базовая работа с git.
+
+## Ход выполнения работы
+
+### Установка и настройка
+
+Git установлен с оффициального [сайта](https://git-scm.com/install/windows). 
+
+Проверка версии:
+
+```bash
+C:\Users\orbit>git version
...
```

Добавил изменения отчета в индекс (файл теперь находится в стадии "Changes to be committed" и его можно коммитить):
```bash
git status
On branch lab1-strpo
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   strpo/lab1.md
```

Внес изменения в README.md и git diff показал что именно изменилось:
```bash
git diff README.md
diff --git a/README.md b/README.md
index df0eba6..bc6ebec 100644
--- a/README.md
+++ b/README.md
@@ -10,3 +10,5 @@
 ## Структура репозитория:
 - c++ - папка с лабораторными работами по дисциплине "Структуры данных"
 - strpo - папкка с лабораторными работами по дисциплине "Современные технологии разработки программного обеспечения"
+^M
+вфывфывфывфывфыввфывфывфы
\ No newline at end of file
```