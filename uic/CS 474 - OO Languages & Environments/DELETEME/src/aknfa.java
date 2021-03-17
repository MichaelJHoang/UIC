import java.util.*;

public class aknfa{

    interface t1 {
        void f() throws CloneNotSupportedException;
    }
    interface t2 {
        void f() throws CloneNotSupportedException;
    }
    interface t3 extends t1, t2{}

    public static class e implements t3 {
        public e f = new e();
        public void f() { System.out.println("eeeee");}
        public static void main (String[] args) throws CloneNotSupportedException {
            t3 nnn = new e();
            nnn.f();
        }
    }
}