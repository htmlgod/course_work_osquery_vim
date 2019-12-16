![vim-info-screenshot](docs/scr1.png)

# :floppy_disk: vim-info
`vim-info` - утилита, позволяющая узнать информацию о конфигурации вашего
`VIM/NVIM` редактора.

[![BuildStatus](https://travis-ci.org/htmlgod/course_work_osquery_vim.svg?branch=master)](https://travis-ci.org/htmlgod/course_work_osquery_vim)

## Содержание
* [Описание курсового проекта](https://github.com/htmlgod/course_work_osquery_vim#описание-курсового-проекта)
   * [Список задач](https://github.com/htmlgod/course_work_osquery_vim#список-задач)
* [Процесс сборки](https://github.com/htmlgod/course_work_osquery_vim#процесс-сборки)
* [Процесс запуска тестов](https://github.com/htmlgod/course_work_osquery_vim#процесс-запуска-тестов)
* [Примеры команд](https://github.com/htmlgod/course_work_osquery_vim#примеры-команд)
* [Архитектура проекта](https://github.com/htmlgod/course_work_osquery_vim#архитектура-проекта)
* [Полезные ссылки](https://github.com/htmlgod/course_work_osquery_vim#полезные-ссылки)
* [TODO-лист](https://github.com/htmlgod/course_work_osquery_vim#TODO-лист)

## Описание курсового проекта

Разработать программу/утилиту, предоставляющую информацию о конфигурации текстового редактора `VIM`.
Типы собираемой информации предусмотрены списком задач.

Реализовать возможность установки данной утилиты.
Проект должен иметь процесс сборки, процесс установки и организованную структуру.
После разработки программы интегрировать с `osquery` в виде osquery-расширения (`osquery-extension`).

### Список задач
1. Получить список плагинов
2. Получить список настроек для плагинов
3. Получить список настроек
4. Получить список отображений для режимов
5. Получить время запуска
6. Получить список звезд для плагина на сервисе `GitHub`
7. Классифицировать плагин с помощью `vim-awesome`
8. Получить соотношение открытых `issues` к закрытым для плагина
9. Посчитать соотношение для группы плагинов количество звезд к количеству плагинов в группе

## Процесс сборки
```bash
$ cmake -H. -B_build
$ cmake --build _build
```
![vim-info-build](docs/demos/build.gif)
## Процесс запуска тестов

**WORK IN PROGRESS** 

## Примеры команд

1. Получить список плагинов
2. Получить список настроек для плагинов
3. Получить список настроек
4. Получить список отображений для режимов
5. Получить время запуска
6. Получить список звезд для плагина на сервисе `GitHub`

![vim-info-stars](docs/demos/stars.gif)

7. Классифицировать плагин с помощью `vim-awesome`
8. Получить соотношение открытых `issues` к закрытым для плагина

![vim-info-issues](docs/demos/issues.gif)

9. Посчитать соотношение для группы плагинов количество звезд к количеству плагинов в группе


![vim-info-group_stars](docs/demos/group_stars.gif)

## Архитектура проекта

[Structure.md](https://gist.github.com/KhmelevskayaYu/37e1c584a141c59493925574316b792d)

## Полезные ссылки

* [Gathered information](https://gist.github.com/htmlgod/e33c7b334f91992d800dd2ce151b3648)
* [GitHub API](https://developer.github.com/v3/)
* [libcurl documentation](https://curl.haxx.se/libcurl/c/libcurl-tutorial.html)
* [nlohmann/json](https://github.com/nlohmann/json)
* [vimdoc](http://vimdoc.sourceforge.net/htmldoc/starting.html)
* [vim wiki](https://vim.fandom.com/wiki/Displaying_the_current_Vim_environment)

## TODO-лист

1. [ ] Получить список плагинов
2. [ ] Получить список настроек для плагинов
3. [ ] Получить список настроек
4. [ ] Получить список отображений для режимов
5. [ ] Получить время запуска
6. [x] Получить список звезд для плагина на сервисе `GitHub`
7. [ ] Классифицировать плагин с помощью `vim-awesome`
8. [x] Получить соотношение открытых `issues` к закрытым для плагина
9. [x] Посчитать соотношение для группы плагинов количество звезд к количеству плагинов в группе
10. [ ] Реализация установки
11. [ ] Тесты
12. [ ] Сборка и установка под `Windows`
13. [ ] Скринкасты для всех команд
14. [ ] Интеграция с `osquery`
15. [ ] Описать структуру всего проекта
16. [ ] Провести рефакторинг кода
17. [ ] Выполнить соблюдения одного стиля кода для всего проекта
18. [ ] Добавить `Clang-code style`
19. [x] Собрать необходимую информацию
20. [x] Написать shell-скрипты
