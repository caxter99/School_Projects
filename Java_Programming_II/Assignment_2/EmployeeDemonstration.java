import java.util.Scanner;
import java.io.*;

public class EmployeeDemonstration
{
   //private static boolean isAnInteger
   
   private static int getIdFromUser()
   {
      Scanner scan = new Scanner(System.in);
      boolean validInput = false;
      int input = 0;
      while(!validInput)
      {
         try
         {
            System.out.print("Enter an integer: ");
            input = scan.nextInt();
            validInput = true;
         }
         catch (Exception e)
         {
            System.out.println("\nThat was not valid input.");
            String s = scan.next();
         }
      }
      
      return input;
   }
   
   public static void main(String[] args)
   {
      EmployeeMap employeeMap = new EmployeeMap();
      employeeMap.addEmployee(new Employee(1, "Devin"));
      employeeMap.addEmployee(new Employee(2, "James"));
      employeeMap.addEmployee(new Employee(3, "Jordan"));
      employeeMap.addEmployee(new Employee(4, "Alexander"));
      employeeMap.addEmployee(new Employee(5, "Brandon"));
      employeeMap.addEmployee(new Employee(6, "Lee"));
      System.out.println(employeeMap);
      System.out.println(employeeMap.getEmployeeFromIdNumber(getIdFromUser()));
   }
}