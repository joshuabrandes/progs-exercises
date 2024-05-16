using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IntStack
{
    class IntStack
    {
        public class IntStackItem
        {
            public int value;
            public IntStackItem next;
            public IntStackItem prev;
        }

        public delegate void StackOperation(ref int v);

        private IntStackItem sp = null;

        private IntStackItem newItem(int value)
        {
            IntStackItem item = new IntStackItem();
            item.value = value;
            item.next = null;
            item.prev = null;
            return item;
        }

        public bool isEmpty()
        {
            return sp == null;
        }

        public void push(int value)
        {
            IntStackItem item = newItem(value);
            if (sp == null)
            {
                // first item
                sp = item;
            }
            else
            {
                // append at sp
                sp.next = item;
                item.prev = sp;
                sp = item;
            }
        }

        public int pop()
        {
            if (isEmpty())
                throw new System.Exception("Stack is empty!");

            IntStackItem itemToRemove = sp;
            sp = sp.prev;
            if (sp != null)
                sp.next = null;

            return itemToRemove.value;
        }

        public void traverse(StackOperation op)
        {
            if (isEmpty())
                return;

            for (IntStackItem curr = sp; curr != null; curr = curr.prev)
            {
                op(ref curr.value);
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            IntStack stack = new IntStack();

            stack.push(1);
            stack.push(2);
            stack.push(3);
            stack.push(4);
            stack.push(5);
            stack.pop();
            stack.push(6);

            IntStack.StackOperation op = (ref int x) => { x = x * 2; };
            stack.traverse(op);

            // (1)
            while (!stack.isEmpty())
            {
                Console.WriteLine("Popping value from the stack: {0}", stack.pop());
            }

            Console.ReadKey();
        }
    }
}