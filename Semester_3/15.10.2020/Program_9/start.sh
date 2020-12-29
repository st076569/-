# !/bin/bash

# Запускаем пять процессов в фоновом режиме
for i in {1..5}
do
    # Запуск одного фонового процесса (вывод в соотв. файл)
    ./binaries/st076569_9 > ./output/output_$i.txt && echo -e "done : ${i}" &
done

# Ожидание окончания работы
wait
echo -e "Finished"
