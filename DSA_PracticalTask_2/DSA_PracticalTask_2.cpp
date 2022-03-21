#include <conio.h>
#include <stdio.h>
#include <windows.h>

enum COMMAND
{
   PUSH  = '0',   // Добавить элемент в очередь
   POP   = '1',   // Вытолкнуть элемент из очереди
   CLEAR = '2',   // Очистить очередь
   PRINT = '3',   // Вывести содержимое очереди на консоль
   EMPTY = '4',   // Проверить, пуста ли очередь
   EXIT  = '5'    // Завершение работы программы
};

struct list
{
   list(char _elem = 0, list *_next = NULL, list *_prev = NULL)
      : elem(_elem), next(_next), prev(_prev) { }

   char elem;
   list *next, *prev;
};

struct queue
{
   private:
   list *l = NULL;

   public:
   /// <summary>
   /// Добавляет элемент в конец очереди.
   /// </summary>
   /// <param name="e">Значение элемента, который нужно добавить в очередь.</param>
   void push(char e)
   {
      l->prev = empty() ? l->next = l = new list(e) 
                           : l->prev->next = new list(e, l, l->prev);
   }
   /// <summary>
   /// Выталкивает первый элемент очереди и передает его в e.
   /// </summary>
   /// <param name="e">Переменная, в которую нужно передать вытолкнутый элемент очереди.</param>
   /// <returns>true - операцию удалось выполнить, false - операция не выполнена.</returns>
   bool pop(char &e)
   {
      bool is_e = empty();

      if (!is_e)
      {
         list *d = l;
         e = d->elem;

         if (l->next == l) l = NULL;
         else
         {
            l = l->next;

            d->prev->next = l;
            l->prev = d->prev;
         }

         delete d;
      }

      return !is_e;
   }

   /// <summary>
   /// Проверяет, пуста ли очередь.
   /// </summary>
   /// <returns>true - пуста, false - не пуста.</returns>
   bool empty() { return !l; }

   /// <summary>
   /// Очищает очередь от элементов.
   /// </summary>
   void clear() { for (char e = 0; pop(e); ); }

   /// <summary>
   /// Выводит содержимое очереди.
   /// </summary>
   void prchar()
   {
      queue q;
      char e = 0;

      for ( ; pop(e); q.push(e)) printf_s("%c\n", e);
      for ( ; q.pop(e); push(e));
   }
};

int main()
{
   UINT inCp = GetConsoleCP(), outCp = GetConsoleOutputCP();
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);


   queue Q;
   bool is_repeat = true;
   do
   {
      char cmd = 0, elem = 0;
      printf_s("Выберите действие:\nДобавить элемент в очередь [%c]\nВытолкнуть элемент из очереди[%c]\nОчистить очередь [%c]\nВывести содержимое очереди [%c]\nПроверить, пуста ли очередь [%c]\nЗавершить работу [%c]\nДействие: ", PUSH, POP, CLEAR, PRINT, EMPTY, EXIT);
      scanf_s("\n%c", &cmd, 1);
      printf_s("\n");
      
      switch (cmd)
      {
         case PUSH:
            printf_s("Введите элемент: ");
            scanf_s("\n%c", &elem, 1);

            Q.push(elem);
            printf_s("Элемент успешно добавлен."); break;
         case POP:
            Q.pop(elem) ? printf_s("Взятый элемент: %c.", elem) : printf_s("Не удалось взять элемент: очередь пуста."); break;
         case CLEAR:
            Q.clear();
            printf_s("Очередь очищена."); break;
         case PRINT:
            printf_s("Содержимое очереди:\n");
            Q.prchar(); break;
         case EMPTY:
            printf_s(Q.empty() ? "Очередь пуста." : "Очередь не пуста."); break;
         case EXIT:
            is_repeat = false; break;
         default: break;
      }
      
      printf_s("\n\n");
   } while(is_repeat);

   SetConsoleCP(inCp);
   SetConsoleOutputCP(outCp);

   return 0 * _getch();
}