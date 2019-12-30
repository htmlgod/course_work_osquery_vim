![vim-info-screenshot](docs/screenshots/logo.png)

# :floppy_disk: vim-info
`vim-info` - утилита, позволяющая узнать информацию о конфигурации вашего
`VIM/NVIM` редактора.

[![Build Status](https://travis-ci.com/htmlgod/course_work_osquery_vim.svg?token=DhyR4qA4NeY9eNsr6S2Q&branch=master)](https://travis-ci.com/htmlgod/course_work_osquery_vim)

## Содержание
* [Описание курсового проекта](https://github.com/htmlgod/course_work_osquery_vim#описание-курсового-проекта)
   * [Список задач](https://github.com/htmlgod/course_work_osquery_vim#список-задач)
* [Зависимости](https://github.com/htmlgod/course_work_osquery_vim#зависимости)
* [Процесс сборки](https://github.com/htmlgod/course_work_osquery_vim#процесс-сборки)
* [Интеграция с osquery](https://github.com/htmlgod/course_work_osquery_vim#интеграция-с-osquery)
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

## Зависимости
```bash
#requirements
$ python3/python
$ pip3/pip
$ pip3/pip install osquery
# Export your Github username and password/token
$ export GITHUB_USERNAME=<username>
$ export GITHUB_PASSWORD=***************
```

## Процесс сборки
```bash
$ git clone https://github.com/htmlgod/course_work_osquery_vim 
$ cd course_work_osquery_vim
$ git submodule update --init
$ cmake -H. -B_build
$ cmake --build _build
$ ./start.sh # Установка расширения
```
![vim-info-build](docs/gifs/build.gif)
## Интеграция с osquery

Запуск расширения
```bash
$ viminfo --json_export # Парсим данные и сохраняем в json формате
# В другом окне/терминале
$ osqueryi --nodisable_extensions
# В изначальном терминале/окне
$ viminfo --start_extension # Запускаем расширение
```
```osquery
Using a virtual database. Need help, type '.help'
osquery> select * from vimplugins;
osquery> select * from viminfodata;
osquery> select * from vimruntime;
```
![settinglist](docs/gifs/osquery.gif)
Доступные таблицы:

1. Таблица плагинов

![plugtable](docs/screenshots/plugtable.png)

2. Таблица времени запуска VIM

![timetable](docs/screenshots/runtimetable.png)

3. Таблица общих данных (включая необходимые для работы программы)

![datatable](docs/screenshots/infotable.png)

## Примеры команд

### Опции запуска

```bash
$ viminfo --help
vim-info options:
  -h [ --help ]             Help screen
  -e [ --start_extension ]  Start osquery extension without GUI
  -j [ --json_export ]      Parse and export information into json files 
                            without GUI
  -v [ --version ]          print version
  -c [ --clear ]            Clear all data
```

1. Получить список плагинов

![pluginlist](docs/gifs/cmd1.gif)

2. Получить список настроек для плагинов
3. Получить список настроек

![settinglist](docs/gifs/cmd2.gif)

4. Получить список отображений для режимов
5. Получить время запуска

![runtime](docs/gifs/cmd3.gif)

6. Получить список звезд для плагина на сервисе `GitHub`

![pluginstars](docs/gifs/cmd4.gif)

7. Классифицировать плагин с помощью `vim-awesome`

![pluginclass](docs/gifs/cmd5.gif)

8. Получить соотношение открытых `issues` к закрытым для плагина

![pluginissues](docs/gifs/cmd6.gif)

9. Посчитать соотношение для группы плагинов количество звезд к количеству плагинов в группе

![pluginsgroup](docs/gifs/cmd7.gif)

## Архитектура проекта

[Structure.md](https://gist.github.com/KhmelevskayaYu/37e1c584a141c59493925574316b792d)

## Полезные ссылки

* [Gathered information](https://gist.github.com/htmlgod/e33c7b334f91992d800dd2ce151b3648)
* [GitHub API](https://developer.github.com/v3/)
* [libcurl documentation](https://curl.haxx.se/libcurl/c/libcurl-tutorial.html)
* [nlohmann/json](https://github.com/nlohmann/json)
* [vimdoc](http://vimdoc.sourceforge.net/htmldoc/starting.html)
* [vim wiki](https://vim.fandom.com/wiki/Displaying_the_current_Vim_environment)
* [Boost docs](https://www.boost.org/doc/libs/)
* [Osquery Docs](https://osquery.readthedocs.io/en/latest/)
* [osquery-python](https://github.com/osquery/osquery-python)

## TODO-лист

1. [x] Получить список плагинов
2. [ ] Получить список настроек для плагинов
3. [x] Получить список настроек
4. [ ] Получить список отображений для режимов
5. [x] Получить время запуска
6. [x] Получить список звезд для плагина на сервисе `GitHub`
7. [x] Классифицировать плагин с помощью `vim-awesome`
8. [x] Получить соотношение открытых `issues` к закрытым для плагина
9. [x] Посчитать соотношение для группы плагинов количество звезд к количеству плагинов в группе
10. [x] Интеграция с `osquery`
11. [x] Описать структуру всего проекта
12. [x] Собрать необходимую информацию
13. [x] Написать shell-скрипты
