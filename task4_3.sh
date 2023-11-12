#!/bin/bash

i=$(pgrep 'task4.sh')
j=$(pgrep 'sleep')

kill -9 "$i" && kill -9 "$j"
echo "Основной скрипт "$i" убит, процесс sleep "$j" убит"

