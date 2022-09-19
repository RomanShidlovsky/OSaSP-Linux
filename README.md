# OSaSP 
Lab1
-----
clargs<br/>
 Написать скрипт, выводящий на консоль и в файл все аргументы командной строки. Выводить одной строкой с пробелами между аргументами.

Srch<br/>
 Написать скрипт, выводящий в файл (имя файла задаётся пользователем в качестве первого аргумента командной строки) имена всех файлов с заданным расширением (третий аргумент командной строки) из заданного каталога (имя каталога задаётся пользователем в качестве второго аргумента  командной строки). Если не хватает параметров, то вывести подсказку с описанием количества параметров и их значения. Если количество параметров верное, но они не валидные, то вывести сообщение об ошибке в поток ошибок (поток номер 2). Имя каждого файла должно печататься с новой строки. Имена файлов должны быть отсортированы в алфавитном порядке.
comp : Написать скрипт, компилирующий и запускающий программу (имя исходного файла и exe- файла результата задаётся пользователем в качестве аргументов командной строки). В случае ошибок при компиляции вывести на консоль сообщение об ошибках и не запускать программу на выполнение.

ex2<br/>
Написать скрипт с использованием цикла for, выводящий на консоль относительные пути к файлам, размеры и права доступа для всех файлов   в заданном каталоге и всех его подкаталогах (имя каталога задается пользователем в качестве первого аргумента командной строки). На консоль выводится общее число просмотренных файлов.

ee<br/>
ex2 в одну строчку

Lab2
-----
task02.c<br/>
Написать программу вывода сообщения на экран. 

task03.c<br/>
Написать программу ввода символов с клавиатуры и записи их в файл (в качестве аргумента при запуске программы вводится имя файла). Для чтения или записи файла использовать только функции посимвольного ввода-вывода getc(),putc(), fgetc(),fputc(). Предусмотреть выход после ввода определённого символа (например: ctrl-F). Предусмотреть контроль ошибок открытия/закрытия/чтения файла.

task04.c<br/>
Написать программу вывода содержимого текстового файла на экран (в качестве аргумента при запуске программы передаётся имя файла, второй аргумент (N) устанавливает вывод по группам строк (по N –строк) или сплошным текстом (N=0)). Для  вывода  очередной группы строк необходимо ожидать нажатия пользователем любой клавиши. Для чтения или записи файла использовать только функции посимвольного ввода-вывода getc(),putc(), fgetc(),fputc(). Предусмотреть контроль ошибок открытия/закрытия/чтения/записи файла.

task05.c<br/>
Написать программу копирования одного файла в другой. В качестве параметров при вызове программы передаются имена первого и второго файлов. Для чтения или записи файла использовать только функции посимвольного ввода-вывода getc(),putc(), fgetc(),fputc(). Предусмотреть копирование  прав доступа к файлу и контроль ошибок открытия/закрытия/чтения/записи файла.

task06.c<br/>
Написать программу вывода на экран содержимого текущего и корневого каталогов. Предусмотреть контроль ошибок открытия/закрытия/чтения каталога.

task_main_var6.c<br/>
Написать программу, находящую в заданном каталоге и всех его подкаталогах все файлы, заданного размера. Имя каталога задаётся пользователем в качестве первого аргумента командной строки. Диапазон (min.- мах.) размеров файлов задаётся пользователем в качестве второго и третьего аргументов командной строки. Программа выводит результаты поиска в файл (четвертый аргумент командной строки) в виде полный путь, имя файла, его размер.  На консоль выводится общее число просмотренных файлов.

Lab3
-----
task_01.c<br/>
2.	Написать программу, создающую два дочерних процесса с использованием двух вызовов fork(). Родительский и два дочерних процесса должны выводить на экран свой pid и pid родительского процесса и текущее время в формате: часы: минуты: секунды: миллисекунды. Используя вызов system (), выполнить команду ps -x в родительском процессе. Найти свои процессы в списке запущенных процессов. 

ind_task_2.c, filecopy</br>
Написать программу синхронизации двух каталогов, например, Dir1 и Dir2. Пользователь задаёт имена Dir1 и Dir2. В результате работы программы файлы, имеющиеся в Dir1, но отсутствующие в Dir2, должны скопироваться в Dir2 вместе с правами доступа. Процедуры копирования должны запускаться в отдельном процессе для каждого копируемого файла. Каждый процесс выводит на экран свой pid, полный путь к копируемому файлу и число скопированных байт. Число одновременно работающих процессов не должно превышать N (вводится пользователем). Скопировать несколько файлов из каталога /etc в свой домашний каталог. Проверить работу программы для каталога /etc и домашнего каталога.
