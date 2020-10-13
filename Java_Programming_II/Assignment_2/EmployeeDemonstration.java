import java.io.*;

public class EmployeeDemonstration
{
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
   }
}