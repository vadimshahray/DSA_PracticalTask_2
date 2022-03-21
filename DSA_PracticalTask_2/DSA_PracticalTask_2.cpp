#include <conio.h>
#include <stdio.h>
#include <locale.h>

enum ACTION
{
   PUSH,       // Добавить элемент в очередь
   POP,        // Вытолкнуть элемент из очереди
   CLEAR,      // Очистить очередь
   PRINT,      // Вывести содержимое очереди на консоль
   IS_EMPTY,   // Проверить, пуста ли очередь
   EXIT        // Завершение работы программы
};

struct list
{
   list(int _elem = 0, list *_next = NULL, list *_prev = NULL)
      : elem(_elem), next(_next), prev(_prev)
   {}

   int elem;
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
   void push(int e)
   {
      l->prev = is_empty() ? l->next = l = new list(e)
         : l->prev->next = new list(e, l, l->prev);
   }
   /// <summary>
   /// Выталкивает первый элемент очереди и передает его в e.
   /// </summary>
   /// <param name="e">Переменная, в которую нужно передать вытолкнутый элемент очере-ди.</param>
   /// <returns>true - операцию удалось выполнить, false - операция не выполне-на.</returns>
   bool pop(int &e)
   {
      bool is_e = is_empty();

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
   bool is_empty() { return !l; }

   /// <summary>
   /// Очищает очередь от элементов.
   /// </summary>
   void clear() { for (int e = 0; pop(e); ); }

   /// <summary>
   /// Выводит содержимое очереди.
   /// </summary>
   void print()
   {
      queue q;
      int e = 0;

      for (; pop(e); q.push(e)) printf_s("%d\n", e);
      for (; q.pop(e); push(e));
   }
};

int main()
{
   setlocale(0, "");

   queue Q;
   int a = 0, elem = 0;
   bool is_repeat = true;

   do
   {
      printf_s("Выберите действие:\nДобавить элемент в очередь [%d]\tВытолкнуть элемент из очереди[%d]\tОчистить очередь [%d]\tВывести содержимое очереди [%d]\tПроверить, пуста ли очередь [%d]\tЗавершить работу [%d]\nДействие: ", PUSH, POP, CLEAR, PRINT, IS_EMPTY, EXIT);
      scanf_s("%d", &a);
      printf_s("\n");

      switch (a)
      {
      case PUSH:
         printf_s("Введите элемент: ");
         scanf_s("%d", &elem);

         Q.push(elem);
         printf_s("Элемент успешно добавлен."); break;
      case POP:
         Q.pop(elem) ? printf_s("Взятый элемент: %d.", elem) : printf_s("Не удалось взять элемент: очередь пуста."); break;
      case CLEAR:
         Q.clear();
         printf_s("Очередь очищена."); break;
      case PRINT:
         printf_s("Содержимое очереди:\n");
         Q.print(); break;
      case IS_EMPTY:
         printf_s(Q.is_empty() ? "Очередь пуста." : "Очередь не пуста."); break;
      case EXIT:
         is_repeat = false; break;
      default: break;
      }

      printf_s("\n\n");
   } while (is_repeat);

   return 0 * _getch();
}