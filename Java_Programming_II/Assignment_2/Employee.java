public class Employee
{
   int id;
   String name;
   
   public Employee(int id, String name)
   {
      this.id = id;
      this.name = name;
   }
   
   public String toString()
   {
      return "Employee Name: " + name + "\nEmployee ID: " + id;
   }
}