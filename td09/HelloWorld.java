
//package td09;
import java.util.Scanner;

public class HelloWorld {
    public static native void printCpp(); // Déclaration prototype méthode native

    public static native void printStringToCpp(String s);

    public native String stringFromCpp();

    public native void callJavaMethod();

    public static void test(String s) {
        System.out.println(s);
    }

    public native String toString();

    public static native int fibonnaci(int entier);

    static {
        System.loadLibrary("HelloWorld"); // Chargement de la bibliothèque
    }

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        sc.nextLine();

        sc.close();
        HelloWorld hello = new HelloWorld();
        System.out.print("Hello "); // Affiche Hello en Java
        HelloWorld.printCpp(); // Affiche World en C/C++
        HelloWorld.printStringToCpp("Test string to cpp");
        System.out.println(hello.stringFromCpp());
        hello.callJavaMethod();
        System.out.println(hello.toString());




        System.out.println(fibonnaci(6));

    }

}