

/*
 *
 * EIP - Instruction pointer
 * EBP - Base pointer
 * ESP - Stack pointer
 *
 *
 *                                                    |--------|
 *                                                    |  ESP   |<---- Current stack frame end
 *                                                    |--------|
 *                                                    |        |
 *                                                    |--------|
 *                                                    |        |
 *                                                    |--------|
 *                                                    |        |
 *                                                    |--------|
 *                                                    |        |
 *                                                    |--------|
 *        RIP - Return Intstruction Pointer           |        |
 *        FA  - Formal arguments                      |--------|
 *        LA  - Local arguments                       |  EBP   |<---- Current Stack frame base/start
 *                                                    |--------|
 *                                                    |  RIP   |
 *                                                    |--------|
 *                                                    |   FA   |<---- Previous stack frame end
 *                                                    |--------|
 *                                                    |   FA   |
 *                                                    |--------|
 *                                                    |   FA   |
 *                                                    |--------|
 *                                                    |        |
 *                                                    |        |
 *                                                    |        |
 *                                                    |--------|
 *                                                    |  LA    |
 *                                                    |--------|
 *                                                    |  LA    |
 *                                                    |--------|
 *                                                    |  EBP   |<---- (EBP) Previous Stack frame base/start
 *                                                    |--------|
 *
 *
 *
 *
 *    -----EXAMPLE-------
 *
 *
 *
 *     ESP  Offet from EBP is calculated based on the runtime useage  choosen by  complier
 *
 *                                                  |--------|
 *                                                  |        |<---- (ESP) stack frame end                                                                                  
 *                                                  |--------|
 *       int main()                                 |        |
 *       {                                          |--------|
 *            int a = 20;                           |        |
 *            inb b = 10;                           |--------|
 *            int c;              <--- EIP          |        |
 *            c = add( a,b);                        |        |
 *         }                                        |        |
 *                                                  |--------|
 *                                                  |  b(10) |
 *                                                  |--------|
 *                                                  |  a(20) |
 *                                                  |--------|
 *                                                  |  c     |
 *                                                  |--------|
 *                                                  |  0     |<---- (EBP) Stack frame base/start
 *                                                  |--------|
 *
 *
 *
 *
 *
 *      --------- Pushing argments to stack before calling funciton --------
 *
 *                                                  |--------|
 *                                                  |        |<---- (ESP) stack frame end                                                                                  
 *                                                  |--------|
 *       int main()                                 |   20   |
 *       {                                          |--------|            |
 *            int a = 20;                           |   10   |            |
 *            inb b = 10;                           |--------|            |  Args pushed downwards
 *            int c;                                |        |            \/
 *            c = add( a,b);     <---- EIP          |        |
 *         }                                        |        |
 *                                                  |--------|
 *                                                  |  b(10) |
 *                                                  |--------|
 *                                                  |  a(20) |
 *                                                  |--------|
 *                                                  |  c     |
 *                                                  |--------|
 *                                                  |  0     |<----(EBP) Stack frame base/start
 *                                                  |--------|
 *
 *
 *
 *
 *
 *
 *
 *        ------------Invoking the function call by cpu -------
 *
 *
 *                                                 |--------|
 *                                                 |        |
 *        int add(int x, int y)                    |--------|
 *        {                      ^                 |        |
 *            int z = 0;         |  Calling        |--------|
 *            z = x+y;           |  Function       |        |
 *            return z;          |                 |--------|
 *        }                      |                 |        |
 *                               |                 |--------|
 *                               |                 |        |
 *                               |                 |--------|
 *                               |                 |        |
 *                               |                 |--------|
 *                               |                 |        |
 *       int main()              |                 |--------|
 *       {                       |                 |        |<---- (ESP)Current stack frame end
 *            int a = 20;        |                 |--------|
 *            inb b = 10;        |                 |  RIP   |    (Push RIP - return Instruction pointer to current ESP by CPU)
 *            int c;             |                 |--------|
 *            c = add( a,b);  ----                 |   20   |
 *              ^                                  |--------|
 *              |                                  |   10   |
 *              |                                  |--------|
 *              |_ _ RIP (Return to this place)    |        |
 *                                                 |        |
 *                                                 |        |
 *                                                 |--------|
 *                                                 |  b(10) |
 *                                                 |--------|
 *                                                 |  a(20) |
 *                                                 |--------|
                                                   |  c     |
                                                   |--------|
 *                                                 |  0     |<---- (EBP) Current Stack frame base/start
 *                                                 |--------|
 *
 *
 *
 *
 *                    Stack frame construction
 *                                                 |--------|
 *                               EIP               | ESP    |<---  Current ESP
 *        int add(int x, int y)  <---              |--------|
 *        {                          |             |        |
 *            int z = 0;             |             |--------|
 *            z = x+y;               |             |        |
 *            return z;              |             |--------|
 *        }                          |             |        |
 *                                   |             |--------|
 *                                   |             |        |
 *                                   |             |--------|
 *                                   |             |        |
 *                                   |             |--------|
 *                                   |             |        |
 *       int main()                  |             |--------|
 *       {                           |             |  EBP   |<--- Current EBP |  Pushes the Prevous EBP address into Curent ESP
 *            int a = 20;            |             |--------|  Move EBP to current ESP and Move ESP to fixed offet above
 *            inb b = 10;            |             |  RIP   |
 *            int c;                 |             |--------|
 *            c = add( a,b);  -------              |   20   |<---- (ESP) Prevous stack frame end
 *              ^                                  |--------|
 *              |                                  |   10   |
 *              |                                  |--------|
 *              |_ _ RIP (Return to this place)    |        |
 *                                                 |        |
 *                                                 |--------|
                                                   |  c     |
 *                                                 |--------|
 *                                                 |  b(10) |
 *                                                 |--------|
 *                                                 |  a(20) |
 *                                                 |--------|
 *                                                 |  0     |<---- (EBP) Previous Stack frame base/start
 *                                                 |--------|
 *
 *
 *
 *
 *
 *
 *
 *
 *                    Stack Formal and local args contruction
 *
 *
 *        int add(int x, int y)                    |--------|
 *        {                   <--EIP-              |        |
 *            int z = 0;             |             |--------|
 *            z = x+y;               |             | ESP    |<---  Current ESP
 *            return z;              |             |--------|
 *        }                          |             |        |
 *                                   |             |--------|
 *                                   |             |        |
 *                                   |             |--------|
 *                                   |             |        |
 *                                   |             |--------|
 *                                   |             |  z(0)  |
 *       int main()                  |             |--------|
 *       {                           |             |  EBP   |<--- Current EBP
 *            int a = 20;            |             |--------|
 *            inb b = 10;            |             |  RIP   |
 *            int c;                 |             |--------|
 *            c = add( a,b);  -------              |  x(20) |<---- (ESP) Prevous stack frame end
 *              ^                                  |--------|
 *              |                                  |  y(10) |
 *              |                                  |--------|
 *              |_ _ RIP (Return to this place)    |        |
 *                                                 |        |
 *                                                 |        |
 *                                                 |--------|
                                                   |  c     |
 *                                                 |--------|
 *                                                 |  b(10) |
 *                                                 |--------|
 *                                                 |  a(20) |
 *                                                 |--------|
 *                                                 |  0     |<---- (EBP) Previous Stack frame base/start
 *                                                 |--------|
 *
 *
 *
 *
 *
 *          Store the return value in EAX register
 *
 *
 *
 *        int add(int x, int y)                    |--------|
 *        {                                        |        |
 *            int z = 0;                           |--------|
 *            z = x+y;                             | ESP    |<---  Current ESP
 *            return z;      <--EIP--              |--------|
 *        }                          |             |        |
 *                                   |             |--------|
 *                                   |             |        |
 *                     Store return  |             |--------|
 *                     value in EAX  |             |        |
 *                     register      |             |--------|
 *                                   |             |  z(0)  |
 *       int main()                  |             |--------|
 *       {                           |             |  EBP   |<--- Current EBP
 *            int a = 20;            |             |--------|
 *            inb b = 10;            |             |  RIP   |
 *            int c;                 |             |--------|
 *            c = add( a,b);  -------              |  x(20) |<---- (ESP) Prevous stack frame end
 *              ^                                  |--------|
 *              |                                  |  y(10) |
 *              |                                  |--------|
 *              |_ _ RIP (Return to this place)    |        |
 *                                                 |        |
 *                                                 |        |
 *                                                 |--------|
                                                   |  c     |
 *                                                 |--------|
 *                                                 |  b(10) |
 *                                                 |--------|
 *                                                 |  a(20) |
 *                                                 |--------|
 *                                                 |  0     |<---- (EBP) Previous Stack frame base/start
 *                                                 |--------|
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *         Restore the Stack pointer to previous location
 *
 *                                                 |--------|
 *                                                 |        |
 *        int add(int x, int y)                    |--------|
 *        {                                        |  z(0)  |
 *            int z = 0;                           |--------|
 *            z = x+y;                             |        |
 *            return z;                            |--------|
 *        }          <----EIP--------              |        |
 *                                   |             |--------|
 *                Retore ESP         |             |        |
 *                                   |             |--------|
 *                                   |             |        |
 *                                   |             |--------|
 *                                   |             |        |
 *       int main()                  |             |--------|
 *       {                           |             |  EBP   |<--- Current ESP
 *            int a = 20;            |             |--------|
 *            inb b = 10;            |             |  RIP   |
 *            int c;                 |             |--------|
 *            c = add( a,b);  -------              |  x(20) |<---- (ESP) Prevous stack frame end
 *              ^                                  |--------|
 *              |                                  |  y(10) |
 *              |                                  |--------|
 *              |_ _ RIP (Return to this place)    |        |
 *                                                 |        |
 *                                                 |--------|
                                                   |  c     |
 *                                                 |--------|
 *                                                 |  b(10) |
 *                                                 |--------|
 *                                                 |  a(20) |
 *                                                 |--------|
 *                                                 |  0     |<---- (EBP) Previous Stack frame base/start
 *                                                 |--------|
 *
 *
 *
 *
 *         Restore the Base pointer pointer to previous location and EIP return previous location
 *
 *                                                 |--------|
 *                                                 |        |
 *        int add(int x, int y)                    |--------|
 *        {                                        |  z(0)  |
 *            int z = 0;                           |--------|
 *            z = x+y;                             |        |
 *            return z;                            |--------|
 *        }                                        |        |
 *                                                 |--------|
 *                                                 |        |
 *                                                 |--------|
 *                                                 |        |
 *                                                 |--------|
 *                                                 |        |
 *       int main()                                |--------|
 *       {                                         |        |
 *            int a = 20;                          |--------|
 *            inb b = 10;                          |        |
 *            int c;                               |--------|
 *            c = add( a,b);                       |  x(20) |<---- (ESP) Current stack frame end
 *              ^                                  |--------|
 *              |                                  |  y(10) |
 *              |                                  |--------|
 *              |_ _ RIP (Return to this place)    |        |
 *                                                 |        |
 *                                                 |--------|
                                                   |  c     |
 *                                                 |--------|
 *                                                 |  b(10) |
 *                                                 |--------|
 *                                                 |  a(20) |
 *                                                 |--------|
 *                                                 |  0     |<---- (EBP) Current  Stack frame base/start
 *                                                 |--------|
 *
 *
 *
 *         Move the EAX to local variable
 *
 *                                                 |--------|
 *                                                 |        |
 *        int add(int x, int y)                    |--------|
 *        {                                        |  z(0)  |
 *            int z = 0;                           |--------|
 *            z = x+y;                             |        |
 *            return z;                            |--------|
 *        }                                        |        |
 *                                                 |--------|
 *                                                 |        |
 *                                                 |--------|
 *                                                 |        |
 *                                                 |--------|
 *                                                 |        |
 *       int main()                                |--------|
 *       {                                         |        |
 *            int a = 20;                          |--------|
 *            inb b = 10;                          |        |
 *            int c;                               |--------| <---- (ESP) Current stack frame end
 *                                                 |--------|
 *            c = add( a,b);                       |  x(20) |
 *              ^                                  |--------|
 *              |                                  |  y(10) |
 *              |                                  |--------|
 *              |_ _ RIP (Return to this place)    |        |
 *                                                 |        |
 *                                                 |        |
 *                                                 |--------|
                                                   |  c(EAX)|
 *                                                 |--------|
 *                                                 |  b(10) |
 *                                                 |--------|
 *                                                 |  a(20) |
 *                                                 |--------|
 *                                                 |  0     |<---- (EBP) Current  Stack frame base/start
 *                                                 |--------|
 *
 *
 *
 *
 */
/*
 int add(int x, int y)
 {
         int z = 0;
         z = x+y;
         return z;
 }






 int main()
 {
         int a = 20;
         inb b = 10;
         int c;
         c = add( a,b);
 }
*/


#include<stdio.h>
#include<execinfo.h>
#include<stdlib.h>


 void fun_stack()
 {
         register int ebp asm("ebp");
         int *frame = (int *)ebp;
         int stack[10];
         int i = 0;

         while(*frame)
         {
                 printf("EBP:0x%x RIP:0x%x \n", *frame, frame[1]);
                 stack[i] = frame[1];
                 frame  = *frame;
                 i++;
         }

         /*add(a, b);*/
         /*RIP*/
         backtrace_symbols_fd(stack, i, 0);

         //
         //
         //
 }

 void fun_inner()
 {
         fun_stack();
 }

 void fun_outer()
 {
         int a;
         a=30;
         fun_inner();
 }

 int main(int argc, char *argv[])
 {
         fun_outer();
 }
