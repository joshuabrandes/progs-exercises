namespace Aufgabe9
{
    struct A
    {
        public string str;
        public short s;
    }

    struct B
    {
        public int a;
        public bool b;
        public A c;
    }

    class Program
    {
        public static void foo()
        {
            int i = 2;
            double j = 1.0;

            B k;
            k.a = 1;
            k.b = true;
            k.c.str = "Hi";
            k.c.s = 255;

            B[] l = new B[3];
            l[0] = k;
            l[1] = l[0];
            l[2] = l[1];
            /* a) */
        }

        public static void Main(string[] args)
        {
            foo();
        }
    }
}