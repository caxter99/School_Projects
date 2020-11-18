public class ExtraOptions
{
   boolean hasInsurance;
   boolean hasHotspot;
   final double INSURANCE_COST_PER_MONTH = 5;
   final double HOTSPOT_COST_PER_MONTH = 10;
   
   public ExtraOptions()
   {
      hasInsurance = false;
      hasHotspot = false;
   }
   
   public void setHasInsurance(boolean insurance)
   {
      hasInsurance = insurance;
   }
   
   public void setHasHotspot(boolean hotspot)
   {
      hasHotspot = hotspot;
   }
   
   public double getCost()
   {
      double cost = 0;
      
      if (hasInsurance)
      {
         cost += INSURANCE_COST_PER_MONTH;
      }
      if (hasHotspot)
      {
         cost += HOTSPOT_COST_PER_MONTH;
      }
      
      return cost;
   }
}