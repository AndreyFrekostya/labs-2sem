# Лабораторная работа №6. Простые CI-CD пайплайны

## Ход выполнения работы

### Базовые хуки в Git на стороне клиента

| Операция git | Этап                                           | Хук                  | Можно прервать? |
| ------------ | ---------------------------------------------- | -------------------- | --------------- |
| `git commit` | До создания коммита                            | `pre-commit`         | Да              |
| `git commit` | После подготовки сообщения коммита             | `prepare-commit-msg` | Да              |
| `git commit` | Перед созданием коммита, после ввода сообщения | `commit-msg`         | Да              |
| `git commit` | После создания коммита                         | `post-commit`        | Нет             |
| `git merge`  | До создания merge-коммита                      | `pre-merge-commit`   | Да              |
| `git push`   | Перед отправкой в удалённый репозиторий        | `pre-push`           | Да              |

Создал хук pre-commit, который проверяет коммит на наличие .env файлов:
```
#!/bin/sh

# Проверяем только файлы, добавленные в индекс
files=$(git diff --cached --name-only --diff-filter=ACM)

[ -z "$files" ] && exit 0

for f in $files; do
  case "$f" in
    .env|*/.env)
      echo "ERROR: файл .env запрещено добавлять в коммит: $f"
      exit 1
      ;;
  esac
done

exit 0
```

Далее сделал файл исполняемым: `chmod +x pre-commit`.
Попробовал закоммитить:
```
andrey@andrew:/mnt/c/Users/orbit/OneDrive/Рабочий стол/1/учеба/аип/2sem/all$ git commit -m "add env"
ERROR: файл .env запрещено добавлять в коммит: .env
```

Дальше сделал хук commit-msg, который проверяет сообщение коммита по выражению (type: project): (description), 
где type - conventional commits,
project - c++/strpo

```
#!/bin/sh

msg_file="$1"
msg=$(head -n 1 "$msg_file")

echo "$msg" | grep -Eq '^\((feat|fix|docs|test|refactor|chore): (stro|c\+\+)\): .+' || {
  echo "ERROR: неверный формат commit message"
  echo "Используйте формат: (type: project): description"
  echo "Примеры:"
  echo "  (feat: c++): ..."
  echo "  (fix: strpo): ..."
  exit 1
}

exit 0
```

Попробовал закоммитить:
```
git commit -m "random message"
ERROR: неверный формат commit message
Используйте формат: (type: project): description
Примеры:
  (feat: c++): ...
  (fix: strpo): ...
```


### Хуки Git на стороне сервера