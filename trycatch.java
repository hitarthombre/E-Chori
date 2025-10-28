public class TryCatchFinallyDemo {
    public static void main(String[] args) {
        int[] numbers = {10, 20, 30};
        int result = 0;

        try {
            System.out.println("Accessing array element...");
            result = numbers[3]; // This will throw ArrayIndexOutOfBoundsException
            System.out.println("This line will not execute.");
        } 
        catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Exception caught: " + e);
        } 
        finally {
            System.out.println("Finally block executed (always runs).");
        }

        System.out.println("Program continues normally...");
    }
}
