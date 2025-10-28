import java.io.FileWriter;
import java.io.FileReader;
import java.io.IOException;

public class FileHandlingDemo {
    public static void main(String[] args) {
        String data = "Java File Handling Example\nThis text is written to a file.";

        try {
            FileWriter writer = new FileWriter("example.txt");
            writer.write(data);
            writer.close();
            System.out.println("Data written to file successfully.");
        } catch (IOException e) {
            System.out.println("An error occurred while writing to file: " + e);
        }

        try {
            FileReader reader = new FileReader("example.txt");
            int i;
            System.out.println("\nReading data from file:");
            while ((i = reader.read()) != -1) {
                System.out.print((char) i);
            }
            reader.close();
        } catch (IOException e) {
            System.out.println("An error occurred while reading the file: " + e);
        }
    }
}
