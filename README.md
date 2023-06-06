# Calculator
- Stack `C` `Qt6`


## Description
Калькулятор с возможностью построения графиков функций. Для вычисления выражения используются два стека, которые определяют порядок операций находящихся в выражении.


- График функции `sin(x)*x`
<img src="images/readme1.png" title="График функции `sin(x)*x`" width="80%" height="80%" />


- График функции `(x/2-1)^3+2`
<img src="images/readme4.png" title="График функции `(x/2-1)^3+2`" width="80%" height="80%" />


- Вычисление значения выражения `ln(arccos(0))`
<img src="images/readme2.png" title="Вычисление значения выражения `ln(arccos(0))`" width="80%" height="80%" />


- Вычисление начения выражения `9^3 + 5%8`
<img src="images/readme3.png" title="Вычисление начения выражения `9^3 + 5%8`" width="80%" height="80%" />

## to run

- запустить тесты
```
make -f Makefile2 tests
```
- получить отсчёт о тестах в виде html-страницы
```
make -f Makefile2 gcov_report
```
- установить приложение калькулятора
```
make -f Makefile2 install
```
- запустить приложение калькулятора
```
make -f Makefile2 run
```
- удалить все созданные файлы
```
make -f Makefile2 clean
```


