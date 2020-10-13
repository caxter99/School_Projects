import java.util.*;

public class EmployeeMap
{
   Map<Integer, Employee> employeeMap;
   
   public EmployeeMap()
   {
      employeeMap = new HashMap<Integer, Employee>();
   }
   
   public void addEmployee(Employee employee)
   {
      employeeMap.put(employee.id, employee);
   }
   
   public Employee getEmployeeFromIdNumber(int id)
   {
      return employeeMap.get(id);
   }
   
   public String toString()
   {
      String mapString = "Displaying all employees in the map nicely:\n";
      for (Map.Entry<Integer, Employee> mapElement : employeeMap.entrySet())
      {
         mapString += "ID: " + mapElement.getKey() + ", Name: " + mapElement.getValue().name + "\n";
      } 
      return mapString;
   }
}