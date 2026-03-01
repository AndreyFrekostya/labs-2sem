# Лабораторная работа №2. Git Flow, Code Review

## Ход выполнения работы

### Подготовка репозитория

До выполнения этой работы я уже сделал две папк: c++ - папка по дисциплине "Структуры данных"; strpo - папка по дисциплине "Современные технологии разработки программного обеспечения"

Добавил файл .gitignore в ветке main и закоммитил его:
```bash
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git add .
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git commit -m "add gitignore"
[main ba2faad] add gitignore
 1 file changed, 2 insertions(+)
 create mode 100644 .gitignore
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git push -u origin
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 16 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 305 bytes | 27.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/AndreyFrekostya/labs-2sem.git
   c1eed27..ba2faad  main -> main
branch 'main' set up to track 'origin/main'.
```

### Защита веток

Через интерфейс GitHub настроил защиту ветки main. Попытался запушить и показало ошибку:
```bash
git push -u origin
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 16 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 321 bytes | 35.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
remote: error: GH006: Protected branch update failed for refs/heads/main.
remote: 
remote: - Changes must be made through a pull request.
remote: 
remote: - Cannot change this locked branch
To https://github.com/AndreyFrekostya/labs-2sem.git
 ! [remote rejected] main -> main (protected branch hook declined)
error: failed to push some refs to 'https://github.com/AndreyFrekostya/labs-2sem.git'
```