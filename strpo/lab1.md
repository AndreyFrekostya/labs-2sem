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

Сделал коммит только файла отчета:
```bash
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git add strpo/lab1.md
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git commit -m "(strpo): change report"
[lab1-strpo 68e5c2b] (strpo): change report
 1 file changed, 107 insertions(+)
```

### Откат изменений
Откатил изменения только в README: `git restore README.md`. Изменения пропали.

После удаления файла отчета (означает что просто файл удален):
```bash
git status
On branch lab1-strpo
Changes not staged for commit:
  (use "git add/rm <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        deleted:    strpo/lab1.md

no changes added to commit (use "git add" and/or "git commit -a")
```

Далее востановил файл с помощью git restore.


### Ветвление версий

Я изначально начал работу в новой ветке от main с помощью git checkout -b "lab1-strpo".
Сейчас `git branch` показывает:
```bash
git branch
  lab1 (note: ветка для лабы по структурам данных)
* lab1-strpo
  main
```

Далее закоммитил:
```bash
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git add .
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git commit -m "(strpo): change report v2"
[lab1-strpo 822fc47] (strpo): change report v2
 1 file changed, 37 insertions(+)
 ```

При checkout на main всех этих файлов нет.

После изменения в README и попытке переключиться на main (означает, что изменения нужно либо закоммитить, либо сохранить в stash):
```bash
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git checkout main
error: Your local changes to the following files would be overwritten by checkout:
        README.md
Please commit your changes or stash them before you switch branches.
Aborting
```

Далее я смержил:
```bash
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git checkout main
Switched to branch 'main'
Your branch is up to date with 'origin/main'.
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git merge lab1-strpo
Updating f975b96..5b661f4
Fast-forward
 strpo/lab1.md | 163 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 163 insertions(+)
 create mode 100644 strpo/lab1.md
 ```

Изменил README и закоммитил:
```bash
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git add .
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git commit -m "(strpo): commit again report of lab1 to main"
[main 2682311] (strpo): commit again report of lab1 to main
 1 file changed, 1 insertion(+), 1 deletion(-)
```