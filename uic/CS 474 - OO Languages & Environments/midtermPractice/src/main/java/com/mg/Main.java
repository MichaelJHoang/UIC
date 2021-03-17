package com.mg;

interface MCall
{
    default int f1()
    {
        return 2;
    }
}

public class Main implements MCall {
    int fvar = 0;

    public int f() {
        return fvar = 1;
    }

    interface MCall {
        default int f() {
            return 2;
        }
    }

    public static class Nested extends Main implements MCall
    {
        int fvar = 3;

        public int f()
        {
            return fvar;
        }
    }

    public static void main(String [] args)
    {
        com.mg.MCall call4 = new Main();

        System.out.println((((Main) call4).f()));
    }
}