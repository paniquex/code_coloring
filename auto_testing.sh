#!/bin/bash
unlink valgrind_log.info
echo "Тестирование началось"
for var in 1 2 3 4 5 6 7 8
do
valgrind ./main.out 1 ./tests/identifier_tests/test$var counting >> valgrind_log.info 2>&1
done
echo "Блок идентификаторов пройден"

for var in 1 2 3 4 5 6
do
valgrind ./main.out 1 ./tests/number_tests/test$var counting >> valgrind_log.info 2>&1
done
echo "Блок чисел пройден"

for var in 1 2 3 4 5 6 7 8 9 10 11 12 13
do
valgrind ./main.out 1 ./tests/comment_tests/test$var counting >> valgrind_log.info 2>&1
done
echo "Блок комментариев пройден"

for var in 1 2 3 4 5 6 7 8 9 10 11 12 13
do
valgrind ./main.out 1 ./tests/string_literal_tests/test$var counting >> valgrind_log.info 2>&1
done
echo "Блок строковых литералов пройден"

for var in 1 2 3 4 5 6 7 8 9 10 11 12 13
do
valgrind ./main.out 1 ./tests/char_const_tests/test$var counting >> valgrind_log.info 2>&1
done
echo "Блок символьных констант пройден"

for var in 1 2 3 4 5 6 7 8
do
valgrind ./main.out 1 ./tests/keyword_tests/test$var counting >> valgrind_log.info 2>&1
done
echo "Блок ключевых слов пройден"

for var in 1 2 3 4 5 6 7 8
do
valgrind ./main.out 1 ./tests/punctuator_tests/test$var counting >> valgrind_log.info 2>&1
done
echo "Блок пунктуаторов пройден"

valgrind  ./main.out >> valgrind_log.info 2>&1
echo "Проверка режима 0. Введите текст программы:"
valgrind  ./main.out 0 counting >> valgrind_log.info 2>&1 
echo "\nВвод закончен. Ожидайте завершения тестирования"
valgrind  ./main.out 1 >> valgrind_log.info 2>&1 
valgrind  ./main.out 2 >> valgrind_log.info 2>&1 
valgrind  ./main.out 1 ./tests/main_tests/test5 >> valgrind_log.info 2>&1 
valgrind  ./main.out 1 ./tests/main_tests/test6 >> valgrind_log.info 2>&1 
valgrind  ./main.out 1 ./tests/main_tests/test7 >> valgrind_log.info 2>&1
echo "Тестирование закончено. Отладочная информация записана в valgrind_log.info"
